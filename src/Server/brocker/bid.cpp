#include "bid.h"

/*
 * Конструтор, получаем необходимую инфомрацию о заявке, указываем время создания заявки.
 */

Bid::Bid(size_t UserId, double Price, int Amount, bool BidType, std::string &uuid) :
		m_UserId(UserId)
		, m_Uuid(uuid)
		, m_Price(Price)
		, m_Amount(Amount)
		, m_BidType(BidType)
		, m_BidTime(std::chrono::system_clock::now())
{
	m_LastDealPrice = 0;
//	std::cout << "constructor " << m_BidTime.time_since_epoch().count() << " Price " << m_Price << " " << BidType << " " << m_Amount <<  std::endl;
}

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

/*
 * Основной метод, который проводит сделку между двумя заявками.
 */

nlohmann::json Bid::makeDeal(std::shared_ptr<Bid> &newBid)
{
	double coast;
	double price;
	int dealAmount = 0;
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
	std::cout << "Deal id:" << m_UserId << " price: " << newBid->m_Price << " and "
		      << "id: " << newBid->m_UserId << " price: "<< this->m_Price
	 		  << " Coast :" << coast << std::endl;
	return(informClientsTransaction(newBid, dealAmount, price));
}

/*
 * Получение информации о прошедшей сделки.
 */

nlohmann::json Bid::informClientsTransaction(std::shared_ptr<Bid> &newBid, int dealAmount, double price)
{
    nlohmann::json jsonDealInfo;
    nlohmann::json jInformLeftClient;
    jInformLeftClient["id"] = newBid->m_UserId;
    jInformLeftClient["amount"] = dealAmount;
	jInformLeftClient["type"] = newBid->getType();
    jInformLeftClient["price"] = price;
    jInformLeftClient["uuid"] = newBid->m_Uuid;
    jsonDealInfo["left"] = jInformLeftClient;
    nlohmann::json jInformRightClient;
    jInformRightClient["id"] = this->m_UserId;
    jInformRightClient["amount"] = dealAmount;
	jInformLeftClient["type"] = this->getType();
	jInformRightClient["price"] = price;
    jInformRightClient["uuid"] = this->m_Uuid;
    jsonDealInfo["right"] = jInformRightClient;
    return jsonDealInfo;
}

Bid::~Bid()
{
//    std::cout << "destructor " << m_BidTime.time_since_epoch().count() << " Price " << m_Price << " " << m_BidType << " " << m_Amount << std::endl;
}
