#include "bid.h"

double Bid::getPrice()
{
    return m_Price;
}

long long Bid::getUnixTimeCreated()
{
    return m_BidTime.time_since_epoch().count();
}

bool Bid::getType()
{
    return m_BidType;
}

int Bid::getAmount()
{
    return m_Amount;
}

double Bid::getDealPrice()
{
    return m_LastDealPrice;
}

std::string Bid::informClientsTransaction(std::shared_ptr<Bid> &newBid, int dealAmount, double price)
{
    nlohmann::json jsonDealInfo;
    nlohmann::json jInformLeftClient;
    jInformLeftClient["id"] = newBid->m_UserId;
    jInformLeftClient["amount"] = dealAmount;
    jInformLeftClient["price"] = price;
    jInformLeftClient["uuid"] = newBid->m_Uuid;
    jsonDealInfo["left"] = jInformLeftClient;
    nlohmann::json jInformRightClient;
    jInformRightClient["id"] = this->m_UserId;
    jInformRightClient["amount"] = dealAmount;
    jInformRightClient["price"] = price;
    jInformRightClient["uuid"] = this->m_Uuid;
    jsonDealInfo["right"] = jInformRightClient;
    return jsonDealInfo;
}

std::string Bid::makeDeal(std::shared_ptr<Bid> &newBid)
{
    double coast;
    double price;
    int dealAmount = 0;
    std::cout << "Dealt with" << newBid->m_Price << "and" << this->m_Price << std::endl;
    if(m_Amount >= newBid->getAmount())
    {
        dealAmount = newBid->m_Amount;
        price = this->m_Price;
        coast = dealAmount * price;
        this->m_Amount -= newBid->m_Amount;
        newBid->m_Amount = 0;
    }
    else
    {
        dealAmount = this->m_Amount;
        price = this->m_Price;
        coast = dealAmount * price;
        newBid->m_Amount -= this->m_Amount;
        this->m_Amount = 0;
    }
    m_LastDealPrice = price;
    std::cout << "Coast :" << coast << std::endl;
    return(informClientsTransaction(newBid, dealAmount, price));
}

Bid::Bid(size_t UserId, double Price, int Amount, bool BidType, std::string &uuid) :
    m_UserId(UserId)
  , m_Uuid(uuid)
  , m_Price(Price)
  , m_Amount(Amount)
  , m_BidType(BidType)
  , m_BidTime(std::chrono::system_clock::now())
{
    m_LastDealPrice = 0;
    std::cout << "constructor " << m_BidTime.time_since_epoch().count() << " Price " << m_Price << " " << BidType << " " << m_Amount <<  std::endl;
}

Bid::~Bid()
{
    std::cout << "destructor " << m_BidTime.time_since_epoch().count() << " Price " << m_Price << " " << m_BidType << " " << m_Amount << std::endl;
}
