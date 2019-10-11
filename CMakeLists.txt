cmake_minimum_required(VERSION 2.8)
project(McDota)
include(FindProtobuf)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.1)
		message(FATAL_ERROR "Your GCC seems outdated. ( Requires >=7.1 for C++17 support )")
	endif()
else()
	message(FATAL_ERROR "You must have GCC >= 7.1 installed in order to compile")
endif()

FUNCTION (EXCLUDE_FILES_FROM_DIR_IN_LIST _InFileList _excludeDirName _verbose)
	foreach (ITR ${_InFileList})
		if ("${_verbose}")
			message(STATUS "ITR=${ITR}")
		endif ("${_verbose}")

		if ("${ITR}" MATCHES "(.*)${_excludeDirName}(.*)") # Check if the item matches the directory name in _excludeDirName
			message(STATUS "Remove Item from List:${ITR}")
			list (REMOVE_ITEM _InFileList ${ITR}) # Remove the item from the list
		endif ("${ITR}" MATCHES "(.*)${_excludeDirName}(.*)")

	endforeach(ITR)
	set(SOURCE_FILES ${_InFileList} PARENT_SCOPE) # Return the SOURCE_FILES variable to the calling parent
ENDFUNCTION (EXCLUDE_FILES_FROM_DIR_IN_LIST)

find_package(Protobuf REQUIRED)

#no-pmf-conversions warning for deducing vtable offsets from our class prototypes sdk
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3 -ggdb -std=c++17 -Wall -Wextra -Wformat -Wno-unused-parameter -Wno-implicit-fallthrough --no-gnu-unique -Wno-pmf-conversions")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -std=c++17 -Wall -Wextra -Wformat -Wno-unused-parameter -Wno-implicit-fallthrough --no-gnu-unique -Wno-pmf-conversions -s -fvisibility=hidden -fvisibility-inlines-hidden")
#set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -std=c++17 -Wall -Wno-maybe-uninitialized -Wno-unused-result -ldl -fpic -shared")

# Depending on system/updates, you may need to statically link libstdc++
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")# -static-libstdc++")

if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type selected, default to Release")
	set(CMAKE_BUILD_TYPE RELEASE)
endif(NOT CMAKE_BUILD_TYPE)

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp"
		"${CMAKE_SOURCE_DIR}/src/Utils/subhook/subhook.c")
EXCLUDE_FILES_FROM_DIR_IN_LIST("${SOURCE_FILES}" "${CMAKE_SOURCE_DIR}/src/Utils/subhook/tests" FALSE)

include_directories(${INCLUDE_DIRS} ${PROTOBUF_INCLUDE_DIR})

add_library(McDota SHARED ${SOURCE_FILES})
target_link_libraries(McDota dl pthread ${PROTOBUF_LIBRARY})
