#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include "tcpclient.h"
#include "Common.hpp"
#include "json.hpp"

class Login : public QDialog
{
    QList<QLineEdit *> m_Fields;
    std::string m_UserId;
    Q_OBJECT
public:
    explicit Login(QDialog *parent = nullptr);
    bool LoginUser();
    std::string getUserId();
public slots:
    void onClickLogin();
    void onClickRegister();
    void onClickExit();
signals:

};

#endif // LOGIN_H
