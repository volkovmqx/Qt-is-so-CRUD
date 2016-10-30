SOURCES += \
    main.cpp \
    mainwindow.cpp \
    autentification.cpp \
    editdossier.cpp \
    qsortfilterproxymodelmorethanrow.cpp \
    detailsdossier.cpp \
    dialog.cpp
QT += widgets
QT += sql
FORMS += \
    mainwindow.ui \
    autentification.ui \
    editdossier.ui \
    detailsdossier.ui \
    dialog.ui

HEADERS += \
    mainwindow.h \
    autentification.h \
    editdossier.h \
    qsortfilterproxymodelmorethanrow.h \
    detailsdossier.h \
    dialog.h

DISTFILES +=

RESOURCES += \
    logo.qrc
QTPLUGIN += qsqlmysql
