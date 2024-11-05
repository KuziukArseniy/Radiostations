#ifndef RADIOCONTAINER_H
#define RADIOCONTAINER_H

#include <radiostation.h>
#include <QGraphicsView>

/**
 * @brief The RadioContainer class
 * Это класс контейнер, он нужен для перерисовки сцены и хранения контейнера радиостанций6
 */
class RadioContainer
{
public:
    RadioContainer();

    static void addRadiostation(int width, int height, int id, int power);
    static void removeRadiostation(int id);
    static void drawScene();
    static void setObject(QObject object);
    static void setScene(QGraphicsScene* scene);

private:
    static QList<Radiostation*> containerRadiostations;
    static QGraphicsScene* scene;
};

#endif // RADIOCONTAINER_H
