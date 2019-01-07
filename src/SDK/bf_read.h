#pragma once

/* originally from: https://www.unknowncheats.me/forum/counterstrike-global-offensive/223748-dispatchusermessage-reader.html */
class bf_read
{
public:
    uintptr_t base_address;
    uintptr_t cur_offset;

    bf_read(uintptr_t addr)
    {
        base_address = addr;
        cur_offset = 0;
    }

    void SetOffset(uintptr_t offset)
    {
        cur_offset = offset;
    }

    void Skip(uintptr_t length)
    {
        cur_offset += length;
    }

    int ReadByte()
    {
        auto val = *reinterpret_cast<char*>(base_address + cur_offset);
        ++cur_offset;
        return val;
    }

    int ReadInt()
    {
        auto val = *reinterpret_cast<char*>(base_address + cur_offset);
        cur_offset += sizeof(int);
        return val;
    }

    int64_t ReadLong()
    {
        auto val = *reinterpret_cast<int64_t*>(base_address + cur_offset);
        cur_offset += sizeof(int64_t);
        return val;
    }

    uint64_t ReadULong()
    {
        auto val = *reinterpret_cast<uint64_t*>(base_address + cur_offset);
        cur_offset += sizeof(uint64_t);
        return val;
    }

    bool ReadBool()
    {
        auto val = *reinterpret_cast<bool*>(base_address + cur_offset);
        ++cur_offset;
        return val;
    }

    std::string ReadString()
    {
        char buffer[256];
        auto str_length = *reinterpret_cast<char*>(base_address + cur_offset);
        ++cur_offset;
        memcpy(buffer, reinterpret_cast<void*>(base_address + cur_offset), str_length > 255 ? 255 : str_length);
        buffer[str_length > 255 ? 255 : str_length] = '\0';
        cur_offset += str_length + 1;
        return std::string(buffer);
    }
};