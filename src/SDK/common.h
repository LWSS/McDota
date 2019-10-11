#pragma once
#include <cstring>
#include <vector>
#include "ConMsg.h"


struct InterfaceMetaData
{
	const char* name;
	uint32_t numVMs;
	void* interface;
};

inline std::vector<InterfaceMetaData> requestedInterfaces = {}; // requested but failed
inline std::vector<InterfaceMetaData> grabbedInterfaces = {}; // grabbed and can be used

typedef void* (*InstantiateInterfaceFn) ();

struct InterfaceReg
{
	InstantiateInterfaceFn m_CreateFn;
	const char *m_pName;
	InterfaceReg *m_pNext;
};

inline void**& getvtable(void* inst, size_t offset = 0)
{
	return *reinterpret_cast<void***>((size_t)inst + offset);
}

template< typename Fn >
inline Fn getvfunc( void* inst, size_t index, size_t offset = 0 ) {
	return reinterpret_cast<Fn>(getvtable( inst, offset )[index]);
}

template <typename interface>
interface* GetInterface(const char* filename, const char* version, uint32_t expectedVMs = 0)
{
	InterfaceMetaData data = {};
	data.name = version;
	data.numVMs = expectedVMs;

	void* library = dlopen(filename, RTLD_NOLOAD | RTLD_NOW | RTLD_LOCAL);

	if ( !library ){
		ConMsg( "%s: Could not open library: %s\n", __func__, filename );
		requestedInterfaces.push_back(data);
		return NULL;
	}

	void* createInterfaceSym = dlsym( library, "CreateInterface" );

	if ( !createInterfaceSym ) {
		dlclose(library);
		ConMsg( "%s: Could not find \"CreateInterface\" for library: %s\n", __func__, filename );
		requestedInterfaces.push_back(data);
		return NULL;
	}

	uintptr_t jump_instruction_addr = uintptr_t(createInterfaceSym) + 5;
	int32_t jump_displacement = *reinterpret_cast<int32_t*>(jump_instruction_addr + 1);
	uintptr_t createinterfaceinternal_addr = (jump_instruction_addr + 5) + jump_displacement;

	uintptr_t interface_list = createinterfaceinternal_addr;
	interface_list += *reinterpret_cast<int32_t*>(createinterfaceinternal_addr + 19); // relative offset to list
	interface_list += 23; // RIP after the address.

	dlclose(library);

	if( !interface_list ){
		ConMsg( "%s: Could not grab InterfaceList for library: %s\n", __func__,  filename );
		requestedInterfaces.push_back(data);
		return NULL;
	}

    for ( InterfaceReg *cur_interface = *reinterpret_cast<InterfaceReg**>(interface_list); cur_interface; cur_interface = cur_interface->m_pNext ){
		if ( strcmp( cur_interface->m_pName, version ) != 0 )
			continue;

		data.interface = cur_interface->m_CreateFn();
		grabbedInterfaces.push_back(data);
		return reinterpret_cast<interface*>(cur_interface->m_CreateFn());
    }

    ConMsg( "%s: Could not find Interface Named: %s in library %s\n", __func__, version, filename );
	requestedInterfaces.push_back(data);
	return NULL;
}

inline uintptr_t GetAbsoluteAddress(uintptr_t instruction_ptr, int offset, int size)
{
	return instruction_ptr + *reinterpret_cast<int32_t*>(instruction_ptr + offset) + size;
}

template <typename T>
T GetSymbolAddress(const char* filename, const char* symbol)
{
	void* handle = dlopen(filename, RTLD_NOW | RTLD_LOCAL);
	T result = reinterpret_cast<T>(dlsym(handle, symbol));
	dlclose(handle);

	return result;
}