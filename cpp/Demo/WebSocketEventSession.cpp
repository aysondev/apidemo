#include "stdafx.h"
#include "WebSocketEventSession.h"

WebSocketEventSession::WebSocketEventSession() {}

WebSocketEventSession::~WebSocketEventSession() {}

void WebSocketEventSession::OnFrontDisconnected()
{
	ExtLogger.server("OnFrontDisconnected");
};

void WebSocketEventSession::OnApiReady()
{
	ExtLogger.server("OnApiReady");
}

void WebSocketEventSession::OnMessage(Json::Value json)
{
	//通过该接口分发事件
	if (json["action"] == "PING") return;

	std::string action = "";
	std::string event = "";
	if (json.isMember("event")) event = json["event"].asString();
	if (json.isMember("action")) action = json["action"].asString();

	if (event == "ORDER" || event == "POSITION" || event == "EXECUTION")
	{
		ExtLogger.server("websocket: event:" + json["event"].asString() + " action:" + json["action"].asString() + " data:" + json.toStyledString());
	}
	else {
		ExtLogger.server("websocket: event:" + json["event"].asString());
	}
}