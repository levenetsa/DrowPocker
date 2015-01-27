TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS_DEBUG +=-Wall -pedantic

SOURCES += main.cpp \
    player.cpp \
    open_card.cpp \
    human_player.cpp \
    game.cpp \
    closed_card.cpp \
    card.cpp

HEADERS += \
    player.h \
    open_card.h \
    human_player.h \
    game.h \
    closed_card.h \
    card.h

