#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "trade.cpp"
#include "output_data.cpp"

#define ticker std::string

void read_input(const std::string &filename, std::vector<trade> &trades)
{
    std::ifstream file; //(filename);

    file.open(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open file");

    for (std::string line; file >> line;)
    {

        std::stringstream ss(line);

        std::string time, symbol, quantity, price;

        std::getline(ss, time, ',');
        std::getline(ss, symbol, ',');
        std::getline(ss, quantity, ',');
        std::getline(ss, price);
        
        trades.emplace_back(symbol, stoll(time), stoi(quantity), stoi(price));
    }

    file.close();
}

std::ostream &operator<<(std::ostream &o, const trade &t)
{

    o << "symbol: " << t.symbol << '\n';
    o << "time: " << t.time << '\n';
    o << "quantity: " << t.quantity << '\n';
    o << "price: " << t.price << '\n';

    return o;
}

std::ostream &operator<<(std::ostream &o, const output_data &t)
{
    o << t.symbol << ',' << t.maxTimeGap << ',' << t.volume << ',' << t.weightedAveragePrice << ',' << t.maxPrice << '\n';
    return o;
}

std::map<ticker, output_data> process_trades(std::vector<trade> &trades){
    std::map<ticker, output_data> out;
    for (const trade& t: trades){
        auto symbol = t.symbol;

        if (out.find(symbol) == out.end())
            out[symbol] = output_data(symbol);

        auto& o = out[symbol];

        o.weightedAveragePrice = (t.quantity * t.price + o.weightedAveragePrice * o.volume)/(t.quantity + o.volume);
        o.maxTimeGap = t.time - o.lastTrade > o.maxTimeGap ? t.time - o.lastTrade : o.maxTimeGap;
        o.maxPrice = t.price > o.maxPrice ? t.price : o.maxPrice;
        o.volume += t.quantity;
        o.lastTrade = t.time;
        
    }

    return out;
}


int main()
{

    std::vector<trade> trades;

    read_input("input.csv", trades);

    // for (auto t : trades)
    //         std::cout << t << '\n';

    std::map<ticker, output_data> out = process_trades(trades);

    std::ofstream out_file("output.csv");
    
    std::for_each(begin(out), end(out), [&](auto e){out_file << e.second;});
    
    return 0;
}
