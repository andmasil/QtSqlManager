#include <QCoreApplication>

#include "SqLite.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //test
    SqLite sqlite;
    if (sqlite.connectDatabase("test.db"))
    {
        SqlBase::tableColumns table;
        table.tableHeader.push_back(SqlBase::singleColumn("INTEGER PRIMARY KEY AUTOINCREMENT", "id"));
        table.tableHeader.push_back(SqlBase::singleColumn("TEXT", "name"));
        table.tableHeader.push_back(SqlBase::singleColumn("INTEGER", "number"));
        sqlite.createTable("TestTable", table);
    }

    return a.exec();
}
