QT += core gui sql
QT += printsupport
Qt += xlsx
QT += charts
QT += network
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QXLSX_PARENTPATH=./         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./source/  # current QXlsx source path is ./source/
include(./QXlsx.pri)
include(QZXing/QZXing.pri)

SOURCES += \
    Arduino.cpp \
    Sms.cpp \
    agendapersonnels.cpp \
    ajouterartistes.cpp \
    ajoutercontrats.cpp \
    ajoutermatriels.cpp \
    ajouterpersonnels.cpp \
    ajoutersalles.cpp \
    ajoutevents.cpp \
    artiste.cpp \
    calendrierevents.cpp \
    connection.cpp \
    contrats.cpp \
    dialog.cpp \
    employe.cpp \
    evenements.cpp \
    imagedelegate.cpp \
    listeartistes.cpp \
    listecontrats.cpp \
    listeevents.cpp \
    listematriels.cpp \
    listepersonnels.cpp \
    listesalles.cpp \
    main.cpp \
    mainwindow.cpp \
    materiel.cpp \
    passwordresetdialog.cpp \
    qcustomplot.cpp \
    salles.cpp \
    smtp.cpp \
    startwindow.cpp \
    statsartistes.cpp \
    statscontrats.cpp \
    statsevents.cpp \
    statsmatriels.cpp \
    statspersonnels.cpp \
    statssalles.cpp

HEADERS += \
    Arduino.h \
    Sms.h \
    agendapersonnels.h \
    ajouterartistes.h \
    ajoutercontrats.h \
    ajoutermatriels.h \
    ajouterpersonnels.h \
    ajoutersalles.h \
    ajoutevents.h \
    artiste.h \
    calendrierevents.h \
    connection.h \
    contrats.h \
    dialog.h \
    employe.h \
    evenements.h \
    imagedelegate.h \
    listeartistes.h \
    listecontrats.h \
    listeevents.h \
    listematriels.h \
    listepersonnels.h \
    listesalles.h \
    mainwindow.h \
    materiel.h \
    passwordresetdialog.h \
    qcustomplot.h \
    salles.h \
    smtp.h \
    startwindow.h \
    statsartistes.h \
    statscontrats.h \
    statsevents.h \
    statsmatriels.h \
    statspersonnels.h \
    statssalles.h

FORMS += \
    agendapersonnels.ui \
    ajouterartistes.ui \
    ajoutercontrats.ui \
    ajoutermatriels.ui \
    ajouterpersonnels.ui \
    ajoutersalles.ui \
    ajoutevents.ui \
    calendrierevents.ui \
    dialog.ui \
    listeartistes.ui \
    listecontrats.ui \
    listeevents.ui \
    listematriels.ui \
    listepersonnels.ui \
    listesalles.ui \
    mainwindow.ui \
    passwordresetdialog.ui \
    startwindow.ui \
    statsartistes.ui \
    statscontrats.ui \
    statsevents.ui \
    statsmatriels.ui \
    statspersonnels.ui \
    statssalles.ui

TRANSLATIONS += \
    Projetfull_en_GB.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc

DISTFILES += \
    mainwindow.ui.txt
