#pragma once

#include <QWidget>
#include <QPainter>
#include <QColor>
#include <vector>
#include <set>
#include"GeometryObjectsClass.h"

class PointWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PointWidget(QWidget *parent = nullptr);
    void setOptional(const PointSet& points) { optional = points; }
    void setMandatory(const std::vector<PointVector>& clusters) { mandatory = clusters; }

    void setL(int l_value) { l = l_value+1; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    PointSet optional;
    std::vector<PointVector> mandatory; 
    int l = 100.0;  
};

