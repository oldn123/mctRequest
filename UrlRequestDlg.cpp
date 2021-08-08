
// UrlRequestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UrlRequest.h"
#include "UrlRequestDlg.h"
#include "afxdialogex.h"

#include "CMctRequest.h"

#include "vector"
#include "string"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



std::string wstring_To_UTF8(const std::wstring & str)
{
	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, NULL, NULL, NULL, NULL);
	char* pBuf = new char[nLen + 1];
	::WideCharToMultiByte(CP_UTF8, 0, str.c_str(), nLen, pBuf, nLen, NULL, NULL);
	std::string strRet(pBuf);
	delete[] pBuf;
	pBuf = nullptr;
	return strRet;
}

std::string UTF8_To_string(const std::string & str)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴  
	memset(pwBuf, 0, nwLen * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr = pBuf;

	delete[]pBuf;
	delete[]pwBuf;

	pBuf = nullptr;
	pwBuf = nullptr;

	return retStr;
}


std::string UnicodeToANSI(const wstring& str)
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte(CP_ACP,
		0,
		str.c_str(),
		-1,
		nullptr,
		0,
		nullptr,
		nullptr);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char)* (iTextLen + 1));
	::WideCharToMultiByte(CP_ACP,
		0,
		str.c_str(),
		-1,
		pElementText,
		iTextLen,
		nullptr,
		nullptr);
	string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUrlRequestDlg 对话框



CUrlRequestDlg::CUrlRequestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_URLREQUEST_DIALOG, pParent)
	, m_nRequestMode(0), m_mr(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUrlRequestDlg::Clear()
{
	m_msgInfo.clear();
	::PostMessage(GetDlgItem(IDC_EDIT_RET)->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)m_msgInfo.c_str());
}

void CUrlRequestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CUrlRequestDlg::AppendMsg(const std::string& s)
{
	USES_CONVERSION;
	CStringA ss = s.c_str();
	ss.Replace("\n", "\r\n");
	m_msgInfo += A2T(ss);

	//::PostMessage(GetDlgItem(IDC_EDIT_RET)->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)m_msgInfo.c_str());
	SetDlgItemText(IDC_EDIT_RET, m_msgInfo.c_str());
}

BEGIN_MESSAGE_MAP(CUrlRequestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CUrlRequestDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CUrlRequestDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_ADDCART, &CUrlRequestDlg::OnBnClickedButtonAddcart)
	ON_BN_CLICKED(IDC_BUTTON_CHECKOUT, &CUrlRequestDlg::OnBnClickedButtonCheckout)
	ON_BN_CLICKED(IDC_BUTTON_CHECKOUT2, &CUrlRequestDlg::OnBnClickedButtonCheckout2)
	ON_BN_CLICKED(IDC_BUTTON_CHECKOUT3, &CUrlRequestDlg::OnBnClickedButtonCheckout3)
	ON_BN_CLICKED(IDC_BUTTON_CHECKOUT4, &CUrlRequestDlg::OnBnClickedButtonCheckout4)
END_MESSAGE_MAP()


// CUrlRequestDlg 消息处理程序



BOOL CUrlRequestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);

	USES_CONVERSION;
    SetDlgItemText(IDC_EDIT_USERNAME, A2T(g_username));
    SetDlgItemText(IDC_EDIT_PWD, A2T(g_userpsd));

    SetDlgItemText(IDC_EDIT_PRODUCT, L"4530956155944");
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUrlRequestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUrlRequestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUrlRequestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

std::string g_urls[] = {
	"https://mct.tokyo/en/account/login",
	"https://mct.tokyo/en/account/login",
};


bool g_request_mode = 1;


CString			g_valueKey;
int				g_nPageIdx = 1;
vector<CString> g_datasArr;
int				g_timerId = 100;

bool DoRequest(std::string& strUrl, std::string& sRet)
{
	CWriteData wd;
	bool  bError = true;
	CURL* curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	struct curl_slist *headers = NULL;
// 	headers = curl_slist_append(headers, hostlogin);
// 	headers = curl_slist_append(headers, "Connection: keep-alive");
// 	headers = curl_slist_append(headers, "Cache-Control: no-cache");
// 	headers = curl_slist_append(headers, "Accept:text/html, application/xhtml+xml, application/xml;q=0.9,image/webp,*/*;q=0.8");
// 	headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
// 	headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate");
// 	headers = curl_slist_append(headers, "Accept-Language: zh-CN,zh;q=0.8");
// 	headers = curl_slist_append(headers, "Cookie:JSESSIONID=0123456789.tomcat1");

// 	char jsonObj[128];
// 	memset(jsonObj, 0, sizeof(jsonObj));
// 	sprintf(jsonObj, "j_username=%s&j_password=%s", "admin", "21232f297a57a5a743894a0e4a801fc3");

	headers = curl_slist_append(headers, "");

	"Accept: text/html, application/xhtml+xml, image/jxr, */*	\
    Referer: https://mct.tokyo/account/login	\
	Accept - Language : zh - CN	\
    User - Agent : Mozilla / 5.0 (Windows NT 10.0; WOW64; Trident / 7.0; rv:11.0) like Gecko	\
    Content - Type : application / x - www - form - urlencoded	\
    Accept - Encoding : gzip, deflate	\
    Host : mct.tokyo	\
    Content - Length : 108	\
    Connection : Keep - Alive	\
    Cache - Control : no - cache	\
    Cookie : _landing_page = % 2F; cart_ts = 1624766086; _shopify_country = China; _shopify_sa_p = ; cart_sig = 3037dc3898de31ad430c6957d48cbdd8; cart_ver = gcp - us - east1 % 3A2; _shopify_y = e2d260f9 - 03c2 - 4a93 - 8f8d - 1632009773c2; cart_currency = TWD; _s = a6d9ab16 - c2a5 - 4e78 - 8474 - d387e3d76e31; _orig_referrer = ; _shopify_sa_t = 2021 - 06 - 27T03 % 3A59 % 3A32.901Z; _y = e2d260f9 - 03c2 - 4a93 - 8f8d - 1632009773c2; _shopify_s = a6d9ab16 - c2a5 - 4e78 - 8474 - d387e3d76e31; secure_customer_sig = ; cart = 03dec579e67677d583ab78756a4ede4f; _secure_session_id = 5bb82bbaf8a0d3d5b1df294a11dd71e6	\
	";

	curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());

	//	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	g_valueKey = L"0123";

	if (g_valueKey.GetLength() > 0)
	{
		USES_CONVERSION;
		char jsonObj[512];
		memset(jsonObj, 0, sizeof(jsonObj));
		sprintf(jsonObj, "calendar=2019-01-05&sortType=num&PageIndex=%d&__RequestVerificationToken=%s", g_nPageIdx, T2A((LPCTSTR)g_valueKey));
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonObj);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(jsonObj));
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE , "d:\\123.txt"); 
	}
	curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "d:\\123.txt"); 
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&wd);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcrp/0.1");
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_PROXY, "127.0.0.1:8888");
	curl_easy_setopt(curl, CURLOPT_POST, TRUE);

	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	if (CURLE_OK != res) {
		fprintf(stderr, "curl told us %d\n", res);
		bError = false;
		string strError;
	//	GetErrorInfo(res, strError);
	}

	if (bError)
	{
		wd.GetString(sRet);
		//ParseLoginResposne(strResponse, loginresponse);
	}
	return bError;
}

bool CUrlRequestDlg::DoRequest2(std::string & sRet)
{
	CMctRequest mr(this);

	for (auto i =0; i < (int)RType::eEnd; i++)
	{
		if (!mr.DoRequest((RType)i)) {
			break;
		}

		if (i == (int)RType::eCheckouts_contact_info)
		{
			mr.DoRequestEPayInfo();
		}

        std::this_thread::sleep_for(1s);
	}


	sRet = mr.GetResponse();

	return 0;
}


int CUrlRequestDlg::GetRequestMode()
{
	return IsDlgButtonChecked(IDC_RADIO1) ? 1 : 0;
}

void CUrlRequestDlg::OnDecodeMsg(const CString & strMsg)
{
	{
		CString sValueKey; 
		CString sFind1 = L"<input name=\"__RequestVerificationToken\" type=\"hidden\" value=\"";
		CString sFind2 = L"\" /></form>";
		int nPos1 = strMsg.Find(sFind1);
		if (nPos1 > 0)
		{
			nPos1 += sFind1.GetLength();
			int nPos2 = strMsg.Find(sFind2, nPos1);
			if (nPos2 > 0)
			{
				sValueKey = strMsg.Mid(nPos1, nPos2 - nPos1);
			}	
		}

		if (sValueKey)
		{
			g_valueKey = sValueKey;
			g_nPageIdx++;
		}
		else
		{
			ASSERT(FALSE);
		}
	}

	{
		CString sFind1 = L"<table class=\"tblType1 mt20\"";
		CString sFind2 = L"<tbody>";
		CString sFind3 = L"<tr>";
		CString sFind4 = L"</tr>";
		CString sEndFlag = L"</tbody>";
		CString sValue; 
		int nPos1 = strMsg.Find(sFind1);
		int nEndPos = 0;
		if (nPos1 > 0)
		{
			nPos1 += sFind1.GetLength();
			int nPos2 = strMsg.Find(sFind2, nPos1);
			if (nPos2 > 0)
			{
				nPos2 += sFind2.GetLength();
				nEndPos = strMsg.Find(sEndFlag, nPos2);
				ASSERT(nEndPos > 0);
				do 
				{
					int nPos3 = strMsg.Find(sFind3, nPos2);
					if (nPos3 > 0)
					{
						if (nPos3 > nEndPos)
						{
							break;
						}
						nPos3 += sFind3.GetLength();
						int nPos4 = strMsg.Find(sFind4, nPos3);
						if (nPos4 > 0)
						{
							sValue = strMsg.Mid(nPos3, nPos4 - nPos3);
							g_datasArr.push_back(sValue);
							
							nPos2 = nPos4 + sFind4.GetLength();
						}
					}
					else
					{
						break;
					}
				} while (true);
			}
		}
	}

	if (g_nPageIdx < 5)
	{
		//g_timerId = SetTimer(g_timerId, 2000, NULL);
	}
}

void CUrlRequestDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	return;

	CString sTips;
	sTips.Format(L"req--idx:%d", g_nPageIdx);
	SetWindowText(sTips);

	CString sUrl;
	GetDlgItemText(IDC_EDIT_URL, sUrl);
	USES_CONVERSION;
	string sParam = T2A(sUrl);
	string sRet;
	//DoRequest(sParam, sRet);

	CString sText;


	DoRequest2(sRet);
	

	//sRet = string_To_UTF8(sRet);
	sText = A2T(sRet.c_str());
	OnDecodeMsg(sText);
	SetDlgItemText(IDC_EDIT_RET, sText);

//	CDialogEx::OnOK();
}


void CUrlRequestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnTimer(nIDEvent);

	if (nIDEvent == g_timerId)
	{
		KillTimer(g_timerId);

		OnBnClickedOk();
	}

}


void CUrlRequestDlg::OnBnClickedButtonLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	CString su;
	CString sw;

	GetDlgItemText(IDC_EDIT_USERNAME, su);
	GetDlgItemText(IDC_EDIT_PWD, sw);

	m_mr.UseProxyAgent(GetRequestMode());
	
	USES_CONVERSION;
	m_mr.SetLoginInfo(W2A(su), W2A(sw));
	m_mr.DoRequest(RType::eLogin);
	m_mr.DoRequest(RType::eAccount);
}


void CUrlRequestDlg::OnBnClickedButtonAddcart()
{
	// TODO: 在此添加控件通知处理程序代码

    CString sp;

    GetDlgItemText(IDC_EDIT_PRODUCT, sp);

	USES_CONVERSION;	
	m_mr.SetProductNum(T2A(sp));

	m_mr.DoRequestEPayInfo();
    m_mr.DoRequest(RType::eProduct);
    m_mr.DoRequest(RType::eAddCart);
    m_mr.DoRequest(RType::eCart);
}


void CUrlRequestDlg::OnBnClickedButtonCheckout()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_mr.DoRequest(RType::eCart2))
	{
        if(m_mr.DoRequest(RType::eCheckouts))
			m_mr.DoRequest(RType::eCheckouts_contact_info);
	}
}


void CUrlRequestDlg::OnBnClickedButtonCheckout2()
{
	// TODO: 在此添加控件通知处理程序代码
    m_mr.DoRequest(RType::eCheckouts2);
    m_mr.DoRequest(RType::eCheckouts2_shipping_method);
}


void CUrlRequestDlg::OnBnClickedButtonCheckout3()
{
	// TODO: 在此添加控件通知处理程序代码
    m_mr.DoRequest(RType::eCheckouts3);
    m_mr.DoRequest(RType::eCheckouts3_payment_method);
}


void CUrlRequestDlg::OnBnClickedButtonCheckout4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_mr.DoRequest_S_before() && m_mr.DoRequest_S())
	{
		m_mr.DoRequest(RType::eCheckouts_beforeProc);
		m_mr.DoRequest(RType::eCheckouts_doProc);
	}
}
