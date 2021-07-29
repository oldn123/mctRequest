#pragma once


#include <Windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include "zlib.h"
#pragma comment(lib, "zlib")



/*Ω‚—π*/
inline int httpgzdecompress(Byte* zdata, uLong nzdata, Byte* data, uLong* ndata)
{
    int err = 0;
    z_stream d_stream = { 0 }; /* decompression stream */
    unsigned char dummy_head[2] = { 0x1F, 0x8B };
    d_stream.zalloc = (alloc_func)0;
    d_stream.zfree = (free_func)0;
    d_stream.opaque = (voidpf)0;
    d_stream.next_in = zdata;
    d_stream.avail_in = 0;
    d_stream.next_out = data;
    //if (inflateInit2(&d_stream, -MAX_WBITS) != Z_OK) return -1;
    if (inflateInit2(&d_stream, 47) != Z_OK) return -1;
    while (d_stream.total_in < nzdata) {
        d_stream.avail_in = d_stream.avail_out = 2048; /* force small buffers */
        if ((err = inflate(&d_stream, Z_NO_FLUSH)) == Z_STREAM_END) break;
        if (err != Z_OK)
        {
            if (err == Z_DATA_ERROR)
            {
                d_stream.next_in = (Bytef*)dummy_head;
                d_stream.avail_in = sizeof(dummy_head);
                if ((err = inflate(&d_stream, Z_NO_FLUSH)) != Z_OK)
                {
                    return -1;
                }
            }
            else return -1;
        }
    }
    *ndata = d_stream.total_out;
    if (inflateEnd(&d_stream) != Z_OK) return -1;

    return 0;

}

inline std::string NewGuidString()
{
    GUID guid;
    HRESULT h = CoCreateGuid(&guid);

    char buf[64] = { 0 };
    sprintf_s(buf, sizeof(buf),
        "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
        guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
        guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
    return std::string(buf);
}

inline std::vector<std::string> __split_string(std::string text, char const delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(text.data());
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}


inline std::string _FindMidString(const std::string& sResponse, const char* sBegin, const char* sEnd) {
    std::string sss = sBegin;
    auto fd = sResponse.find(sss);
    if (fd != sResponse.npos)
    {
        fd += sss.size();
        auto fd2 = sResponse.find(sEnd, fd);
        if (fd2 != sResponse.npos)
        {
            return sResponse.substr(fd, fd2 - fd);
        }
    }
    return "";
}

inline void __appendCookieItem(std::stringstream& ss, const char* sKey, const std::map<std::string, std::string>& infoMap) {
    auto fd = infoMap.find(sKey);
    if (fd != infoMap.end())
    {
        ss << (ss.str().empty() ? "" : ";") << fd->first << "=" << fd->second;
        //ss << ";" << fd->first << "=" << fd->second;
    }
}

inline void __fillCookieItems(std::stringstream& ss,  const std::map<std::string, std::string>& infoMap) {
    for (auto & item : infoMap)
    {
        std::string skey = ";";
        skey += item.first;
        skey += "=";

        if (ss.str().find(skey) == std::string::npos)
        {
            __appendCookieItem(ss, item.first.c_str(), infoMap);
        }
    }
}