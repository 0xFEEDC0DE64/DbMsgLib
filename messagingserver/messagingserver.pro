QT += core network

TARGET = messagingserver
TEMPLATE = app

CONFIG -= app_bundle

PROJECT_ROOT = ..

DESTDIR = $${OUT_PWD}/$${PROJECT_ROOT}/bin

DBLIBS += core

SOURCES += main.cpp

HEADERS +=

FORMS +=

RESOURCES +=

TRANSLATIONS +=

include($${PROJECT_ROOT}/project.pri)
