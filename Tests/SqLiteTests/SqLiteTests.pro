QT += testlib sql
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCDIR = ../../src/Base
INCLUDEPATH += $$INCDIR

SOURCES += $$INCDIR/SqlBase.cpp \
           $$INCDIR/SqLite.cpp

SOURCES +=  tst_sqlitetests.cpp
