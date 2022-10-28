#include "tcpclient.h"

TCPClient::TCPClient()
{
    s = nullptr;
    connect();
}

void TCPClient::connect()
{
    if(s)
        delete s;
    try
    {
        tcp::resolver *resolver = new tcp::resolver(io_service);
        tcp::resolver::query *query = new tcp::resolver::query(tcp::v4(), "127.0.0.1", std::to_string(port));
        tcp::resolver::iterator iterator = resolver->resolve(*query);
        s = new tcp::socket(io_service);
        s->connect(*iterator);
    }
    catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    }
}

TCPClient &TCPClient::getClient()
{
    static TCPClient client;
    return client;
}

TCPClient::~TCPClient()
{
    if(s)
        delete s;
}

std::string TCPClient::messageExchange(const std::string &aId, const std::string &aRequestType, const std::string &aMessage)
{
    if(!s->is_open())
    {
        std::cout << "Socket is CLOSE!" << std::endl;
        connect();
    }
    nlohmann::json req;
    req["UserId"] = aId;
    req["ReqType"] = aRequestType;
    req["Message"] = aMessage;

    std::string request = req.dump();
    boost::asio::write(*s, boost::asio::buffer(request, request.size()));
    return readMessage();
}

std::string TCPClient::readMessage()
{
    boost::asio::streambuf b;
    boost::asio::read_until(*s, b, "\0");
    std::istream is(&b);
    std::string line(std::istreambuf_iterator<char>(is), {});
    return line;
}

