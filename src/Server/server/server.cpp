#include "server.h"

Server::Server(boost::asio::io_service& io_service)
    : m_IOService(io_service)
    , m_Acceptor(io_service, tcp::endpoint(tcp::v4(), port))
{
    std::cout << "Server started! Listen " << port << " port" << std::endl;

    Session* new_session = new Session(m_IOService);
    m_Acceptor.async_accept(new_session->socket(),
        boost::bind(&Server::handle_accept, this, new_session,
            boost::asio::placeholders::error));
}

void Server::handle_accept(Session* new_session,
    const boost::system::error_code& error)
{
    if (!error)
    {
        new_session->start();
        new_session = new Session(m_IOService);
        m_Acceptor.async_accept(new_session->socket(),
            boost::bind(&Server::handle_accept, this, new_session,
                boost::asio::placeholders::error));
    }
    else
    {
        delete new_session;
    }
}
