#pragma once

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <exception>
#include "curl/curl.h"
#include "json/json.h"
using namespace std;


enum REQUEST_ACTION
{
	ACTION_GET = 0,
	ACTION_POST = 1,
	ACTION_DELETE = 2,
	ACTION_PUT = 3,
};


class LoginResponse {
public:
	std::string result;
	std::string token;
	std::string accountId;

	LoginResponse() {
		result = "";
		token = "";
		accountId = "";
	}

	bool Parse(Json::Value json) {
		if (json.isMember("data")) {
			Json::Value values = json["data"];
			if (values.isMember("result")) {
				result = values["result"].asString();
			}
			if (values.isMember("token")) {
				token = values["token"].asString();
			}
			if (values.isMember("loginId")) {
				accountId = values["loginId"].asString();
			}
			return true;
		}
		return false;
	}
};

typedef struct
{
	int contractId;
	int orderType;
	std::string orderPrice;
	std::string tpPrice;
	std::string slPrice;
	std::string closeTpAmount;
	std::string closeSlAmount;
	std::string trailAmount;
	int orderLot;
	int tradeType;
	int expireType;
	int side;
	std::string clientAccountId;
	std::string clientOrderId;
}PlaceOrderRequest;

typedef struct
{
	std::string orderPrice;
	std::string tpPrice;
	std::string slPrice;
	std::string closeTpAmount;
	std::string closeSlAmount;
	std::string trailAmount;
	int orderLot;
}ModifyOrderRequest;

class RestApi {
private:
	string m_ssl_file = SSL_FILE;
	std::string m_token = "";

	std::string GetRequest(std::string token, std::string url);
	std::string DeleteRequest(std::string token, std::string url);

public:
	RestApi();
	~RestApi();

	void CurlApi(string& url, string& result_json);
	void CurlApiWithHeader(string& url, string& result_json, vector <string>& extra_http_header, string& post_data, REQUEST_ACTION action);
	void Init();
	void Cleanup();

	//
	bool Login(const std::string& loginId, const std::string& password, LoginResponse& response);
	bool Logout(bool force);
	//
	bool GetContract(const std::string& token, std::string& response);
	void Ping(const std::string& token, std::string cookie, std::string& response);
	void QueryBaseCurrency(const std::string& token, std::string& response);
	void QueryContract(const std::string& token, std::string& response);
	void QueryCurrency(const std::string& token, std::string& response);
	void QueryCurrencyPair(const std::string& token, std::string& response);
	void QueryInstitution(const std::string& token, std::string& response);
	void QueryInstrumentContract(const std::string& token, int instrumentId, std::string& response);
	void QueryItInstrument(const std::string& token, std::string& response);
	void QueryMainContract(const std::string& token, std::string& response);
	void QueryMajorContract(const std::string& token, std::string& response);
	void IteratorCashflow(const std::string& token, std::string& response);
	void IteratorExecution(const std::string& token, std::string& response);
	void TodaysExecution(const std::string& token, std::string& response);
	void QueryPosition(const std::string& token, std::string& response);
	void PlaceOrder(const std::string& token, PlaceOrderRequest request, std::string& response);
	void ModifyOrder(const std::string& token, std::string orderId, ModifyOrderRequest request, std::string& response);
	void CancelOrder(const std::string& token, std::string orderId,std::string& response);
	void ClearOrder(const std::string& token, std::string& response);
};
