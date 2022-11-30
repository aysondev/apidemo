DOC URL:https://swagger.ayson.us/v1/



交易相关的枚举
```
orderStatus: 
[2, 3, 4, 5, 6, 8, 10, 12, 14, 22 ]
[PLACING:下单, ACCEPTED:服务器接受, PLACED：下单成功, FAILED：下单失败, CANCELLING：取消中, CANCELLED：取消成功, MODIFYING：修改中, EXPIRED：过期, EXECUTED：约定成功, TRIGGERING：触发中]

fillStatus: 
[2, 4, 6]  
[NONE：无, PARTIAL：部分, FILLED：全部约定]

 
expireType:
 [1, 2, 3, 4 ]
[FOK：全部或失败, IOC：全部或部分,剩余部分取消, GTC：一直有效, DAY：当天有效]

triggerType: 
[1, 2 ]
[TP：止盈, SL：止损]

orderType: 
[3, 5, 6, 7 ]
[LIMIT：挂单, MARKET：市价单, TRAIL：追踪单, TP_SL：止盈止损单]

side: 
[1, -1]
[BUY：买, SELL：卖]

executeType: 
[1, 2]
[OPEN:开仓, CLOSE:关仓]

marginStatus: 
[1, 3, 5 ]
NORMAL:正常状态, LIQUIDATING：清算, LIQUIDATION_FAILED：清算失败

tradeType: 
[1, 2, 3 ]
[OPEN:开仓, CLOSE:关仓, NET:单仓模式,只有买卖没有开平.]
```


# **订阅成交事件**
## 推送订单的成交信息

订阅请求:
 ```
{
  "id": "string (int64)",
  "event": "EXECUTION",
  "action": "SUBSCRIBE",
  "snapshot": "string"
}
 ```

推送事件信息:
 ```
data:{
        "action" : null,
        "data" :
        {
                "executions" :
                [
                        {
                                "agentId" : 54,
                                "clientAccountId" : "0",
                                "clientOrderId" : "0",
                                "commission" : "10.00",
                                "contractCode" : "CL2312",
                                "contractId" : 395528,
                                "currencyId" : 1,
                                "executeAmount" : "78770.000000000000000000",
                                "executeDate" : "2022-11-09",
                                "executeLot" : 1,
                                "executePrice" : "78.770000000",
                                "executeTime" : "1667966149854",
                                "executeType" : 1,
                                "id" : "1815228919391463477",
                                "instrumentId" : 6,
                                "itId" : 6,
                                "orderId" : "1815191395965560373",
                                "orderType" : 3,
                                "pl" : "0",
                                "placeType" : 1,
                                "side" : 1,
                                "version" : 1
                        }
                ],
                "snapshot" : false
        },
        "event" : "EXECUTION"
}
 ```



# **订阅持仓事件**
## 推送活跃订单，持仓，账户资金信息.

"account":账户相关的信息数据。

"orders"：活跃订单的信息

"positionDetails"：持仓信息


订阅请求:
 ```
{
  "id": "string (int64)",
  "event": "POSITION",
  "action": "SUBSCRIBE",
  "snapshot": "string"
}
 ```
推送事件信息:

```
data:{
        "action" : null,
        "data" :
        {
                "account" :
                {
                        "agentId" : 54,
                        "balance" : "2913.980000000",
                        "financed" : "0.000000000",
                        "id" : "1689081788509768",
                        "intradayPl" : "0.000000000",
                        "itId" : 6,
                        "loginId" : "yy01",
                        "marginStatus" : 1,
                        "status" : 1,
                        "version" : 743,
                        "ytdBalance" : "2923.980000000"
                },
                "orders" :
                [
                        {
                                "agentId" : 54,
                                "cancelLot" : 0,
                                "clientAccountId" : "0",
                                "clientOrderId" : "0",
                                "contractCode" : "CL2312",
                                "contractId" : 395528,
                                "currencyId" : 1,
                                "executeLot" : 0,
                                "expireType" : 4,
                                "fillStatus" : 2,
                                "id" : "1815303149568673333",
                                "instrumentId" : 6,
                                "itId" : 6,
                                "lpExecuteQty" : 0,
                                "lpOrderStatus" : 1,
                                "modifyType" : 12,
                                "orderDate" : "2022-11-09",
                                "orderLot" : 1,
                                "orderPrice" : "2.000000000",
                                "orderStatus" : 4,
                                "orderTime" : "1667974998774",
                                "orderType" : 3,
                                "placeType" : 1,
                                "side" : 1,
                                "tradeType" : 1,
                                "version" : 6
                        }
                ],
                "positionDetails" :
                [
                        {
                                "accountId" : "1689081788509768",
                                "agentId" : 54,
                                "closedLot" : 0,
                                "contractCode" : "CL2312",
                                "contractId" : 395528,
                                "currency" : 1,
                                "id" : "1815228919391463477",
                                "instrumentId" : 6,
                                "itId" : 6,
                                "openDate" : "2022-11-09",
                                "openLot" : 1,
                                "openPrice" : "78.770000000",
                                "openTime" : "1667966149854",
                                "orderId" : "1815191395965560373",
                                "pl" : "0.000000000",
                                "side" : 1,
                                "status" : 1
                        }
                ],
                "snapshot" : true
        },
        "event" : "POSITION"
}
```

# **订阅订单事件**
## 推送订单变化

订阅请求:
 ```
{
  "id": "string (int64)",
  "event": "ORDER",
  "action": "SUBSCRIBE",
  "snapshot": "string"
}
 ```

推送事件信息:
```
 {
  "data": {
    "snapshot": "boolean",
    "orders": [
      {
        "id": "string (int64)",
        "version": "integer (int32)",
        "itId": "integer (int32)",
        "agentId": "integer (int32)",
        "contractId": "integer (int32)",
        "contractCode": "string",
        "instrumentId": "integer (int32)",
        "currencyId": "integer (int32)",
        "side": "integer (int32)",
        "orderStatus": "integer (int32)",
        "fillStatus": "integer (int32)",
        "modifyType": "integer (int32)",
        "orderTime": "string (int64)",
        "orderDate": "string (date)",
        "orderType": "integer (int32)",
        "orderPrice": "string (decimal)",
        "tpPrice": "string (decimal)",
        "slPrice": "string (decimal)",
        "closeTpAmount": "string (decimal)",
        "closeSlAmount": "string (decimal)",
        "trailAmount": "string (decimal)",
        "orderLot": "integer (int32)",
        "executeLot": "integer (int32)",
        "cancelLot": "integer (int32)",
        "executePrice": "string (decimal)",
        "triggerTime": "string (int64)",
        "placeType": "integer (int32)",
        "tradeType": "integer (int32)",
        "expireType": "integer (int32)",
        "triggerType": "integer (int32)",
        "clientAccountId": "string (int64)",
        "clientOrderId": "string (int64)",
        "exchangeOrderId": "string",
        "errorMessage": "string",
        "lpOrderStatus": "integer (int32)",
        "lpExecutePrice": "string (decimal)",
        "lpExecuteQty": "integer (int32)"
      }
    ]
  },
  "event": "ORDER"
}
 ```

# **订阅市场深度**
## 推送市场深度

订阅请求:
 ```
{
  "id": "string (int64)",
  "contractId": "integer (int32)",
  "event": "DEPTH",
  "action": "SUBSCRIBE",
  "snapshot": "string"
}
 ```


推送事件信息:
```
{
  "data": {
    "snapshot": "boolean",
    "instrumentId": "integer (int32)",
    "contractId": "integer (int32)",
    "depth": {
      "id": "string (int64)",
      "instrumentDate": "string (date)",
      "quoteTime": "string (int64)",
      "bids": [
        {
          "price": "string (decimal)",
          "qty": "integer (int32)"
        }
      ],
      "asks": [
        {
          "price": "string (decimal)",
          "qty": "integer (int32)"
        }
      ]
    }
  },
  "event": "DEPTH"
}
```

# **订阅市场成交**
## 推送市场成交

订阅请求:
 ```
{
  "id": "string (int64)",
  "contractId": "integer (int32)",
  "event": "TICK",
  "action": "SUBSCRIBE",
  "limit": "integer (int32)",
  "snapshot": "string"
}
 ```


推送事件信息:
```
{
  "id": "string (int64)",
  "result": "string",
  "data": {
    "snapshot": "boolean",
    "instrumentId": "integer (int32)",
    "contractId": "integer (int32)",
    "purchased": "boolean",
    "ticks": [
      {
        "id": "string (int64)",
        "lowPrice": "string (decimal)",
        "highPrice": "string (decimal)",
        "openingPrice": "string (decimal)",
        "bidPrice": "string (decimal)",
        "askPrice": "string (decimal)",
        "lastPrice": "string (decimal)",
        "lastQty": "integer (int32)",
        "totalQty": "integer (int32)",
        "positionQty": "integer (int32)",
        "preClosingPrice": "string (decimal)",
        "preSettlePrice": "string (decimal)",
        "instrumentDate": "string (date)",
        "tickTime": "string (int64)"
      }
    ]
  },
  "event": "TICK",
  "action": "SUBSCRIBE",
  "snapshot": "string"
}
```