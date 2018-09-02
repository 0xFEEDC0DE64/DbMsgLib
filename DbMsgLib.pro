TEMPLATE = subdirs

SUBDIRS += messagingclient \
           messagingcorelib \
           messagingserver \
           messagingtest

messagingclient.depends += messagingcorelib
messagingserver.depends += messagingcorelib
messagingtest.depends += messagingcorelib
