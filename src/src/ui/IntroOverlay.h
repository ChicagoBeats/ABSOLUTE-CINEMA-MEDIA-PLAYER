#pragma once
#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>

// Crown + "ABSOLUTE CINEMA" title that starts tiny at top centre, approaches,
// grows huge and fades. Transparent overlay: the visualizer shows through.
class IntroOverlay : public QWidget
{
    Q_OBJECT
public:
    explicit IntroOverlay(QWidget *parent);
    void start();
    void skip();
    bool isRunning() const { return m_running; }

    double approachSeconds = 5.0;
    double fadeSeconds = 1.5;
    double finalScale = 1.7;   // 1.0 = title about 60% of the width
    bool leanForward = true;

signals:
    void finished();

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override { skip(); }
    bool eventFilter(QObject *o, QEvent *e) override;

private:
    void finish();
    QTimer m_timer;
    QElapsedTimer m_clock;
    bool m_running = false;
};
