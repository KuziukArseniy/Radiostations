#include "radiostation.h"
#include "communications.h"
#include <QBrush>
#include<QDebug>

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

    QGraphicsEllipseItem::mousePressEvent(event);
}

void Radiostation::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    Communications* comm = new Communications();
    comm->checkCollisions();
}
