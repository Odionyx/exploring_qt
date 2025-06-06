#ifndef EXAMPLERACE_H
#define EXAMPLERACE_H

#include <QThread>
#include <QMutex>
#include <functional>

//Создаем класс в котором будем реализовывать код, выполняемый в нескольких потоках
class ExampleRace : public QObject{
    Q_OBJECT
    QMutex* mut;    //Сразу добавим примитив синхронизации

public:
    //Прокидываем мьютекс
    ExampleRace(QMutex* m) : mut(m){
    }
    //Передаем указатель на переменную которую будем инкрементировать,
    //флак включения мьютексов, и количесво итераций
    void DoWork(uint32_t* inc, bool mutexOn, int numIterat);

signals:

    void sig_Finish( void );

};


//Класс-обертка QThread, который будет распределять наш класс по потокам.
//Именно так правильно использовать QThread, можно переопределить класс run,
//но разработчики Qt рекомендуют делать именно так.
class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread; //Экземпляр потока
    QMutex* mut; //Прокидываем мьютекс

public:
    Controller(QMutex* m) : mut(m) {
        //экземпляр нашего класса
        ExampleRace *race = new ExampleRace(mut);
        race->moveToThread(&workerThread); //Помещаем в поток
        //По завершению потока удаляем экземпляр класса
        connect(&workerThread, &QThread::finished, race,&QObject::deleteLater);
        //Запускаем "тяжелый" метод
        connect(this, &Controller::operate, race, &ExampleRace::DoWork);
        //Пробрасываем сигнал для отображения в GUI
        connect(race,&ExampleRace::sig_Finish,this,&Controller::sig_WorkFinish);
        workerThread.start(); //Запускаем работу потока
    }
    ~Controller(){

        //Завершаем работу потока
        workerThread.quit();
        workerThread.wait();

    }

signals:
    void operate( uint32_t *num, bool mutexOn, int numIterat );
    void sig_WorkFinish( void );

};

#endif // EXAMPLERACE_H
