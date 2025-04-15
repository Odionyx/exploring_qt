#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include <QDataStream>
#include <QMessageBox>
#include <QtGlobal>
#include <QtConcurrent>
#include <algorithm>
//Подключаем все что нужно для графиков
#include <QValueAxis>
#include <QLineSeries>
#include <QChartView>
#include <QtCharts>

#include "graphicchart.h"
#define NUM_GRAPHS 2
//частота дискретизации
#define FD 1000.0

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //Метод считывает данные из исходного файла
    QVector<uint32_t> readFile(QString path, uint8_t numberChannel);
    //Метод преобразует данные физические величины, В?
    QVector<double> processFile(QVector<uint32_t> &dataFile);
    //Метод ищет 2 максимума
    QVector<double> find2Maximums(QVector<double> &resultData);
    //Метод ищет 2 минимума
    QVector<double> find2Minimums(QVector<double> &resultData);
    //Метод отображает результаты
    void displayResult(QVector<double> mins, QVector<double> maxs);

signals:
    void sig_activatingGraph();
    void sig_displayGraph(QVector<double> value);

private slots:
    void slot_displayGraph(QVector<double> value);
    void on_pb_Path_clicked();
    void on_pb_Start_clicked();
    void slot_activatingTheGraph();

private:
    Ui::MainWindow *ui;
    void viewGraph(void);

    QString pathToFile = "";
    uint8_t numberSelectChannel = 0xEA;

    QVector<uint32_t> readData;
    QVector<double> procesData;
    QVector<double> mins, maxs;

    GraphicChart *graphClass;
    QChartView *chartView;
    QLineSeries *series;
    QGridLayout *layout;
    QChart *chart;

};
