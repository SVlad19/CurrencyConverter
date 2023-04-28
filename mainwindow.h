#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

private:
    QNetworkAccessManager* manager = nullptr;
    QNetworkReply* reply;
    QByteArray response;
    QJsonDocument jsonDoc;
    QJsonObject jsonObj;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
