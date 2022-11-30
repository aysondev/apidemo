#include "stdafx.h"
#include "Websocket.h"

Websocket::Websocket() : m_wsi(nullptr), m_context(nullptr) {}

Websocket::~Websocket() {
	Shutdown();
}

//--------------------------
static int callback(struct lws* wsi, enum lws_callback_reasons reason, void* user, void* in, size_t len)
{
	Websocket* websocket = (Websocket*)user;
	try {
		switch (reason)
		{
		case LWS_CALLBACK_CLIENT_ESTABLISHED: {
			if (websocket != nullptr && websocket->m_open_function != nullptr) websocket->m_open_function();
			lws_callback_on_writable(wsi);
			break;
		}
		case LWS_CALLBACK_CLIENT_RECEIVE: {
			try {
				string data(string((char*)in));
				Json::Reader reader;
				Json::Value json_value;
				reader.parse(data, json_value);
				if (websocket != nullptr && websocket->m_msg_function != nullptr) websocket->m_msg_function(json_value);
				lws_callback_on_writable(wsi);
			}
			catch (exception& e) {
				ExtLogger.error("m_websocket exception.");
			}
			break;
		}
		case LWS_CALLBACK_CLIENT_WRITEABLE:
		{
			while (websocket != nullptr && websocket->m_request.size() > 0) {

				uint8_t buf[LWS_PRE + WS_SEND_BUF_SIZE] = { 0 };
				int n = lws_snprintf((char*)buf + LWS_PRE, WS_SEND_BUF_SIZE, "%s", websocket->m_request.front().c_str());
				lws_write(wsi, buf + LWS_PRE, n, LWS_WRITE_TEXT);
				websocket->m_request.pop();
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
			lws_callback_on_writable(wsi);
			break;
		}
		case LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER: {
			string token_header("X-API-TOKEN:"); token_header.append(websocket->m_token).append("\x0d\x0a");
			char** p = (char**)in;
			*p += sprintf(*p, token_header.c_str());
			break;
		}
		case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
		case LWS_CALLBACK_WS_CLIENT_DROP_PROTOCOL:
		case LWS_CALLBACK_CLOSED:
		case LWS_CALLBACK_CLIENT_CLOSED: {

			std::stringstream ss;
			ss.str("");
			ss << "ws_callback close.";
			ss << "reason:" << reason;;
			ExtLogger.error(ss.str());

			if (websocket != nullptr) {
				if (websocket->m_close_function != nullptr) websocket->m_close_function();
				websocket->m_connected = false;
			}
			lws_cancel_service(lws_get_context(wsi));
			break;
		}
		default:
			std::stringstream ss;
			ss.str("");
			ss << "ws_callback debug";
			ss << "reason:" << reason;
			ExtLogger.server(ss.str());
			break;
		}
	}
	catch (...) {
		ExtLogger.error("m_websocket exception !");

		if (websocket != nullptr) {
			if (websocket->m_close_function != nullptr) websocket->m_close_function();
			websocket->m_connected = false;
		}
		lws_cancel_service(lws_get_context(wsi));
	}
	return 0;
}

struct lws_protocols protocols[] =
{
	{
		"m_websocket",callback,0,WS_RECV_BUF_SIZE,
	},
	{ NULL, NULL, 0, 0 }
};

//-------------------
bool Websocket::Init()
{

	m_connected = true;
	struct lws_context_creation_info info;
	memset(&info, 0, sizeof(info));
	info.port = CONTEXT_PORT_NO_LISTEN;
	info.protocols = protocols;
	info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
	info.ssl_ca_filepath = SSL_FILE;
	info.ssl_cert_filepath = NULL;
	info.ssl_private_key_filepath = NULL;
	info.fd_limit_per_thread = 3;
	/*
	if (proxy_address != "") {
		info.http_proxy_address = proxy_address.c_str();
		info.http_proxy_port = proxy_port;
	}
	*/
	m_context = lws_create_context(&info);
	if (!m_context)
	{
		std::stringstream ss;
		ss.str("");
		ss << "lws_create_context error.";
		ExtLogger.error(ss.str());
		m_connected = false;
	}
	return m_connected;
}

void Websocket::WebsocketSendMessage(const std::string& json)
{
	m_request.push(json);
	if (m_wsi != nullptr) lws_callback_on_writable(m_wsi);
}

//----------------------------
// Register call backs
bool Websocket::ConnectEndpoint(std::string path, std::string token)
{
	try {
		m_token = token;
		struct lws_client_connect_info ccinfo = { 0 };
		ccinfo.context = m_context;
		ccinfo.address = WSS_HOST;
		ccinfo.port = WSS_PORT;
		ccinfo.host = WSS_HOST;
		ccinfo.origin = WSS_HOST;
		ccinfo.path = path.c_str();
		ccinfo.protocol = "m_websocket";
		ccinfo.userdata = shared_from_this().get();
		ccinfo.ssl_connection = LCCSCF_USE_SSL | LCCSCF_ALLOW_SELFSIGNED | LCCSCF_SKIP_SERVER_CERT_HOSTNAME_CHECK;
		m_wsi = lws_client_connect_via_info(&ccinfo);
		if (!m_wsi)
		{
			std::stringstream ss;
			ss.str("");
			ss << "lws_client_connect_via_info error.";
			ExtLogger.error(ss.str());
			m_connected = false;
		}
	}
	catch (...) {
		ExtLogger.error("ConnectEndpoint exception.");
		m_connected = false;
	}
	return m_connected;
}


//----------------------------
// Entering event loop
void Websocket::EnterEventLoop()
{
	time_t current_time = time(NULL);
	while (m_connected)
	{
		try {
			if (time(NULL) - current_time > PING_INTERVAL) {
				Ping();
				current_time = time(NULL);
			}
			lws_service(m_context, 0);
		}
		catch (exception& e) {
			m_connected = false;
			ExtLogger.error("EnterEventLoop exception.");
			break;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	Shutdown();
}

void Websocket::Shutdown() {
	std::lock_guard<std::recursive_mutex> lock(_lock);
	ExtLogger.error("WebsocketEvent Shutdown!");
	m_connected = false;
	m_wsi = nullptr;
	if (m_context != nullptr) {
		lws_context_destroy(m_context);
		m_context = nullptr;
	}
}

bool Websocket::Connect(const std::string& token) {
	return ConnectEndpoint(REALTIME_URL, token);
}

void Websocket::SubscribeExecution() {
	auto now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
	std::string json = "{\"id\":\"" + std::to_string(now.count()) + "\",\"event\":\"EXECUTION\",\"action\":\"SUBSCRIBE\",\"snapshot\":\"NOP\"}";
	WebsocketSendMessage(json.c_str());
}
void Websocket::UnsubscribeExecution() {
	auto now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
	std::string json = "{\"id\":\"" + std::to_string(now.count()) + "\",\"event\":\"EXECUTION\",\"action\":\"UNSUBSCRIBE\"}";
	WebsocketSendMessage(json.c_str());
}

void Websocket::SubscribePosition() {
	auto now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
	std::string json = "{\"action\":\"SUBSCRIBE\",\"event\":\"POSITION\",\"id\":\"" + std::to_string(now.count()) + "\",\"snapshot\":\"NOP\"}";
	WebsocketSendMessage(json.c_str());
}
void Websocket::UnsubscribePosition() {
	auto now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
	std::string json = "{\"action\":\"UNSUBSCRIBE\",\"event\":\"POSITION\",\"id\":\"" + std::to_string(now.count()) + "\"}";
	WebsocketSendMessage(json.c_str());
}

void Websocket::SubscribeOrder() {
	auto now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
	std::string json = "{\"action\":\"SUBSCRIBE\",\"event\":\"ORDER\",\"id\":\"" + std::to_string(now.count()) + "\",\"snapshot\":\"NOP\"}";
	WebsocketSendMessage(json.c_str());
}
void Websocket::UnsubscribeOrder() {
	auto now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
	std::string json = "{\"action\":\"UNSUBSCRIBE\",\"event\":\"ORDER\",\"id\":\"" + std::to_string(now.count()) + "\"}";
	WebsocketSendMessage(json.c_str());
}

void Websocket::SubscribeTick(int contractId) {
	auto now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
	std::string json = "{\"action\":\"SUBSCRIBE\",\"contractId\":" + std::to_string(contractId) + ",\"event\":\"TICK\",\"id\":\"" + std::to_string(now.count()) + "\",\"snapshot\":\"NOP\"}";
	WebsocketSendMessage(json.c_str());
}

void Websocket::UnsubscribeTick(int contractId) {
	auto now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
	std::string json = "{\"action\":\"UNSUBSCRIBE\",\"contractId\":" + std::to_string(contractId) + ",\"event\":\"TICK\",\"id\":\"" + std::to_string(now.count()) + "\"}";
	WebsocketSendMessage(json.c_str());
}


void Websocket::SubscribeDepth(int contractId) {
	auto now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
	std::string json = "{\"action\":\"SUBSCRIBE\",\"contractId\":" + std::to_string(contractId) + ",\"event\":\"DEPTH\",\"id\":\"" + std::to_string(now.count()) + "\",\"snapshot\":\"NOP\"}";
	WebsocketSendMessage(json.c_str());
}

void Websocket::UnsubscribeeDepth(int contractId) {
	auto now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
	std::string json = "{\"action\":\"UNSUBSCRIBE\",\"contractId\":" + std::to_string(contractId) + ",\"event\":\"DEPTH\",\"id\":\"" + std::to_string(now.count()) + "\"}";
	WebsocketSendMessage(json.c_str());
}

void Websocket::Ping() {
	auto now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
	std::string json = "{\"action\":\"PING\", \"id\" : \"" + std::to_string(now.count()) + "\"}";
	WebsocketSendMessage(json.c_str());
}

void Websocket::WsOnOpen() {
	if (m_open_function) m_open_function();
}

void Websocket::WsOnClose() {
	if (m_close_function) m_close_function();
}

void Websocket::WsOnMsg(Json::Value json) {
	if (m_msg_function) m_msg_function(json);
}