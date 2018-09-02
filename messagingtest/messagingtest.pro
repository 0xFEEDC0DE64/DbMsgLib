QT += core testlib
QT -= gui widgets

TARGET = messagingserver
TEMPLATE = app

CONFIG += testcase

PROJECT_ROOT = ..

DESTDIR = $${OUT_PWD}/$${PROJECT_ROOT}/bin

DBLIBS += core

SOURCES += tst_messagingtest.cpp

HEADERS +=

FORMS +=

RESOURCES +=

TRANSLATIONS +=

include($${PROJECT_ROOT}/project.pri)
