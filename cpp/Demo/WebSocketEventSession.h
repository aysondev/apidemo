#pragma once

#include "stdafx.h"
#include "RestApi.h"
#include "Websocket.h"

//+------------------------------------------------------------------+
//| Class of Quote gateway                                           |
//+------------------------------------------------------------------+

class WebSocketEventSession : public std::enable_shared_from_this<WebSocketEventSession>
{
public:

	WebSocketEventSession();
	~WebSocketEventSession();

	virtual void OnFrontDisconnected();
	virtual void OnApiReady();
	virtual void OnMessage(Json::Value json);
};
