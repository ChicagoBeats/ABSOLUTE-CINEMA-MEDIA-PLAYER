#include "app/MainWindow.h"
#include "ui/IntroOverlay.h"
#include "visualizers/StarfieldVisualizer.h"
#include <QListWidget>
#include <QSplitter>
#include <QMenuBar>
#include <QAction>
#include <QShortcut>
#include <QSettings>
#include <QStorageInfo>
#include <QTimer>

MainWindow::MainWindow()
{
    setWindowTitle("ABSOLUTE CINEMA");
    setStyleSheet("QMainWindow,QListWidget{background:#05070d;color:#d7e3ff;} QMenuBar,QMenu{background:#0a1020;color:#d7e3ff;}");

    m_devices = new QListWidget;
    m_devices->setMinimumWidth(220);
    m_vis = new StarfieldVisualizer;
    auto *split = new QSplitter;
    split->addWidget(m_devices);
    split->addWidget(m_vis);
    split->setStretchFactor(1, 1);
    setCentralWidget(split);

    m_intro = new IntroOverlay(m_vis);

    QSettings s;
    auto *view = menuBar()->addMenu("&View");
    auto *enable = view->addAction("Cinematic intro on startup");
    enable->setCheckable(true);
    enable->setChecked(s.value("intro/enabled", true).toBool());
    connect(enable, &QAction::toggled, this, [](bool on) { QSettings().setValue("intro/enabled", on); });
    auto *replay = view->addAction("Play intro now");
    connect(replay, &QAction::triggered, m_intro, &IntroOverlay::start);

    auto *esc = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(esc, &QShortcut::activated, m_intro, &IntroOverlay::skip);

    connect(&m_devTimer, &QTimer::timeout, this, &MainWindow::refreshDevices);
    m_devTimer.start(2000);
    refreshDevices();

    if (enable->isChecked())
        QTimer::singleShot(200, m_intro, &IntroOverlay::start);
}

void MainWindow::refreshDevices()
{
    QStringList now;
    for (const QStorageInfo &v : QStorageInfo::mountedVolumes()) {
        if (!v.isValid() || !v.isReady()) continue;
        QString name = v.displayName().isEmpty() ? v.rootPath() : v.displayName();
        now << QString("%1\n%2 GB free of %3 GB (%4)")
                   .arg(name)
                   .arg(v.bytesAvailable() / 1000000000)
                   .arg(v.bytesTotal() / 1000000000)
                   .arg(QString::fromLatin1(v.fileSystemType()));
    }
    now << "Phones and cameras (MTP)\nComing next: needs Windows Portable Devices";
    if (now == m_lastDevices) return;
    m_lastDevices = now;
    m_devices->clear();
    m_devices->addItems(now);
}
