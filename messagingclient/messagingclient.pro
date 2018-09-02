QT += core network

TARGET = messagingclient
TEMPLATE = app

PROJECT_ROOT = ..

DESTDIR = $${OUT_PWD}/$${PROJECT_ROOT}/bin

DBLIBS += core

SOURCES += main.cpp

HEADERS +=

FORMS +=

RESOURCES +=

TRANSLATIONS +=

include($${PROJECT_ROOT}/project.pri)
