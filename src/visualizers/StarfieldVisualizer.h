#pragma once
#include <QWidget>
#include <QTimer>
#include <vector>

// Placeholder visualizer. setPulse() will be fed by the shared audio analyzer.
class StarfieldVisualizer : public QWidget
{
    Q_OBJECT
public:
    explicit StarfieldVisualizer(QWidget *parent = nullptr);
    void setPulse(double pulse);   // 0..1; negative = use gentle idle motion

protected:
    void paintEvent(QPaintEvent *) override;

private slots:
    void tick();

private:
    struct Star { double x, y, z; };
    void respawn(Star &s);
    std::vector<Star> m_stars;
    QTimer m_timer;
    double m_pulse = -1.0;
    double m_phase = 0.0;
    double m_speed = 0.002;
};
