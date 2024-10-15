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

QList<QGraphicsLineItem*> Communications::lines;

QGraphicsScene* Communications::scene;

//метод, который принимает сцену для последующей работы с ней
void Communications::setSc(QGraphicsScene* sc)
{
    Communications::scene = sc;
}

//метод, который проверяет соприкосеновения с другими радиостанциями
void Communications::checkCollisions()
{
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

//метод отрисовки связей между радиостанциями
void Communications::updateLine(Radiostation* radiostation1, Radiostation* radiostation2)
{
    /*
    for (QGraphicsLineItem* lineItem : lines)
    {
        QLineF oldLine = lineItem->line();
        QPointF center1 = radiostation1->scenePos() + radiostation1->rect().center();
        QPointF center2 = radiostation2->scenePos() + radiostation2->rect().center();

        if ((oldLine.p1() != center1 && oldLine.p2() != center2) ||
            (oldLine.p1() != center2 && oldLine.p2() != center1))
        {
            scene->removeItem(lineItem);
            lines.removeOne(lineItem);
        }
    }
    */

    //центры радиостанций
    QPointF center1 = radiostation1->scenePos() + radiostation1->rect().center();
    QPointF center2 = radiostation2->scenePos() + radiostation2->rect().center();

    //создаем линию между центрами
    QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(center1, center2));
    line->setPen(QPen(Qt::red, 2));

    //добавляем линию на сцену
    radiostation1->scene()->addItem(line);

    //добавляем линию в список
    lines.append(line);


}

    /*
    //удаление старых линий
    for (QGraphicsLineItem* lineItem : lines)
    {
        scene->removeItem(lineItem);
        delete lineItem;
    }
    lines.clear();
    //qDebug() << "Соприкоснулись";

    //центры радиостанций и радиусов
    QPointF center1 = radiostation1->scenePos() + radiostation1->rect().center();
    QPointF center2 = radiostation2->scenePos() + radiostation2->rect().center();

    //линия между центрами
    QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(center1, center2));
    line->setPen(QPen(Qt::red, 2));

    //добавление линии на сцену
    radiostation1->scene()->addItem(line);

    //добавление линии в список
    lines.append(line);
    */
