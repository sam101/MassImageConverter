QT       += core gui
INCLUDEPATH += include
TARGET = massimageconverter
TEMPLATE = app
CODECFORTR = UTF-8

SOURCES += src/main.cpp\
        src/MainWindow.cpp \
    src/Converter.cpp

HEADERS  += include/MainWindow.h \
    include/Converter.h \
    include/Config.h

TRANSLATIONS = text/Client_fr.ts text/Client_en.ts



