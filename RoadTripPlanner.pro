QT += widgets
CONFIG += c++17
TEMPLATE = app
TARGET = RoadTripPlanner

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    Trip.cpp \
    FileManager.cpp

HEADERS += \
    MainWindow.h \
    Trip.h \
    FileManager.h
