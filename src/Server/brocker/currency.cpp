#include "currency.h"

Currency::Currency(const std::string &currName, double exchangeRate)
    : m_Name(currName)
    , m_ExchangeRate(exchangeRate)
{

}

std::string Currency::addBid(std::string jSonBidInfo)
{
    std::string jsonBidResponse;
    try {
        auto jBid = nlohmann::json::parse(jSonBidInfo);
        std::cout << jBid["id"] << std::endl;
        size_t UserId = jBid["id"].get<size_t>();
        std::cout <<jBid["price"] << std::endl;
        double price = jBid["price"].get<double>();
        std::cout << jBid["amount"]<< std::endl;
        int amount = jBid["amount"].get<int>();
        std::cout <<jBid["type"] << std::endl;
        bool bidType = jBid["type"].get<int>();
        std::cout << jBid["uuid"] << std::endl;
        std::string uuid = jBid["uuid"];
        std::shared_ptr<Bid> newBid = std::make_shared<Bid>(UserId, price, amount, bidType, uuid);
        jsonBidResponse = checkBid(newBid);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        jsonBidResponse = "error"; // поменять на джейсон статус ошибки
    }
    return jsonBidResponse;
}

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
        else
            ++itBegin;
    }
    if(newBid->getAmount() != 0)
    {
        m_PurchaseRequests.insert(newBid);
    }
    return jsonBidResponse.dump().c_str();
}

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
    return jsonBidResponse.dump().c_str();
}
