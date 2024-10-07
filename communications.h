#ifndef COMMUNICATIONS_H
#define COMMUNICATIONS_H

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsItem>
#include "radiostation.h"

class Communications: QGraphicsItem
{
public:
    Communications();

    ~Communications()
    {
        delete line;
    }

    void checkCollisions();

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    QGraphicsLineItem* line;
    void updateLine(Radiostation* radiostation1, Radiostation* radiostation2);
    QList<QGraphicsLineItem*> lines;
};

#endif // COMMUNICATIONS_H
