#include "mainwindow.h"
#include "radiostation.h"
#include "communications.h"
#include "radiocontainer.h"
#include <QMessageBox>
#include <radiocontainer.h>

#include <QDebug>

//конструктор класса MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->simulatioArea->setScene(scene);

    Communications::setSc(scene);
    Radiostation::setScene(ui);
    RadioContainer::setScene(scene);

    ui->simulatioArea->viewport()->installEventFilter(this);
}

//деструктор класса MainWindow
MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

//метод для фильтрации событий
bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    //проверка нажатия на сцену
    if (obj == ui->simulatioArea->viewport() && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        QPointF scenePos = ui->simulatioArea->mapToScene(mouseEvent->pos());
        QGraphicsItem* item = scene->itemAt(scenePos, QTransform());

        //если элемент не найден, значит нажата пустая область сцены
        if (!item) {
            handleGraphicsViewClick(mouseEvent);
            return true;
        }
        //если элемент найден, позволяем ему обрабатывать свои события
        return false;
    }
    return QMainWindow::eventFilter(obj, event);
}

//обработчик нажатия по пустой части сцены
void MainWindow::handleGraphicsViewClick(QMouseEvent* event)
{
    QPointF scenePos = ui->simulatioArea->mapToScene(event->pos());
    qDebug() << "Клик на позиции сцены";
    QGraphicsItem* item = scene->itemAt(scenePos, QTransform());
    if (!item)
    {
        Radiostation::getWhite();
        ui->tableRadiostations->setItem(0, 0, new QTableWidgetItem(""));
        ui->tableRadiostations->setItem(0, 1, new QTableWidgetItem(""));
        ui->tableRadiostations->setItem(0, 2, new QTableWidgetItem(""));
    }
}

//кнопка добавления радиостанции
void MainWindow::on_createRadioButton_clicked()
{
    //мощность радиостанции
    int power = ui->editPower->text().toInt();

    if(power >= 5 && power <= 20)
    {
        int id = ui->editId->text().toInt();

        //добавление радиостанции
        RadioContainer::addRadiostation(30, 30, id, power);

        //итерация для ID
        ui->editId->setText(QString::number(ui->editId->text().toInt() + 1));
    }
    else
    {
        QMessageBox::information(this, "Ошибка", "Мощность должна быть 5-20");
    }
}

//кнопка рассылки пакетов
void MainWindow::on_messageButton_clicked()
{
    QString message = ui->editMessage->text();
    Radiostation::sendMessage(message);
}
