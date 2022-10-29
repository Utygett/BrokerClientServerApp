#ifndef TCPCLIENT_H
#define TCPCLIENT_H

/*
 * Синглтон класс, клиент для подключения к серверу и обмена сообщениями.
 */

#include <iostream>
#include <boost/asio.hpp>
#include "../Common.hpp"
#include "../json.hpp"

using boost::asio::ip::tcp;

class TCPClient
{
    boost::asio::io_service io_service;
    tcp::socket *s;
    std::string readMessage();
    void connect();
    TCPClient();
public:
    static TCPClient &getClient();
    ~TCPClient();
    std::string messageExchange(const std::string& aId,
                    const std::string& aRequestType,
                    const std::string& aMessage);
};

#endif // TCPCLIENT_H
