#ifndef RADIUS_H
#define RADIUS_H

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QDebug>
#include <QPen>

class Radius : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Radius(qreal x, qreal y, qreal width, qreal height)
        : QGraphicsEllipseItem(x, y, width, height)
    {
        QPen penRadius(Qt::DashLine);
        setPen(penRadius);
    }

    static QList<Radius*> radiuses;
};

#endif // RADIUS_H
