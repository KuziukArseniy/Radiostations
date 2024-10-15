#ifndef COMMUNICATIONS_H
#define COMMUNICATIONS_H

#include <QGraphicsLineItem>
#include "radiostation.h"

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
    static void updateLine(Radiostation* radiostation1, Radiostation* radius);

    static void setSc(QGraphicsScene* sc);

    static QList<QGraphicsLineItem*> lines;
    static QGraphicsScene* scene;
};

#endif // COMMUNICATIONS_H
