#ifndef RADIOSTATION_H
#define RADIOSTATION_H

#include "ui_mainwindow.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <QObject>

/**
 * @brief The Radiostation class
 * В этом классе представелна реализация радиостанции
 * Здесь реализованы события на передвижение радиостанции и на клик на радиостанцию
 */

class Radiostation : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Radiostation(int width, int height, int id, int power);
    static QList<QGraphicsEllipseItem*> radiostations;
    static QList<QGraphicsEllipseItem*> radiuses;
    static void getWhite();
    static void sendMessage(QString message);
    static int getIdRadiostation();
    static void setScene(Ui::MainWindow* scene);


private:
    QGraphicsEllipseItem* radiusItem;
    QGraphicsTextItem* textItem;
    static Ui::MainWindow* ui;

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // RADIOSTATION_H
