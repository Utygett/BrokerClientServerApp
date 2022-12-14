#ifndef CORE_H
#define CORE_H

/*
 * Класс реализующий запросы логику ответов, на запросы клиентов.
 */

#include <cstdlib>
#include <iostream>
#include <memory>
#include "json.hpp"
#include "Common.hpp"
#include "brocker/currency.h"
#include "unordered_map"

class Core
{
private:
    // <UserId, UserName>
    struct sUser{
        std::string password;
        size_t id;
    };
    std::unordered_map<size_t, std::string>   m_UsersId;
    std::unordered_map<std::string, sUser>   m_Users;
    std::unordered_map<std::string, std::shared_ptr<Currency> > m_Forex;
    std::unordered_map<size_t, nlohmann::json>  m_CompletedOrders;
	nlohmann::json getCompleteOrders(size_t userId);
	nlohmann::json getDepthOfMarket();
    Core(Core &forCopy);
    Core operator = (Core &forAssign);
    Core();
public:
    std::string registerNewUser(const std::string& userInfo);
    std::string loginUser(const std::string& userInfo);
    std::string newBid(const std::string& bidInfo);
    std::string getInfo(const std::string& aUserId);
    std::string getCurrencyList(const std::string& aUserId);
    static Core &getCore();
};

#endif // CORE_H

