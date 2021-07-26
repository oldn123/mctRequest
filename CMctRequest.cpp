#include "stdafx.h"
#include "CMctRequest.h"



const char* encodeURI(const char* Str)
{
    wchar_t* Bufw = NULL;
    char* Bufc = NULL;
    static char RTV[5120] = { 0 };
    std::string strLocale = setlocale(LC_ALL, "");
    long needSize = mbstowcs(NULL, Str, 0) + 1;
    Bufw = new wchar_t[needSize];
    if (0 == needSize || NULL == Bufw) {
        if (NULL != Bufw) {
            delete[] Bufw;
            Bufw = NULL;
        }
        if (NULL != Bufc) {
            delete[] Bufc;
            Bufc = NULL;
        }
        return NULL;
    }
    memset(Bufw, 0x0, needSize * 2);
    mbstowcs(Bufw, Str, needSize);

    strLocale = setlocale(LC_ALL, "en_US.utf8");
    needSize = wcstombs(NULL, Bufw, 0) + 1;
    Bufc = new char[needSize];
    if (0 == needSize || NULL == Bufc) {
        if (NULL != Bufw) {
            delete[] Bufw;
            Bufw = NULL;
        }
        if (NULL != Bufc) {
            delete[] Bufc;
            Bufc = NULL;
        }
        return NULL;
    }
    memset(Bufc, 0x0, needSize);
    wcstombs(Bufc, Bufw, needSize);
    unsigned char* pWork = (unsigned char*)Bufc;
    memset(RTV, 0x0, sizeof(RTV));
    if (strlen(Bufc) > 5120) {
        if (NULL != Bufw) {
            delete[] Bufw;
            Bufw = NULL;
        }
        if (NULL != Bufc) {
            delete[] Bufc;
            Bufc = NULL;
        }
        return NULL;
    }
    while (*pWork != 0x0) {
        if (*pWork != '!' && *pWork != '@' && *pWork != '#' &&
            *pWork != '$' && *pWork != '&' && *pWork != '*' &&
            *pWork != '(' && *pWork != ')' && *pWork != '=' &&
            *pWork != ':' && *pWork != '/' && *pWork != ';' &&
            *pWork != '?' && *pWork != '+' && *pWork != '\'' &&
            *pWork != '.') {
            sprintf(RTV + strlen(RTV), "%%%2X", *pWork);
        }
        else {
            sprintf(RTV + strlen(RTV), "%c", *pWork);
        }
        pWork++;
    }
    if (NULL != Bufw) {
        delete[] Bufw;
        Bufw = NULL;
    }
    if (NULL != Bufc) {
        delete[] Bufc;
        Bufc = NULL;
    }
    return RTV;
}