#ifndef CURRENCYVAULT_H
#define CURRENCYVAULT_H

#include <unordered_map>
#include <iostream>
#include <QString>
#include "../Common.hpp"
#include "../json.hpp"

class CurrencyVault
{
    std::unordered_map<std::string, double> m_CurrencyStorage;
public:
    CurrencyVault();
    bool initStorage(std::string currencyInfo);
};

#endif // CURRENCYVAULT_H
