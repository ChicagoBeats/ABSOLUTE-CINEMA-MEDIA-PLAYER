#include "ui/IntroOverlay.h"
#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>
#include <QTransform>
#include <QEvent>
#include <cmath>
#include <algorithm>

static double easeInOut(double x) { return x < 0.5 ? 4 * x * x * x : 1 - std::pow(-2 * x + 2, 3) / 2; }
static double easeOut(double x) { return 1 - std::pow(1 - x, 3); }

IntroOverlay::IntroOverlay(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    parent->installEventFilter(this);
    setGeometry(parent->rect());
    hide();
    connect(&m_timer, &QTimer::timeout, this, [this] { update(); });
}

bool IntroOverlay::eventFilter(QObject *o, QEvent *e)
{
    if (o == parent() && e->type() == QEvent::Resize)
        setGeometry(static_cast<QWidget *>(o)->rect());
    return QWidget::eventFilter(o, e);
}

void IntroOverlay::start()
{
    m_running = true;
    m_clock.start();
    setGeometry(static_cast<QWidget *>(parent())->rect());
    show();
    raise();
    m_timer.start(16);
}

void IntroOverlay::skip() { if (m_running) finish(); }

void IntroOverlay::finish()
{
    m_running = false;
    m_timer.stop();
    hide();
    emit finished();
}

void IntroOverlay::paintEvent(QPaintEvent *)
{
    if (!m_running) return;
    const double e = m_clock.elapsed();
    const double D = approachSeconds * 1000, Fd = fadeSeconds * 1000, Hd = 900;
    double y, sc, op, lean = 0;
    if (e < D) {
        double p = easeInOut(e / D);
        op = std::min(1.0, e / 600.0);
        y = 0.1 + 0.4 * p;
        sc = 0.03 + (finalScale - 0.03) * std::pow(p, 2.2);
    } else {
        double f = std::min(1.0, (e - D) / Fd);
        y = 0.5;
        sc = finalScale * (1 + 0.3 * f);
        op = 1 - f;
        if (leanForward) lean = -16 * easeOut(std::min(1.0, (e - D) / Hd));
        if (f >= 1.0) { QTimer::singleShot(0, this, [this] { finish(); }); return; }
    }

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setOpacity(op);
    const double em = sc * width() / 6.2;      // pixel size of one "em"
    p.translate(width() / 2.0, y * height());
    if (lean != 0) {                           // tilt toward the viewer
        QTransform t; t.rotate(lean, Qt::XAxis); p.setTransform(t, true);
    }
    p.scale(em / 100.0, em / 100.0);           // draw in 100-unit em

    // Block layout in em units (x100): crown 90 tall, then two lines of 95.
    const double top = -140;
    // Crown (same shape as the prototype; replace with brand asset later)
    auto cx = [](double vx) { return (vx - 50) / 100.0 * 150.0; };
    auto cy = [&](double vy) { return top + vy / 60.0 * 90.0; };
    QPolygonF crown;
    const double pts[][2] = {{8,52},{4,14},{26,32},{50,6},{74,32},{96,14},{92,52}};
    for (auto &pt : pts) crown << QPointF(cx(pt[0]), cy(pt[1]));
    QLinearGradient cg(0, top, 0, top + 90);
    cg.setColorAt(0, QColor(255, 255, 255));
    cg.setColorAt(0.55, QColor(125, 142, 169));
    cg.setColorAt(1, QColor(230, 238, 255));
    p.setBrush(cg);
    p.setPen(QPen(QColor(156, 194, 255), 1.5));
    p.drawPolygon(crown);
    p.setBrush(QColor(93, 160, 255)); p.setPen(Qt::NoPen);
    p.drawEllipse(QPointF(0, cy(38)), 6, 6);

    // Title text
    QFont f("Old English Text MT");
    f.setStyleHint(QFont::Serif);
    f.setBold(true);
    f.setPixelSize(100);
    QFontMetricsF fm(f);
    const QString lines[2] = {"Absolute", "Cinema"};
    double base = top + 90 + 72;
    for (int i = 0; i < 2; ++i) {
        QPainterPath path;
        path.addText(-fm.horizontalAdvance(lines[i]) / 2, base, f, lines[i]);
        QLinearGradient g(0, base - 75, 0, base + 15);
        g.setColorAt(0.0, QColor(255, 255, 255));
        g.setColorAt(0.38, QColor(223, 232, 245));
        g.setColorAt(0.52, QColor(111, 127, 153));
        g.setColorAt(0.70, QColor(244, 248, 255));
        g.setColorAt(1.0, QColor(159, 179, 212));
        p.setPen(QPen(QColor(120, 170, 255, 200), 2));
        p.setBrush(g);
        p.drawPath(path);
        base += 95;
    }
}
