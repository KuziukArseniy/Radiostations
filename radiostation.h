#ifndef RADIOSTATION_H
#define RADIOSTATION_H

#include "ui_mainwindow.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <QObject>

class Radiostation: public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Radiostation();
    Radiostation(Ui::MainWindow *ui, int width, int height, int id, int power);
    static int getIdRadiostation();
    //void sendMessage(QString message);
    //static void getWhite();
    static void checkCollisions();
    //static QList<QGraphicsEllipseItem*> radiostationCircuits;
    //static QList<QGraphicsEllipseItem*> radiuses;
    static QList<QGraphicsEllipseItem*> getRadiostationCircuits();
    static void setRadiostationCircuits(QList<QGraphicsEllipseItem*> radiostationCircuits);
    static QList<QGraphicsEllipseItem*> getRadiuses();
    static void setRadiuses(QList<QGraphicsEllipseItem*> radiuses);

private:
    static QList<QGraphicsEllipseItem*> radiostationCircuits;
    static QList<QGraphicsEllipseItem*> radiuses;
    QGraphicsEllipseItem* radiusItem;
    QGraphicsTextItem* textItem;
    Ui::MainWindow* ui;

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // RADIOSTATION_H
