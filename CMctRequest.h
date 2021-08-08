#pragma once

#include <ctime>
#include <string>
#include <map>
#include <sstream>
#include <mutex>
#include <memory>
#include <functional>
using namespace std;


#include "writeData.h"

#include "UrlConvert.h"

enum class RType
{
    eLogin,                 //POST /en/account/login HTTP/1.1
    eAccount,               //GET /en/account HTTP/1.1
    eProduct,               //GET /en/products/4530956593920 HTTP/1.1
    eAddCart,               //POST /en/cart/add HTTP/1.1
    eCart,                  //GET /en/cart HTTP/1.1
    eCart2,                 //POST /en/cart HTTP/1.1
    eCheckouts,             //GET /3623944241/checkouts/382b7f0b429e2cfa02228d7bc1fe07eb HTTP/1.1
    eCheckouts_contact_info,//GET /3623944241/checkouts/382b7f0b429e2cfa02228d7bc1fe07eb?step=contact_information HTTP/1.1
    eCheckouts2,             //POST /3623944241/checkouts/382b7f0b429e2cfa02228d7bc1fe07eb HTTP/1.1
    eCheckouts2_shipping_method, 
    eCheckouts3,             //POST /3623944241/checkouts/382b7f0b429e2cfa02228d7bc1fe07eb HTTP/1.1
    eCheckouts3_payment_method,
    eCheckouts_beforeProc,  //POST https://mct.tokyo/3623944241/checkouts/19dfc090eac2cb78033d0b99e1676e61 HTTP/1.1
    eCheckouts_doProc,      //GET https://mct.tokyo/3623944241/checkouts/19dfc090eac2cb78033d0b99e1676e61/processing HTTP/1.1
    eEnd
};

enum class RMethod{
    ePost,
    eGet
};

enum class checkouts_step_type {
    eContact_information,
    eShipping_method,
    ePayment_method
};

struct RequestItem {
    RType       rt;
    RMethod     rm;
    uint32_t    hf;
    const char* sUrl;
    
};

enum class ReqAttiType : uint32_t {
    eAccept = 1,
    eAccept_Language = 1 << 1,
    eContent_Type = 1 << 2,
    eAccept_Encoding = 1 << 3,
    eConnection = 1 << 4,
    eCache_Control = 1 << 5,
    eHost = 1 << 6,
    eContent_Length = 1 << 7,
    eCookie = 1 << 8
//    eUser_Agent = 1 << 8,
//    eReferer = 1 << 9,
};

struct ReqAtti
{
    ReqAttiType rat;
    const char* sKey;
    const char* sValue;
};

inline const char* s_https     = "https://";
inline const char* s_hostUrl   = "mct.tokyo";
inline const char* s_l         = "";
//inline const char* s_http_ver  = " HTTP/1.1";
inline const char* s_http_ver = "";

inline uint32_t g_defht_post = (uint32_t)ReqAttiType::eAccept | (uint32_t)ReqAttiType::eAccept_Language | \
(uint32_t)ReqAttiType::eAccept_Encoding | (uint32_t)ReqAttiType::eConnection | \
(uint32_t)ReqAttiType::eCache_Control | (uint32_t)ReqAttiType::eHost | (uint32_t)ReqAttiType::eCookie |
(uint32_t)ReqAttiType::eContent_Type | (uint32_t)ReqAttiType::eContent_Length ;

inline uint32_t g_defht_get = (uint32_t)ReqAttiType::eAccept | (uint32_t)ReqAttiType::eAccept_Language | \
(uint32_t)ReqAttiType::eAccept_Encoding | (uint32_t)ReqAttiType::eConnection | \
(uint32_t)ReqAttiType::eCache_Control | (uint32_t)ReqAttiType::eHost | (uint32_t)ReqAttiType::eCookie;

inline ReqAtti g_rAtti[] = {
    {ReqAttiType::eAccept, "Accept", "text/html, application/xhtml+xml, image/jxr, */*"},
    {ReqAttiType::eAccept_Language, "Accept-Language", "zh-CN"},
 //   {ReqAttiType::eUser_Agent, "User-Agent", "Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; rv:11.0) like Gecko"},
    {ReqAttiType::eContent_Type, "Content-Type", "application/x-www-form-urlencoded"},
    {ReqAttiType::eAccept_Encoding, "Accept-Encoding", "gzip, deflate"},
    {ReqAttiType::eConnection, "Connection", "Keep-Alive"},
    {ReqAttiType::eCache_Control, "Cache-Control", "no-cache"},
 //   {ReqAttiType::eReferer, "Referer", ""},
    {ReqAttiType::eHost, "Host", ""},
    {ReqAttiType::eContent_Length, "Content-Length", ""},
    {ReqAttiType::eCookie, "Cookie", ""}
};

// Accept: text/html, application/xhtml+xml, image/jxr, */*
// Referer: https://mct.tokyo/en/account/login
// Accept-Language: zh-CN
// User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; rv:11.0) like Gecko
// Content-Type: application/x-www-form-urlencoded
// Accept-Encoding: gzip, deflate
// Host: mct.tokyo
// Content-Length: 108
// Connection: Keep-Alive
// Cache-Control: no-cache


//Cookie: _landing_page = % 2F; cart_ts = 1625411717; _shopify_sa_p = ; cart_sig = f3a65f52bbd2b596b71282b6a9cf189c; cart_ver = gcp - us - east1 % 3A10; _shopify_y = c6b56e5b - f3f4 - 4d57 - a089 - a46d12831dd8; cart_currency = TWD; _s = be6c0322 - 1931 - 4960 - 9ad2 - f65fb3b502da; _orig_referrer = ; _shopify_sa_t = 2021 - 07 - 04T15 % 3A18 % 3A08.068Z; _y = c6b56e5b - f3f4 - 4d57 - a089 - a46d12831dd8; _shopify_s = be6c0322 - 1931 - 4960 - 9ad2 - f65fb3b502da; secure_customer_sig = ; _checkout_queue_checkout_token = eyJfcmFpbHMiOnsibWVzc2FnZSI6IkJBaEpJaVV6T0RKaU4yWXdZalF5T1dVeVkyWmhNREl5TWpoa04ySmpNV1psTURkbFlnWTZCa1ZVIiwiZXhwIjoiMjAyMS0wNy0wNFQxNTo1NjowMS43OTZaIiwicHVyIjoiY29va2llLl9jaGVja291dF9xdWV1ZV9jaGVja291dF90b2tlbiJ9fQ % 3D % 3D--33eed02c76188bed7fa8e39f22c5a07d513be4fe; _secure_session_id = 627c671f9db5c2fc3e61dc1d07b77d23; _checkout_queue_token = AgKPdCOwCPUttu48oUPDnBFRr6HqdlZk1B8vVr3FGaDVbhXVFs3PTwaINGsNMjsi29GjL323MFYj842xABg - LvDSiovFP3kiBy0vX_md4FlhS2Mn1lI75Aj7BfJqfmOOG8xla1URHrPJGk1ocVXLBucveVPC5v_3h - xWXKi5kcXi46l1zjOSaDkGpQ % 3D % 3D; cart = 575e78417499c9ea6000f4dac492fb89; _shopify_evids = pv % 3D9109f96e9f95e738bf326ebfd98704afe155fd9b79b4549f39aca9bdc6c435b0
//form_type=customer_login&utf8=%E2%9C%93&customer%5Bemail%5D=270081974@qq.com&customer%5Bpassword%5D=Qq890821


inline const char* g_username = "270081974@qq.com";
inline const char* g_userpsd = "Qq890821";

inline string          g_apaySessionSet;
inline string          g_shopifysessions;
inline std::string     g_cart_sid;     //382b7f0b429e2cfa02228d7bc1fe07eb

inline CUrlConvert     g_urlC;
inline std::time_t     g_cart_ts = 0;
inline std::string     g_sa_t = "";

inline std::string      g_sPdciId;

inline const char* g_cart = "e2a6157c8e8811eac7d4ddbb2b71cf9f";
inline const char* g_cart_sig = "31a10bf9243a4cfcefe8fafc2e3a53f5";

inline std::string __get_cookie_login() {
    std::time_t t = std::time(0);
    g_cart_ts = t;
    auto ptm = gmtime(&t);
    char sbuf[64] = { 0 };
    strftime(sbuf, 64, "%Y-%m-%d %H:%M:%S", ptm);

    auto st = g_urlC.UrlEncode_GBK(sbuf);
    g_sa_t = st;

    std::stringstream ss;
//     ss << "_landing_page=%2F; cart_ts=" << t << ";_shopify_sa_p=; "
//         << "cart_sig=" << g_cart_sig
//         << "; cart_ver=gcp-us-east1%3A17; " 
//         << "_shopify_y=c6b56e5b-f3f4-4d57-a089-a46d12831dd8; cart_currency=TWD; " 
//         << "_s=de050c49-4e45-4d9d-b36d-337268b939b6;_orig_referrer=; _shopify_sa_t=" << st << "01.700Z; " 
//         << "_y=c6b56e5b-f3f4-4d57-a089-a46d12831dd8; _shopify_s=de050c49-4e45-4d9d-b36d-337268b939b6; " 
//         << "secure_customer_sig=; "
//         << "_secure_session_id=da6471849a193c0805a0c80bd06388db; " 
//         << "cart=" << g_cart;
    return ss.str().c_str();
}

inline std::string __get_cookie_2(const std::map<std::string, std::string> & sInfo) {

    std::stringstream ss;
    __fillCookieItems(ss, sInfo);
    return ss.str().c_str();
}



inline std::string __get_cookie_3(std::map<RType, std::map<std::string, std::string>> & sInfoMap) {
    const std::map<std::string, std::string>& sInfoLogin = sInfoMap[RType::eLogin];
    const std::map<std::string, std::string>& sInfoAccount = sInfoMap[RType::eAccount];
    std::stringstream ss;
    __fillCookieItems(ss, sInfoLogin);
    if (!g_apaySessionSet.empty())
    {
        ss << ";apay-session-set=" << g_apaySessionSet;
    }
    return ss.str();
}



inline std::string __get_cookie_4(std::map<RType, std::map<std::string, std::string>>& sInfoMap) {  //eAddCart
    const std::map<std::string, std::string>& sInfoLogin = sInfoMap[RType::eLogin];
    const std::map<std::string, std::string>& sInfoProduct = sInfoMap[RType::eProduct];

    std::stringstream ss;
    __fillCookieItems(ss, sInfoLogin);
    __fillCookieItems(ss, sInfoProduct);
    if (!g_apaySessionSet.empty())
    {
        ss << ";apay-session-set=" << g_apaySessionSet;
    }
    return ss.str();
}

inline std::string __get_cookie_5(std::map<RType, std::map<std::string, std::string>>& sInfoMap) {  //Cart
    const std::map<std::string, std::string>& sInfoLogin = sInfoMap[RType::eLogin];
    const std::map<std::string, std::string>& sInfoAddCart = sInfoMap[RType::eAddCart];
    std::stringstream ss;
    __fillCookieItems(ss, sInfoLogin);
    __fillCookieItems(ss, sInfoAddCart);
    return ss.str();
}

inline std::string __get_cookie_6(std::map<RType, std::map<std::string, std::string>>& sInfoMap) { //eCart2
    const std::map<std::string, std::string>& sInfoLogin = sInfoMap[RType::eLogin];
    const std::map<std::string, std::string>& sInfoAddCart = sInfoMap[RType::eAddCart];
    std::stringstream ss;
    __fillCookieItems(ss, sInfoLogin);
    __fillCookieItems(ss, sInfoAddCart);
    return ss.str();
}

inline std::string __get_cookie_7(std::map<RType, std::map<std::string, std::string>>& sInfoMap) { //checkouts
    const std::map<std::string, std::string>& sInfoLogin = sInfoMap[RType::eLogin];
    const std::map<std::string, std::string>& sInfoCart2 = sInfoMap[RType::eCart2];
    std::stringstream ss;
    __fillCookieItems(ss, sInfoLogin);
    __appendCookieItem(ss, "_checkout_queue_token", sInfoCart2);
    __appendCookieItem(ss, "_checkout_queue_checkout_token", sInfoCart2);
    __fillCookieItems(ss, sInfoCart2);
    return ss.str();
}

inline std::string __get_cookie_8(std::map<RType, std::map<std::string, std::string>>& sInfoMap) { //Checkouts_contact_info
    const std::map<std::string, std::string>& sInfoLogin = sInfoMap[RType::eLogin];
    std::stringstream ss;
    __fillCookieItems(ss, sInfoLogin);
    return ss.str();
}

inline std::string __get_cookie_9(std::map<RType, std::map<std::string, std::string>>& sInfoMap) { //Checkouts2
    const std::map<std::string, std::string>& sInfoLogin = sInfoMap[RType::eLogin];
    const std::map<std::string, std::string>& sInfoCart2 = sInfoMap[RType::eCart2];
    const std::map<std::string, std::string>& sInfoCheckouts = sInfoMap[RType::eCheckouts];

    std::stringstream ss;
    __fillCookieItems(ss, sInfoLogin);
    __fillCookieItems(ss, sInfoCart2);
    __appendCookieItem(ss, "checkout", sInfoCheckouts);
    __appendCookieItem(ss, "checkout_token", sInfoCheckouts);
    __fillCookieItems(ss, sInfoCheckouts);
    if (!g_apaySessionSet.empty())
    {
        ss << ";apay-session-set=" << g_apaySessionSet;
    }
    return ss.str();
}

inline std::string __get_cookie_10(std::map<RType, std::map<std::string, std::string>>& sInfoMap) { //Checkouts2-end
    const std::map<std::string, std::string>& sInfoLogin = sInfoMap[RType::eLogin];
    const std::map<std::string, std::string>& sInfoCart2 = sInfoMap[RType::eCart2];
    const std::map<std::string, std::string>& sInfoCheckouts2 = sInfoMap[RType::eCheckouts2];

    std::stringstream ss;
    __fillCookieItems(ss, sInfoLogin);
    __fillCookieItems(ss, sInfoCart2);
    __appendCookieItem(ss, "checkout", sInfoCheckouts2);
    __appendCookieItem(ss, "checkout_token", sInfoCheckouts2);
    __appendCookieItem(ss, "_checkout_queue_token", sInfoCheckouts2);
    __appendCookieItem(ss, "_checkout_queue_checkout_token", sInfoCheckouts2);
    __fillCookieItems(ss, sInfoCheckouts2);
    if (!g_apaySessionSet.empty())
    {
        ss << ";apay-session-set=" << g_apaySessionSet;
    }
    return ss.str();
}

inline std::string __get_cookie_11(std::map<RType, std::map<std::string, std::string>>& sInfoMap) { //Checkouts3
    const std::map<std::string, std::string>& sInfoLogin = sInfoMap[RType::eLogin];
    const std::map<std::string, std::string>& sInfoCart2 = sInfoMap[RType::eCart2];
    const std::map<std::string, std::string>& sInfoCheckouts = sInfoMap[RType::eCheckouts];
    const std::map<std::string, std::string>& sInfoCheckouts2_shipping_m = sInfoMap[RType::eCheckouts2_shipping_method];
    std::stringstream ss;

    __fillCookieItems(ss, sInfoCart2);
    __fillCookieItems(ss, sInfoLogin);
    __appendCookieItem(ss, "checkout", sInfoCheckouts2_shipping_m);
    __appendCookieItem(ss, "checkout_token", sInfoCheckouts2_shipping_m);
    __appendCookieItem(ss, "_checkout_queue_token", sInfoCheckouts);
    __appendCookieItem(ss, "_checkout_queue_checkout_token", sInfoCheckouts);
    __fillCookieItems(ss, sInfoCheckouts2_shipping_m);

    if (!g_apaySessionSet.empty())
    {
        ss << ";apay-session-set=" << g_apaySessionSet;
    }
    return ss.str();
}


inline std::string __get_cookie_12(std::map<RType, std::map<std::string, std::string>>& sInfoMap) { //Checkouts3-end
    const std::map<std::string, std::string>& sInfoLogin = sInfoMap[RType::eLogin];
    const std::map<std::string, std::string>& sInfoCart2 = sInfoMap[RType::eCart2];
    const std::map<std::string, std::string>& sInfoCheckouts3 = sInfoMap[RType::eCheckouts3];
    std::stringstream ss;
    __fillCookieItems(ss, sInfoCart2);
    __fillCookieItems(ss, sInfoLogin);
    __fillCookieItems(ss, sInfoCheckouts3);
    if (!g_apaySessionSet.empty())
    {
        ss << ";apay-session-set=" << g_apaySessionSet;
    }

    return ss.str();
}

inline std::string __get_cookie_beforeproc(std::map<RType, std::map<std::string, std::string>>& sInfoMap) { 
    const std::map<std::string, std::string>& sInfoLogin = sInfoMap[RType::eLogin];
    const std::map<std::string, std::string>& sInfoCart2 = sInfoMap[RType::eCart2];
    const std::map<std::string, std::string>& sInfoCheckouts3 = sInfoMap[RType::eCheckouts3];
    const std::map<std::string, std::string>& sInfoCheckouts3_payment = sInfoMap[RType::eCheckouts3_payment_method];
    std::stringstream ss;
    __fillCookieItems(ss, sInfoCart2);
    __fillCookieItems(ss, sInfoLogin);
    __appendCookieItem(ss, "checkout", sInfoCheckouts3_payment);
    __appendCookieItem(ss, "checkout_token", sInfoCheckouts3_payment);
    __fillCookieItems(ss, sInfoCheckouts3);
    if (!g_apaySessionSet.empty())
    {
        ss << ";apay-session-set=" << g_apaySessionSet;
    }
    return ss.str();
}

inline std::string __get_cookie_throttle_cart2(std::map<RType, std::map<std::string, std::string>>& sInfoMap) {
    const std::map<std::string, std::string>& sInfoLogin = sInfoMap[RType::eLogin];
    const std::map<std::string, std::string>& sInfoCart2 = sInfoMap[RType::eCart2];
    std::stringstream ss;
    __fillCookieItems(ss, sInfoCart2);
    __fillCookieItems(ss, sInfoLogin);
    return ss.str();
}

inline std::string __get_cookie_doproc(std::map<RType, std::map<std::string, std::string>>& sInfoMap) { 
    const std::map<std::string, std::string>& sInfoLogin = sInfoMap[RType::eLogin];
    const std::map<std::string, std::string>& sInfoCart2 = sInfoMap[RType::eCart2];
    const std::map<std::string, std::string>& sInfoCheckouts3 = sInfoMap[RType::eCheckouts3];
    const std::map<std::string, std::string>& sInfoCheckouts_beforeProc = sInfoMap[RType::eCheckouts_beforeProc];
    std::stringstream ss;

    __appendCookieItem(ss, "_checkout_queue_token", sInfoCheckouts_beforeProc);
    __appendCookieItem(ss, "checkout", sInfoCheckouts_beforeProc);
    __appendCookieItem(ss, "checkout_token", sInfoCheckouts_beforeProc);
    __appendCookieItem(ss, "_checkout_queue_checkout_token", sInfoCheckouts_beforeProc);

    __appendCookieItem(ss, "_y", sInfoCheckouts_beforeProc);
    __appendCookieItem(ss, "_shopify_y", sInfoCheckouts_beforeProc);
    __appendCookieItem(ss, "_s", sInfoCheckouts_beforeProc);
    __appendCookieItem(ss, "_shopify_s", sInfoCheckouts_beforeProc);

    __fillCookieItems(ss, sInfoCart2);

    __fillCookieItems(ss, sInfoLogin);

    if (!g_apaySessionSet.empty())
    {
        ss << ";apay-session-set=" << g_apaySessionSet;
    }

    return ss.str();
}

const char* encodeURI(const char* Str);

class IReportMsg {

public:
    virtual void Clear() = 0;
    virtual void AppendMsg(const string&) = 0;
};

inline const char* g_card_info_json = "{\"credit_card\":{\"number\":\"4616 7605 6150 0874\",\"name\":\"zhiyong wu\",\"month\":12,\"year\":2025,\"verification_value\":\"198\"},\"payment_session_scope\":\"mct.tokyo\"}";

class CMctRequest
{
public:
    CMctRequest(IReportMsg * p) {
        m_fnAppendMsg = p;
        curl = nullptr;
        static std::once_flag of;
        std::call_once(of, []() {
            curl_global_init(CURL_GLOBAL_ALL);
            });
    }
    ~CMctRequest() {

    }


private:
    RequestItem m_ri[(const int)RType::eEnd] = {
        {   RType::eLogin,      RMethod::ePost,  g_defht_post, "/account/login"    },
        {   RType::eAccount,    RMethod::eGet,   g_defht_get, "/account"    },
        {   RType::eProduct,    RMethod::eGet,   g_defht_get & ~(uint32_t)ReqAttiType::eCache_Control, "/products/"    },
        {   RType::eAddCart,    RMethod::ePost,  g_defht_post, "/cart/add"    },
        {   RType::eCart,       RMethod::eGet,   g_defht_get, "/cart"    },
        {   RType::eCart2,      RMethod::ePost,  g_defht_post, "/cart"    },
        {   RType::eCheckouts,  RMethod::eGet,   g_defht_get, "/%s/checkouts/%s"    },
        {   RType::eCheckouts_contact_info, RMethod::eGet,  g_defht_get & ~(uint32_t)ReqAttiType::eCache_Control, "/%s/checkouts/%s?step=contact_information"    },
        {   RType::eCheckouts2, RMethod::ePost,  g_defht_post, "/%s/checkouts/%s"    },
        {   RType::eCheckouts2_shipping_method, RMethod::eGet,  g_defht_get & ~(uint32_t)ReqAttiType::eCache_Control, "/%s/checkouts/%s?previous_step=contact_information&step=shipping_method"    },
        {   RType::eCheckouts3, RMethod::ePost,  g_defht_post, "/%s/checkouts/%s"    },
        {   RType::eCheckouts3_payment_method, RMethod::eGet,  g_defht_get & ~(uint32_t)ReqAttiType::eCache_Control, "/%s/checkouts/%s?previous_step=shipping_method&step=payment_method"    },
        {   RType::eCheckouts_beforeProc, RMethod::ePost,  g_defht_post, "/%s/checkouts/%s"    },
        {   RType::eCheckouts_doProc, RMethod::eGet,  g_defht_get & ~(uint32_t)ReqAttiType::eCache_Control, "/%s/checkouts/%s/processing"    }
    };

    std::string BuildUrl(RType rt) {
        string su;
        switch (rt)
        {
        case RType::eProduct:
            su = string(m_ri[(int)rt].sUrl) + m_product_id;
            break;
        case RType::eCheckouts:
        case RType::eCheckouts_contact_info:
        case RType::eCheckouts2:
        case RType::eCheckouts2_shipping_method:
        case RType::eCheckouts3:
        case RType::eCheckouts3_payment_method:
        case RType::eCheckouts_beforeProc:
        case RType::eCheckouts_doProc:
            {
                char sBuf[1024] = { 0 };
                sprintf(sBuf, m_ri[(int)rt].sUrl, m_shop_id.c_str(), g_cart_sid.c_str());
                su = sBuf;
            }
            break;
        default:
            su = m_ri[(int)rt].sUrl;
            break;
        }

        stringstream ss;
        ss << s_https << s_hostUrl << s_l << su << s_http_ver;

        if (rt == RType::eCheckouts3_payment_method)
        {
            m_shopfysparam = g_urlC.UrlEncode_UTF8(ss.str());
        }

        return ss.str();
    }

    std::string BuildReferer(RType rt) {
        switch (rt)
        {
        case RType::eLogin:
        case RType::eAccount:
            return "https://mct.tokyo/account/login";
            break;
        case RType::eProduct:
            return "https://mct.tokyo/";
            break;
        case RType::eAddCart:
        case RType::eCart:
            return string("https://mct.tokyo/products/") + m_product_id;
            break;
        case RType::eCart2:
        case RType::eCheckouts:
            return "https://mct.tokyo/cart";
            break;
        case RType::eCheckouts_contact_info:
        case RType::eCheckouts2:
        case RType::eCheckouts2_shipping_method:
        case RType::eCheckouts3:
        case RType::eCheckouts3_payment_method:
        case RType::eCheckouts_beforeProc:
        case RType::eCheckouts_doProc:
            return "https://mct.tokyo/";
            break;
        default:
            ASSERT(0);
            break;
        }
        return "";
    }


    std::string BuildCookie(RType rt) {
        switch (rt)
        {
        case RType::eLogin:
            return __get_cookie_login();
            break;
        case RType::eAccount:
            return __get_cookie_2(m_cookicMap_resp[RType::eLogin]);
            break;
        case RType::eProduct:
            return __get_cookie_3(m_cookicMap_resp);
            break;
        case RType::eAddCart:
            return __get_cookie_4(m_cookicMap_resp);
            break;
        case RType::eCart:
            return __get_cookie_5(m_cookicMap_resp);
            break;
        case RType::eCart2:
            return __get_cookie_6(m_cookicMap_resp);
            break;
        case RType::eCheckouts:
            return __get_cookie_7(m_cookicMap_resp);
            break;
        case RType::eCheckouts_contact_info:
            return __get_cookie_8(m_cookicMap_resp);
            break;
        case RType::eCheckouts2:
            return __get_cookie_9(m_cookicMap_resp);
            break;      
        case RType::eCheckouts2_shipping_method:
            return __get_cookie_10(m_cookicMap_resp);
            break;
        case RType::eCheckouts3:
            return __get_cookie_11(m_cookicMap_resp);
            break;
        case RType::eCheckouts3_payment_method:
            return __get_cookie_12(m_cookicMap_resp);
            break;
        case RType::eCheckouts_beforeProc:
            return __get_cookie_beforeproc(m_cookicMap_resp);
            break;
        case RType::eCheckouts_doProc:
            return __get_cookie_doproc(m_cookicMap_resp);
            break;
        case RType::eEnd:
            break;
        default:
            break;
        }

        return "";
    }

    std::string BuildPostFields(RType rt) {
        stringstream ss;
        switch (rt)
        {
        case RType::eLogin:
            ss << "form_type=customer_login&utf8=%E2%9C%93" << "&customer%5Bemail%5D=" << m_username << "&customer%5Bpassword%5D=" << m_psw;
            break;
        case RType::eAddCart:
            /**
            -----------------------------7e50780f94
            Content-Disposition: form-data; name="form_type"

            product
            -----------------------------7e50780f94
            Content-Disposition: form-data; name="utf8"

            ✓
            -----------------------------7e50780f94
            Content-Disposition: form-data; name="id"

            32576981073969
            -----------------------------7e50780f94
            Content-Disposition: form-data; name="quantity"

            1
            -----------------------------7e50780f94
            Content-Disposition: form-data; name="add"


            -----------------------------7e50780f94
            Content-Disposition: form-data; name="event_id"

            721b2bcb-F9DE-4BB7-2B48-8E7963AA61E6
            -----------------------------7e50780f94--

            */
            {
                USES_CONVERSION;
                wstringstream wss;
                wss << L"-----------------------------7e50780f94\r\n" << L"Content-Disposition: form-data; name=\"form_type\"\r\n\r\n" << L"product" << L"\r\n"
                    << L"-----------------------------7e50780f94\r\n" << L"Content-Disposition: form-data; name=\"utf8\"\r\n\r\n" << L"✓" << L"\r\n"
                    << L"-----------------------------7e50780f94\r\n" << L"Content-Disposition: form-data; name=\"id\"\r\n\r\n" << g_sPdciId.c_str() << L"\r\n"
                    << L"-----------------------------7e50780f94\r\n" << L"Content-Disposition: form-data; name=\"quantity\"\r\n\r\n" << 1 << L"\r\n"
                    << L"-----------------------------7e50780f94\r\n" << L"Content-Disposition: form-data; name=\"add\"\r\n\r\n\r\n"
                    << L"-----------------------------7e50780f94\r\n" << L"Content-Disposition: form-data; name=\"event_id\"\r\n\r\n" << A2W(NewGuidString().c_str()) << L"\r\n"
                    << L"-----------------------------7e50780f94--\r\n";

                std::string r = CUrlConvert::_utf16_to_utf8(wss.str().c_str());
                return r;
            }
            break;
        case RType::eCart2:
            ss << "updates%5B%5D=1&note=&checkout=%E3%81%94%E8%B3%BC%E5%85%A5%E6%89%8B%E7%B6%9A%E3%81%8D%E3%81%B8";
            break;
        case RType::eCheckouts2:
        {
            ss << "_method=patch" 
                <<"&authenticity_token=" << m_authenticity_tokenMap[checkouts_step_type::eContact_information]//"NiCXJXOlOLD2W7EVTQThOs440vqPP7nNO9PN38OyX1esJKhaIZZsFtWwKp_TXvCKHd4UcDSE7YFLpLow5uyJxA"
                <<"&previous_step=" << "contact_information" 
                <<"&step=" << "shipping_method"
                <<"&checkout%5Bemail%5D=" << g_username
                <<"&checkout%5Bbuyer_accepts_marketing%5D=0"
                <<"&checkout%5Bshipping_address%5D%5Bfirst_name%5D=" << "ZHIYONG" 
                <<"&checkout%5Bshipping_address%5D%5Blast_name%5D=" << "WU"
                <<"&checkout%5Bshipping_address%5D%5Bcompany%5D=" << "orangemarket%E6%A0%AA%E5%BC%8F%E4%BC%9A%E7%A4%BE"
                <<"&checkout%5Bshipping_address%5D%5Baddress1%5D=" << "Osaka+Chou-ku%2CTanimach6-6-7"
                <<"&checkout%5Bshipping_address%5D%5Baddress2%5D=" << "daigomatsuya+biru%2Croom1065"
                <<"&checkout%5Bshipping_address%5D%5Bcity%5D=Osaka"
                <<"&checkout%5Bshipping_address%5D%5Bcountry%5D=" << "Japan"
                <<"&checkout%5Bshipping_address%5D%5Bprovince%5D=" << "JP-27"
                <<"&checkout%5Bshipping_address%5D%5Bzip%5D=" << "542-0012"
                <<"&checkout%5Bshipping_address%5D%5Bphone%5D=" << "080-6155-8183"
                <<"&checkout%5Bshipping_address%5D%5Bid%5D=" << "6343807533105"
                <<"&checkout%5Bclient_details%5D%5Bbrowser_width%5D=1005"
                <<"&checkout%5Bclient_details%5D%5Bbrowser_height%5D=961"
                <<"&checkout%5Bclient_details%5D%5Bjavascript_enabled%5D=1"
                <<"&checkout%5Bclient_details%5D%5Bcolor_depth%5D=24"
                <<"&checkout%5Bclient_details%5D%5Bjava_enabled%5D=true"
                <<"&checkout%5Bclient_details%5D%5Bbrowser_tz%5D=-480";
        }
            break;
        case RType::eCheckouts3:
        {
            ss << "_method=patch"
                << "&authenticity_token=" << m_authenticity_tokenMap[checkouts_step_type::eShipping_method]//"NiCXJXOlOLD2W7EVTQThOs440vqPP7nNO9PN38OyX1esJKhaIZZsFtWwKp_TXvCKHd4UcDSE7YFLpLow5uyJxA"
                << "&previous_step=" << "shipping_method"
                << "&step=" << "payment_method"
                << "&checkout%5Bshipping_rate%5D%5Bid%5D=" << m_datashippingmethod
                << "&checkout%5Bclient_details%5D%5Bbrowser_width%5D=1005"
                << "&checkout%5Bclient_details%5D%5Bbrowser_height%5D=961"
                << "&checkout%5Bclient_details%5D%5Bjavascript_enabled%5D=1"
                << "&checkout%5Bclient_details%5D%5Bcolor_depth%5D=24"
                << "&checkout%5Bclient_details%5D%5Bjava_enabled%5D=true"
                << "&checkout%5Bclient_details%5D%5Bbrowser_tz%5D=-480";
        }
        break;
        case RType::eCheckouts_beforeProc:
        {
            ss << "_method=patch"
                << "&authenticity_token=" << m_authenticity_tokenMap[checkouts_step_type::ePayment_method]
                << "&previous_step=payment_method"
                << "&step="
                << "&s=" << g_shopifysessions
                << "&checkout%5Bpayment_gateway%5D=" << m_data_select_gateway
                << "&checkout%5Bcredit_card%5D%5Bvault%5D=false"
                << "&checkout%5Bdifferent_billing_address%5D=false"
                << "&checkout%5Bremember_me%5D="
                << "&checkout%5Bremember_me%5D=0"
                << "&="
                << "&checkout%5Bvault_phone%5D="
                << "&checkout%5Btotal_price%5D=" << m_payment
                << "&complete=1"
                << "&checkout%5Bclient_details%5D%5Bbrowser_width%5D=1005"
                << "&checkout%5Bclient_details%5D%5Bbrowser_height%5D=961"
                << "&checkout%5Bclient_details%5D%5Bjavascript_enabled%5D=1"
                << "&checkout%5Bclient_details%5D%5Bcolor_depth%5D=24"
                << "&checkout%5Bclient_details%5D%5Bjava_enabled%5D=true"
                << "&checkout%5Bclient_details%5D%5Bbrowser_tz%5D=-480";
        }
        default:
            break;
        }

        
        string sret = g_urlC.string_To_UTF8(ss.str());
      
        return sret;
    }

    void    BuildRequest(RType rt) {

        static std::string spf;
        spf = BuildPostFields(rt);

        struct curl_slist* headers = NULL;
        auto hac = sizeof(g_rAtti) / sizeof(ReqAtti);
        for (auto i = 0; i < hac; i++)
        {
            std::string sVal;
            if ((uint32_t)g_rAtti[i].rat != ((uint32_t)g_rAtti[i].rat & m_ri[(int32_t)rt].hf))
            {
                continue;
            }

            switch (g_rAtti[i].rat)
            {
            case ReqAttiType::eHost:
                sVal = s_hostUrl;
                break;
            case ReqAttiType::eCookie:
                {
                    sVal = BuildCookie(rt);
                    if (m_fnAppendMsg)
                    {
                        std::stringstream ss;
                        ss << "\n**** send--cookies [" << (int32_t)rt << "] :\n" << sVal << "\n";
                        m_fnAppendMsg->AppendMsg(ss.str());
                    }
                }
                break;
            case ReqAttiType::eContent_Length:
                sVal = to_string(spf.length());
                break;
            default:
                sVal = g_rAtti[i].sValue;
                break;
            }

            if (rt == RType::eAddCart && g_rAtti[i].rat == ReqAttiType::eContent_Type)
            {
                sVal = "multipart/form-data; boundary=---------------------------7e50780f94";
            }
            
            std::stringstream ss;
            ss << g_rAtti[i].sKey << ": " << sVal;


            OutputDebugStringA(ss.str().c_str());
            OutputDebugStringA("\n");

            headers = curl_slist_append(headers, ss.str().c_str());
        }

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "d:\\123.txt");

        if (!spf.empty())
        {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, spf.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, 1);
            curl_easy_setopt(curl, CURLOPT_POST, 1);
        }
    }

    CURL* _init_curl() {
        curl = curl_easy_init();

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, FALSE);

        curl_easy_setopt(curl, CURLOPT_PROXY_SSL_VERIFYPEER, FALSE);

        curl_easy_setopt(curl, CURLOPT_PROXY_SSL_VERIFYHOST, FALSE);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);

        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; rv:11.0) like Gecko");

        curl_easy_setopt(curl, CURLOPT_VERBOSE, true);

        if (m_bUseProxyAgent) { curl_easy_setopt(curl, CURLOPT_PROXY, "127.0.0.1:8888"); }

        return curl;
    }

    bool _request_throttle_cart2(std::string & sToken) {
        CWriteData wd;
        bool  bError = true;

        auto curl = _init_curl();

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&wd);

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Host: mct.tokyo");
        headers = curl_slist_append(headers, "Connection: keep-alive");
        headers = curl_slist_append(headers, "Upgrade-Insecure-Requests: 1");
        headers = curl_slist_append(headers, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;");
        headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate");
        headers = curl_slist_append(headers, "Referer: https://mct.tokyo/cart");

        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "d:\\123.txt");

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

        std::string surl = "https://mct.tokyo/throttle/queue";
        curl_easy_setopt(curl, CURLOPT_URL, surl.c_str());

        auto cookies = __get_cookie_throttle_cart2(m_cookicMap_resp);
        stringstream sss;
        sss << "Cookie: " << cookies;
        headers = curl_slist_append(headers, sss.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        auto res = curl_easy_perform(curl);

        if (CURLE_OK != res) {
            fprintf(stderr, "curl told us %d\n", res);
            bError = false;
        }
        else
        {

        }

        if (bError)
        {
            wd.GetString(m_sResponse);

            std::map<std::string, std::string>  cMap;
            cookieToMap(curl, cMap);

            auto & stoken = cMap.find("_checkout_queue_token");
            if (stoken != cMap.end())
            {
                auto sv = g_urlC.UrlEncode_GBK(stoken->second);
                sToken = sv;
            }
        }

        curl_easy_cleanup(curl);

        return bError;
    }

    std::string _make_poll_json(std::string & sToken) {
        RAPIDJSON_NAMESPACE::StringBuffer ss;
        RAPIDJSON_NAMESPACE::Writer<RAPIDJSON_NAMESPACE::StringBuffer> writer(ss);
        writer.StartObject();

        writer.Key("query");
        writer.String("\n      {\n        poll(token: $token) {\n          token\n          pollAfter\n          queueEtaSeconds\n          productVariantAvailability {\n            id\n            available\n          }\n        }\n      }\n    ");
        
        writer.Key("variables");
        writer.StartObject();
        writer.Key("token");
        writer.String(sToken.c_str());
        writer.EndObject();

        writer.EndObject();
        return ss.GetString();
    }

    bool _request_poll(std::string & sToken) {
        CWriteData wd;
        bool  bError = true;

        auto curl = _init_curl();

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&wd);

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Host: mct.tokyo");
        headers = curl_slist_append(headers, "Connection: keep-alive");  
        headers = curl_slist_append(headers, "Cache-Control: no-cache");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Accept: */*");
        headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate");
        headers = curl_slist_append(headers, "Referer: https://mct.tokyo/throttle/queue");

        auto sJson = _make_poll_json(sToken);

        int32_t nContentLen = sJson.length();
        stringstream ss;
        ss << "Content-Length: " << nContentLen;
        headers = curl_slist_append(headers, ss.str().c_str());

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        std::string surl = "https://mct.tokyo/queue/poll";
        curl_easy_setopt(curl, CURLOPT_URL, surl.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, sJson.c_str());

        stringstream sss;
        sss << "Cookie: " << __get_cookie_throttle_cart2(m_cookicMap_resp).c_str();
        headers = curl_slist_append(headers, sss.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        auto res = curl_easy_perform(curl);

        if (CURLE_OK != res) {
            fprintf(stderr, "curl told us %d\n", res);
            bError = false;
        }
        else
        {

        }

        if (bError)
        {
            wd.GetString(m_sResponse);
        }

        curl_easy_cleanup(curl);

        return bError;
    }



    void _thread_checking() {

        std::string sToken;
        _request_throttle_cart2(sToken);

        _request_poll(sToken);

    }

    bool OnDecodeResponse(RType rt, std::string & sResponse) {

        if (rt == RType::eCart2)
        {
            if (m_shop_id.empty())
            {
                const char* sf = "<a href=\"https://mct.tokyo/";
                const char* se = "/checkouts/";
                m_shop_id = _FindMidString(sResponse, sf, se);
            }

            if (m_shop_id.empty())
            {
                const char* sf = "<html><body>You are being <a href=\"";
                const char* se = "\">";
                auto sk = _FindMidString(sResponse, sf, se);
                if (sk == "https://mct.tokyo/throttle/queue")
                {
                    m_keepchecking = sk;

                    std::thread thChecking(&CMctRequest::_thread_checking, this);
                    thChecking.detach();
                }
            }

            if (g_cart_sid.empty())
            {
                /*
                <html><body>You are being <a href="https://mct.tokyo/3623944241/checkouts/4eabf50bbf82fb50b5375d97dc76d308">redirected</a>.</body></html>               
                */
                const string sf = m_shop_id + "/checkouts/";
                const char* se = "\">";
                g_cart_sid = _FindMidString(sResponse, sf.c_str(), se);

                if (g_cart_sid.empty())
                {
                    return false;
                }
            }
        }
        
        if (rt == RType::eProduct)
        {
            const char* sss = "\",\"variantId\":";
            const char* se = ",";
            g_sPdciId = _FindMidString(sResponse, sss, se);
            if (g_sPdciId.empty())
            {
                AfxMessageBox(L"貌似商品不存在？");
            }
        }    

        if (rt == RType::eCheckouts)
        {
            auto sval = _FindMidString(sResponse, "name=\"authenticity_token\" value=\"", "\" ");
            if (sval.empty())
            {
                return false;
            }
            m_authenticity_tokenMap[checkouts_step_type::eContact_information] = sval;
        }
        else if (rt == RType::eCheckouts_contact_info)
        {
           
        }
        else if (rt == RType::eCheckouts2)
        {
            auto sval = _FindMidString(sResponse, "name=\"authenticity_token\" value=\"", "\" ");
            if (sval.empty())
            {
                return false;
            }
            m_authenticity_tokenMap[checkouts_step_type::eShipping_method] = sval;
        }
        else if (rt == RType::eCheckouts2_shipping_method)
        {
            m_datashippingmethod = _FindMidString(sResponse, " data-shipping-method=\"", "\">");

            if (!m_authenticity_tokenMap.count(checkouts_step_type::eShipping_method))
            {
                auto sval = _FindMidString(sResponse, "name=\"authenticity_token\" value=\"", "\" ");
                if (sval.empty())
                {
                    return false;
                }
                m_authenticity_tokenMap[checkouts_step_type::eShipping_method] = sval;
            }
        }
        else if (rt == RType::eCheckouts3)
        {
            auto sval = _FindMidString(sResponse, "name=\"authenticity_token\" value=\"", "\" ");
            if (sval.empty())
            {
                return false;
            }
            m_authenticity_tokenMap[checkouts_step_type::ePayment_method] = sval;
        }
        else if (rt == RType::eCheckouts3_payment_method)
        {
            m_data_select_gateway = _FindMidString(sResponse, "data-select-gateway=\"", "\"");  

            m_payment = _FindMidString(sResponse, "data-checkout-payment-due-target=\"", "\"");//" data-checkout-payment-due-target="

            if (!m_authenticity_tokenMap.count(checkouts_step_type::ePayment_method))
            {
                auto sval = _FindMidString(sResponse, "name=\"authenticity_token\" value=\"", "\" ");
                if (sval.empty())
                {
                    return false;
                }
                m_authenticity_tokenMap[checkouts_step_type::ePayment_method] = sval;
            }
        }


        return true;

    }

public:
    void    SetLoginInfo(char* su, char* spsd) {
        m_username = su;
        m_psw = spsd;
    }

    void    SetProductNum(char * sn) {
        m_product_id = sn;
    }

    bool    DoRequest_S_before() {

        CWriteData wd;
        bool  bError = true;

        curl = _init_curl();

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&wd);

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "OPTIONS");

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Access-Control-Request-Method: POST");
        headers = curl_slist_append(headers, "Access-Control-Request-Headers: accept, content-type");
        headers = curl_slist_append(headers, "Accept: */*");
        headers = curl_slist_append(headers, "Origin: https://checkout.shopifycs.com");
        headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate");
        headers = curl_slist_append(headers, "Host: deposit.us.shopifycs.com");
        headers = curl_slist_append(headers, "Connection: Keep-Alive");
        headers = curl_slist_append(headers, "Cache-Control: no-cache");

        std::stringstream ssLen;
        ssLen << "Content-Length: 0";
        headers = curl_slist_append(headers, ssLen.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        std::string surl = "https://deposit.us.shopifycs.com/sessions";
        curl_easy_setopt(curl, CURLOPT_URL, surl.c_str());

        auto res = curl_easy_perform(curl);

        if (CURLE_OK != res) {
            fprintf(stderr, "curl told us %d\n", res);
            bError = false;
        }
        else
        {

        }

        if (bError)
        {
            wd.GetString(m_sResponse);
        }

        curl_easy_cleanup(curl);

        return bError;
    }

    bool    DoRequest_S() {

        CWriteData wd;
        bool  bError = true;

        curl = _init_curl();

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&wd);

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Accept-Language: zh-CN");
        headers = curl_slist_append(headers, "content-type: application/json");
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Origin: https://checkout.shopifycs.com");
        headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate");
        headers = curl_slist_append(headers, "Host: deposit.us.shopifycs.com");
        headers = curl_slist_append(headers, "Connection: Keep-Alive");
        headers = curl_slist_append(headers, "Cache-Control: no-cache"); 

        stringstream sref;
        sref << "https://checkout.shopifycs.com/number?identifier=" << g_cart_sid
            << "&location=" << m_shopfysparam
            << "&dir=ltr";

        std::stringstream ssLen;
        ssLen << "Content-Length: " << strlen(g_card_info_json);
        headers = curl_slist_append(headers, ssLen.str().c_str());

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_REFERER, sref.str().c_str());

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, g_card_info_json);
        
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, 1);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        std::string surl = "https://deposit.us.shopifycs.com/sessions";
        curl_easy_setopt(curl, CURLOPT_URL, surl.c_str());

        auto res = curl_easy_perform(curl);

        if (CURLE_OK != res) {
            fprintf(stderr, "curl told us %d\n", res);
            bError = false;
        }
        else
        {

        }

        if (bError)
        {
            wd.GetString(m_sResponse);
            //{"id":"east-85f2fccf01847d9d246c4573e52af376"}
            const char* sf = "{\"id\":\"";
            const char* se = "\"}";
            g_shopifysessions = _FindMidString(m_sResponse, sf, se);
        }

        curl_easy_cleanup(curl);

        return !g_shopifysessions.empty();
    }

    void    DoRequestEPayInfo() {

        CWriteData wd;
        bool  bError = true;

        curl = _init_curl();

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&wd);

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Accept-Language: zh-CN");
        headers = curl_slist_append(headers, "Origin: https://mct.tokyo");
        headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate");
        headers = curl_slist_append(headers, "Host: payments-fe.amazon.com");
        headers = curl_slist_append(headers, "Connection: Keep-Alive");
        headers = curl_slist_append(headers, "Accept: */*");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_REFERER, "https://mct.tokyo/");

        std::string surl = "https://payments-fe.amazon.com/gp/widgets/sessionstabilizer?countryOfEstablishment=JP&ledgerCurrency=JPY&isSandbox=false";
        curl_easy_setopt(curl, CURLOPT_URL, surl.c_str());

        auto res = curl_easy_perform(curl);

        int rt = 100;
        if (CURLE_OK != res) {
            fprintf(stderr, "curl told us %d\n", res);
            bError = false;
        }
        else
        {
        }

        if (bError)
        {
            wd.GetString(m_sResponse);

            char sPath[260] = { 0 };
            GetModuleFileNameA(nullptr, sPath, 260);

            stringstream ssf;
            ssf << sPath << ".." << (int)rt << ".dat";
            wd.WriteToFile(ssf.str().c_str());


            const char* sf = "{\"apaySessionSet\":\"";
            const char* se = "\"}";
            g_apaySessionSet = _FindMidString(m_sResponse, sf, se);
        }


        curl_easy_cleanup(curl);

    }

    void cookieToMap(CURL * curl, std::map<string, string> & rMap) {
        struct curl_slist* cookies = NULL;
        curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);
        int i = 1;
        while (cookies)
        {
            auto sa = __split_string(CUrlConvert::UTF8ToGBK(cookies->data), '	');
            rMap[sa[5]] = sa.size() > 6 ? sa[6] : "";

            cookies = cookies->next;
            i++;

            if (m_fnAppendMsg)
            {
                std::stringstream ss;
                ss << sa[5] << "=" << rMap[sa[5]] << "\n";
                m_fnAppendMsg->AppendMsg(ss.str());
            }
        }

    }

    bool DoRequest(RType rt) {
        CWriteData wd;
        bool  bError = true;

        curl = _init_curl();

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&wd);

        BuildRequest(rt);

        if (m_ri[(int32_t)rt].rm == RMethod::eGet)
        {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        }
        else
        {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        }

        curl_easy_setopt(curl, CURLOPT_REFERER, BuildReferer(rt).c_str());
 
        std::string surl = BuildUrl(rt);
        curl_easy_setopt(curl, CURLOPT_URL, surl.c_str());

        auto res = curl_easy_perform(curl);

        if (CURLE_OK != res) {
            fprintf(stderr, "curl told us %d\n", res);
            bError = false;
        }
        else
        {
            if (m_fnAppendMsg)
            {
                std::stringstream ss;
                ss << "**** recv--cookies [" << (int32_t)rt << "] :\n";
                m_fnAppendMsg->AppendMsg(ss.str());
            }

            auto& rMap = m_cookicMap_resp[rt];
            cookieToMap(curl, rMap);
        }

        bool bRet = false;
        if (bError)
        {
            wd.GetString(m_sResponse);

            auto ssss = CUrlConvert::UTF8ToGBK(m_sResponse);

            char sPath[260] = { 0 };
            GetModuleFileNameA(nullptr, sPath, 260);

            stringstream ssf;
            ssf << sPath << "\\..\\coo_" << (int)rt << ".dat";
            wd.WriteToFile(ssf.str().c_str());

            bRet = OnDecodeResponse(rt, ssss);
        }


        curl_easy_cleanup(curl);

        return bRet;
   }

    string GetResponse() {
        return m_sResponse;
    }

    void    UseProxyAgent(bool b) {
        m_bUseProxyAgent = b;
    }
private:
    CURL*           curl;

    std::string     m_username = g_username;
    std::string     m_psw = g_userpsd;

    std::string     m_shop_id;      //3623944241
    std::string     m_product_id = "4530956155944";//"4530956593920";
    std::string     m_sResponse;

    std::string     m_keepchecking;

    std::string     m_data_select_gateway;
    std::string     m_payment;

    std::string     m_shopfysparam;

    std::map<checkouts_step_type, std::string>  m_authenticity_tokenMap;
    std::string     m_datashippingmethod;
    std::map<RType, std::map<std::string, std::string>>    m_cookicMap_resp;

    RType           m_lastType = RType::eLogin;
    IReportMsg *  m_fnAppendMsg = nullptr;

    bool            m_bUseProxyAgent = true;


};

