#ifndef CLIENSERVERECN_COMMON_HPP
#define CLIENSERVERECN_COMMON_HPP

#include <string>

static unsigned short port = 5555;

namespace Requests
{
    static std::string Login = "Log";
    static std::string Registration = "Reg";
    static std::string Hello = "Hel";
    static std::string NewBid = "Bid";
    static std::string Info = "Inf";
	static std::string CurrInfo = "CurrInf";
    static std::string Init = "Init";
    static std::string Vault = "Val";
}

#endif //CLIENSERVERECN_COMMON_HPP
