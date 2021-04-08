#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->resize(WINDOW_WIDTH, WINDOW_HIGHT);

    myWidget = new MyGLWidget(this);
    myWidget->move(0, 0);
    myWidget->resize(WINDOW_WIDTH, WINDOW_HIGHT);
    myWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete myWidget;
    myWidget = nullptr;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    myWidget->resize(event->size().width(), event->size().height());
}

