#include "DatabaseInterface.h"
#include "Base/SqLite.h"
#include <QDebug>

DatabaseInterface::DatabaseInterface(DatabaseInterface::DatabaseDrivers driver, SqlBase::databaseInfo dbInfo)
{
    switch (driver)
    {
        case QSQLITE:
        {
            m_db = new SqLite();
            break;
        }
    }
}

DatabaseInterface::~DatabaseInterface()
{
    delete m_db;
}

bool DatabaseInterface::connectDatabase(SqlBase::databaseInfo info)
{
    return m_db->connectDatabase(info);
}

void DatabaseInterface::createTable(QString name, SqlBase::tableColumns table, bool uniqueValues)
{
    m_db->createTable(name, table, uniqueValues);
}

bool DatabaseInterface::insertValue(SqlBase::tableRow rowValues, QString tableName)
{
    return m_db->insertValue(rowValues, tableName);
}

bool DatabaseInterface::removeValue(QString column, QString value, QString tableName)
{
    return m_db->removeValue(column, value, tableName);
}

bool DatabaseInterface::removeValue(int index, QString tableName)
{
    return m_db->removeValue(index, tableName);
}

bool DatabaseInterface::removeAllData(QString tableName)
{
    return m_db->removeAllData(tableName);
}

SqlBase::tableRow DatabaseInterface::getValue(QString column, QString value, QString tableName)
{
    return m_db->getValue(column, value, tableName);
}

SqlBase::tableRow DatabaseInterface::getValue(int index, QString tableName)
{
    return m_db->getValue(index, tableName);
}

SqlBase::dataTable DatabaseInterface::getAllData(QString tableName)
{
    return m_db->getAllData(tableName);
}

SqlBase::tableColumns DatabaseInterface::getTableHeader(QString tableName)
{
    return m_db->getTableHeader(tableName);
}

bool DatabaseInterface::isExist(QString column, QString value, QString tableName)
{
    return m_db->isExist(column, value, tableName);
}

QString DatabaseInterface::getType(SqlBase::EItemType type, int textMaxLenght)
{
    return m_db->getType(type, textMaxLenght);
}
