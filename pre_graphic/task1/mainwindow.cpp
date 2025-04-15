#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , series(new QLineSeries)
    , chart(new QChart)
{
    ui->setupUi(this);
    ui->pb_ClearResult->setCheckable(true);
    //Объект QChart является основным
    chart->legend()->setVisible(false); //legend()->hide();
    chart->addSeries(series);
    chart->setTitle("1000Гц");
    chart->setAnimationOptions(QChart::AllAnimations);

    //chart -> chartVuiew -> данные для отображения
    chartView = new QChartView(chart);
    graphClass= new GraphicChart(NUM_GRAPHS);
    graphClass->updateGraph(chart);
    layout = new QGridLayout;
    layout->addWidget(chartView);

    connect(this, &MainWindow::sig_activatingGraph,
            this, &MainWindow::slot_activatingTheGraph);
    connect(this, &MainWindow::sig_displayGraph,
            this, &MainWindow::slot_displayGraph);
}

MainWindow::~MainWindow()
{
    delete graphClass;
    delete chartView;
    delete series;
    delete chart;
    delete ui;
}
/****************************************************/
/*!
@brief:	Метод считывает данные из файла
@param: path - путь к файлу
        numberChannel - какой канал АЦП считать
*/
/****************************************************/
QVector<uint32_t> MainWindow::readFile(QString path, uint8_t numberChannel)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);

    if(file.isOpen() == false){

        if(pathToFile.isEmpty()){
            QMessageBox mb;
            mb.setWindowTitle("Ошибка");
            mb.setText("Ошибка открытия фала");
            mb.exec();
        }
    }

    QDataStream dataStream;
    dataStream.setDevice(&file);
    dataStream.setByteOrder(QDataStream::LittleEndian);

    QVector<uint32_t> readData;
    readData.clear();
    uint32_t currentWorld = 0, sizeFrame = 0;

    while(dataStream.atEnd() == false){

        dataStream >> currentWorld;
        if(currentWorld == 0xFFFFFFFF){

            dataStream >> currentWorld;
            if(currentWorld < 0x80000000){

                dataStream >> sizeFrame;
                if(sizeFrame > 1500){
                    continue;
                }
                for(int i = 0; i<sizeFrame/sizeof(uint32_t); i++){

                    dataStream >> currentWorld;
                    if((currentWorld >> 24) == numberChannel){

                        readData.append(currentWorld);
                    }
                }
            }
        }
    }
    ui->cb_ReadSucces->setChecked(true);
    return readData;
}

QVector<double> MainWindow::processFile(QVector<uint32_t> &dataFile)
{
    QVector<double> resultData;
    resultData.clear();

    foreach (int word, dataFile) {
        word &= 0x00FFFFFF;
        if(word > 0x800000){
            word -= 0x1000000;
        }
        double res = ((double)word/6000000)*10;
        resultData.append(res);
    }
    ui->cb_ProcFileSucces->setChecked(true);
    return resultData;
}

QVector<double> MainWindow::find2Maximums(QVector<double> &resultData)
{
    double max = 0, sMax=0;
    //Поиск первого максиума
    foreach (double num, resultData){
        //QThread::usleep(1);
        if(num > max){
            max = num;
        }
    }
    //Поиск 2го максимума
    foreach (double num, resultData){
        //QThread::usleep(1);
        if(num > sMax && (qFuzzyCompare(num, max) == false)){
            sMax = num;
        }
    }
    QVector<double> maxs = {max, sMax};
    ui->cb_MaxSucess->setChecked(true);
    return maxs;
}

QVector<double> MainWindow::find2Minimums(QVector<double> &resultData)
{
    double min = 0, sMin = 0;
    QThread::sleep(1);
    //Поиск первого максиума
    foreach (double num, resultData){
        if(num < min){
            min = num;
        }
    }
    QThread::sleep(1);
    //Поиск 2го максимума
    foreach (double num, resultData){
        if(num < sMin && (qFuzzyCompare(num, min) == false)){
            sMin = num;
        }
    }
    QVector<double> mins = {min, sMin};
    ui->cb_MinSucess->setChecked(true);
    return mins;
}

void MainWindow::displayResult(QVector<double> mins, QVector<double> maxs)
{
    ui->te_Result->append("Расчет закончен!");

    ui->te_Result->append("Первый минимум " + QString::number(mins.first()));
    ui->te_Result->append("Второй минимум " + QString::number(mins.at(1)));

    ui->te_Result->append("Первый максимум " + QString::number(maxs.first()));
    ui->te_Result->append("Второй максимум " + QString::number(maxs.at(1)));
}

void MainWindow::slot_displayGraph(QVector<double> value)
{
    chart->removeSeries(series);
    for(int i= 0; i< FD; ++i){
        series->append(i, value.at(i));
    }
    chart->addSeries(series);
    chart->createDefaultAxes();

    viewGraph();
    emit sig_activatingGraph();
}

/****************************************************/
/*!
@brief:	Обработчик клика на кнопку "Выбрать путь"
*/
/****************************************************/
void MainWindow::on_pb_Path_clicked()
{
    pathToFile = "";
    ui->le_Path->clear();

    pathToFile =  QFileDialog::getOpenFileName(this,
                                               tr("Открыть файл"), "/home/",
                                               tr("ADC Files (*.adc)"));
    ui->le_Path->setText(pathToFile);
}
/****************************************************/
/*!
@brief:	Обработчик клика на кнопку "Старт"
*/
/****************************************************/
void MainWindow::on_pb_Start_clicked()
{
    //проверка на то, что файл выбран
    if(pathToFile.isEmpty()){

        QMessageBox mb;
        mb.setWindowTitle("Ошибка");
        mb.setText("Выберите файл!");
        mb.exec();
        return;
    }

    ui->cb_MaxSucess->setChecked(false);
    ui->cb_ProcFileSucces->setChecked(false);
    ui->cb_ReadSucces->setChecked(false);
    ui->cb_MinSucess->setChecked(false);

    int selectIndex = ui->cbox_NumCh->currentIndex();
    //Маски каналов
    if(selectIndex == 0){
        numberSelectChannel = 0xEA;
    }
    else if(selectIndex == 1){
        numberSelectChannel = 0xEF;
    }
    else if(selectIndex == 2){
        numberSelectChannel = 0xED;
    }

    auto read = [&]{ return readFile(pathToFile, numberSelectChannel); };
    auto process = [&](QVector<uint32_t> res){ return processFile(res);};
    auto findMax = [&](QVector<double> res){
        maxs = find2Maximums(res);
        mins = find2Minimums(res);
        displayResult(mins, maxs);
        emit sig_displayGraph(res);

    };
    auto result = QtConcurrent::run(read)
                                .then(process)
                                .then(findMax);
}

void MainWindow::slot_activatingTheGraph()
{
    chartView->show();
}

void MainWindow::viewGraph()
{
    chartView->chart()->createDefaultAxes();
}
