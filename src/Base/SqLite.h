#ifndef SQLITE_H
#define SQLITE_H

#include "SqlBase.h"

class SqLite : public SqlBase
{
public:
    SqLite();

    bool connectDatabase(databaseInfo info);
    void createTable(QString name, tableColumns table, bool uniqueValues);
    bool insertValue(tableRow rowValues, QString tableName = nullptr);
    bool removeValue(QString column, QString value, QString tableName = nullptr);
    bool removeValue(int index, QString tableName = nullptr);
    bool removeAllData(QString tableName = nullptr);
    tableRow getValue(QString column, QString value, QString tableName = nullptr);
    tableRow getValue(int index, QString tableName = nullptr);
    dataTable getAllData(QString tableName = nullptr);
    tableColumns getTableHeader(QString tableName = nullptr);
    bool isExist(QString column, QString value, QString tableName = nullptr);
    QString getType(EItemType type, int textMaxLenght = 0);

protected:
    unsigned int getColumnNumber(QString tableName);
    QString getColumnNames(QString tableName, bool valuePrepare = false);


private:
};

#endif // SQLITE_H
