#include "stdafx.h"
#include "RestApi.h"
#include <windows.h>

RestApi::RestApi() {
	Init();
}

RestApi::~RestApi() {
	Cleanup();
}

void RestApi::Init()
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
	m_ssl_file = SSL_FILE;
}

void RestApi::Cleanup()
{
}

size_t curl_cb(void* content, size_t size, size_t nmemb, std::string* buffer)
{
	buffer->append((char*)content, size * nmemb);
	return size * nmemb;
}

void RestApi::CurlApi(string& url, string& result_json) {
	vector <string> v;
	string post_data = "";
	CurlApiWithHeader(url, result_json, v, post_data, ACTION_GET);
}


void RestApi::CurlApiWithHeader(string& url, string& str_result, vector <string>& extra_http_header, string& post_data, REQUEST_ACTION action)
{
	try {
		CURLcode res;
		CURL* m_curl = curl_easy_init();
		if (m_curl) {
			curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, curl_cb);
			curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void*)&str_result);
			curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, false);
			curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, false);
			curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, 5);
			curl_easy_setopt(m_curl, CURLOPT_CAINFO, m_ssl_file.c_str());
			//curl_easy_setopt(m_curl, CURLOPT_SSLVERSION, 1);
			//curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, true);
			//curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1);//可以看到调试信息
			if (extra_http_header.size() > 0) {
				struct curl_slist* chunk = NULL;
				for (int i = 0; i < extra_http_header.size(); i++) {
					chunk = curl_slist_append(chunk, extra_http_header[i].c_str());
				}
				curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, chunk);
			}
			if (post_data.size() > 0 || action == ACTION_POST || action == ACTION_PUT || action == ACTION_DELETE) {
				if (action == ACTION_PUT || action == ACTION_DELETE) {
					if (action == ACTION_PUT) curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "PUT");
					else if (action == ACTION_DELETE) curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "DELETE");
				}
				curl_easy_setopt(m_curl, CURLOPT_POST, 1);
				curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, post_data.c_str());
			}
			res = curl_easy_perform(m_curl);

			std::string log = "";
			log.append(" res_code:").append(std::to_string(res));
			log.append(" url:").append(url);
			log.append(" request:").append(post_data);
			log.append(" response:").append(str_result);
			ExtLogger.server(log);
		}
		else {
			std::string log = "curl is null,";
			log.append(" url:").append(url);
			ExtLogger.error(log);
		}
		curl_easy_cleanup(m_curl);
	}
	catch (...) {
		ExtLogger.error("curl_api_with_header exception.");
	}
}

std::string RestApi::GetRequest(std::string token, std::string url) {
	vector <string> extra_http_header;
	string header_chunk("Content-Type: application/json");
	extra_http_header.push_back(header_chunk);
	string token_header("X-API-TOKEN: "); token_header.append(token);
	extra_http_header.push_back(token_header);
	string post_data = "", str_result = "";
	CurlApiWithHeader(url, str_result, extra_http_header, post_data, ACTION_GET);
	return str_result;
}

std::string RestApi::DeleteRequest(std::string token, std::string url) {

}

//------------------
//GET api/v1/Login
//------------------
bool RestApi::Login(const std::string& loginId, const std::string& password, LoginResponse& response)
{
	try {
		string url(HOST_URL); url += "/api/v1/apiLogin";
		auto timeNow = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
		string post_data("{ \"loginId\": \"" + loginId + "\", \"password\": \"" + password + "\", \"captcha\": \"\", \"id\": \"" + std::to_string(timeNow.count()) + "\"}");
		vector <string> extra_http_header;
		string header_chunk("Content-Type: application/json");
		extra_http_header.push_back(header_chunk);
		string str_result = "";
		CurlApiWithHeader(url, str_result, extra_http_header, post_data, ACTION_POST);
		if (str_result.size() > 0) {
			Json::Value json_result;
			Json::Reader reader;
			reader.parse(str_result, json_result);
			return response.Parse(json_result);
		}
	}
	catch (exception& e) {
		ExtLogger.error("<Restful::login> exception.");
	}
	return false;
}

bool RestApi::Logout(bool force) {
	try {
		string url(HOST_URL); url += "/api/v1/apiLogin";
		std::string param = (force ? "true" : "false");
		string post_data("{ \"force\": " + param + "}");
		vector <string> extra_http_header;
		string header_chunk("Content-Type: application/json");
		extra_http_header.push_back(header_chunk);
		string str_result = "";
		CurlApiWithHeader(url, str_result, extra_http_header, post_data, ACTION_POST);
		if (str_result.size() > 0) {
			Json::Value json_result;
			Json::Reader reader;
			reader.parse(str_result, json_result);
			if (json_result.isMember("data")) {
				return true;
			}
		}
	}
	catch (exception& e) {
		ExtLogger.error("<Restful::login> exception.");
	}
	return false;
}

bool RestApi::GetContract(const std::string& token, std::string& response) {
	try {
		string url(HOST_URL);
		url += "/api/v1/market/contract";
		response = GetRequest(token, url);
	}
	catch (exception& e) {
		ExtLogger.error("<Restful::GetContract> exception.");
	}
	return false;
}

void RestApi::Ping(const std::string& token, std::string cookie, std::string& response) {
	try {
		auto now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());

		string url(HOST_URL);
		url += "/api/v1/ping";
		vector <string> extra_http_header;
		string header_chunk("Content-Type: application/json");
		extra_http_header.push_back(header_chunk);
		string token_header("X-API-TOKEN:"); token_header.append(token);
		extra_http_header.push_back(token_header);

		string post_data = "{\"id\":\"" + std::to_string(now.count()) + "\",\"cookie\":\"" + cookie + "\",\"action\":\"PING\"}", str_result = "";
		CurlApiWithHeader(url, str_result, extra_http_header, post_data, ACTION_POST);
	}
	catch (exception& e) {
		ExtLogger.error("<Restful::Ping> exception.");
	}
}


void RestApi::QueryBaseCurrency(const std::string& token, std::string& response) {
	string url(HOST_URL);
	url += "/api/v1/market/baseCurrency";
	response = GetRequest(token, url);
}

void RestApi::QueryContract(const std::string& token, std::string& response) {
	string url(HOST_URL);
	url += "/api/v1/market/contract";
	response = GetRequest(token, url);
}

void RestApi::QueryCurrency(const std::string& token, std::string& response) {
	string url(HOST_URL);
	url += "/api/v1/market/currency";
	response = GetRequest(token, url);
}

void RestApi::QueryCurrencyPair(const std::string& token, std::string& response) {
	string url(HOST_URL);
	url += "/api/v1/market/currencyPair";
	response = GetRequest(token, url);
}

void RestApi::QueryInstitution(const std::string& token, std::string& response) {
	string url(HOST_URL);
	url += "/api/v1/market/institution";
	response = GetRequest(token, url);
}

void RestApi::QueryInstrumentContract(const std::string& token, int instrumentId, std::string& response) {
	string url(HOST_URL);
	url += "/api/v1/market/instrumentContract?instrumentId=" + instrumentId;
	response = GetRequest(token, url);
}

void RestApi::QueryItInstrument(const std::string& token, std::string& response) {
	string url(HOST_URL);
	url += "/api/v1/market/itInstrument";
	response = GetRequest(token, url);
}

void RestApi::QueryMainContract(const std::string& token, std::string& response) {
	string url(HOST_URL);
	url += "/api/v1/market/mainContract";
	response = GetRequest(token, url);
}

void RestApi::QueryMajorContract(const std::string& token, std::string& response) {
	string url(HOST_URL);
	url += "/api/v1/market/majorContract";
	response = GetRequest(token, url);
}

void RestApi::IteratorCashflow(const std::string& token, std::string& response) {
	string url(HOST_URL);
	url += "/api/v1/trading/cashflow/iterator";
	response = GetRequest(token, url);
}

void RestApi::IteratorExecution(const std::string& token, std::string& response) {
	string url(HOST_URL);
	url += "/api/v1/trading/execution/iterator";
	response = GetRequest(token, url);
}

void RestApi::TodaysExecution(const std::string& token, std::string& response) {
	string url(HOST_URL);
	url += "/api/v1/trading/execution/todays";
	response = GetRequest(token, url);
}

void RestApi::QueryPosition(const std::string& token, std::string& response) {
	string url(HOST_URL);
	url += "/api/v1/trading/position";
	response = GetRequest(token, url);
}


void RestApi::ClearOrder(const std::string& token, std::string& response) {
	string url(HOST_URL);
	url += "/api/v1/trading/order/clear";

	string post_data = "";
	vector <string> extra_http_header;
	string header_chunk("Content-Type: application/json");
	extra_http_header.push_back(header_chunk);
	string token_header("X-API-TOKEN:"); token_header.append(token);
	extra_http_header.push_back(token_header);
	CurlApiWithHeader(url, response, extra_http_header, post_data, ACTION_DELETE);
}

void RestApi::PlaceOrder(const std::string& token, PlaceOrderRequest request, std::string& response) {
	string url(HOST_URL);
	url += "/api/v1/trading/order";

	auto timeNow = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
	string post_data = "{\"contractId\":" + std::to_string(request.contractId) + ",\"orderType\":" + std::to_string(request.orderType) + ",\"orderPrice\":\"" + request.orderPrice + "\",\"tpPrice\":\"" + request.tpPrice + "\",\"slPrice\":\"" + request.slPrice + "\",\"closeTpAmount\":\"" + request.closeTpAmount + "\",\"closeSlAmount\":\"" + request.closeSlAmount + "\",\"trailAmount\":\"" + request.trailAmount + "\",\"orderLot\":" + std::to_string(request.orderLot) + ",\"tradeType\":" + std::to_string(request.tradeType) + ",\"expireType\":" + std::to_string(request.expireType) + ",\"side\":" + std::to_string(request.side) + ",\"clientAccountId\":\"" + request.clientAccountId + "\",\"clientOrderId\":\"" + request.clientOrderId + "\"}";
	vector <string> extra_http_header;
	string header_chunk("Content-Type: application/json");
	extra_http_header.push_back(header_chunk);
	string token_header("X-API-TOKEN:"); token_header.append(token);
	extra_http_header.push_back(token_header);
	CurlApiWithHeader(url, response, extra_http_header, post_data, ACTION_POST);
}

void RestApi::ModifyOrder(const std::string& token, std::string orderId, ModifyOrderRequest request, std::string& response) {
	string url(HOST_URL);
	url += "/api/v1/trading/order/" + orderId;

	auto timeNow = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
	string post_data = "{\"orderPrice\":\"" + request.orderPrice + "\",\"tpPrice\":\"" + request.tpPrice + "\",\"slPrice\":\"" + request.tpPrice + "\",\"closeTpAmount\":\"" + request.closeTpAmount + "\",\"closeSlAmount\":\"" + request.closeSlAmount + "\",\"trailAmount\":\"" + request.trailAmount + "\",\"orderLot\":" + std::to_string(request.orderLot) + "}";
	vector <string> extra_http_header;
	string header_chunk("Content-Type: application/json");
	extra_http_header.push_back(header_chunk);
	string token_header("X-API-TOKEN:"); token_header.append(token);
	extra_http_header.push_back(token_header);
	CurlApiWithHeader(url, response, extra_http_header, post_data, ACTION_PUT);
}

void RestApi::CancelOrder(const std::string& token, std::string orderId, std::string& response) {
	string url(HOST_URL);
	url += "/api/v1/trading/order/" + orderId;

	string post_data = "";
	vector <string> extra_http_header;
	string header_chunk("Content-Type: application/json");
	extra_http_header.push_back(header_chunk);
	string token_header("X-API-TOKEN:"); token_header.append(token);
	extra_http_header.push_back(token_header);
	CurlApiWithHeader(url, response, extra_http_header, post_data, ACTION_DELETE);
}
