#include "communications.h"
#include "qpainter.h"
#include "radiostation.h"
#include "radius.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

Communications::Communications()
{

}

QRectF boundingRect()
{
    return QRectF(0, 0, 100, 100);
}

void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setBrush(Qt::blue);
    painter->drawRect(boundingRect());
}

void Communications::checkCollisions()
{
    //удаление старых линий
    for (auto lineItem : lines)
    {
        this->scene()->removeItem(lineItem);
        delete lineItem;
    }
    lines.clear();


    //проверка столкновений с другими кругами
    for (auto i = 0; i < Radiostation::radiostations.size(); ++i)
    {
        for (auto j = 0; j < Radius::radiuses.size(); ++j)
        {
            if (i != j)
            {
                if(Radius::radiuses[j]->collidesWithItem(Radiostation::radiostations[i]))
                {
                    updateLine(Radiostation::radiostations[j], Radiostation::radiostations[i]);
                }
            }
        }
    }
}

void Communications::updateLine(Radiostation* radiostation1, Radiostation* radiostation2)
{
    qDebug() << "Соприкоснулись";
    /*
    //центр двух кругов в координатах сцены
    QPointF center1 = this->mapToScene(this->boundingRect().center());
    QPointF center2 = otherCircle->mapToScene(otherCircle->boundingRect().center());

    //создание линии между центрами двух кругов
    QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(center1, center2));
    line->setPen(QPen(Qt::red, 2));

    //добавление линии
    this->scene()->addItem(line);
    lines.append(line);
    */
}
