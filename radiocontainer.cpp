#include "radiocontainer.h"
#include <radiostation.h>
#include <QtMath>
#include <sstream>
#include <QMessageBox>
#include <QDebug>

QList<QGraphicsPolygonItem*> RadioContainer::arrows;
QList<QGraphicsLineItem*> RadioContainer::lines;
QList<Radiostation*> RadioContainer::containerRadiostations;

//конструктор по умолчанию
RadioContainer::RadioContainer()
{

}

//конструктор с параметрами
RadioContainer::RadioContainer(QGraphicsScene* scene, Ui::MainWindow *ui, int width, int height, int id, int power)
    : ui(ui), scene(scene), width(width), height(height), id(id), power(power)
{

}

//добавление радиостанции в контейнер
void RadioContainer::addRadiostation()
{
    Radiostation* radiostation = new Radiostation(ui, width, height, id, power);
    containerRadiostations.append(radiostation);
    scene->addItem(radiostation);
}

//отрисовка, обновление сцены
void RadioContainer::drawScene()
{
    scene->update();
}

//метод для удаления связей между радиостанциями
void RadioContainer::deleteRadioCommunications()
{
    //удаление устаревших линий
    for (QGraphicsLineItem* line : RadioContainer::lines)
    {
        delete line;
    }
    RadioContainer::lines.clear();

    //удаление устаревших стрелок
    for (QGraphicsPolygonItem* arrow : RadioContainer::arrows)
    {
        delete arrow;
    }
    RadioContainer::arrows.clear();
}

//метод отрисовки связей между радиостанциями
void RadioContainer::updateLine(QGraphicsEllipseItem* radiostation1, QGraphicsEllipseItem* radiostation2)
{
    //центры радиостанций
    QPointF center1 = radiostation1->scenePos() + radiostation1->rect().center();
    QPointF center2 = radiostation2->scenePos() + radiostation2->rect().center();

    //радиус радиостанций
    qreal radius = radiostation1->rect().width() / 2;

    //вектор от первой радиостанции ко второй
    QLineF lineBetween(center1, center2);

    //смещение начала и конеца линии к краям радиостанций
    lineBetween.setP1(lineBetween.pointAt(radius / lineBetween.length()));
    lineBetween.setP2(lineBetween.pointAt(1 - (radius / lineBetween.length())));

    //линия от края первой радиостанции до края второй радиостанции
    QGraphicsLineItem* line = new QGraphicsLineItem(lineBetween);
    line->setPen(QPen(Qt::red, 2));
    radiostation1->scene()->addItem(line);

    //угол линии для создания наконечника стрелки
    double angle = std::atan2(lineBetween.dy(), lineBetween.dx());

    //позиция стрелки на краю первой радиостанции
    QPointF arrowTip = lineBetween.p1();

    //длина и угол стрелки
    qreal arrowSize = 10;
    QPointF arrowP1 = arrowTip + QPointF(arrowSize * std::cos(angle - M_PI / 6),
                                         arrowSize * std::sin(angle - M_PI / 6));
    QPointF arrowP2 = arrowTip + QPointF(arrowSize * std::cos(angle + M_PI / 6),
                                         arrowSize * std::sin(angle + M_PI / 6));

    //треугольник для наконечника стрелки
    QPolygonF arrowHead;
    arrowHead << arrowTip << arrowP1 << arrowP2;

    //добавление стрелки на сцену
    QGraphicsPolygonItem* arrowItem = new QGraphicsPolygonItem(arrowHead);
    arrowItem->setBrush(Qt::red);
    radiostation1->scene()->addItem(arrowItem);

    //добавление линии и стрелки в список
    RadioContainer::lines.append(line);
    RadioContainer::arrows.append(arrowItem);
}

//метод для рассылки сообщеинй
void RadioContainer::sendMessage(QString message)
{
    int radioId = Radiostation::getIdRadiostation();

    if(radioId == -1)
    {
        QMessageBox::information(NULL, "Ошибка", "Надо выбрать радиостанцию чтобы разослать пакет");
    }
    else
    {
        auto radiostationCircuits = Radiostation::getRadiostationCircuits();
        auto radiuses = Radiostation::getRadiuses();
        QString package= "";
        for (int i = 0; i < radiostationCircuits.size(); ++i)
        {
            if(radioId != i)
            {
                if(radiuses[radioId]->collidesWithItem(radiostationCircuits[i]))
                {
                    std::stringstream textToPackage;
                    textToPackage << "Радиостанция " << radioId + 1 << " отправляет сообщение радиостанции " << i + 1 << ": " << message.toStdString() << "\n";
                    package += QString::fromStdString(textToPackage.str());
                }
            }
        }
        QMessageBox::information(NULL, "Рассылка пакетов", package);
    }
}

//метод, который перекрашивает все круги в белый
void RadioContainer::getWhite()
{
    auto radiostationCircuits = Radiostation::getRadiostationCircuits();
    for(int i = 0; i < radiostationCircuits.size(); i++)
    {
        radiostationCircuits[i]->setBrush(Qt::white);
    }
    Radiostation::setRadiostationCircuits(radiostationCircuits);
}
