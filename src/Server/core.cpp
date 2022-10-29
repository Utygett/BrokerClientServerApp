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
            std::cout << "Find currency" << std::endl;
			std::string addBidResult = m_Forex[currency]->addBid(jBidInfo["bid"].dump());
			std::cout << "AddBidresult:" << addBidResult << std::endl;
			auto jOrderResult = nlohmann::json::parse(addBidResult);// нужно возвращать одному пользователю а второго кидать исполненые заказы
			std::cout << "END PARSE " << jOrderResult << std::endl;
			nlohmann::json jDeals = jOrderResult["deals"];
			std::cout << "SIZE IS " << jDeals.size() << "    " << jDeals.dump(4) << std::endl;
//             if(jDeals.size() == 1)
//             {
//                 std::cout << "STEP 1" << std::endl;
////                 std::cout << jDeals["left"] << std::endl;
//                 std::cout << "STEP 1.1" << std::endl;
//                 auto jLeftSideDeal = jDeals[0];
//                 std::cout << "STEP 1.2 " << jLeftSideDeal << std::endl;
////                 auto jRightSideDeal = jDeals["right"];
////                 m_CopletedOrders[jLeftSideDeal["id"].get<size_t>()].push_back(jLeftSideDeal);
////                 m_CopletedOrders[jRightSideDeal["id"].get<size_t>()].push_back(jLeftSideDeal);
//             }
//             else
//             {
                 for(size_t i = 0; i < jDeals.size(); ++i)
                 {
                     auto jRecord = jDeals[i];
                     std::cout << "STEP 2 " << jRecord.dump(4) << std::endl;
                     auto jLeftSideDeal1 = jRecord;
                     std::cout << "STEP 2.1" << jLeftSideDeal1 << std::endl;
                     std::cout << "STEP 2.1" << jLeftSideDeal1["left"] << std::endl;
                     std::cout << "STEP 2.1" << jLeftSideDeal1["right"] << std::endl;
                     auto jLeftSideDeal = jRecord["left"];
                     std::cout << "STEP 2.2" << std::endl;
                     m_CopletedOrders[jLeftSideDeal["id"].get<size_t>()].push_back(jLeftSideDeal);
                     auto jRightSideDeal = jRecord["right"];
                     m_CopletedOrders[jRightSideDeal["id"].get<size_t>()].push_back(jLeftSideDeal);
                 }
//             }
             for(const auto &it : m_CopletedOrders)
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

std::string Core::getCurrencyList()
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
    return  jCurrList.dump();
}

Core &Core::getCore()
{
    static Core core;
    return core;
}
