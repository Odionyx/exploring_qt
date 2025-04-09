#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    counter= 0;
    /* Name */
    ui->rbMainOn->setText(" Вкл.");
    ui->rbMainOff->setText(" Выкл.");
    ui->pbMainMake->setText(" Выполнить");
    ui->gBoxMainRadioButton->setTitle("Соединение");
    ui->gBoxMainList->setTitle("Запрос");
    /* drop list */
    ui->cBoxMainList->addItem("  Создать");
    ui->cBoxMainList->addItem("  Добавить столбец");
    ui->cBoxMainList->addItem("  Добавить строку");
    ui->cBoxMainList->addItem("  далить строку");
    ui->cBoxMainList->addItem("  Удалить столбец");
    ui->cBoxMainList->addItem("  Удалить");
    /* Progress bard */
    ui->pBarMainResult->setMaximum(10);
    ui->pBarMainResult->setMinimum(0);
    ui->pBarMainResult->setValue(0);
    /* PushButton */
    ui->pbMainMake->setAutoDefault(true);

    // Connect button signal to appropriate slot
    connect(ui->pbMainMake, &QPushButton::clicked,
            this, &MainWindow::onPbMainMakeToggled, Qt::UniqueConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPbMainMakeToggled(bool checked)
{
    if( counter< 10)
        ++counter;
    else {
        ui->rbMainOff->animateClick();
        counter= 0;
    }
    ui->pBarMainResult->setValue(counter);
}
