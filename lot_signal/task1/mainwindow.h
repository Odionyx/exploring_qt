#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QDebug>
#include <QMainWindow>
#include "stopwatch.h"
#include <QAbstractButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slotLTimer(int, int);

private slots:
    void slotPbStartToggled(bool checked);
    void slotTbResultTextChanged();

private:
    Ui::MainWindow *ui;
    Stopwatch *watch;

};
#endif // MAINWINDOW_H
