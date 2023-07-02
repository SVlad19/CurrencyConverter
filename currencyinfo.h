#ifndef CURRENCYINFO_H
#define CURRENCYINFO_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class CurrencyInfo :public QObject
{
    Q_OBJECT
public:
    CurrencyInfo() = delete;
    explicit CurrencyInfo(QUrl _url);

    QStringList takeCurrency()const;
    QJsonArray getArray()const;

signals:
    void info();

private slots:
     void takeInfo();

private:
     QNetworkAccessManager* manager;
     QObject* obj;
     QNetworkReply* reply;
     QByteArray response;
     QJsonDocument jsonDoc;
     QJsonObject jsonObj;
     QStringList curList;
     QJsonArray array;
};

#endif // CURRENCYINFO_H
