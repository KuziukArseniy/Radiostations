#include "radiostation.h"
#include "radius.h"
#include "communications.h"
#include "ui_mainwindow.h"
#include <QBrush>
#include <QDebug>
#include <QGraphicsScene>
#include <QMessageBox>
#include <sstream>
#include <QDateTime>

QList<Radiostation*> Radiostation::radiostations;
Ui::MainWindow* Radiostation::ui = nullptr;

//конструктор класса Radiostations
Radiostation::Radiostation(int x, int y, int width, int height)
    : QObject(), QGraphicsEllipseItem()
{
    //размеры окружности
    setRect(x, y, width, height);

    //зеленая рамка
    QPen penCircle(Qt::green);
    setPen(penCircle);

    //подвижный
    setFlag(QGraphicsItem::ItemIsMovable);

    //расположение
    setZValue(1);
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

    int power = Radius::radiuses[radioId]->rect().width() / 30;
    ui->tableRadiostations->setItem(0, 1, new QTableWidgetItem(QString::number(power)));

    int countCommunications = 0;
    //проверка столкновений с другими кругами
    for (int i = 0; i < Radiostation::radiostations.size(); ++i)
    {
        if(radioId != i)
        {
            if(Radius::radiuses[radioId]->collidesWithItem(Radiostation::radiostations[i]))
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
    Communications::checkCollisions();

    QGraphicsEllipseItem::mouseMoveEvent(event);

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
                if(Radius::radiuses[radioId]->collidesWithItem(Radiostation::radiostations[i]))
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
