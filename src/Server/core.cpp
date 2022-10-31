#include "core.h"

/*
 * Конструктор, добавляем валютные пары и их стартовые курсы обмена.
 */

Core::Core()
{
    m_Forex["USD/RUB"] = std::make_shared<Currency>("USD/RUB", 60);
    m_Forex["USD/EUR"] = std::make_shared<Currency>("USD/EUR", 0.9);
    m_Forex["EUR/RUB"] = std::make_shared<Currency>("EUR/RUB", 70);
}

/*
 * Регистрируем нового пользователя и возвращаем его ID.
 */

std::string Core::registerNewUser(const std::string& userInfo)
{
    nlohmann::json jRegStatus;
    try {
        auto jUserInfo = nlohmann::json::parse(userInfo);
        if(m_Users.find(jUserInfo["username"]) == m_Users.end())
        {
            size_t newUserId = m_Users.size();
            m_UsersId[newUserId] = jUserInfo["username"];
            m_Users[jUserInfo["username"]].password = jUserInfo["password"];
            m_Users[jUserInfo["username"]].id = newUserId;
            jRegStatus["status"] = "true";
            jRegStatus["userId"] = newUserId;
        }
        else
        {
            jRegStatus["status"] = "false";
            jRegStatus["msg"] = "The " + jUserInfo["username"].dump() + " already exists!";
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        jRegStatus["status"] = "false";
        jRegStatus["msg"] = e.what();
    }
    return jRegStatus.dump();
}

/*
 * Проверяем зарегистрирован ли пользователь.
 */

std::string Core::loginUser(const std::string &userInfo)
{
    nlohmann::json jRegStatus;
    try {
        auto jUserInfo = nlohmann::json::parse(userInfo);
        if(m_Users.find(jUserInfo["username"]) != m_Users.end())
        {
            if(m_Users[jUserInfo["username"]].password == jUserInfo["password"])
            {
                jRegStatus["status"] = "true";
                jRegStatus["userId"] = m_Users[jUserInfo["username"]].id;
            }
            else
            {
                jRegStatus["status"] = "false";
                jRegStatus["msg"] = "Incorret password";
            }
        }
        else
        {
            jRegStatus["status"] = "false";
            jRegStatus["msg"] = "The " + jUserInfo["username"].dump() + " does not exsist!";
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        jRegStatus["status"] = "false";
        jRegStatus["msg"] = e.what();
    }
    return jRegStatus.dump();
}

/*
 * Добавляем заявку, проверяем можно ли ее исполнить,
 * если заявка исполнена то добавляем в таблицу исполненых заявок.
 */

std::string Core::newBid(const std::string &bidInfo)
{
	nlohmann::json jBidStatus;
	try {
        nlohmann::json jBidInfo = nlohmann::json::parse(bidInfo);
        std::string currency = jBidInfo["currency"];
        if(m_Forex.find(currency) != m_Forex.end())
        {
			auto jOrderResult = m_Forex[currency]->addBid(jBidInfo["bid"].dump());
			std::cout << "END PARSE " << jOrderResult.dump(3) << std::endl;
			std::cout << "SIZE IS " << jOrderResult.size() << std::endl;
                 for(size_t i = 0; i < jOrderResult.size(); ++i)
                 {
                     auto jRecord = nlohmann::json::parse(jOrderResult[i].dump());
                     std::cout << "STEP 2 " << jRecord.dump(4) << std::endl;
                     auto jLeftSideDeal = jRecord["left"];
                     std::cout << "STEP 2.1" << jLeftSideDeal << std::endl;
                     m_CompletedOrders[jLeftSideDeal["id"].get<size_t>()].push_back(jLeftSideDeal);
					 auto jRightSideDeal = jRecord["right"];
					 std::cout << "STEP 2.2" << jRightSideDeal << std::endl;
					 m_CompletedOrders[jRightSideDeal["id"].get<size_t>()].push_back(jLeftSideDeal);
                 }
             for(const auto &it : m_CompletedOrders)
             {
                 std::cout << "RECORDS IN STORE" << it.second.dump(4);
             }
			jBidStatus["status"] = "true";
        }
        else
        {
			jBidStatus["status"] = "false";
            std::string msg =  "Currency is " + jBidInfo["currency"];
			msg += " Not found";
			jBidStatus["msg"] = msg;
            std::cerr << "Error! Unknown Currency" << std::endl;
        }
        } catch (std::exception &e) {
			jBidStatus["status"] = "false";
			jBidStatus["msg"] = e.what();
            std::cerr << e.what() << std::endl;
        }
    return  jBidStatus.dump();
}

std::string Core::getInfo(const std::string &UserId)
{
//    const auto userIt = m_UsersId.find(std::stoi(UserId));
//    if (userIt == m_Users.cend())
//    {
//    }

    return "Error! Unknown User";
}

std::string Core::getCurrencyList(const std::string& UserId)
{
    nlohmann::json jCurrList;
    try {
            auto itBegin = m_Forex.begin();
            while (itBegin != m_Forex.end()) {
                nlohmann::json jCurrInfo;
                jCurrInfo["name"] = itBegin->second->getName();
                jCurrInfo["price"] = itBegin->second->getExchangeRate();
                jCurrList["currInfo"].push_back(jCurrInfo);
                ++itBegin;
        }
        jCurrList["status"] = "true";
    } catch (std::exception &e) {
        jCurrList["status"] = "false";
        jCurrList["msg"] = e.what();
        //error log append
    }
	jCurrList["orders"] = getCompleteOrders(std::stoi(UserId));
	jCurrList["DOM"] = getDepthOfMarket();
	return  jCurrList.dump();
}

/*
 * Проверяем есть ли у пользователя совершенные сделки.
 */

nlohmann::json Core::getCompleteOrders(size_t userId)
{
	nlohmann::json jCompletedUserOrders;
	const auto userIt = m_UsersId.find(userId);
	if(userIt == m_UsersId.end())
		return jCompletedUserOrders;
	jCompletedUserOrders = m_CompletedOrders[userId];
	m_UsersId[userId].clear();
	return jCompletedUserOrders;
}

nlohmann::json Core::getDepthOfMarket()
{
	nlohmann::json jDOM;
	for(auto itBegin = m_Forex.begin(); itBegin != m_Forex.end(); ++itBegin)
	{
		jDOM[itBegin->first] = itBegin->second->getDepthOfMarket();
	}
	return jDOM;
}

Core &Core::getCore()
{
    static Core core;
    return core;
}
