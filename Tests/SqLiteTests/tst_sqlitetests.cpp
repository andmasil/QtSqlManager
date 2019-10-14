#include <QtTest>
#include "SqLite.h"

const QString DEFAULT_TEST_TABLE = "testTable";

class SqLiteTests : public QObject
{
    Q_OBJECT

public:
    SqLiteTests();
    ~SqLiteTests();

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

SqLiteTests::SqLiteTests()
{

}

SqLiteTests::~SqLiteTests()
{

}

void SqLiteTests::initTestCase()
{
    QCOMPARE(m_sqlite.connectDatabase(m_dbInfo), false);
    m_dbInfo.name = "unitTest.db";
    QCOMPARE(m_sqlite.connectDatabase(m_dbInfo), true);

    SqlBase::tableColumns table;
    table.tableHeader.push_back(SqlBase::singleColumn(SqlBase::ID, "id"));
    table.tableHeader.push_back(SqlBase::singleColumn(SqlBase::TEXT, "name"));
    table.tableHeader.push_back(SqlBase::singleColumn(SqlBase::INTEGER, "number"));
    m_sqlite.createTable(DEFAULT_TEST_TABLE, table, false);
}

void SqLiteTests::cleanupTestCase()
{
}

void SqLiteTests::connectDatabaseTest()
{
    //tested in initTestCase()
}

void SqLiteTests::createTableTest()
{
    SqlBase::tableColumns table;
    table.tableHeader.push_back(SqlBase::singleColumn(SqlBase::ID, "id"));
    table.tableHeader.push_back(SqlBase::singleColumn(SqlBase::TEXT, "name"));
    table.tableHeader.push_back(SqlBase::singleColumn(SqlBase::INTEGER, "number"));

    QString tableName;
    //check uniq data table
    tableName = "uniqTable";
    m_sqlite.createTable(tableName, table, true);
    m_sqlite.removeAllData(tableName);

    SqlBase::tableRow data;
    data.completeRow.push_back("danny");
    data.completeRow.push_back("123");
    QVERIFY(m_sqlite.insertValue(data, tableName));
    QCOMPARE(m_sqlite.insertValue(data, tableName), false);


    //check nouniq data table
    tableName = "noUniqTable";
    m_sqlite.createTable(tableName, table, false);
    m_sqlite.removeAllData(tableName);

    QVERIFY(m_sqlite.insertValue(data, tableName));
    QVERIFY(m_sqlite.insertValue(data, tableName));\
}

void SqLiteTests::dropTableTest()
{
    SqlBase::tableColumns table;
    table.tableHeader.push_back(SqlBase::singleColumn(SqlBase::ID, "id"));
    table.tableHeader.push_back(SqlBase::singleColumn(SqlBase::TEXT, "name"));

    m_sqlite.createTable("toRemove", table, false);

    m_sqlite.dropTable("toRemove");
    m_sqlite.dropTable("toRemove2");
}

void SqLiteTests::insertValueTest()
{
    m_sqlite.removeAllData(DEFAULT_TEST_TABLE);

    SqlBase::tableRow data;
    data.completeRow.push_back("danny");
    data.completeRow.push_back("123");
    QVERIFY(m_sqlite.insertValue(data, DEFAULT_TEST_TABLE));
    QCOMPARE(m_sqlite.getAllData(DEFAULT_TEST_TABLE).completeData.size(), 1);
    QVERIFY(m_sqlite.isExist("name", "danny", DEFAULT_TEST_TABLE));
    QVERIFY(m_sqlite.isExist("number", "123", DEFAULT_TEST_TABLE));
    QCOMPARE(m_sqlite.isExist("name", "tommy", DEFAULT_TEST_TABLE), false);
    QCOMPARE(m_sqlite.isExist("number", "7007", DEFAULT_TEST_TABLE), false);

    data = SqlBase::tableRow();
    data.completeRow.push_back("tommy");
    data.completeRow.push_back("7007");
    QVERIFY(m_sqlite.insertValue(data, DEFAULT_TEST_TABLE));
    QCOMPARE(m_sqlite.getAllData(DEFAULT_TEST_TABLE).completeData.size(), 2);
    QVERIFY(m_sqlite.isExist("name", "tommy", DEFAULT_TEST_TABLE));
    QVERIFY(m_sqlite.isExist("number", "7007", DEFAULT_TEST_TABLE));
    QCOMPARE(m_sqlite.isExist("name", "mark", DEFAULT_TEST_TABLE), false);
    QCOMPARE(m_sqlite.isExist("number", "007", DEFAULT_TEST_TABLE), false);
    QVERIFY(m_sqlite.isExist("name", "danny", DEFAULT_TEST_TABLE));
    QVERIFY(m_sqlite.isExist("number", "123", DEFAULT_TEST_TABLE));
}

QTEST_APPLESS_MAIN(SqLiteTests)

#include "tst_sqlitetests.moc"
