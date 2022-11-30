#include "stdafx.h"
#include "RestApi.h"
#include "Websocket.h"
#include "WebSocketEventSession.h"

/*
*
* pro doc:https://swagger.ayson.us/v1/
*
* dev account:yy01
* dev password:000000
*/

int wmain(int argc, wchar_t** argv)
{
	std::string account = "yy01";
	std::string password = "000000";

	//rest api
	std::shared_ptr<RestApi> restapi = std::make_shared<RestApi>();
	//login
	LoginResponse login_response = {};
	restapi->Login(account.c_str(), password.c_str(), login_response);
	//
	std::string response = "";
	restapi->GetContract(login_response.token, response);
	restapi->Ping(login_response.token, "cookie", response);
	restapi->QueryBaseCurrency(login_response.token, response);
	restapi->QueryContract(login_response.token, response);
	restapi->QueryCurrency(login_response.token, response);
	restapi->QueryCurrencyPair(login_response.token, response);
	restapi->QueryInstitution(login_response.token, response);
	restapi->QueryInstrumentContract(login_response.token, 1, response);
	restapi->QueryItInstrument(login_response.token, response);
	restapi->QueryMainContract(login_response.token, response);
	restapi->QueryMajorContract(login_response.token, response);
	restapi->IteratorCashflow(login_response.token, response);
	restapi->IteratorExecution(login_response.token, response);
	restapi->TodaysExecution(login_response.token, response);
	restapi->QueryPosition(login_response.token, response);

	int contractId = 395528;
	PlaceOrderRequest place_request;
	place_request.contractId = contractId;
	place_request.expireType = 4;
	place_request.orderLot = 1;
	place_request.orderPrice = "1";
	place_request.orderType = 3;
	place_request.side = 1;
	place_request.tradeType = 1;
	restapi->PlaceOrder(login_response.token, place_request, response);

	std::string orderId = "1820461365220823093";
	//modify
	ModifyOrderRequest modify_request;
	modify_request.orderLot = 1;
	modify_request.orderPrice = "4";
	restapi->ModifyOrder(login_response.token, orderId, modify_request, response);

	//cancel
	restapi->CancelOrder(login_response.token, orderId, response);
	restapi->ClearOrder(login_response.token, response);

	//websocket
	WebSocketEventSession session;
	std::shared_ptr<Websocket> web_socket = std::make_shared<Websocket>();
	web_socket->m_close_function = std::bind(&WebSocketEventSession::OnFrontDisconnected, session);
	web_socket->m_open_function = std::bind(&WebSocketEventSession::OnApiReady, session);
	web_socket->m_msg_function = std::bind(&WebSocketEventSession::OnMessage, session, std::placeholders::_1);
	web_socket->Init();
	web_socket->Connect(login_response.token);
	web_socket->SubscribeDepth(contractId);
	web_socket->SubscribeTick(contractId);
	web_socket->SubscribeExecution();
	web_socket->SubscribeOrder();
	web_socket->SubscribePosition();
	web_socket->EnterEventLoop();

	system("pause");
	return(0);
}

//---
Websocket ExtWebsocket;
CppLogger ExtLogger;
