#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QNetworkAccessManager>
//#include <QNetworkReply>
//#include <QUrl>
//#include <QJsonDocument>
#include <QJsonObject>
//#include <QJsonArray>
#include <QDebug>
#include <QComboBox>
#include <QPalette>
#include <QPixmap>

class CurrencyInfo;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void FillComboBox();
    void FillValue(QString cur);


private slots:
    void on_actionQuit_triggered();
    void changedElement(const QString&);
    void takeInfo();
private:

    QJsonObject jsonObj;
    QComboBox* box;
    CurrencyInfo* currency;
    QStringList curInfo;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
