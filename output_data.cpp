#include <string>

struct output_data {

    std::string symbol;
    long long int maxTimeGap;
    long long int volume;
    double weightedAveragePrice;
    int maxPrice;

    long long int lastTrade;

    output_data(std::string ticker): symbol(ticker), maxTimeGap(0), volume(0), weightedAveragePrice(0), maxPrice(0), lastTrade(999999999) {}
    output_data() {}
};