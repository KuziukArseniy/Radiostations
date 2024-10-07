#ifndef RADIOSTATION_H
#define RADIOSTATION_H

#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <QObject>

/**
 * @brief The Radiostation class
 * В данном классе содержаться данные о радиостанциях
 * Здесь обработано событие, которое срабатывает по нажатию на станцию
 */
class Radiostation : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Radiostation(int x, int y, int width, int height);

    static QList<Radiostation*> radiostations;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // RADIOSTATION_H
