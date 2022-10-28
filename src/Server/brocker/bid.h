#ifndef BID_H
#define BID_H

#include <string>
#include <chrono>
#include <iostream>
#include "src/json.hpp"

enum {PURCHASE, SELL};

class Bid
{
    size_t m_UserId;
    std::string m_Uuid;
    double m_Price;
    int m_Amount;
    bool m_BidType;
    double m_LastDealPrice;
    const std::chrono::system_clock::time_point m_BidTime;

    Bid(Bid &forCopy);
    Bid operator = (Bid &forAssign);
public:
    double getPrice();
    long long getUnixTimeCreated();
    bool getType();
    int getAmount();
    double getDealPrice();
    std::string informClientsTransaction(std::shared_ptr<Bid> &newBid, int dealAmount, double price);
    std::string makeDeal(std::shared_ptr<Bid> &newBid);
    explicit Bid(size_t UserId, double Price, int Amount, bool BidType, std::string &uuid);
    ~Bid();
private:

};

#endif // BID_H
