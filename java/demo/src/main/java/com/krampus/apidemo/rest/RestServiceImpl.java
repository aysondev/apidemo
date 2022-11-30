package com.krampus.apidemo.rest;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.krampus.apidemo.common.ModifyRequest;
import com.krampus.apidemo.common.PlaceRequest;
import org.apache.commons.io.IOUtils;

import javax.net.ssl.HttpsURLConnection;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Map;

import static com.krampus.apidemo.common.Consts.HOST;
public class RestServiceImpl {
    private static final String PREFIX = "https://" + HOST;
    private static final ObjectMapper mapper = new ObjectMapper();
    @SuppressWarnings("rawtypes")
    public String getToken(String loginId, String password) throws IOException {
        String json = this.login(loginId, password);
        Map readValue = mapper.readValue(json, Map.class);
        return (String) ((Map) readValue.get("data")).get("token");
    }


    public String login(String loginId, String password) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/apiLogin");
        String param ="{ \"loginId\": \"" + loginId + "\", \"password\": \"" + password + "\", \"captcha\": \"\", \"id\": \"" + System.currentTimeMillis() + "\"}";
        HttpsURLConnection con = (HttpsURLConnection) url.openConnection();
        con.setRequestMethod("POST");
        con.setRequestProperty("Content-Type", "application/json");
        con.setDoOutput(true);
        IOUtils.write(param, con.getOutputStream(), "utf8");
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    public String logout(boolean force) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/apiLogin");
        String param ="{ \"force\": " + force + "}";
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("POST");
        con.setRequestProperty("Content-Type", "application/json");
        con.setDoOutput(true);
        IOUtils.write(param, con.getOutputStream(), "utf8");
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String getContract(String token) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/market/contract");
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");
        con.setRequestProperty("X-API-TOKEN", token);
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String ping(String token, String cookie) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/ping");
        String param ="{\"id\":\"" + System.currentTimeMillis() + "\",\"cookie\":\"" + cookie + "\",\"action\":\"PING\"}";
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("POST");
        con.setRequestProperty("Content-Type", "application/json");
        con.setRequestProperty("X-API-TOKEN", token);
        con.setDoOutput(true);
        IOUtils.write(param, con.getOutputStream(), "utf8");
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String queryBaseCurrency(String token) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/market/baseCurrency");
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");
        con.setRequestProperty("X-API-TOKEN", token);
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String queryContract(String token) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/market/contract");
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");
        con.setRequestProperty("X-API-TOKEN", token);
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String queryCurrency(String token) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/market/currency");
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");
        con.setRequestProperty("X-API-TOKEN", token);
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String queryCurrencyPair(String token) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/market/currencyPair");
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");
        con.setRequestProperty("X-API-TOKEN", token);
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String queryInstitution(String token) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/market/institution");
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");
        con.setRequestProperty("X-API-TOKEN", token);
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String queryInstrumentContract(String token,int instrumentId) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/market/instrumentContract?instrumentId=" + instrumentId);
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");
        con.setRequestProperty("X-API-TOKEN", token);
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String queryItInstrument(String token) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/market/itInstrument");
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");
        con.setRequestProperty("X-API-TOKEN", token);
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String queryMainContract(String token) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/market/mainContract");
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");
        con.setRequestProperty("X-API-TOKEN", token);
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String queryMajorContract(String token) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/market/majorContract");
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");
        con.setRequestProperty("X-API-TOKEN", token);
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String iteratorCashflow(String token) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/trading/cashflow/iterator");
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");
        con.setRequestProperty("X-API-TOKEN", token);
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String iteratorExecution(String token) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/trading/execution/iterator");
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");
        con.setRequestProperty("X-API-TOKEN", token);
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String todaysExecution(String token) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/trading/execution/todays");
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");
        con.setRequestProperty("X-API-TOKEN", token);
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String queryPosition(String token) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/trading/position");
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("GET");
        con.setRequestProperty("X-API-TOKEN", token);
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String clearOrder(String token) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/trading/order/clear");
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("DELETE");
        con.setRequestProperty("X-API-TOKEN", token);
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String placeOrder(String token, PlaceRequest request) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/trading/order/");
        String param ="{\"contractId\":" + request.getContractId() + ",\"orderType\":" + request.getOrderType() + ",\"orderPrice\":\"" + request.getOrderPrice() + "\",\"tpPrice\":\"" + request.getTpPrice() + "\",\"slPrice\":\"" + request.getSlPrice() + "\",\"closeTpAmount\":\"" + request.getCloseTpAmount() + "\",\"closeSlAmount\":\"" + request.getCloseSlAmount() + "\",\"trailAmount\":\"" + request.getTrailAmount() + "\",\"orderLot\":" + request.getOrderLot() + ",\"tradeType\":" + request.getTradeType() + ",\"expireType\":" + request.getExpireType() + ",\"side\":" + request.getSide() + ",\"clientAccountId\":\"" + request.getClientAccountId() + "\",\"clientOrderId\":\"" + request.getClientOrderId() + "\"}";
        System.out.println("placeOrder request:"+param);
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("POST");
        con.setRequestProperty("Content-Type", "application/json");
        con.setRequestProperty("X-API-TOKEN", token);
        con.setDoOutput(true);
        IOUtils.write(param, con.getOutputStream(), "utf8");
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String modifyOrder(String token,long orderId, ModifyRequest request) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/trading/order/" + orderId);
        String param ="{\"orderPrice\":\"" + request.getOrderPrice() + "\",\"tpPrice\":\"" + request.getTpPrice() + "\",\"slPrice\":\"" + request.getTpPrice() + "\",\"closeTpAmount\":\"" + request.getCloseTpAmount() + "\",\"closeSlAmount\":\"" + request.getCloseSlAmount() + "\",\"trailAmount\":\"" + request.getTrailAmount() + "\",\"orderLot\":" + request.getOrderLot() + "}";
        System.out.println("modify request:"+param);
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("PUT");
        con.setRequestProperty("Content-Type", "application/json");
        con.setRequestProperty("X-API-TOKEN", token);
        con.setDoOutput(true);
        IOUtils.write(param, con.getOutputStream(), "utf8");
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }

    String cancelOrder(String token,long orderId) throws IOException {
        URL url = new URL(PREFIX + "/api/v1/trading/order/" + orderId);
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("DELETE");
        con.setRequestProperty("X-API-TOKEN", token);
        InputStream inputStream = con.getInputStream();
        return IOUtils.toString(inputStream, "utf8");
    }
}
