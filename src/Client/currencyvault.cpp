#include "currencyvault.h"

CurrencyVault::CurrencyVault()
{

}

bool CurrencyVault::initStorage(std::string currencyInfo)
{
    bool result = true;
    try {
        nlohmann::json jCurrency = nlohmann::json::parse(currencyInfo);
        for(int i = 0; i < jCurrency.size(); ++i)
        {
//            nlohmann::json jRecord = jCurrency[i];
//            QString currencyPair(jRecord["name"].dump().c_str());
//            currencyPair = currencyPair.remove('"');
//            std::cout << jRecord["name"].dump().c_str() << std::endl;
        }
    } catch (std::exception &e) {
        result = false;
    }
    return result;
}
