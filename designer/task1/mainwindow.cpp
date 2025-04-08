#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dialog= new Dialog(this);
    QObject::connect(ui->mainDialogButton, &QPushButton::clicked, this, [&](){
        dialog->activateWindow();
        dialog->showNormal();
    });
}

MainWindow::~MainWindow()
{
    delete dialog;
    delete ui;
}
