#include "radiostation.h"
#include "communications.h"
#include "radiocontainer.h"
#include <QBrush>
#include <QDebug>
#include <QGraphicsScene>
#include <QMessageBox>
#include <sstream>
#include <QDateTime>
#include <QRandomGenerator>

QList<QGraphicsEllipseItem*> Radiostation::radiostations;
QList<QGraphicsEllipseItem*> Radiostation::radiuses;
Ui::MainWindow* Radiostation::ui = nullptr;

//конструктор класса Radiostations
//Radiostation::Radiostation(int x, int y, int width, int height, int id, int power)
Radiostation::Radiostation(int width, int height, int id, int power)
    : QObject(), QGraphicsEllipseItem()
{
    //генерация рандомных координат
    int x = QRandomGenerator::global()->bounded(0, 700);
    int y = QRandomGenerator::global()->bounded(0, 700);

    //размеры окружности
    setRect(x, y, width, height);
    //зеленая рамка
    QPen penCircle(Qt::green);
    setPen(penCircle);
    //подвижный
    setFlag(QGraphicsItem::ItemIsMovable);
    //уровень расположения радиостанции
    setZValue(1);

    radiostations.append(this);

    //радиус действия
    radiusItem = new QGraphicsEllipseItem(x, y, width * power, height * power);
    //штриховая окружность
    radiusItem->setPen(QPen(Qt::DashLine));
    //уровень расположения радиуса
    radiusItem->setZValue(0);
    //расположение радиуса действия
    radiusItem->setPos(this->rect().width() / 2 - radiusItem->rect().width() / 2,
                       this->rect().height() / 2 - radiusItem->rect().height() / 2);

    radiuses.append(radiusItem);

    //id радиостанции
    textItem = new QGraphicsTextItem(QString::number(id));
    //шрифт цифры
    textItem->setFont(QFont("Arial", 14, QFont::Bold));
    //уровень расположения id
    textItem->setZValue(2);
    //расположение цифры
    textItem->setPos(QPointF(this->rect().center().x() - textItem->boundingRect().width() / 2,
                             this->rect().center().y() - textItem->boundingRect().height() / 2));

    //добавление родителя для передвижения за им
    radiusItem->setParentItem(this);
    textItem->setParentItem(this);
}

//метод, который перекрашивает все круги в белый
void Radiostation::getWhite()
{
    for(int i = 0; i < radiostations.size(); i++)
    {
        radiostations[i]->setBrush(Qt::white);
    }
}

//методя для получения id выбранной радиостанции
int Radiostation::getIdRadiostation()
{
    for (int i = 0; i < Radiostation::radiostations.size(); ++i)
    {
        if(radiostations[i]->brush().color() == Qt::green)
        {
            return i;
        }
    }
    return -1;
}

//событие, срабатывающее по нажатию на радиостанцию
void Radiostation::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    getWhite();
    //окружность в зелёный при нажатии
    setBrush(QBrush(Qt::green));

    int radioId = getIdRadiostation();

    ui->tableRadiostations->setItem(0, 0, new QTableWidgetItem(QString::number(radioId + 1)));

    int power = Radiostation::radiuses[radioId]->rect().width() / 30;
    ui->tableRadiostations->setItem(0, 1, new QTableWidgetItem(QString::number(power)));

    int countCommunications = 0;
    //проверка столкновений с другими кругами
    for (int i = 0; i < Radiostation::radiostations.size(); ++i)
    {
        if(radioId != i)
        {
            if(Radiostation::radiuses[radioId]->collidesWithItem(Radiostation::radiostations[i]))
            {
                countCommunications++;
            }
        }
    }
    ui->tableRadiostations->setItem(0, 2, new QTableWidgetItem(QString::number(countCommunications)));


    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->logsTextEdit->appendPlainText(currentDateTime + " Radiostation pressed");
}

//событие, срабатывающее при перемещении радиостанции
void Radiostation::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsEllipseItem::mouseMoveEvent(event);

    Communications::checkCollisions();

    RadioContainer::drawScene();

    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->logsTextEdit->appendPlainText(currentDateTime + " Radiostation moved");
}

//метод для рассылки сообщеинй
void Radiostation::sendMessage(QString message)
{

    int radioId = getIdRadiostation();

    if(radioId == -1)
    {
        QMessageBox::information(NULL, "Ошибка", "Надо выбрать радиостанцию чтобы разослать пакет");
    }
    else
    {
        QString package= "";
        for (int i = 0; i < Radiostation::radiostations.size(); ++i)
        {
            if(radioId != i)
            {
                if(Radiostation::radiuses[radioId]->collidesWithItem(Radiostation::radiostations[i]))
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
