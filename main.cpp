//
//  main.cpp
//  Backtest Environment
//
//  Created by Evan Kirkiles on 5/25/18.
//  Copyright © 2018 Evan Kirkiles. All rights reserved.
//

#include <iostream>
#include "DataHandling/YahooFinanceCSVReader.hpp"
#include "Infrastructure/interface.hpp"
#include "Graphics/gnuplotter.hpp"

#include <QApplication>
#include "Graphics/qtwindow.hpp"

int main(int argc, char **argv) {

    auto startdate = string("1970-01-01");
    auto enddate = string("1971-01-01");
    double initialcapital = 100000000;
    vector<string> symbol_list = {string("GS"), string("AAPL"), string("SPY")};
    vector<string> symbol_list2 = {string("SPY")};

    TradingInterface interface = TradingInterface(symbol_list, symbol_list2, &initialcapital, &startdate, &enddate);
    BuyAndHoldStrategy strat = BuyAndHoldStrategy(&interface.pipeline, &interface.events);
    Benchmark bench = Benchmark(&interface.benchmarkpipeline, &interface.events);
    GNUPlotter gnuplot(&interface.portfolio,
                       &interface.benchmarkportfolio, (char*)"/Users/samkirkiles/Desktop/algobacktester/Graphics/data.csv", (char*)"/Users/samkirkiles/Desktop/algobacktester/Graphics/positions.csv", &startdate, &enddate, false);

    // Begin the backtest on the created plot device
    //interface.runbacktest(strat, bench, &gnuplot);

    QApplication app(argc, argv);

    AlgoWindow window(&interface, &strat, &bench, &gnuplot, &startdate, &enddate, &initialcapital);
    window.show();
    window.raise();

    app.exec();

    return 0;
}
