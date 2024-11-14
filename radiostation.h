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
    void sendMessage(QString message);
    int getIdRadiostation();
    static void getWhite();
    static void checkCollisions();

private:
    static QList<QGraphicsEllipseItem*> radiostations;
    static QList<QGraphicsEllipseItem*> radiuses;
    QGraphicsEllipseItem* radiusItem;
    QGraphicsTextItem* textItem;
    Ui::MainWindow* ui;

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // RADIOSTATION_H
