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

        for (int i = 0; i < Radiostation::radiostations.size(); ++i)
        {
            for (int j = 0; j < Radiostation::radiostations.size(); ++j)
            {
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

        if (!lineExists)
        {
            scene->removeItem(lines[l]);
            delete lines[l];
            lines.removeAt(l);
        }
    }
}

//метод, который проверяет соприкосеновения с другими радиостанциями
void Communications::checkCollisions()
{
    // Удаление устаревших линий
    for (QGraphicsLineItem* line : lines) {
        scene->removeItem(line);
        delete line;
    }
    lines.clear();

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

    //создаем линию между центрами
    QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(center1, center2));
    line->setPen(QPen(Qt::red, 2));

    //добавляем линию на сцену
    radiostation1->scene()->addItem(line);

    //добавляем линию в список
    lines.append(line);
}
