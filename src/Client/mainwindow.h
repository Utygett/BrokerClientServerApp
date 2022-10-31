#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "login.h"

#include <boost/asio.hpp>
#include <QLabel>
#include <QUuid>
#include "../Common.hpp"
#include "../json.hpp"
#include "tcpclient.h"
using boost::asio::ip::tcp;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    enum {PURCHASE, SELL};
    Q_OBJECT
    Login m_loginUser;
    std::string m_UserId;
	void initDOM(nlohmann::json jDOM);
	void initUi();
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
private slots:
    void on_currencyComboBox_activated(const QString &arg1);
    void on_pbBuy_clicked();
    void on_pbSell_clicked();
	void getCurrentCurrencyInfoSlot();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
