#include "communications.h"
#include "qpainter.h"
#include "radiostation.h"
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

//метод для удлания отрисовки связей
void Communications::deleteLines()
{
    for (int l = lines.size() - 1; l >= 0; --l)
    {
        bool lineExists = false;

        for (int i = 0; i < Radiostation::radiostations.size(); ++i) {
            for (int j = 0; j < Radiostation::radiostations.size(); ++j) {
                if (i != j) {
                    if (Radiostation::radiuses[i]->collidesWithItem(Radiostation::radiostations[j]))
                    {
                        lineExists = true;
                        break;
                    }
                }
            }
            if (lineExists) break;
        }

        if (!lineExists) {
            scene->removeItem(lines[l]);
            delete lines[l];
            lines.removeAt(l);
        }
    }
}

// for (auto it = lines.begin(); it != lines.end();)
// {
//     QGraphicsLineItem* lineItem = *it;
//     bool isTrue = false;

//     for (int i = 0; i < Radiostation::radiostations.size(); i++)
//     {
//         for (int j = 0; j < Radiostation::radiuses.size(); j++)
//         {
//             if (i != j)
//             {
//                 QLineF oldLine = lineItem->line();
//                 if ((oldLine.p1() == Radiostation::radiostations[i]->scenePos() && oldLine.p2() == Radiostation::radiostations[j]->scenePos()) ||
//                     (oldLine.p1() == Radiostation::radiostations[j]->scenePos() && oldLine.p2() == Radiostation::radiostations[i]->scenePos()))
//                 {
//                     isTrue = true;
//                     break;
//                 }
//             }
//         }
//         if (isTrue) break;
//     }

//     if (!isTrue)
//     {
//         scene->removeItem(lineItem);
//         it = lines.erase(it);
//     }
//     else
//     {
//         it++;
//     }
// }

// void Communications::deleteLines()
// {
//     for (int l = 0; l < Communications::lines.size(); l++)
//     {
//         bool isTrue = false;
//         for (int i = 0; i < Radiostation::radiostations.size(); i++)
//         {
//             for (int j = 0; j < Radiostation::radiuses.size(); j++)
//             {
//                 if (i != j)
//                 {
//                     QLineF oldLine = Communications::lines[l]->line();
//                     if((oldLine.p1() == Radiostation::radiostations[i]->scenePos() && oldLine.p2() == Radiostation::radiostations[j]->scenePos()) ||
//                         (oldLine.p1() == Radiostation::radiostations[j]->scenePos() && oldLine.p2() == Radiostation::radiostations[i]->scenePos()))
//                     {
//                         isTrue = true;
//                     }
//                 }
//                 /*
//                 QLineF oldLine = lineItem->line();
//                 QPointF center1 = radiostation1->scenePos() + radiostation1->rect().center();
//                 QPointF center2 = radiostation2->scenePos() + radiostation2->rect().center();

//                 if ((oldLine.p1() != center1 && oldLine.p2() != center2) ||
//                     (oldLine.p1() != center2 && oldLine.p2() != center1))
//                 {
//                     scene->removeItem(lineItem);
//                     lines.removeOne(lineItem);
//                 }
//                 */
//             }
//         }
//         if(!isTrue)
//         {
//             scene->removeItem(Communications::lines[l]);
//             lines.removeOne(Communications::lines[l]);
//         }
//     }
// }

//метод, который проверяет соприкосеновения с другими радиостанциями
void Communications::checkCollisions()
{
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
                else
                {
                    deleteLines();
                }
            }
        }
    }
}

//метод отрисовки связей между радиостанциями
void Communications::updateLine(QGraphicsEllipseItem* radiostation1, QGraphicsEllipseItem* radiostation2)
{
    deleteLines();

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
for (QGraphicsLineItem* lineItem : lines)
{
    bool isTrue = false;
    for (int i = 0; i < Radiostation::radiostations.size(); i++)
    {
        for (int j = 0; j < Radiostation::radiuses.size(); j++)
        {
            if (i != j)
            {
                QLineF oldLine = lineItem->line();
                if((oldLine.p1() == Radiostation::radiostations[i]->scenePos() && oldLine.p2() == Radiostation::radiostations[j]->scenePos()) ||
                    (oldLine.p1() == Radiostation::radiostations[j]->scenePos() && oldLine.p2() == Radiostation::radiostations[i]->scenePos()))
                {
                    isTrue = true;
                }
            }
        }
    }
    if(!isTrue)
    {
        scene->removeItem(lineItem);
        lines.removeOne(lineItem);
    }
}
*/

/*
                QLineF oldLine = lineItem->line();
                QPointF center1 = radiostation1->scenePos() + radiostation1->rect().center();
                QPointF center2 = radiostation2->scenePos() + radiostation2->rect().center();

                if ((oldLine.p1() != center1 && oldLine.p2() != center2) ||
                    (oldLine.p1() != center2 && oldLine.p2() != center1))
                {
                    scene->removeItem(lineItem);
                    lines.removeOne(lineItem);
                }
                */

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
