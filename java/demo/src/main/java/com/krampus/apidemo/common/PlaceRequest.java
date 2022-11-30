package com.krampus.apidemo.common;

public class PlaceRequest {
    private int contractId;
    private int orderType;
    private String orderPrice = "";
    private String tpPrice = "";
    private String slPrice = "";
    private String closeTpAmount = "";
    private String closeSlAmount = "";
    private String trailAmount = "";
    private int orderLot;
    private  int tradeType;
    private int expireType;
    private int side;
    private String clientAccountId = "";
    private  String clientOrderId = "";

    public int getContractId() {
        return contractId;
    }

    public void setContractId(int contractId) {
        this.contractId = contractId;
    }

    public int getOrderType() {
        return orderType;
    }

    public void setOrderType(int orderType) {
        this.orderType = orderType;
    }

    public String getOrderPrice() {
        return orderPrice;
    }

    public void setOrderPrice(String orderPrice) {
        this.orderPrice = orderPrice;
    }

    public String getTpPrice() {
        return tpPrice;
    }

    public void setTpPrice(String tpPrice) {
        this.tpPrice = tpPrice;
    }

    public String getSlPrice() {
        return slPrice;
    }

    public void setSlPrice(String slPrice) {
        this.slPrice = slPrice;
    }

    public String getCloseTpAmount() {
        return closeTpAmount;
    }

    public void setCloseTpAmount(String closeTpAmount) {
        this.closeTpAmount = closeTpAmount;
    }

    public String getCloseSlAmount() {
        return closeSlAmount;
    }

    public void setCloseSlAmount(String closeSlAmount) {
        this.closeSlAmount = closeSlAmount;
    }

    public String getTrailAmount() {
        return trailAmount;
    }

    public void setTrailAmount(String trailAmount) {
        this.trailAmount = trailAmount;
    }

    public int getOrderLot() {
        return orderLot;
    }

    public void setOrderLot(int orderLot) {
        this.orderLot = orderLot;
    }

    public int getTradeType() {
        return tradeType;
    }

    public void setTradeType(int tradeType) {
        this.tradeType = tradeType;
    }

    public int getExpireType() {
        return expireType;
    }

    public void setExpireType(int expireType) {
        this.expireType = expireType;
    }

    public int getSide() {
        return side;
    }

    public void setSide(int side) {
        this.side = side;
    }

    public String getClientAccountId() {
        return clientAccountId;
    }

    public void setClientAccountId(String clientAccountId) {
        this.clientAccountId = clientAccountId;
    }

    public String getClientOrderId() {
        return clientOrderId;
    }

    public void setClientOrderId(String clientOrderId) {
        this.clientOrderId = clientOrderId;
    }
}
