CONFIG += qt console warn_on depend_includepath c++14

DEFINES += QT_DEPRECATED_WARNINGS \
           QT_DISABLE_DEPRECATED_BEFORE=0x060000 \
           QT_MESSAGELOGCONTEXT

equals(TEMPLATE, "app") {
    CONFIG -= app_bundle
}

equals(TEMPLATE, "lib") {
    win32: DESTDIR = $${OUT_PWD}/$${PROJECT_ROOT}/bin
    else: DESTDIR = $${OUT_PWD}/$${PROJECT_ROOT}/lib
}

!isEmpty(DBLIBS) {
    win32: LIBS += -L$${OUT_PWD}/$${PROJECT_ROOT}/bin
    else: LIBS += -Wl,-rpath=\\\$$ORIGIN/../lib -L$${OUT_PWD}/$${PROJECT_ROOT}/lib
}

contains(DBLIBS, core) {
    LIBS += -lmessagingcorelib

    INCLUDEPATH += $$PWD/messagingcorelib
    DEPENDPATH += $$PWD/messagingcorelib
}

isEmpty(QMAKE_LRELEASE) {
    win32:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]\lrelease.exe
    else:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]/lrelease
}

lrelease.input = TRANSLATIONS
lrelease.output = $${OUT_PWD}/$${PROJECT_ROOT}/bin/translations/${QMAKE_FILE_BASE}.qm
lrelease.commands = $${QMAKE_LRELEASE} ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_OUT}
lrelease.CONFIG += no_link
QMAKE_EXTRA_COMPILERS += lrelease
PRE_TARGETDEPS += compiler_lrelease_make_all
