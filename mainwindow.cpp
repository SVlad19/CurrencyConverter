#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "currencyinfo.h"
#include "fileinfo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette palette = ui->centralwidget->palette();
    QPixmap pixmap{":/image/Image/Privat24_Logo.png"};

    ui->lImage->setPixmap(pixmap.scaled(ui->lImage->width(),ui->lImage->height(),Qt::KeepAspectRatio));

    palette.setColor(QPalette::Window,QColor(212,206,183));

    ui->centralwidget->setAutoFillBackground(true);
    ui->centralwidget->setPalette(palette);
    ui->centralwidget->show();

    currency = std::make_unique<CurrencyInfo>(QUrl("https://api.privatbank.ua/p24api/pubinfo"));
    fileinfo = std::make_unique<FileInfo>();

    connect(currency.get(),SIGNAL(info()),this,SLOT(takeInfo()));
    connect(this,SIGNAL(info(const CurrencyInfo&)),fileinfo.get(),SLOT(WriteToFile(const CurrencyInfo&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FillComboBox()
{
    box = ui->cbCur;

    qDebug()<<curInfo.size()<<"\n";
    for(int i = 0;i<curInfo.size();++i){
        qDebug()<<curInfo[i]<<'\n';
        box->addItem(curInfo[i]);
    }

    connect(box,SIGNAL(currentTextChanged(const QString&)),this,SLOT(changedElement(const QString&)));
}

void MainWindow::FillValue(QString cur)
{
    foreach(const QJsonValue& val,currency->getArray()){
              if(val.isObject()){
                    jsonObj = val.toObject();
                       if(cur == jsonObj.value("ccy").toString()){
                           ui->lVAL->setText("1 " + cur + " = ");
                           QString curString = jsonObj.value("buy").toString();
                           ui->lUAH->setText((curString.left(5) + " UAH"));
                       }
                  }
    }
}

void MainWindow::takeInfo()
{
    curInfo = currency->takeCurrency();
    FillValue(curInfo[0]);
    FillComboBox();
    emit info(*currency);
}

void MainWindow::changedElement(const QString & element)
{
    FillValue(element);
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionClear_file_triggered()
{
    fileinfo->ClearFile();
}

