#include "visualizers/StarfieldVisualizer.h"
#include <QPainter>
#include <QRandomGenerator>
#include <cmath>

StarfieldVisualizer::StarfieldVisualizer(QWidget *parent) : QWidget(parent)
{
    m_stars.resize(260);
    for (auto &s : m_stars) { respawn(s); s.z = QRandomGenerator::global()->generateDouble(); }
    connect(&m_timer, &QTimer::timeout, this, &StarfieldVisualizer::tick);
    m_timer.start(16);
}

void StarfieldVisualizer::respawn(Star &s)
{
    auto *r = QRandomGenerator::global();
    s.x = r->generateDouble() * 2.0 - 1.0;
    s.y = r->generateDouble() * 2.0 - 1.0;
    s.z = 1.0;
}

void StarfieldVisualizer::setPulse(double pulse) { m_pulse = pulse; }

void StarfieldVisualizer::tick()
{
    m_phase += 0.016;
    double p = m_pulse >= 0.0 ? m_pulse
             : 0.12 + 0.1 * std::sin(m_phase * 2.4) * std::sin(m_phase * 0.6);
    m_speed = 0.002 + p * 0.01;
    for (auto &s : m_stars) {
        s.z -= m_speed;
        if (s.z < 0.02) respawn(s);
    }
    update();
}

void StarfieldVisualizer::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(rect(), Qt::black);
    p.setRenderHint(QPainter::Antialiasing, true);
    const double w = width(), h = height();
    for (const auto &s : m_stars) {
        double px = s.x / s.z * w * 0.25 + w / 2;
        double py = s.y / s.z * h * 0.25 + h / 2;
        double z2 = s.z + m_speed * 8;
        double nx = s.x / z2 * w * 0.25 + w / 2;
        double ny = s.y / z2 * h * 0.25 + h / 2;
        double b = 1.0 - s.z;
        QPen pen(QColor(190 + int(b * 60), 210 + int(b * 40), 255, int(b * 255)));
        pen.setWidthF(1.0 + b * 1.5);
        p.setPen(pen);
        p.drawLine(QPointF(nx, ny), QPointF(px, py));
    }
}
