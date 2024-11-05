#include "communications.h"
#include "qpainter.h"
#include "radiostation.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QList>
#include <QtMath>
#include <QGraphicsPolygonItem>
#include <QDebug>

QList<QGraphicsLineItem*> Communications::lines;
QList<QGraphicsPolygonItem*> Communications::arrows;
QGraphicsScene* Communications::scene;

//метод, который принимает сцену для последующей работы с ней
void Communications::setSc(QGraphicsScene* sc)
{
    Communications::scene = sc;
}

//метод, который проверяет соприкосеновения с другими радиостанциями
void Communications::checkCollisions()
{
    //удаление устаревших линий
    for (QGraphicsLineItem* line : lines)
    {
        delete line;
    }
    lines.clear();

    //удаление устаревших стрелок
    for (QGraphicsPolygonItem* arrow : arrows)
    {
        delete arrow;
    }
    arrows.clear();

    for (int i = 0; i < Radiostation::radiostations.size(); i++)
    {
        for (int j = 0; j < Radiostation::radiuses.size(); j++)
        {
            if (i != j)
            {
                if(Radiostation::radiuses[j]->collidesWithItem(Radiostation::radiostations[i]))
                {
                    updateLine(Radiostation::radiostations[i], Radiostation::radiostations[j]);
                }
            }
        }
    }
}

//метод отрисовки связей между радиостанциями
void Communications::updateLine(QGraphicsEllipseItem* radiostation1, QGraphicsEllipseItem* radiostation2)
{
    //центры радиостанций
    QPointF center1 = radiostation1->scenePos() + radiostation1->rect().center();
    QPointF center2 = radiostation2->scenePos() + radiostation2->rect().center();

    //радиус радиостанций
    qreal radius = radiostation1->rect().width() / 2;

    //вектор от первой радиостанции ко второй
    QLineF lineBetween(center1, center2);

    //смещение начала и конеца линии к краям радиостанций
    lineBetween.setP1(lineBetween.pointAt(radius / lineBetween.length()));
    lineBetween.setP2(lineBetween.pointAt(1 - (radius / lineBetween.length())));

    //линия от края первой радиостанции до края второй радиостанции
    QGraphicsLineItem* line = new QGraphicsLineItem(lineBetween);
    line->setPen(QPen(Qt::red, 2));
    radiostation1->scene()->addItem(line);

    //угол линии для создания наконечника стрелки
    double angle = std::atan2(lineBetween.dy(), lineBetween.dx());

    //позиция стрелки на краю первой радиостанции
    QPointF arrowTip = lineBetween.p1();

    //длина и угол стрелки
    qreal arrowSize = 10;
    QPointF arrowP1 = arrowTip + QPointF(arrowSize * std::cos(angle - M_PI / 6),
                                         arrowSize * std::sin(angle - M_PI / 6));
    QPointF arrowP2 = arrowTip + QPointF(arrowSize * std::cos(angle + M_PI / 6),
                                         arrowSize * std::sin(angle + M_PI / 6));

    //треугольник для наконечника стрелки
    QPolygonF arrowHead;
    arrowHead << arrowTip << arrowP1 << arrowP2;

    //добавление стрелки на сцену
    QGraphicsPolygonItem* arrowItem = new QGraphicsPolygonItem(arrowHead);
    arrowItem->setBrush(Qt::red);
    radiostation1->scene()->addItem(arrowItem);

    //добавление линии и стрелки в список
    lines.append(line);
    arrows.append(arrowItem);
}
