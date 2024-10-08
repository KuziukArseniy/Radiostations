#include "radiostation.h"
#include "communications.h"
#include "radius.h"
#include <QBrush>
#include <QDebug>
#include <QGraphicsScene>

QList<Radiostation*> Radiostation::radiostations;

Radiostation::Radiostation(int x, int y, int width, int height)
    : QObject(), QGraphicsEllipseItem()
{
    //размеры окружности
    setRect(x, y, width, height);

    //зеленая рамка
    QPen penCircle(Qt::green);
    setPen(penCircle);

    //подвижный
    setFlag(QGraphicsItem::ItemIsMovable);
}

void Radiostation::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //окружность в зелёный при нажатии
    //setBrush(QBrush(Qt::green));
}

void Radiostation::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    Communications::checkCollisions();

    QGraphicsEllipseItem::mouseMoveEvent(event);
}
