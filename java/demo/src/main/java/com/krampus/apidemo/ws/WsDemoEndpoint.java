package com.krampus.apidemo.ws;

import javax.websocket.*;
public class WsDemoEndpoint extends Endpoint {

	@Override
	public void onOpen(Session session, EndpointConfig endpointConfig) {
		final Session mySession = session;
		mySession.addMessageHandler(new MessageHandler.Whole<String>() {
			@Override
			public void onMessage(String text) {
				System.out.println(String.format("Session[%s] client onMessage: [%s]", session, text));
			}
		});
	}

	@Override
	public void onClose(Session session, CloseReason closeReason) {
		System.out.println(String.format("Session[%s] is closed. ref: [%s]", session, closeReason));
	}

	@Override
	public void onError(Session session, Throwable thr) {
		System.out.println(String.format("Session[%s] error", session));
	}
}