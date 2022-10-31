#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 * Конструктор, запускаем окно (входа\регистрации) и инициализируем интерфейс.
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    if(m_loginUser.LoginUser())
    {
        this->show();
        ui->setupUi(this);
        qDebug() << "Ready to work";
        initUi();
    }
    else
    {
//        this->deleteLater();
        qDebug() << "Wont to quit";
        exit(0);
    }
	m_interfaceInitTimer =  new QTimer(this);
	connect(m_interfaceInitTimer, SIGNAL(timeout()), this, SLOT(getCurrentCurrencyInfoSlot()));
	m_interfaceInitTimer->start(5000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 *  Инициализируем интерфейс, получаем данные о валютах и текущих заявках.
 */

void MainWindow::initUi()
{
	m_UserId = m_loginUser.getUserId();
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
			if(ui->currencyComboBox->count() < jCurrency.size())
            	ui->currencyComboBox->addItem(currencyPair);
			// TODO убрать отсюда инициализацию цены, в слот получения информации вызывать его в конце метода.
			std::string currentCurrency = ui->currencyComboBox->currentText().toStdString();
            if(currentCurrency == currencyPair.toStdString())
            {
				nlohmann::json jDOM = jInitInfo["DOM"];
				initDOM(jDOM[currentCurrency]);
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

void MainWindow::initDOM(nlohmann::json jDOM)
{
	std::cout << "DOM INIT " << jDOM.dump(3) << std::endl;
	ui->tbBuyOrders->clear();
	for(int i = 0; i < jDOM["buy"].size(); ++i)
	{
		QString order = jDOM["buy"][i].dump().c_str();
		ui->tbBuyOrders->append(order);
	}
	ui->tbSellOrders->clear();
	for(int i = 0; i < jDOM["sell"].size(); ++i)
	{
		QString order = jDOM["sell"][i].dump().c_str();
		ui->tbSellOrders->append(order);
	}
}

void MainWindow::getCurrentCurrencyInfoSlot()
{
	initUi();
}

/*
 * Выпадающий список валют, при переходе должен отправляться запрос к серверу что бы получить данные
 * по валюте.
 */

void MainWindow::on_currencyComboBox_activated(const QString &arg1)
{
    qDebug() << "Combo xob activated" << arg1;
	initUi();
}

/*
 * Слот для кнопки Купить, отправляет на сервер заявку на покупку валюты.
 */

void MainWindow::on_pbBuy_clicked()
{
    try {
        nlohmann::json jBuyRequest;
        jBuyRequest["price"] = ui->lineBuyPrice->text().toDouble();
        jBuyRequest["amount"] = ui->lineBuyAmount->text().toInt();
        jBuyRequest["id"] = std::atoi(m_UserId.c_str());
        jBuyRequest["type"] = PURCHASE;
        jBuyRequest["uuid"] = QUuid::createUuid().toString().toStdString();
        nlohmann::json jRequest;
        jRequest["currency"] = ui->currencyComboBox->currentText().toStdString();
        jRequest["bid"] = jBuyRequest;
        std::cout << "Answer: " <<TCPClient::getClient().messageExchange(m_UserId, Requests::NewBid, jRequest.dump()) << std::endl;

    } catch (std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
        //message box
    }
}

/*
 * Слот для кнопки Продать, отправляет на сервер заявку на продажу валюты.
 */

void MainWindow::on_pbSell_clicked()
{
    try {
        nlohmann::json jSellRequest;
        jSellRequest["price"] = ui->lineSellPrice->text().toDouble();
        jSellRequest["amount"] = ui->lineSellAmount->text().toInt();
        jSellRequest["id"] = std::atoi(m_UserId.c_str());
        jSellRequest["type"] = SELL;
        jSellRequest["uuid"] = QUuid::createUuid().toString().toStdString();
        nlohmann::json jRequest;
        jRequest["currency"] = ui->currencyComboBox->currentText().toStdString();
        jRequest["bid"] = jSellRequest;
        std::cout << "Answer: " <<TCPClient::getClient().messageExchange(m_UserId, Requests::NewBid, jRequest.dump()) << std::endl;

    } catch (std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
        //message box
    }
}
