#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include "Base/SqlBase.h"

class DatabaseInterface
{
public:
    enum DatabaseDrivers
    {
        QSQLITE = 0
    };

    DatabaseInterface(DatabaseDrivers driver, SqlBase::databaseInfo dbInfo);
    ~DatabaseInterface();

    bool connectDatabase(SqlBase::databaseInfo info);
    void createTable(QString name, SqlBase::tableColumns table, bool uniqueValues);
    bool insertValue(SqlBase::tableRow rowValues, QString tableName = nullptr);
    bool removeValue(QString column, QString value, QString tableName = nullptr);
    bool removeValue(int index, QString tableName = nullptr);
    bool removeAllData(QString tableName = nullptr);
    SqlBase::tableRow getValue(QString column, QString value, QString tableName = nullptr);
    SqlBase::tableRow getValue(int index, QString tableName = nullptr);
    SqlBase::dataTable getAllData(QString tableName = nullptr);
    SqlBase::tableColumns getTableHeader(QString tableName = nullptr);
    bool isExist(QString column, QString value, QString tableName = nullptr);
    QString getType(SqlBase::EItemType type, int textMaxLenght = 0);

private:
    SqlBase *m_db;
};

#endif // DATABASEINTERFACE_H
