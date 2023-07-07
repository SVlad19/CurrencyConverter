#include "fileinfo.h"
#include "currencyinfo.h"

FileInfo::FileInfo()
{
    file = std::make_unique<QFile>(QCoreApplication::applicationDirPath() + "/info.txt");
    qDebug() << file->fileName();

}

void FileInfo::WriteToFile(const CurrencyInfo& cur)
{
    if(file->open(QIODevice::Append)){
        qDebug()<<"The file was created!";
        QTextStream stream{file.get()};
        QDateTime data = QDateTime::currentDateTime();
        QString value;

        foreach(const QJsonValue& val,cur.getArray()){
                  if(val.isObject()){
                        QJsonObject jsonObj = val.toObject();
                               value += jsonObj.value("ccy").toString() + " = " + jsonObj.value("buy").toString() + " UAH\n";
                      }
        }

         if(file->size() == 0){
             stream << (QString(data.toString()) + ":\n" + value);
         }else{
             file->seek(file->size());
             stream << "\n\n" + (QString(data.toString()) + ":\n" + value);
         }
         file->close();
    }else{
        qDebug()<<"We can`t open the file!";
        QMessageBox::information(nullptr,"Error","We can`t open the file!");
    }


}

FileInfo::~FileInfo()
{
    qDebug()<<"FileInfo::~FileInfo()";

}

void FileInfo::ClearFile()
{
    if(file->open(QIODevice::Append)){
        qDebug()<<"The file opened!";
        file->resize(0);
    }else{
        qDebug()<<"We can`t open the file!";
        QMessageBox::information(nullptr,"Error","We can`t open the file!");
    }
     file->close();
}



