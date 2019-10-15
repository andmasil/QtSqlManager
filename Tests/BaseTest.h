#ifndef BASETEST_H
#define BASETEST_H

#include <QObject>
#include <QtTest>

class BaseTest : public QObject
{
    Q_OBJECT
public:
    explicit BaseTest(QObject *parent = nullptr) {Q_UNUSED(parent)}

private slots:
    virtual void initTestCase() = 0;
    virtual void cleanupTestCase() = 0;
};

#endif // BASETEST_H
