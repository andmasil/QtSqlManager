#include <QCoreApplication>
#include <QDateTime>

#include "Base/SqLite.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //SQLite tests
    SqLite sqlite;
    const QString tableName = "TestTable";
    sqlite.connectDatabase("test.db");
    SqlBase::tableColumns table;
    table.tableHeader.push_back(SqlBase::singleColumn(SqlBase::ID, "id"));
    table.tableHeader.push_back(SqlBase::singleColumn(SqlBase::TEXT, "name"));
    table.tableHeader.push_back(SqlBase::singleColumn(SqlBase::INTEGER, "number"));
    sqlite.createTable(tableName, table, false);
    qDebug() << "----------------------------------------------------------------";
    SqlBase::tableRow data;
    data.completeRow.push_back("danny");
    data.completeRow.push_back("123");
    sqlite.insertValue(data);
    qDebug() << "----------------------------------------------------------------";
    data = SqlBase::tableRow();
    data.completeRow.push_back("tommy");
    data.completeRow.push_back("7007");
    sqlite.insertValue(data);
    qDebug() << "----------------------------------------------------------------";
    data = SqlBase::tableRow();
    data.completeRow.push_back("mark");
    data.completeRow.push_back("69");
    sqlite.insertValue(data);
    qDebug() << "----------------------------------------------------------------";
    data = SqlBase::tableRow();
    data.completeRow.push_back("data3");
    data.completeRow.push_back("data4");
    data.completeRow.push_back("23123");
    sqlite.insertValue(data);
    qDebug() << "----------------------------------------------------------------";
    data = SqlBase::tableRow();
    sqlite.insertValue(data);
    qDebug() << "----------------------------------------------------------------";
    sqlite.isExist("id", "1");
    sqlite.isExist("id", "1111111");
    qDebug() << "----------------------------------------------------------------";
    sqlite.isExist("name", "data1");
    sqlite.isExist("name", "data1111");
    qDebug() << "----------------------------------------------------------------";
    sqlite.isExist("number", "2312323123");
    sqlite.isExist("number", "23123");
    qDebug() << "----------------------------------------------------------------";
    sqlite.removeValue("number", "2312323123");
    sqlite.removeValue("number", "23123");
    qDebug() << "----------------------------------------------------------------";
    sqlite.removeValue("name", "data1");
    sqlite.removeValue("name", "data1111data1111");
    qDebug() << "----------------------------------------------------------------";
    SqlBase::dataTable completeTable = sqlite.getAllData();
    for (int i = 0; i < completeTable.completeData.size(); ++i)
    {
        qDebug() << i+1;
        for (int j = 0; j < completeTable.completeData.at(i).completeRow.size(); ++j)
        {
            qDebug() << completeTable.completeData.at(i).completeRow.at(j);
        }
        qDebug() << "-------------";
    }

    return 0;
}
