#pragma once
//UrlConvert.h
#ifndef __URLCONVERT_H__
#define __URLCONVERT_H__
#pragma once
/*
使用方法：
CUrlConvert url;
//Encode test
string str1 = url.UrlEncode_GBK("谷姐");
cout << "UrlEncode_GBK " << str1.c_str() <<endl;
string str2 = url.UrlEncode_UTF8("谷姐");
cout << "UrlEncode_UTF8 " << str2.c_str() <<endl;
//Decode test
string str3 = url.UrlDecode_GBK(str1);
cout << "UrlDecode_GBK " << str3.c_str() <<endl;
string str4 = url.UrlDecode_UTF8(str2);
cout << "UrlDecode_UTF8 " << str4.c_str() <<endl;
*/
#include <Windows.h>
#include <string>

class CUrlConvert
{
public:
    CUrlConvert(void);
    ~CUrlConvert(void);

    // URL编码，编码为GBK
    std::string UrlEncode_GBK(std::string strOrg);
    // URL编码，编码为UTF-8
    std::string UrlEncode_UTF8(std::string strOrg);

    // URL解码，解码为GBK
    std::string UrlDecode_GBK(std::string strOrg);
    // URL解码，解码为UTF-8
    std::string UrlDecode_UTF8(std::string strOrg);



    std::string string_To_UTF8(const std::string& str)
    {
        int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

        wchar_t* pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
        ZeroMemory(pwBuf, nwLen * 2 + 2);

        ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

        int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

        char* pBuf = new char[nLen + 1];
        ZeroMemory(pBuf, nLen + 1);

        ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

        std::string retStr(pBuf);

        delete[]pwBuf;
        delete[]pBuf;

        pwBuf = nullptr;
        pBuf = nullptr;

        return retStr;
    }


    static std::string _utf16_to_utf8(const wchar_t* str)
    {
        int len;
        len = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
        char* szUtf8 = (char*)malloc(len + 1);
        memset(szUtf8, 0, len + 1);
        WideCharToMultiByte(CP_UTF8, 0, str, -1, szUtf8, len, NULL, NULL);
        std::string ss = szUtf8;
        free(szUtf8);
        return ss;
    }



public:
    // URL解码，解码为GBK
    static std::string URLDecode(std::string& strOrg);
    // URL编码，编码为GBK
    static std::string URLEncode(std::string& strOrg);

    static std::string GBKToUTF8(const std::string& strGBK);
    static std::string UTF8ToGBK(const std::string& strUTF8);
};

#endif //__URLCONVERT_H__