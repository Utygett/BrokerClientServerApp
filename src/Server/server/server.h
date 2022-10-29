#ifndef SERVER_H
#define SERVER_H

/*
 * Класс реализующий сервер.
 */

#include "src/Server/server/session.h"

class Server
{
private:
    boost::asio::io_service& m_IOService;
    tcp::acceptor m_Acceptor;
public:
    Server(boost::asio::io_service& io_service);
    void handle_accept(Session* new_session, const boost::system::error_code& error);
};

#endif // SERVER_H
