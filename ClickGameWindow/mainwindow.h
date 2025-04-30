#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "counter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ClickGameWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::ClickGameWindow *ui;
    Counter c;
    void click();
    void win();
};
#endif // MAINWINDOW_H
