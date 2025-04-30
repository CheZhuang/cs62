#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClickGameWindow)
{
    ui->setupUi(this);
    ui->winLabel->setVisible(false);
    c = Counter();

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::click);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::click()
{
    c.add();
    std::string text = "Number of Clicks: ";
    ui->counterLabel->setText(QString::fromStdString(text) + QString::number(c.getCount()));
    if (c.getCount() == 10) win();
}
void MainWindow::win()
{
    ui->pushButton->setVisible(false);
    ui->counterLabel->setVisible(false);
    ui->winLabel->setVisible(true);
}
