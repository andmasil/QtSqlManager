#include <QtTest>
#include <QList>

//include test classes
#include "SqLiteTests.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<BaseTest*> tests;
    SqLiteTests sqliteTests;

    tests.append(&sqliteTests);

    QList<BaseTest*>::iterator i;
    for (i = tests.begin(); i != tests.end(); ++i)
    {
        QTest::qExec(*i);
    }

    return 0;
}
