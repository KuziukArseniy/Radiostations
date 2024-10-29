#include "radiocontainer.h"
#include <radiostation.h>
#include <communications.h>
#include <QDebug>

QGraphicsScene* RadioContainer::scene;
QList<Radiostation*> RadioContainer::containerRadiostations;

//конструктор
RadioContainer::RadioContainer()
{

}

//добавление радиостанции в контейнер
void RadioContainer::addRadiostation(int width, int height, int id, int power)
{
    Radiostation *radiostation = new Radiostation(width, height, id, power);
    containerRadiostations.append(radiostation);
    scene->addItem(radiostation);
}

//отрисовка сцены
void RadioContainer::drawScene()
{
    //scene->clear();

    for (Radiostation* radiostation : containerRadiostations)
    {
        scene->addItem(radiostation);
    }

    //обновляем связи между радиостанциями
    Communications::checkCollisions();

    scene->update();
}
