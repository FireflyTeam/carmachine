//#include "videomediadatabase.h"

//#include <QtSql/qsqlquery.h>
//#include <QVariant>
//#include <QSqlError>

//// 连接Video数据库
//void videoMediaDataBase::connectVideoInfo()
//{
//    QSqlDatabase datebase;
//    if(QSqlDatabase::contains("qt_sql_default_connection"))
//        datebase = QSqlDatabase::database("qt_sql_default_connection");
//    else
//        datebase = QSqlDatabase::addDatabase("QSQLITE");
//    datebase.setDatabaseName("VideoDateBase.db");
//    datebase.open();
//    datebase.exec(QString("create table if not exists videoinfo(id INT ,videoname TEXT,videopath TEXT,duration TEXT)"));
//}

//void videoMediaDataBase::removeVideo(const QString& videoName,const QString& path)
//{
//    connectVideoInfo();
//    QSqlQuery query;

//    query.prepare(QString("delete from videoinfo where videoname = ?,videopath = ?"));
//    query.addBindValue(videoName);
//    query.addBindValue(path);
//    query.exec();
//}


//void videoMediaDataBase::addVideo(const QString& videoName,const QString& path,const QString& duration)
//{
//    connectVideoInfo();
//    QSqlQuery query;
//    query.prepare(QString("select * from videoinfo where id = (select max(id) from videoinfo)"));
//    query.exec();

//    int  index=0;
//    while(query.next()) // 取最大值
//    {
//        index= query.value("id").toInt();
//        index++;
//    }

//    query.prepare(QString("INSERT INTO videoinfo(id,videoname,videopath,duration)"
//                          "VALUES (:id,:videoname,:videopath,:duration)"));
//    query.bindValue(":id", index);
//    query.bindValue(":videoname", videoName);
//    query.bindValue(":videopath", path);
//    query.bindValue(":duration", duration);
//    query.exec();
//}


//QVector<QStringList> videoMediaDataBase::getVideoInfo()
//{
//    connectVideoInfo();
//    QStringList list1;
//    QStringList list2;
//    QStringList list3;

//    QSqlQuery sql_query;
//    sql_query.prepare(QString("select * from videoinfo order by id"));

//    if(!sql_query.exec())
//    {
//        //        qDebug()<<sql_query.lastError();
//    }
//    else
//    {
//        while(sql_query.next())
//        {
//            QString songname = sql_query.value("videoname").toString();
//            QString songurl = sql_query.value("videopath").toString();
//            QString songdur=sql_query.value("duration").toString();

//            list1<<songname;
//            list2<<songurl;
//            list3<<songdur;
//        }
//    }
//    QVector<QStringList> vec;
//    vec<<list1<<list2<<list3;
//    return vec;
//}
