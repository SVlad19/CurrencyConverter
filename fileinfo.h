#ifndef FILEINFO_H
#define FILEINFO_H

#include <QObject>
#include <QCoreApplication>
#include <QFile>
#include <QDateTime>

class CurrencyInfo;

class FileInfo : public QObject
{
    Q_OBJECT
public:
    FileInfo();
    ~FileInfo();

    void ClearFile();
signals:

private slots:
    void WriteToFile(const CurrencyInfo&);
private:
    std::unique_ptr<QFile> file;
};

#endif // FILEINFO_H
