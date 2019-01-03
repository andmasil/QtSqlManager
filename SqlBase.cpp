#include "SqlBase.h"

QString SqlBase::getTypesString(SqlBase::tableColumns table)
{
    QString result = "";
    for (int i = 0; i < table.tableHeader.size(); ++i)
    {
        result.append(table.tableHeader.at(i).itemName + " " + table.tableHeader.at(i).itemType + ", ");
    }
    result.chop(2);
    return result;
}
