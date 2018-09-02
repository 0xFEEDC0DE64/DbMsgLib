QT += core network
QT -= gui widgets

TARGET = messagingcorelib
TEMPLATE = lib

PROJECT_ROOT = ..

DEFINES += MESSAGINGCORELIB_LIBRARY

SOURCES += \
    dbmsgbase.cpp \
    dbmsgfieldbase.cpp \
    messages/mymessage.cpp

HEADERS += \
    dbmsgbase.h \
    dbmsgfield.h \
    dbmsgfieldbase.h \
    dbmsgmacros.h \
    messagingcorelib_global.h \
    messages/mymessage.h

FORMS +=

RESOURCES +=

TRANSLATIONS +=

include($${PROJECT_ROOT}/project.pri)
