#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "radiostation.h"
#include "radius.h"

#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::on_createRadioButton_clicked()
{
    //мощность радиостанции
    int power = ui->editPower->text().toInt();

    //создание объектов и их параметров
    Radiostation *radiostation = new Radiostation(0, 0, 30, 30);

    Radius *radius = new Radius(0, 0, 30 * power, 30 * power);

    QGraphicsTextItem *textItem = new QGraphicsTextItem(ui->editId->text());
    textItem->setFont(QFont("Arial", 14, QFont::Bold));

    //генерация рандомных координат
    int x = QRandomGenerator::global()->bounded(0, 700);
    int y = QRandomGenerator::global()->bounded(0, 700);

    //расположение радиостанции
    radiostation->setPos(x, y);

    //расположение диапазона радиостанции
    radius->setPos(radiostation->rect().center().x() - radius->rect().width() / 2,
                   radiostation->rect().center().y() - radius->rect().height() / 2);

    //расположение цифры
    textItem->setPos(QPointF(radiostation->rect().center().x() - textItem->boundingRect().width() / 2,
                             radiostation->rect().center().y() - textItem->boundingRect().height() / 2));

    //расположение объектов на канве(передний план, задний план)
    radius->setZValue(0);
    radiostation->setZValue(1);
    textItem->setZValue(2);

    //добавление элементов
    scene->addItem(radius);
    scene->addItem(radiostation);
    scene->addItem(textItem);

    //добавление элементов в классы для последующей работы с ими
    Radiostation::radiostations.append(radiostation);
    Radius::radiuses.append(radius);

    //добавление родителя для передвижения за им
    radius->setParentItem(radiostation);
    textItem->setParentItem(radiostation);

    //итерация для ID
    ui->editId->setText(QString::number(ui->editId->text().toInt() + 1));
}

