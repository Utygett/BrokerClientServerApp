#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    if(m_loginUser.LoginUser())
    {
        this->show();
        ui->setupUi(this);
        qDebug() << "Ready to work";
        startInitUi();
    }
    else
    {
//        this->deleteLater();
        qDebug() << "Wont to quit";
        exit(0);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startInitUi()
{
    std::string currencyInfo = TCPClient::getClient().messageExchange(m_UserId, Requests::Init, "");
    std::cout << currencyInfo << std::endl;
    try {
        nlohmann::json jInitInfo = nlohmann::json::parse(currencyInfo);
        if(jInitInfo["status"] == "false")
        {
            //messabe box or function error with exit
        }
        nlohmann::json jCurrency = jInitInfo["currInfo"];
        for(int i = 0; i < jCurrency.size(); ++i)
        {
            nlohmann::json jRecord = jCurrency[i];
            QString currencyPair(jRecord["name"].dump().c_str());
            currencyPair = currencyPair.remove('"');
            std::cout << jRecord["name"].dump().c_str() << std::endl;
            ui->currencyComboBox->addItem(currencyPair);
            if(i == 0)
            {
                ui->lbCurrCourse->setText(jRecord["price"].dump().c_str());
                ui->lbFirstCurrName->setText(currencyPair.split('/').first());
                ui->lbSecondCurrencyName->setText(currencyPair.split('/').last());
            }
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        //message box
    }
}

void MainWindow::startLogic()
{
    std::cout << "Response " << TCPClient::getClient().messageExchange("0", Requests::Registration, "Hellow") << std::endl;
}

void MainWindow::on_currencyComboBox_activated(const QString &arg1)
{
    qDebug() << "Combo xob activated" << arg1;
}

void MainWindow::on_pbBuy_clicked()
{
    try {
        nlohmann::json jBuyRequest;
        jBuyRequest["price"] = ui->lineBuyPrice->text().toDouble();
        jBuyRequest["amount"] = ui->lineBuyAmount->text().toInt();
        jBuyRequest["id"] = std::atoi(m_UserId.c_str());
        jBuyRequest["type"] = PURCHASE;
        jBuyRequest["uuid"] = "sdfj32hr97hgfkg";
        nlohmann::json jRequest;
        jRequest["currency"] = ui->currencyComboBox->currentText().toStdString();
        jRequest["bid"] = jBuyRequest;
        std::cout << TCPClient::getClient().messageExchange(m_UserId, Requests::NewBid, jRequest.dump()) << std::endl;

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        //message box
    }
}

void MainWindow::on_pbSell_clicked()
{
    try {
        nlohmann::json jSellRequest;
        jSellRequest["price"] = ui->lineSellPrice->text().toDouble();
        jSellRequest["amount"] = ui->lineSellAmount->text().toInt();
        jSellRequest["id"] = std::atoi(m_UserId.c_str());
        jSellRequest["type"] = SELL;
        jSellRequest["uuid"] = "sdfj32hdhfhg";
        nlohmann::json jRequest;
        jRequest["currency"] = ui->currencyComboBox->currentText().toStdString();
        jRequest["bid"] = jSellRequest;
        std::cout << TCPClient::getClient().messageExchange(m_UserId, Requests::NewBid, jRequest.dump()) << std::endl;

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        //message box
    }
}
