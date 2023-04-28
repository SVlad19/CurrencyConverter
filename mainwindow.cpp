#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QUrl url("https://api.privatbank.ua/p24api/pubinfo");
    manager = new QNetworkAccessManager(this);
    reply = manager->get(QNetworkRequest(url));
    QObject::connect(reply,&QNetworkReply::finished,this,[=](){

    if(reply->error() == QNetworkReply::NoError) {
       response = reply->readAll();
       jsonDoc = QJsonDocument::fromJson(response);

       if(jsonDoc.isArray()){
           QJsonArray array = jsonDoc.array();
           foreach(const QJsonValue& val,array){
               if(val.isObject()){
                   jsonObj = val.toObject();
                    if(jsonObj.value("ccy").toString() == "USD"){
                       QString curVal = jsonObj.value("buy").toString();
                       ui->lUAH->setText(curVal.left(5));
                   }
               }
           }
       }


     }else{
        qDebug()<<"Error: "<<reply->errorString();
     }

       reply->deleteLater();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

