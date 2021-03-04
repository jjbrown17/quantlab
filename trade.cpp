#include <string>
#include <ostream>

struct trade
{

    std::string symbol;
    long long int time;
    int quantity;
    int price;

public:
    trade(std::string ticker, int t, int q, int p) : symbol(ticker), time(t), quantity(q), price(p) {}
};
