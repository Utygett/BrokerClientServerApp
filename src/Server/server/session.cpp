#include "session.h"

Session::Session(boost::asio::io_service& io_service)
    : m_Socket(io_service)
{
}

tcp::socket &Session::socket()
{
    return m_Socket;
}

// TODO Узнать как это работает

void Session::start()
{
    m_Socket.async_read_some(boost::asio::buffer(m_DataBuffer, max_length),
        boost::bind(&Session::handle_read, this,
            boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

// TODO Убрать лес ифелсов и сделать свитчкейз

/*
 * Получаем сообщение от клиента, парсим его и даем ответ.
 */

void Session::handle_read(const boost::system::error_code &error, size_t bytes_transferred)
{
    if (!error)
    {
        m_DataBuffer[bytes_transferred] = '\0';
        // Парсим json, который пришёл нам в сообщении.
        auto j = nlohmann::json::parse(m_DataBuffer);
        auto reqType = j["ReqType"];
        std::cout << j.dump(2) << std::endl;
        std::cout << "^^^^^^^^^^^^^^^^^^" << std::endl;
        std::string reply = "Error! Unknown request type";
        if (reqType == Requests::Registration)
        {
            // Запрос на регистрацию пользователя.
            // Добавляем нового пользователя и возвращаем его ID.
            reply = Core::getCore().registerNewUser(j["Message"]);
        }
        else if (reqType == Requests::NewBid)
        {
            // Запрос на новую заявку.
            // Проверяем можем ли сразу ее исполнить, если нет то добавляем в стакан.
            reply = Core::getCore().newBid(j["Message"]);
        }
        else if (reqType == Requests::Info)
        {
            // Запрос на информацию по заявкам.
            // Получаем информацию о активных заявках, а так же узнаем если наши заявки исполнены.
            reply = Core::getCore().getInfo(j["UserId"]);
        }
        else if (reqType == Requests::Login)
        {
            // Запрос на информацию по заявкам.
            // Получаем информацию о активных заявках, а так же узнаем если наши заявки исполнены.
            reply = Core::getCore().loginUser(j["Message"]);
        }
        else if (reqType == Requests::Init)
        {
            std::cout << "Init querry request" << std::endl;
            // Запрос на информацию по заявкам.
            // Получаем информацию о активных заявках, а так же узнаем если наши заявки исполнены.
            reply = Core::getCore().getCurrencyList(j["UserId"]);
        }
        std::cout << "Reply is:" << reply << std::endl;
		std::cout << "Reply size is: " << reply.size() << std::endl;
        boost::asio::async_write(m_Socket,
            boost::asio::buffer(reply.c_str(), reply.size()),
            boost::bind(&Session::handle_write, this,
                boost::asio::placeholders::error));
    }
    else
    {
        delete this;
    }
}

/*
 * Пишем ответ клиенту.
 */

// TODO понять как это работает.

void Session::handle_write(const boost::system::error_code &error)
{
    if (!error)
    {
		std::cout  << "Data bufer" << m_DataBuffer << std::endl;
        m_Socket.async_read_some(boost::asio::buffer(m_DataBuffer, max_length),
            boost::bind(&Session::handle_read, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        delete this;
    }
}
