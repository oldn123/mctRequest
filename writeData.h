#pragma once

#include <vector>
#include <string>
using namespace std;



class CWriteData
{
public:
    CWriteData() {
    }
    ~CWriteData() {
        for (auto iter = m_dataArr.begin(); iter != m_dataArr.end(); iter++)
        {
            DataNode* pdn = *iter;
            delete pdn;
        }
        m_dataArr.clear();
    }

    struct DataNode
    {
        int nDataLen;
        uint8_t * pBuf;

        DataNode() {
            nDataLen = 0;
            pBuf = NULL;
        }
        ~DataNode() {
            if (pBuf)
            {
                delete[] pBuf;
                pBuf = 0;
            }
        }
    };
    void AddData(int nLen, uint8_t* pBuf) {
        m_nTotalSize += nLen;
        DataNode* pdn = new DataNode;
        pdn->nDataLen = nLen;
        pdn->pBuf = new uint8_t[pdn->nDataLen];
        memcpy(pdn->pBuf, pBuf, pdn->nDataLen);
        m_dataArr.push_back(pdn);
    }


    void GetString(string& str) {
        char* pBuf = new char[m_nTotalSize];
        memset(pBuf, 0, m_nTotalSize);
        int nFrom = 0;
        for (auto iter = m_dataArr.begin(); iter != m_dataArr.end(); iter++)
        {
            memcpy(pBuf + nFrom, (*iter)->pBuf, (*iter)->nDataLen);
            nFrom += (*iter)->nDataLen;
        }

        uLong ul = 1024 * 1024 * 10;
        static Byte* pOut = new Byte[ul];
        memset(pOut, 0, ul);
        char* __pbuf = pBuf;
        int32_t nl = m_nTotalSize;
        if (httpgzdecompress((Byte*)pBuf, m_nTotalSize, pOut, &ul) >= 0) {

            __pbuf = (char*)pOut;
            nl = ul;
        }
        str.clear();
        str.append(__pbuf, nl);
        delete[] pBuf;
        pBuf = NULL;
    }

    void WriteToFile(const char* sFileName) {
        FILE* fp = fopen(sFileName, "wb");
        if (fp)
        {
            for (auto iter = m_dataArr.begin(); iter != m_dataArr.end(); iter++)
            {
                fwrite((*iter)->pBuf, 1, (*iter)->nDataLen, fp);
            }
            fclose(fp);
        }
    }

protected:
    std::vector<DataNode*>	m_dataArr;
    int						m_nTotalSize = 0;
};


static size_t OnWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
    CWriteData* pWd = (CWriteData*)lpVoid;
    pWd->AddData(size * nmemb, (uint8_t*)buffer);
    return nmemb;
}
