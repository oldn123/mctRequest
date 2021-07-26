#include "stdafx.h"
#include "UrlConvert.h"

byte toHex(const byte& x)
{
    return x > 9 ? x - 10 + 'A' : x + '0';
}

byte fromHex(const byte& x)
{
    return isdigit(x) ? x - '0' : x - 'A' + 10;
}

CUrlConvert::CUrlConvert(void)
{
}


CUrlConvert::~CUrlConvert(void)
{
}

// URL解码，解码为GBK
std::string CUrlConvert::URLDecode(std::string& strOrg)
{
    std::string sOut;
    for (size_t ix = 0; ix < strOrg.size(); ix++)
    {
        byte ch = 0;
        if (strOrg[ix] == '%')
        {
            ch = (fromHex(strOrg[ix + 1]) << 4);
            ch |= fromHex(strOrg[ix + 2]);
            ix += 2;
        }
        else if (strOrg[ix] == '+')
        {
            ch = ' ';
        }
        else
        {
            ch = strOrg[ix];
        }
        sOut += (char)ch;
    }
    return sOut;
}

// URL编码，编码为GBK
std::string CUrlConvert::URLEncode(std::string& strOrg)
{
    std::string sOut;
    for (size_t ix = 0; ix < strOrg.size(); ix++)
    {
        byte buf[4];
        memset(buf, 0, 4);
        if (isalnum((byte)strOrg[ix]))
        {
            buf[0] = strOrg[ix];
        }
        //else if ( isspace( (byte)strOrg[ix] ) ) //貌似把空格编码成%20或者+都可以  
        //{  
        //    buf[0] = '+';  
        //}  
        else
        {
            buf[0] = '%';
            buf[1] = toHex((byte)strOrg[ix] >> 4);
            buf[2] = toHex((byte)strOrg[ix] % 16);
        }
        sOut += (char*)buf;
    }
    return sOut;
}

std::string CUrlConvert::GBKToUTF8(const std::string& strGBK)
{
    std::string strOutUTF8 = "";
    int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
    wchar_t* str1 = new wchar_t[n];
    MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
    n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
    char* str2 = new char[n];
    WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
    strOutUTF8 = str2;
    delete[] str1;
    delete[] str2;
    return strOutUTF8;
}

std::string CUrlConvert::UTF8ToGBK(const std::string& strUTF8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
    wchar_t* wszGBK = new wchar_t[len + 1];
    memset(wszGBK, 0, (len + 1) * sizeof(WCHAR));
    MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUTF8.c_str(), -1, wszGBK, len);
    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
    char* szGBK = new char[len + 1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
    //strUTF8 = szGBK;
    std::string strTemp(szGBK);
    delete[] szGBK;
    delete[] wszGBK;
    return strTemp;
}

// URL编码，编码为GBK
std::string CUrlConvert::UrlEncode_GBK(std::string strOrg)
{
    return URLEncode(strOrg);
}

// URL编码，编码为UTF-8
std::string CUrlConvert::UrlEncode_UTF8(std::string strOrg)
{
    return URLEncode(GBKToUTF8(strOrg));
}

// URL解码，解码为GBK
std::string CUrlConvert::UrlDecode_GBK(std::string strOrg)
{
    return URLDecode(strOrg);
}

// URL解码，解码为UTF-8
std::string CUrlConvert::UrlDecode_UTF8(std::string strOrg)
{
    return UTF8ToGBK(URLDecode(strOrg));
}
