#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>

class Stopwatch : public QObject
{
    Q_OBJECT
public:
    explicit Stopwatch(QObject *parent = nullptr);
    ~Stopwatch();

signals:
    void sigTimer(int, int);
    void sigResult(int, int, int);

public slots:
    void slotStart(bool checked);
    void slotCircle();
    void slotClear();

private:
    QTimer *timer;
    int circle, timeS, timeMs, timeS2, timeMs2;
    long int count, temp, temp2;
    bool checked;
};

#endif // STOPWATCH_H
