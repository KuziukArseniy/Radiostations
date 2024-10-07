#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "radiostation.h"
#include "radius.h"
#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_createRadioButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QList<Radiostation*> radiostations;
    QList<Radius*> radiuses;
    QList<QGraphicsTextItem*> textItems;
};
#endif // MAINWINDOW_H
