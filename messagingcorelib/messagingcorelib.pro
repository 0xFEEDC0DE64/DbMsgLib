QT += core network
QT -= gui widgets

TARGET = messagingcorelib
TEMPLATE = lib

PROJECT_ROOT = ..

DEFINES += MESSAGINGCORELIB_LIBRARY

SOURCES += \
    mymessage.cpp

HEADERS += messagingcorelib_global.h \
    mymessage.h

FORMS +=

RESOURCES +=

TRANSLATIONS +=

include($${PROJECT_ROOT}/project.pri)
