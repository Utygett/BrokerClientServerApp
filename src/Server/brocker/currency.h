#ifndef CURRENCY_H
#define CURRENCY_H

/*
 * Класс реализующий логику работы с валютой (покуку, продажу, хранение) и текущий курс.
 * Хранит в себе заявки на покупку и продажу.
 */

#include <string>
#include <set>
#include <iostream>
#include "bid.h"
#include <memory>

// TODO добавить метод удаления заявки по uuid.

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

	nlohmann::json checkBid(std::shared_ptr<Bid> &newBid);
	nlohmann::json checkActiveRequestForSell(std::shared_ptr<Bid> &newBid);
	nlohmann::json checkActiveRequestForBuy(std::shared_ptr<Bid> &newBid);

	Currency operator = (const Currency &);
	Currency(const Currency &);
public:
    explicit Currency(const std::string &currName, double exchangeRate);
	nlohmann::json addBid(std::string jSonBidInfo);
    nlohmann::json getDepthOfMarket();
    std::string getName();
    double getExchangeRate();
};

#endif // CURRENCY_H
