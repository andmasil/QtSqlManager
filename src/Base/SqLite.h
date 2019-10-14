#ifndef SQLITE_H
#define SQLITE_H

#include "SqlBase.h"

class SqLite : public SqlBase
{
public:
    SqLite();
    ~SqLite();

    bool connectDatabase(databaseInfo info);
    void createTable(QString name, tableColumns table, bool uniqueValues);
    void dropTable(QString name);
    bool insertValue(tableRow rowValues, QString tableName);
    bool removeValue(QString column, QString value, QString tableName);
    bool removeValue(int index, QString tableName);
    bool removeAllData(QString tableName);
    tableRow getValue(QString column, QString value, QString tableName);
    tableRow getValue(int index, QString tableName);
    dataTable getAllData(QString tableName);
    tableColumns getTableHeader(QString tableName);
    bool isExist(QString column, QString value, QString tableName);
    QString getType(EItemType type, int textMaxLenght = 0);

protected:
    unsigned int getColumnNumber(QString tableName);
    QString getColumnNames(QString tableName, bool valuePrepare = false);


private:
};

#endif // SQLITE_H
