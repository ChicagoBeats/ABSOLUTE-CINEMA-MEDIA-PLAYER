QT += widgets
CONFIG += c++17
TEMPLATE = app
TARGET = AbsoluteCinema
INCLUDEPATH += src
SOURCES += src/main.cpp src/app/MainWindow.cpp src/ui/IntroOverlay.cpp src/visualizers/StarfieldVisualizer.cpp
HEADERS += src/app/MainWindow.h src/ui/IntroOverlay.h src/visualizers/StarfieldVisualizer.h
