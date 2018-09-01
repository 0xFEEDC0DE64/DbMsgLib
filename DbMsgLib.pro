TEMPLATE = subdirs

SUBDIRS += messagingclient \
           messagingcorelib \
           messagingserver

messagingclient.depends += messagingcorelib
messagingserver.depends += messagingcorelib
