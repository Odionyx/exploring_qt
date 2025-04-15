#ifndef GRAPHICCHART_H
#define GRAPHICCHART_H

#include <QObject>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>

#define FIRST_GRAPH 0
#define SECOND_GRAPH 1

class GraphicChart : public QObject
{
    Q_OBJECT
public:
    GraphicChart(uint32_t numberGr = 0);

    void addDataToGraph(QVector<double> x,QVector<double> y,uint32_t numGraph);
    void updateGraph(QChart* chart);
    void clearGraph(QChart* chart);

signals:

private:
    QList<QLineSeries*> ptrGraph;
    uint32_t numGraphs = 0;

};

#endif // GRAPHICCHART_H
