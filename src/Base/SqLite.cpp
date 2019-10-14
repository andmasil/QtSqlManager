#include "SqLite.h"

SqLite::SqLite()
{

}

SqLite::~SqLite()
{

}

bool SqLite::connectDatabase(databaseInfo info)
{
    bool result = false;

    if (nullptr != info.name)
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(info.name);
        if(!db.open())
        {
            qWarning() << "SqLite open/create failed: " << db.lastError();
        }
        else
        {
            qDebug() << "SqLite open/create sucessful";
            result = true;
        }
    }
    return result;
}

void SqLite::createTable(QString name, SqlBase::tableColumns table, bool uniqueValues)
{
    QString command;

    if (uniqueValues)
    {
        command = QString("CREATE TABLE %1 (%2, UNIQUE(%3))").arg(name)
                .arg(getTypesString(table))
                .arg(getColumnsString(table));
    }
    else
    {
        command = QString("CREATE TABLE %1 (%2)").arg(name)
                .arg(getTypesString(table));
    }

    QSqlQuery query(command);
    qDebug() << "Query exec: " << command;
    if (!query.exec())
    {
        qDebug() << query.lastError();
    }
}

void SqLite::dropTable(QString name)
{
    QString command = QString("DROP TABLE %1").arg(name);
    QSqlQuery query(command);
    qDebug() << "Query exec: " << command;
}

bool SqLite::insertValue(SqlBase::tableRow rowValues, QString tableName)
{
    bool result = false;

    unsigned int paramsNumber = rowValues.completeRow.size();
    if ((0 < paramsNumber) && (paramsNumber == getColumnNumber(tableName)))
    {
        QString command = QString("INSERT INTO %1 (%2) VALUES (%3)").arg(tableName)
                .arg(getColumnNames(tableName))
                .arg(getColumnNames(tableName, true));
        QSqlQuery query;
        query.prepare(command);

        for (unsigned int i = 0; i < paramsNumber; ++i)
        {
            query.bindValue(static_cast<int>(i), rowValues.completeRow.at(i));
        }

        if (!query.exec())
        {
            qWarning() << "ERROR: " << query.lastError().text();
        }
        else
        {
            qDebug() << "Inserted " << rowValues.completeRow.at(0);
            result = true;
        }
    }
    else
    {
        qDebug() << "Not inserted - wrong params number";
    }
    return result;
}

bool SqLite::removeValue(QString column, QString value, QString tableName)
{
    QSqlQuery query;
    QString command;
    bool ret = false;

    if (isExist(column, value, tableName))
    {
        command = QString("DELETE FROM %1 WHERE %2 = (\"%3\")").arg(tableName)
                .arg(column)
                .arg(value);
        ret = query.exec(command);
        if (!ret)
        {
            qDebug() << query.lastError();
        }
    }

    qDebug() << "removeValue " << column << " " << value << " = " << ret;
    return ret;
}

bool SqLite::removeValue(int index, QString tableName)
{
    Q_UNUSED(index)
    Q_UNUSED(tableName)
    return false;
}

bool SqLite::removeAllData(QString tableName)
{
    QSqlQuery removeQuery;
    bool ret = false;
    removeQuery.prepare("DELETE FROM " + tableName);
    if (!removeQuery.exec())
    {
        qDebug() << "remove all contacts failed: " << removeQuery.lastError();
    }
    else
    {
        qDebug() << "removed all data from " << tableName;
        ret = true;
    }
    return ret;
}

SqlBase::tableRow SqLite::getValue(QString column, QString value, QString tableName)
{
    Q_UNUSED(column)
    Q_UNUSED(value)
    Q_UNUSED(tableName)
    return SqlBase::tableRow();
}

SqlBase::tableRow SqLite::getValue(int index, QString tableName)
{
    Q_UNUSED(index)
    Q_UNUSED(tableName)
    return SqlBase::tableRow();
}

SqlBase::dataTable SqLite::getAllData(QString tableName)
{
    dataTable completeTable;
    tableRow row;
    QString command = QString("SELECT * FROM %1").arg(tableName);
    QSqlQuery query(command);
    QString tableColumnsName = getColumnNames(tableName);
    QString firstTableColumnName = tableColumnsName.left(tableColumnsName.indexOf(','));
    int firstItem = query.record().indexOf(firstTableColumnName);

    if (firstItem >= 0)
    {
        while (query.next())
        {
            row = tableRow();
            for (int i = 0; i < getColumnNumber(tableName); ++i)
            {
                row.completeRow.push_back(query.value(firstItem+i).toString());
            }
            completeTable.completeData.push_back(row);
        }
    }

    return completeTable;
}

SqlBase::tableColumns SqLite::getTableHeader(QString tableName)
{
    Q_UNUSED(tableName)
    return SqlBase::tableColumns();
}

bool SqLite::isExist(QString column, QString value, QString tableName)
{
    bool ret = false;
    QString command;
    QSqlQuery query;

    command = QString("SELECT %2 FROM %1 WHERE %2 = (\"%3\")").arg(tableName)
            .arg(column)
            .arg(value);
    if (query.exec(command))
    {
        if (query.next())
        {
            ret = true;
        }
    }
    else
    {
        qDebug() << query.lastError();
    }
    qDebug() << "isExist " << column << " " << value << " = " << ret;
    return ret;
}

QString SqLite::getType(SqlBase::EItemType type, int textMaxLenght)
{
    Q_UNUSED(textMaxLenght)
    QString result;
    switch (type)
    {
    case ID:
    {
        result = "INTEGER PRIMARY KEY AUTOINCREMENT";
        break;
    }
    case BOOL:
    {
        result = "BOOLEAN";
        break;
    }
    case FLOAT:
    {
        result = "REAL";
        break;
    }
    case INTEGER:
    {
        result = "INTEGER";
        break;
    }
    case TEXT:
    {
        result = "TEXT";
        break;
    }
    case DATE:
    {
        result = "";
        break;
    }
    }
    return result;
}

unsigned int SqLite::getColumnNumber(QString tableName)
{
    unsigned int result = 0;

    QSqlQuery query;
    if (query.exec(QString("PRAGMA table_info(%1)").arg(tableName)))
    {
        while (query.next())
        {
            result++;
        }
    }

    if (0 < result)
    {
        result--;
    }

    return result;
}

QString SqLite::getColumnNames(QString tableName, bool valuePrepare)
{
    QString result = "";

    QSqlQuery query;
    if (query.exec(QString("PRAGMA table_info(%1)").arg(tableName)))
    {
        while (query.next())
        {
            if (0 != query.at() && valuePrepare)
            {
                result.append(":" + query.value(1).toString() + ", ");
            }
            else if (0 != query.at())
            {
                result.append(query.value(1).toString() + ", ");
            }
        }
    }

    result.chop(2);
    return result;
}
