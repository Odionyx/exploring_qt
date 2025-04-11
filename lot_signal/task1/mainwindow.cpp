#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    watch = new Stopwatch(this);

    ui->pbStart->setText("  Старт  ");
    ui->pbClear->setText("Очистить");
    ui->pbCircle->setText("Круг");
    ui->lTime->setText("Время");

    ui->pbCircle->blockSignals(true);
    ui->pbCircle->setEnabled(false);

    connect(ui->pbCircle,&QAbstractButton::pressed,
                    watch, &Stopwatch::slotCircle);

    connect(ui->pbStart, &QAbstractButton::clicked,
                    watch, &Stopwatch::slotStart);
    connect(ui->pbStart, &QAbstractButton::clicked,
                    this, &MainWindow::slotPbStartToggled);

    connect(ui->pbClear, &QAbstractButton::released,
                    watch, &Stopwatch::slotClear);
    connect(ui->pbClear, &QAbstractButton::released,
                    this, &MainWindow::slotTbResultTextChanged);

    connect(watch, &Stopwatch::sigResult, this,
            [&](int circle, int s, int ms){
                ui->tbResult->append( QString("«Круг %1, время: %2.%3 сек»")
                                      .arg(circle).arg(s).arg(ms));});

    connect(watch, &Stopwatch::sigTimer, this, &MainWindow::slotLTimer);

}

MainWindow::~MainWindow()
{
    delete watch;
    delete ui;
}

void MainWindow::slotLTimer(int s, int ms)
{
    ui->lTime->setText((QString("%1:%2").arg(s).arg(ms)));
}

void MainWindow::slotPbStartToggled(bool checked)
{
    if(checked){
        ui->pbStart->setText("  Стоп   ");
        ui->pbCircle->blockSignals(!checked);
        ui->pbCircle->setEnabled(true);
    } else {
        ui->pbStart->setText("  Старт  ");
        ui->pbCircle->blockSignals(!checked);
        ui->pbCircle->setEnabled(false);
    }
}

void MainWindow::slotTbResultTextChanged()
{
    ui->tbResult->clear();
}
