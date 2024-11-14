#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "radiocontainer.h"
#include "radiostation.h"
#include <QMessageBox>
#include <QDebug>

//конструктор главной формы
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->simulatioArea->setScene(scene);
    ui->simulatioArea->viewport()->installEventFilter(this);
}

//деструктор главной формы
MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
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
        RadioContainer* radiostation = new RadioContainer(scene, ui, 30, 30, id, power);
        radiostation->addRadiostation();

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
    Radiostation* radioSendMessage = new Radiostation();
    radioSendMessage->sendMessage(message);
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
        if (!item)
        {
            handleGraphicsViewClick(mouseEvent);
            return true;
        }
        //если элемент найден, позволяем ему обрабатывать свои события
        return false;
    }
    return QMainWindow::eventFilter(obj, event);
}
