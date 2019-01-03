#include "SqLite.h"

SqLite::SqLite()
{

}

bool SqLite::connectDatabase(QString name, QString user, QString password)
{
    bool result = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(name);
    if(!db.open())
    {
        qWarning() << "SqLite open/create failed: " << db.lastError();
    }
    else
    {
        qDebug() << "SqLite open/create sucessful";
        result = true;
    }
    return result;
}

void SqLite::createTable(QString name, SqlBase::tableColumns table)
{
    QString command = QString("CREATE TABLE %1 (%2)").arg(name).arg(getTypesString(table));
    QSqlQuery query(command);
    qDebug() << "Query exec: " << command;
    if (!query.exec())
    {
        qDebug() << "Couldn't create the table or might already exist.";
    }

    m_lastCreatedTableName = name;
}

bool SqLite::insertValue(SqlBase::tableRow rowValues, QString tableName)
{

}

bool SqLite::removeValue(QString column, QString value, QString tableName)
{

}

bool SqLite::removeValue(int index, QString tableName)
{

}

bool SqLite::removeAllData(QString tableName)
{

}

SqlBase::tableRow SqLite::getValue(QString column, QString value, QString tableName)
{

}

SqlBase::tableRow SqLite::getValue(int index, QString tableName)
{

}

SqlBase::dataTable SqLite::getAllData(QString tableName)
{

}

SqlBase::tableColumns SqLite::getTableHeader(QString tableName)
{

}

bool SqLite::isExist(QString column, QString value, QString tableName)
{

}

QString SqLite::getType(SqlBase::EItemType type, int textMaxLenght)
{

}
