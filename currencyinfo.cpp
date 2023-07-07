#include "currencyinfo.h"

CurrencyInfo::CurrencyInfo(QUrl url){
    manager = std::make_unique<QNetworkAccessManager>(this);
    reply = manager->get(QNetworkRequest(url));
    connect(reply,SIGNAL(finished()),this, SLOT(takeInfo()));

}

CurrencyInfo::~CurrencyInfo()
{
    qDebug() << "CurrencyInfo::~CurrencyInfo()";
}

QStringList CurrencyInfo::takeCurrency() const
{
    return curList;
}

QJsonArray CurrencyInfo::getArray() const
{
    return array;
}

void CurrencyInfo::takeInfo()
{
    if(reply->error() == QNetworkReply::NoError) {
           response = reply->readAll();
           jsonDoc = QJsonDocument::fromJson(response);

           if(jsonDoc.isArray()){
               array = jsonDoc.array();

               for(auto val: array){
                   if(val.isObject()){
                       jsonObj = val.toObject();
                       curList.push_back(jsonObj.value("ccy").toString());
                    }
               }
           }
         }else{
            qDebug()<<"Error: "<<reply->errorString();
            QMessageBox::information(nullptr,"Error",reply->errorString());
         }
           reply->deleteLater();
           emit info();
}
