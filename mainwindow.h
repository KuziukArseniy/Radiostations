#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void on_messageButton_clicked();
    void handleGraphicsViewClick(QMouseEvent* event);
    bool eventFilter(QObject* obj, QEvent* event);

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
};
#endif // MAINWINDOW_H
