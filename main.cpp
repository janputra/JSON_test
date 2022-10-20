#include <QCoreApplication>
#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path = "/home/jan/JSON_test/test.json";
    QFile file(path);

    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray bytes = file.readAll();
        file.close();

        QJsonParseError jsonError;
        QJsonDocument doc = QJsonDocument::fromJson(bytes , &jsonError);
        if (jsonError.error != QJsonParseError::NoError)
        {
            std::cout<<"fromJson failed: "<<jsonError.errorString().toStdString()<<std::endl;
            return -1;
        }else{
            std::cout<<"fromJson Success  "<<std::endl;

            QJsonObject obj = doc.object();
            QStringList keys = obj.keys();
            for (auto key: keys){
                auto value = obj.take(key);
                if (value.isString()){
                    qDebug()<<key<<":"<<value.toString();
                }else{
                     qDebug()<<key<<":"<<value.toInt();
                }
            }



            return 0;
        }



    }

    return a.exec();
}
