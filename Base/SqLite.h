#ifndef SQLITE_H
#define SQLITE_H

#include "SqlBase.h"

class SqLite : public SqlBase
{
public:
    SqLite();

    bool connectDatabase(databaseInfo info);
    void createTable(QString name, tableColumns table, bool uniqueValues);
    bool insertValue(tableRow rowValues, QString tableName = 0);
    bool removeValue(QString column, QString value, QString tableName = 0);
    bool removeValue(int index, QString tableName = 0);
    bool removeAllData(QString tableName = 0);
    tableRow getValue(QString column, QString value, QString tableName = 0);
    tableRow getValue(int index, QString tableName = 0);
    dataTable getAllData(QString tableName = 0);
    tableColumns getTableHeader(QString tableName = 0);
    bool isExist(QString column, QString value, QString tableName = 0);
    QString getType(EItemType type, int textMaxLenght = 0);

protected:
    unsigned int getColumnNumber(QString tableName);
    QString getColumnNames(QString tableName, bool valuePrepare = false);


private:
};

#endif // SQLITE_H
