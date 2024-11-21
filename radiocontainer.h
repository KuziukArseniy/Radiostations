#ifndef RADIOCONTAINER_H
#define RADIOCONTAINER_H

#include <radiostation.h>
#include <QGraphicsView>

/**
 * @brief The RadioContainer class
 * Это класс контейнер, он нужен для отрисовки и перерисовки сцены и хранения контейнера радиостанций
 */
class RadioContainer
{
public:
    RadioContainer();
    RadioContainer(QGraphicsScene* scene, Ui::MainWindow *ui, int width, int height, int id, int power);

    void addRadiostation();
    void drawScene();
    static void sendMessage(QString message);
    static void getWhite();
    static void deleteRadioCommunications();
    static void updateLine(QGraphicsEllipseItem* radiostation1, QGraphicsEllipseItem* radius);

private:
    static QList<QGraphicsPolygonItem*> arrows;
    static QList<QGraphicsLineItem*> lines;
    static QList<Radiostation*> containerRadiostations;
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    int width;
    int height;
    int id;
    int power;
};

#endif // RADIOCONTAINER_H
