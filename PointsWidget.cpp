#include "PointsWidget.h"
#include <QPainter>
#include <QColor>
#include <cmath>

PointWidget::PointWidget(QWidget *parent) : QWidget(parent) {setMouseTracking(true);}

void PointWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    double w = width();
    double h = height();
    double scale = std::min(w, h) / l;

    painter.setPen(QPen(QColor(220, 220, 220), 1, Qt::DashLine));

    int steps = 10;
    for (int i = 0; i <= steps; ++i) {
        double val = i * l / steps;
        double x_px = val * scale + 1; 
        double y_px = h - val * scale - 1; 

        painter.drawLine(QPointF(x_px, 0), QPointF(x_px, h)); 
        painter.drawLine(QPointF(0, y_px), QPointF(w, y_px)); 
    }


    painter.setPen(QPen(Qt::gray, 1));
    painter.drawLine(QPointF(0, h - 1), QPointF(w, h - 1)); 
    painter.drawLine(QPointF(0, h), QPointF(0, h - l * scale - 1)); 


    painter.setPen(QPen(Qt::darkGray, 1));
    QFont font = painter.font();
    font.setPointSize(8);
    painter.setFont(font);

    for (int i = 0; i <= steps; ++i) {
        double val = i * l / steps;
        double x_px = val * scale + 1;
        double y_px = h - val * scale - 1;

        painter.drawLine(QPointF(x_px, h - 1), QPointF(x_px, h - 6));  
        painter.drawText(QPointF(x_px + 2, h - 4), QString::number(val, 'f', 1));  

        painter.drawLine(QPointF(0, y_px), QPointF(5, y_px)); 
        if (val > 0) painter.drawText(QPointF(7, y_px + 3), QString::number(val, 'f', 1)); 
    }

    painter.setPen(Qt::black);
    painter.setBrush(Qt::blue);

    for (const Point& p : optional) {
        double x = p.SetX() * scale + 1;
        double y = p.SetY() * scale + 1;
        y = h - y;
        painter.drawEllipse(QPointF(x, y), 3, 3);
    }


    int colorIndex = 0;
    for (const PointVector& cluster : mandatory) {

        int hue = (colorIndex * 360) / mandatory.size();  
        QColor color = QColor::fromHsl(hue, 255, 180); 

        painter.setBrush(color);
        painter.setPen(Qt::black);

        for (const Point& p : cluster) {
            double x = p.SetX() * scale + 1;
            double y = p.SetY() * scale + 1;
            y = h - y;
            painter.drawEllipse(QPointF(x, y), 4, 4);  
        }

        colorIndex++;
    }

    if (hoveredClusterIndex != -1) {
        painter.setPen(Qt::black);
        QFont font = painter.font();
        font.setPointSize(10);
        font.setBold(true);
        painter.setFont(font);

        painter.drawText(lastMousePos + QPoint(10, -10),
                         QString("Cluster №%1").arg(hoveredClusterIndex+1));
    }
}

void PointWidget::mouseMoveEvent(QMouseEvent* event) {
    lastMousePos = event->pos();
    hoveredClusterIndex = -1;

    double w = width();
    double h = height();
    double scale = std::min(w, h) / l;

    for (int i = 0; i < mandatory.size(); ++i) {
        for (const Point& p : mandatory[i]) {
            double x = p.SetX() * scale + 1;
            double y = p.SetY() * scale + 1;
            y = h - y;

            QPointF point(x, y);
            if (QLineF(point, event->pos()).length() < 5) {
                hoveredClusterIndex = i;
                update(); 
                return;
            }
        }
    }

    update();
}

