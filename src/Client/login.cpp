#include "login.h"

Login::Login(QDialog *parent) : QDialog(parent)
{

}

bool Login::LoginUser()
{
    this->setWindowTitle("Login window");
    this->setMinimumSize(280,160);

    QFormLayout form(this);
    {
        QLineEdit *lineEdit = new QLineEdit(this);
        QString label = QString("ID");
        form.addRow(label, lineEdit);
        m_Fields << lineEdit;
    }
    {
        QLineEdit *lineEdit = new QLineEdit(this);
        lineEdit->setEchoMode(QLineEdit::Password);
        QString label = QString("Password");
        form.addRow(label, lineEdit);
        m_Fields << lineEdit;
    }
    QPushButton *loginButton = new QPushButton(this);
    loginButton->setText("Login");
    form.addRow(loginButton);
    connect(loginButton, SIGNAL(clicked()), this, SLOT(onClickLogin()));

    QPushButton *registerButton = new QPushButton(this);
    registerButton->setText("Register");
    form.addRow(registerButton);
    connect(registerButton, SIGNAL(clicked()), this, SLOT(onClickRegister()));

    QPushButton *exitButton = new QPushButton(this);
    exitButton->setText("Exit");
    form.addRow(exitButton);
    connect(exitButton, SIGNAL(clicked()), this, SLOT(onClickExit()));

    this->show();
    return this->exec();
}

size_t Login::getUserId()
{
    return std::atoll(m_UserId.c_str());
}

void Login::onClickLogin()
{
    qDebug() << "Login";
    nlohmann::json jLogin;
    jLogin["username"] = m_Fields.first()->text().toStdString();
    jLogin["password"] = m_Fields.last()->text().toStdString();
    std::string response = TCPClient::getClient().messageExchange("0", Requests::Login, jLogin.dump());
    std::cout << "response " << response << std::endl;
    try {
        auto jResponse = nlohmann::json::parse(response);
        if(jResponse["status"] == "true")
        {
            std::cout << "Login id is " << jResponse["userId"] << std::endl;
            m_UserId = jResponse["userId"].dump();
            std::cout << "Login done" << std::endl;
            this->done(1);
        }
        else
        {
            std::cout << jResponse["msg"] << std::endl;
        }
    } catch (std::exception &e) {
        std::cerr << e.what();
        //msg box needed
    }
}

void Login::onClickRegister()
{
    nlohmann::json jRegister;
    jRegister["username"] = m_Fields.first()->text().toStdString();
    jRegister["password"] = m_Fields.last()->text().toStdString();
    std::string response = TCPClient::getClient().messageExchange("0", Requests::Registration, jRegister.dump());
    std::cout << "response " << response << std::endl;
    try {
        auto jResponse = nlohmann::json::parse(response);
        if(jResponse["status"] == "true")
            std::cout << "Register, id is " << jResponse["userId"] << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what();
        //msg box needed
    }
    //msgBox
}

void Login::onClickExit()
{
    this->done(0);
}

