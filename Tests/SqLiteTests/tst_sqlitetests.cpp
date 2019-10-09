#include <QtTest>
#include "SqLite.h"

class SqLiteTests : public QObject
{
    Q_OBJECT

public:
    SqLiteTests();
    ~SqLiteTests();

private slots:
    void connectDatabaseTest();

};

SqLiteTests::SqLiteTests()
{

}

SqLiteTests::~SqLiteTests()
{

}

void SqLiteTests::connectDatabaseTest()
{
    SqlBase::databaseInfo info;
    SqLite sqlite;
    QCOMPARE(sqlite.connectDatabase(info), false);
    info.name = "test.db";
    QCOMPARE(sqlite.connectDatabase(info), true);
}

QTEST_APPLESS_MAIN(SqLiteTests)

#include "tst_sqlitetests.moc"
