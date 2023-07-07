#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QDebug>
#include <QComboBox>
#include <QPalette>
#include <QPixmap>
#include <memory>

class CurrencyInfo;
class FileInfo;

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

signals:
    void info(const CurrencyInfo& cur);
private slots:
    void on_actionQuit_triggered();
    void changedElement(const QString&);
    void takeInfo();
    void on_actionClear_file_triggered();

private:

    QJsonObject jsonObj;
    QComboBox* box;
    std::unique_ptr<CurrencyInfo> currency;
    std::unique_ptr<FileInfo> fileinfo;
    QStringList curInfo;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
