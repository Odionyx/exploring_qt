#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer(this);
    timer->setInterval(94);

    timeS = timeMs = timeS2 = timeMs2 = 0;
    circle =  count = temp = temp2 = 0;
    checked = true;

    connect(timer, &QTimer::timeout, this, [&]{
        count++;
        timeMs = count % 10;
        timeS  = count / 10;
        emit sigTimer(timeS, timeMs);
    });
}

Stopwatch::~Stopwatch()
{
    delete timer;
}

void Stopwatch::slotStart(bool checked)
{
    if(checked)
        timer->start();
    else timer->stop();
}

void Stopwatch::slotCircle()
{
    circle++;

    temp = count - temp2;
    temp2 = count;

    timeMs2 = temp % 10;
    timeS2  = temp / 10;

    emit sigResult(circle, timeS2, timeMs2);
}

void Stopwatch::slotClear()
{
    timeS = timeMs = timeS2 = timeMs2 = 0;
    circle =  count = temp = temp2 = 0;
    emit sigTimer(timeS, timeMs);
}
