#ifndef SQLITETESTS_H
#define SQLITETESTS_H

#include "BaseTest.h"
#include "SqLite.h"

class SqLiteTests : public BaseTest
{
    Q_OBJECT
public:
    explicit SqLiteTests();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void connectDatabaseTest();
    void createTableTest();
    void dropTableTest();
    void insertValueTest();

private:
    SqLite m_sqlite;
    SqlBase::databaseInfo m_dbInfo;
};

#endif // SQLITETESTS_H
