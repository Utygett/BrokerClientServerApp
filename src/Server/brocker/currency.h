#ifndef CURRENCY_H
#define CURRENCY_H


#include <string>
#include <set>
#include <iostream>
#include <src/Server/brocker/bid.h>
#include <memory>

class Currency
{

    struct compare {
        bool operator()(std::shared_ptr<Bid> lhs, std::shared_ptr<Bid> rhs) const {
            if(lhs->getType() == SELL && (lhs->getPrice() < rhs->getPrice() ||
                    (lhs->getPrice() == rhs->getPrice() &&
                     lhs->getUnixTimeCreated() < rhs->getUnixTimeCreated())))
                return true;
            else if(lhs->getType() == PURCHASE && (lhs->getPrice() > rhs->getPrice() ||
                                               (lhs->getPrice() == rhs->getPrice() &&
                                                lhs->getUnixTimeCreated() < rhs->getUnixTimeCreated())))
                return true;
            return false;
        }
    };
    std::string m_Name;
    double  m_ExchangeRate;
    std::multiset<std::shared_ptr<Bid>, compare> m_PurchaseRequests;
    std::multiset<std::shared_ptr<Bid>, compare> m_SellRequests;

    std::string checkBid(std::shared_ptr<Bid> &newBid);
    std::string checkActiveRequestForSell(std::shared_ptr<Bid> &newBid);
    std::string checkActiveRequestForBuy(std::shared_ptr<Bid> &newBid);

public:
    explicit Currency(const std::string &currName, double exchangeRate);
    std::string addBid(std::string jSonBidInfo);
    nlohmann::json getDepthOfMarket();
    std::string getName();
    double getExchangeRate();
};

#endif // CURRENCY_H
