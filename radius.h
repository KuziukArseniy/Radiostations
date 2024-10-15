#ifndef RADIUS_H
#define RADIUS_H

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QDebug>
#include <QPen>

/**
 * @brief The Radius class
 * В этом клссе представлена реализация радиуса действия радиостанции
 * Данный класс нужен для определения радиуса действия станции для последующей связи между станциями
 */

class Radius : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Radius(qreal x, qreal y, qreal width, qreal height)
        : QGraphicsEllipseItem(x, y, width, height)
    {
        QPen penRadius(Qt::DashLine);
        setPen(penRadius);
        setZValue(0);
    }

    static QList<Radius*> radiuses;
};

#endif // RADIUS_H
