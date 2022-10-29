#ifndef SESSION_H
#define SESSION_H



#include <cstdlib>
#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include "src/json.hpp"
#include "src/Common.hpp"
#include "src/Server/core.h"

using boost::asio::ip::tcp;

class Session
{
private:
    tcp::socket m_Socket;
    enum { max_length = 1024 };
    char m_DataBuffer[max_length];
public:
    Session(boost::asio::io_service& io_service);
    tcp::socket& socket();
    void start();
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
    void handle_write(const boost::system::error_code& error);
};

#endif // SESSION_H
