package com.krampus.apidemo.common;

public class ModifyRequest {
    String orderPrice ="";
    String tpPrice="";
    String slPrice="";
    String closeTpAmount="";
    String closeSlAmount="";
    String trailAmount="";
    int orderLot;

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
}
