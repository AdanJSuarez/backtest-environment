//
//  events.hpp
//  Backtest Environment
//
//  Created by Evan Kirkiles on 5/29/18.
//  Copyright © 2018 Evan Kirkiles. All rights reserved.
//

#ifndef events_hpp
#define events_hpp
#ifndef string
#include <string>
#endif

#include <stdio.h>

using namespace std;

// Base event class to which we can add features
class Event {};

// Market event for updating data with corresponding bars
class MarketEvent:Event {
public:
    string type = "MARKET";
    MarketEvent();
};

// Signal event for sending a signal from an algo
class SignalEvent:Event {
public:
    string type = "SIGNAL";
    string symbol;
    string datetime;
    string signal_type;
    
    // PARAMS:
    // symbol: ticker symbol
    // datetime: the timestamp at which signal was generated
    // signal_type: "LONG" or "SHORT"
    SignalEvent(string symbol, string datetime, string signal_type);
};

// Order event for sending an order to execution system
class OrderEvent: Event {
public:
    string type = "ORDER";
    string symbol;
    string order_type;
    int quantity;
    string direction;
    
    // PARAMS:
    // symbol: ticker symbol
    // order_type: "MKT" or "LMT" for market or limit
    // quantity: non-negative integer for quantity
    // direction: "BUY" or "SELL" for long or short
    OrderEvent(string symbol, string order_type, int quantity, string direction);
    
    // Prints the values in the order
    void print_order();
};

// Gets the filled information about an order from the broker
class FillEvent:Event {
public:
    string type = "FILL";
    string timeindex;
    string symbol;
    string exchange;
    int quantity;
    string direction;
    double fill_cost;
    double commission;
    
    // PARAMS:
    // timeindex: bar resolution when order was filled
    // symbol: ticker symbol for order filled
    // exchange: the exchange on which order was filled
    // quantity: the filled quantity (can implement slippage)
    // direction: the direction of the fill ("BUY" or "SELL")
    // fill_cost: the holdings value in dollars
    // commission: optional commission sent from IB
    
    FillEvent(string timeindex, string symbol, string exchange, int quantity, string direction,
              double fill_cost, double commission=0);
};

#endif /* events_hpp */
