#pragma once
#include <QMainWindow>
#include <QTimer>
#include <QStringList>

class StarfieldVisualizer;
class IntroOverlay;
class QListWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

private:
    void refreshDevices();
    StarfieldVisualizer *m_vis;
    IntroOverlay *m_intro;
    QListWidget *m_devices;
    QTimer m_devTimer;
    QStringList m_lastDevices;
};
