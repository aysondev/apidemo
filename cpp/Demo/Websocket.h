#pragma once

#include "stdafx.h"
#include "json/json.h"
#include  <libwebsockets.h>

#define PING_INTERVAL 7
#define REALTIME_URL "/api/v1/realtime"
const int WS_RECV_BUF_SIZE = 4096 * 100;

using namespace std;
typedef int(*CB)(Json::Value& json_value);
const int WS_SEND_BUF_SIZE = 1024 * 64;


typedef std::function<void()> _OnClose;
typedef std::function<void()> _OnOpen;
typedef std::function<void(Json::Value json)> _OnMsg;

class Websocket :public std::enable_shared_from_this<Websocket> {
private:
	std::recursive_mutex _lock;
	void WebsocketSendMessage(const std::string& json);
	bool ConnectEndpoint(std::string path, std::string token);
	void Ping();

public:
	std::string m_token ="";
	lws_context* m_context = nullptr;
	struct lws* m_wsi = nullptr;
	bool m_connected = false;
	std::queue<string> m_request;
	_OnClose m_close_function = nullptr;
	_OnOpen m_open_function = nullptr;
	_OnMsg m_msg_function = nullptr;

	Websocket();
	~Websocket();


	bool Connect(const std::string& token);
	bool Init();

	void SubscribeTick(int contractId);
	void UnsubscribeTick(int contractId);

	void SubscribeDepth(int contractId);
	void UnsubscribeeDepth(int contractId);

	void SubscribePosition();
	void UnsubscribePosition();

	void SubscribeExecution();
	void UnsubscribeExecution();

	void SubscribeOrder();
	void UnsubscribeOrder();

	void EnterEventLoop();
	void Shutdown();

	void WsOnOpen();
	void WsOnClose();
	void WsOnMsg(Json::Value json);
};
