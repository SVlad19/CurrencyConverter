#include "currencyinfo.h"

CurrencyInfo::CurrencyInfo(QUrl url){
    manager = new QNetworkAccessManager(this);
    reply = manager->get(QNetworkRequest(url));
    connect(reply,SIGNAL(finished()),this, SLOT(takeInfo()));

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

               foreach(const QJsonValue& val,array){
                   if(val.isObject()){
                       jsonObj = val.toObject();
                       curList.push_back(jsonObj.value("ccy").toString());
                    }
               }
           }
         }else{
            qDebug()<<"Error: "<<reply->errorString();
         }
           reply->deleteLater();
           emit info();
}
