package com.krampus.apidemo.rest;

import com.krampus.apidemo.common.ModifyRequest;
import com.krampus.apidemo.common.PlaceRequest;
import org.apache.commons.lang3.StringUtils;

public class RestDemo {
	public static void main(String[] args) throws Exception {

		int contractId = 395528;
		RestServiceImpl service = new RestServiceImpl();
		// login
		String token = service.getToken("yy01", "000000");
		System.out.println("token:" + token);
		if (StringUtils.isBlank(token)) return;

		System.out.println("getContract:" + service.getContract(token));
		System.out.println("ping:" + service.ping(token,"11"));
		System.out.println("queryBaseCurrency:" + service.queryBaseCurrency(token));
		System.out.println("queryContract:" + service.queryContract(token));
		System.out.println("queryCurrency:" + service.queryCurrency(token));
		System.out.println("queryInstitution:" + service.queryInstitution(token));
		System.out.println("queryInstrumentContract:" + service.queryInstrumentContract(token,1));
		System.out.println("queryItInstrument:" + service.queryItInstrument(token));
		System.out.println("queryMainContract:" + service.queryMainContract(token));
		System.out.println("queryMajorContract:" + service.queryMajorContract(token));
		System.out.println("iteratorCashflow:" + service.iteratorCashflow(token));
		System.out.println("iteratorExecution:" + service.iteratorExecution(token));
		System.out.println("todaysExecution:" + service.todaysExecution(token));
		System.out.println("queryPosition:" + service.queryPosition(token));
		//
		PlaceRequest placeRequest = new PlaceRequest();
		placeRequest.setContractId(contractId);
		placeRequest.setExpireType(4);
		placeRequest.setOrderLot(1);
		placeRequest.setOrderPrice("1");
		placeRequest.setOrderType(3);
		placeRequest.setSide(1);
		placeRequest.setTradeType(1);
		System.out.println("placeOrder:" + service.placeOrder(token,placeRequest));
		//
		long orderId = 1820455835056150069L;
		ModifyRequest modifyRequest = new ModifyRequest();
		modifyRequest.setOrderLot(1);
		modifyRequest.setOrderPrice("4");
		System.out.println("ModifyOrder:" + service.modifyOrder(token,orderId,modifyRequest));
        //
        System.out.println("cancelOrder:" + service.cancelOrder(token,orderId));
		System.out.println("clearOrder:" + service.clearOrder(token));
	}

}
