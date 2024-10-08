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
    /*
    //удаление старых линий
    for (auto lineItem : lines)
    {
        this->scene()->removeItem(lineItem);
        delete lineItem;
    }
    lines.clear();
    */
    qDebug() << "Соприкоснулись";

    /*
    //центры радиостанций и радиусов
    QPointF center1 = radiostation1->scenePos() + radiostation1->rect().center();
    QPointF center2 = radiostation2->scenePos() + radiostation2->rect().center();

    // Создаем линию между центрами
    QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(center1, center2));
    line->setPen(QPen(Qt::red, 2));

    //добавление линии на сцену
    radiostation1->scene()->addItem(line);

    //добавление линии в список
    lines.append(line);
    */
}
