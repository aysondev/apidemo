package com.krampus.apidemo.ws;

import com.krampus.apidemo.common.Consts;
import com.krampus.apidemo.rest.RestServiceImpl;

import javax.websocket.ClientEndpointConfig;
import javax.websocket.ContainerProvider;
import javax.websocket.Session;
import javax.websocket.WebSocketContainer;
import java.net.URI;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class WsDemo {
    private static String uri = "wss://" + Consts.HOST + "/api/v1/realtime";

    public static void main(String[] args) throws Exception {
        //
        RestServiceImpl service = new RestServiceImpl();
        String token = service.getToken("yy01", "000000");
        ClientEndpointConfig.Builder configBuilder = ClientEndpointConfig.Builder.create();
        configBuilder.configurator(new ClientEndpointConfig.Configurator() {
            @Override
            public void beforeRequest(Map<String, List<String>> headers) {
                ArrayList<String> value = new ArrayList<>();
                value.add("X-API-TOKEN=" + token);
                headers.put("Cookie", value);
            }
        });
        ClientEndpointConfig clientConfig = configBuilder.build();
        WebSocketContainer container = ContainerProvider.getWebSocketContainer();
        Session session = container.connectToServer(WsDemoEndpoint.class, clientConfig, URI.create(uri));
        //
        String contractId = "395528";
        String requestId = String.valueOf(System.currentTimeMillis());
        session.getBasicRemote().sendText("{\"id\":\"" + requestId + "\",\"event\":\"EXECUTION\",\"action\":\"SUBSCRIBE\",\"snapshot\":\"NOP\"}");
        //
        session.getBasicRemote().sendText("{\"action\":\"SUBSCRIBE\",\"event\":\"POSITION\",\"id\":\"" + requestId + "\",\"snapshot\":\"NOP\"}");
        //
        session.getBasicRemote().sendText("{\"action\":\"SUBSCRIBE\",\"event\":\"ORDER\",\"id\":\"" + requestId + "\",\"snapshot\":\"NOP\"}");
        //
        session.getBasicRemote().sendText("{\"action\":\"SUBSCRIBE\",\"contractId\":" + contractId + ",\"event\":\"TICK\",\"id\":\"" + requestId + "\",\"snapshot\":\"NOP\"}");
        //
        session.getBasicRemote().sendText("{\"action\":\"SUBSCRIBE\",\"contractId\":" + contractId + ",\"event\":\"DEPTH\",\"id\":\"" + requestId + "\",\"snapshot\":\"NOP\"}");
        //
        //session.getBasicRemote().sendText("{\"action\":\"UNSUBSCRIBE\",\"contractId\":" + contractId + ",\"event\":\"DEPTH\",\"id\":\"" + requestId + "\"}");
        //
        //session.getBasicRemote().sendText("{\"action\":\"UNSUBSCRIBE\",\"contractId\":" + contractId + ",\"event\":\"TICK\",\"id\":\"" + requestId + "\"}");
        //
        //session.getBasicRemote().sendText("{\"action\":\"UNSUBSCRIBE\",\"event\":\"ORDER\",\"id\":\"" + requestId + "\"}");
        //
        //session.getBasicRemote().sendText("{\"action\":\"UNSUBSCRIBE\",\"event\":\"POSITION\",\"id\":\"" + requestId + "\"}");
        //
        //session.getBasicRemote().sendText("{\"id\":\"" + requestId + "\",\"event\":\"EXECUTION\",\"action\":\"UNSUBSCRIBE\"}");
        while(true){
            session.getBasicRemote().sendText("{\"action\":\"PING\", \"id\" : \"" + requestId + "\"}");
            Thread.sleep(10000);
        }
    }
}