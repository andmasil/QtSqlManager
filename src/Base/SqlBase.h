#ifndef SQLBASE_H
#define SQLBASE_H

//  QT includes
#include <QString>
#include <QDebug>

// QT sql includes
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

// C++ includes
#include <vector>

class SqlBase
{
public:

    enum EItemType
    {
        ID,
        BOOL,
        INTEGER,
        FLOAT,
        TEXT,
        DATE
    };

    struct databaseInfo
    {
        QString name;
        QString user;
        QString password;

        databaseInfo(QString name = 0, QString user = 0, QString password = 0)
        {
            this->name = name;
            this->user = user;
            this->password = password;
        }
    };

    struct singleColumn
    {
        EItemType itemType;
        QString itemName;

        singleColumn(EItemType itemType, QString itemName)
        {
            this->itemType = itemType;
            this->itemName = itemName;
        }
    };

    struct tableColumns
    {
        std::vector<singleColumn> tableHeader;
    };

    struct tableRow
    {
        std::vector<QString> completeRow;
    };

    struct dataTable
    {
        std::vector<tableRow> completeData;
    };

    virtual ~SqlBase();

    // connect/create database
    virtual bool connectDatabase(databaseInfo info) = 0;

    // create table
    virtual void createTable(QString name, tableColumns table, bool uniqueValues) = 0;

    // drop table
    virtual void dropTable(QString name) = 0;

    // add new row to table
    virtual bool insertValue(tableRow rowValues, QString tableName) = 0;

    // remove specific row from table
    virtual bool removeValue(QString column, QString value, QString tableName) = 0;
    virtual bool removeValue(int index, QString tableName) = 0;

    // remove all data from table
    virtual bool removeAllData(QString tableName) = 0;

    // get specific data row
    virtual tableRow getValue(QString column, QString value, QString tableName) = 0;
    virtual tableRow getValue(int index, QString tableName) = 0;

    // get all data
    virtual dataTable getAllData(QString tableName) = 0;

    // get table header
    virtual tableColumns getTableHeader(QString tableName) = 0;

    // check if proper value exist in table
    virtual bool isExist(QString column, QString value, QString tableName) = 0;

    // get specific data type
    virtual QString getType(EItemType type, int textMaxLenght = 0) = 0;

    //virtual QString getTypesString(tableColumns table) = 0;

protected:
    virtual unsigned int getColumnNumber(QString tableName) = 0;
    virtual QString getColumnNames(QString tableName, bool valuePrepare = false) = 0;
    QString getTypesString(tableColumns table);
    QString getColumnsString(tableColumns table);
};

#endif // SQLBASE_H
