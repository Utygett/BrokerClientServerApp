#include "currency.h"

Currency::Currency(const std::string &currName, double exchangeRate)
    : m_Name(currName)
    , m_ExchangeRate(exchangeRate)
{

}

/*
 *  Добавление новой заявки, и проверка можно ли ее сразу исполнить.
 */

std::string Currency::addBid(std::string jSonBidInfo)
{
    std::string jsonBidResponse;
    try {
        auto jBid = nlohmann::json::parse(jSonBidInfo);
        size_t UserId = jBid["id"].get<size_t>();
        double price = jBid["price"].get<double>();;
        int amount = jBid["amount"].get<int>();
        bool bidType = jBid["type"].get<int>();
        std::string uuid = jBid["uuid"];
        std::shared_ptr<Bid> newBid = std::make_shared<Bid>(UserId, price, amount, bidType, uuid);
		std::cout << "Success add bid" << std::endl;
        jsonBidResponse = checkBid(newBid);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        jsonBidResponse = "error"; // TODO поменять на джейсон статус ошибки
    }
    return jsonBidResponse;
}

/*
 * Получаем информацию о текущих заявках по валюте.
 */

nlohmann::json Currency::getDepthOfMarket()
{
    nlohmann::json jDOM;
    nlohmann::json jBuyRequest;
    nlohmann::json jSellRequest;
    for(auto &bid : m_SellRequests)
    {
        nlohmann::json jSell;
        jSell["price"] = bid->getPrice();
        jSell["amount"] = bid->getAmount();
        jSellRequest.push_back(jSell);
    }
    for(auto &bid : m_PurchaseRequests)
    {
        nlohmann::json jBuy;
        jBuy["price"] = bid->getPrice();
        jBuy["amount"] = bid->getAmount();
        jBuyRequest.push_back(jBuy);
    }
    jDOM["buy"] = jBuyRequest;
    jDOM["sell"] = jSellRequest;
    return jDOM;
}

std::string Currency::getName()
{
    return m_Name;
}

double Currency::getExchangeRate()
{
    return m_ExchangeRate;
}

/*
 * Проверяем тип заявки и проверяем можно ли ее реализовать.
 */

std::string Currency::checkBid(std::shared_ptr<Bid> &newBid)
{
    std::string jsonBidResponse;
    std::string result;
    if(newBid->getType() == PURCHASE)
        jsonBidResponse = checkActiveRequestForSell(newBid);
    else if(newBid->getType() == SELL)
        jsonBidResponse = checkActiveRequestForBuy(newBid);
    return jsonBidResponse;
}

/*
 *  Смотрим активные заявки на продажу, если заявку можно исполнить совершаем сделку,
 *  если нет то добавляем в хранилище.
 */

std::string Currency::checkActiveRequestForSell(std::shared_ptr<Bid> &newBid)
{
    nlohmann::json jsonBidResponse;
    auto itBegin = m_SellRequests.begin();
    while (itBegin != m_SellRequests.end() &&
           newBid->getAmount() > 0 &&
           (*itBegin)->getPrice() <= newBid->getPrice())
    {
        jsonBidResponse.push_back((*itBegin)->makeDeal(newBid));
        m_ExchangeRate = (*itBegin)->getDealPrice();
        if((*itBegin)->getAmount() == 0)
        {
            m_SellRequests.erase(itBegin++);
        }
        else // TODO проверить нужна ли вообще эта проверка, потому что если шет амоунт не равно 0 мы выходим из цикла
            ++itBegin;
    }
    if(newBid->getAmount() != 0)
    {
        m_PurchaseRequests.insert(newBid);
    }
    return jsonBidResponse.dump();
}

/*
 *  Смотрим активные заявки на продажу, если заявку можно исполнить совершаем сделку,
 *  если нет то добавляем в хранилище.
 */

std::string Currency::checkActiveRequestForBuy(std::shared_ptr<Bid> &newBid)
{
    nlohmann::json jsonBidResponse;
    auto itBegin = m_PurchaseRequests.begin();
    while (itBegin != m_PurchaseRequests.end() &&
           newBid->getAmount() &&
           (*itBegin)->getPrice() >= newBid->getPrice())
    {
        jsonBidResponse.push_back((*itBegin)->makeDeal(newBid));
        m_ExchangeRate = (*itBegin)->getDealPrice();
        if((*itBegin)->getAmount() == 0)
        {
            m_PurchaseRequests.erase(itBegin++);
        }
    }
    if(newBid->getAmount() != 0)
    {
        m_SellRequests.insert(newBid);
    }
    return jsonBidResponse.dump();
}
