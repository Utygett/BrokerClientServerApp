#include <cstdlib>
#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include "src/json.hpp"
#include "src/Common.hpp"
#include "server/server.h"

int main()
{
    try
    {
        boost::asio::io_service io_service;
        Server s(io_service);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
