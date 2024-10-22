#ifndef COMMUNICATIONS_H
#define COMMUNICATIONS_H

#include <QGraphicsLineItem>

/**
 * @brief The Communications class
 * В этом классе представлены связи между радиостанциями
 * Здесь реализованы проверка соприкосновения станций и генерация связи между станциями
 */

class Communications: QGraphicsItem
{
public:
    Communications()
    {

    }
    ~Communications()
    {

    }

    static void checkCollisions();
    static void updateLine(QGraphicsEllipseItem* radiostation1, QGraphicsEllipseItem* radius);
    static void deleteLines();

    static void setSc(QGraphicsScene* sc);

    static QList<QGraphicsLineItem*> lines;
    static QList<bool*> linesIsCollide;
    static QGraphicsScene* scene;
};

#endif // COMMUNICATIONS_H
