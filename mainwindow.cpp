#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "radiostation.h"
#include "communications.h"
#include <QMessageBox>

//конструктор класса MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->simulatioArea->setScene(scene);

    Communications::scene = scene;
    Communications::setSc(scene);

    Radiostation::ui = ui;
}

//деструктор класса MainWindow
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

    if(power >= 5)
    {
        int id = ui->editId->text().toInt();

        //создание объектов и их параметров
        Radiostation *radiostation = new Radiostation(30, 30, id, power);

        //расположение радиостанции
        //radiostation->setPos(x, y);

        //добавление элементов
        scene->addItem(radiostation);

        //итерация для ID
        ui->editId->setText(QString::number(ui->editId->text().toInt() + 1));
    }
    else
    {
        QMessageBox::information(this, "Ошибка", "Мощность должна быть 5 и больше");
    }
}

//кнопка рассылки пакетов
void MainWindow::on_messageButton_clicked()
{
    QString message = ui->editMessage->text();
    Radiostation::sendMessage(message);
}

