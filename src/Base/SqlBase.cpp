#include "SqlBase.h"

QString SqlBase::getTypesString(SqlBase::tableColumns table)
{
    QString result = "";
    unsigned int tableSize = table.tableHeader.size();
    for (unsigned int i = 0; i < tableSize; ++i)
    {
        result.append(table.tableHeader.at(i).itemName + " " +
                      getType(table.tableHeader.at(i).itemType) + ", ");
    }
    result.chop(2);
    return result;
}

QString SqlBase::getColumnsString(SqlBase::tableColumns table)
{
    QString result = "";
    unsigned int tableSize = table.tableHeader.size();
    for (unsigned int i = 0; i < tableSize; ++i)
    {
        if (table.tableHeader.at(i).itemType != ID)
        {
            result.append(table.tableHeader.at(i).itemName + ", ");
        }
    }
    result.chop(2);
    return result;
}
