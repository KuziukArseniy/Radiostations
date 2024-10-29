#ifndef RADIOCONTAINER_H
#define RADIOCONTAINER_H

#include <radiostation.h>
#include <QGraphicsView>

class RadioContainer
{
public:
    RadioContainer();

    static void addRadiostation(int width, int height, int id, int power);
    static void removeRadiostation(int id);
    static void drawScene();
    static void setObject(QObject object);
    static void initializeScene(QGraphicsScene* sc);
    static  QGraphicsScene *scene;

private:
    static QList<Radiostation*> containerRadiostations;
};

#endif // RADIOCONTAINER_H
