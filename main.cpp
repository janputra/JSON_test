#include <QCoreApplication>
#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    QList<QVariant> data;

    QJsonObject _obj{
      {"Test1","Value1"},
      {"Test2","Value2"}
    };


    data.append(QStringList{"Test1","Test2","Test3"});

    QJsonDocument inputDoc = QJsonDocument::fromVariant(QStringList{"Test1","Test2","Test3","Test4"});
    inputDoc.setObject(_obj);
    QString path = "/home/jan/Project/JSON_test/test2.json";
    QByteArray bytes =  inputDoc.toJson(QJsonDocument::Indented);

    QFile file(path);

    if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate)){
        QTextStream iStream(&file);
        iStream.setCodec("utf-8");
        iStream<<bytes;
        file.close();

    }
    else{
        std::cout<<"file open failed"<<std::endl;


    }


   // QFile file(path);

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
