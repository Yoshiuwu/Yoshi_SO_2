#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Slots
void MainWindow::on_noProcLE_textChanged(const QString &arg1)
{
    if(arg1.toInt() > 0){
        ui->noProcePB->setEnabled(true);
    }
    else {
        ui->noProcePB->setEnabled(false);
    }
}

void MainWindow::on_noProcePB_clicked()
{
    contProc = ui->noProcLE->text().toInt();
    setProce(contProc);
    ui->stackedWidget->setCurrentIndex(1);
    contBatch = (procList.size() / 5);
    if(procList.size() % 5 != 0)
        ++contBatch;

}

void MainWindow::on_startPB_clicked()
{
    startProc();
    ui->startPB->setEnabled(false);
}

//Functions

void MainWindow::setProce(const int &totalProc)
{
    srand(time(NULL));
    for (int i(0); i < totalProc; ++i) {
        Proc p;
        int op = rand() % 5;
        switch (op) {
            case 0:
                p.setOperator('+');
            break;

            case 1:
                p.setOperator('-');
            break;

            case 2:
                p.setOperator('*');
            break;

            case 3:
                p.setOperator('/');
            break;

            case 4:
                p.setOperator('%');
            break;
         }
        p.setNum1(rand() % 100);
        if(op == 3 || op == 4){
            p.setNum2(rand() % 99 + 1);
        }
        else {
            p.setNum2(rand() % 99 + 1);
        }
        p.setId(i + 1);
        p.setEstTime(rand() % 10 + 6);
        p.setResult(0);
        p.setTTtime(0);

        procList.push_back(p);
    }
}

void MainWindow::startProc()
{
    int batchcount = 0, batchTop = 0;
    bool first = false;
    ui->globalCountLB->setText("Contador: " + QString::number(contGlob));
    for(int i(0); i < procList.size(); ++i){
        if(batchcount == 0){
            int aux = 0;
            for(int j(i); j < procList.size(); ++j){
                unfinishedProc* pendProc = new unfinishedProc();
                pendProc->setFormat(procList.at(j).getId(), procList.at(j).getEstTime(), procList.at(i).getTTtime());
                ui->pendingProcGL->addWidget(pendProc);
                ++aux;
                batchTop = j + 1;
                if(aux == 5){
                    break;
                }
            }
            batchcount = 5;
            if(contBatch > 0){
                --contBatch;
            }
            ui->unfinishedBatchLB->setText("Lotes pendientes: " + QString::number(contBatch));
            if(first){
                batchSeparator* bs = new batchSeparator;
                ui->finishedProcGL->addWidget(bs);
            }
            else {
                first = true;
            }
        }
        delay(1);
        QLayoutItem* child;
        child = ui->pendingProcGL->takeAt(0);
        delete child->widget();
        --batchcount;

        int tr = procList.at(i).getEstTime() - procList.at(i).getTTtime();

        ui->onIdLB->setNum(procList.at(i).getId());
        ui->onOperatorLB->setText(QString::number(procList.at(i).getNum1()) + procList.at(i).getOperator() + QString::number(procList.at(i).getNum2()));
        ui->onEstimatedTimeLB->setNum(procList.at(i).getEstTime());
        ui->onPassTimeLB->setNum(procList.at(i).getTTtime());
        ui->onRestTimeB->setNum(tr);

        for (int n (procList.at(i).getTTtime()); n < procList.at(i).getEstTime(); ++n) {
            procList[i].setTTtime(procList.at(i).getTTtime() + 1);
            delay(1);
            ui->onPassTimeLB->setNum(procList.at(i).getTTtime());
            ui->onRestTimeB->setNum(--tr);
            ++contGlob;
            ui->globalCountLB->setText("Contador: " + QString::number(contGlob));

            if(interruption)
                break;
            if(error)
                break;
            if(pause){
                do{
                    for (; ; ) {
                        delay(1);
                        if(continua)
                            break;
                    }
                }while(!continua);
                pause = false;
                continua = false;
            }
        }

        ui->onIdLB->setText("");
        ui->onOperatorLB->setText("");
        ui->onEstimatedTimeLB->setText("");
        ui->onPassTimeLB->setText("");
        ui->onRestTimeB->setText("");

        if(!interruption){
            finishedProc* finproc = new finishedProc();
            if (!error){
                procList[i].setResult(resolProc(procList.at(i).getNum1(), procList.at(i).getNum2(), procList.at(i).getOperator()));
                finproc->setFormat(procList.at(i).getId(), QString::number(procList.at(i).getNum1()) + procList.at(i).getOperator() + QString::number(procList.at(i).getNum2()),
                                   QString::number(procList.at(i).getResult()));
            }
            else {
                finproc->setFormat(procList.at(i).getId(), QString::number(procList.at(i).getNum1()) + procList.at(i).getOperator() + QString::number(procList.at(i).getNum2()),
                                   "Error");
                error = false;
            }
            ui->finishedProcGL->addWidget(finproc);
        }
        else{
            ++batchcount;
            procList.insert(batchTop, procList.at(i));
            ++batchTop;
            unfinishedProc* pendProc = new unfinishedProc();
            pendProc->setFormat(procList.at(i).getId(), procList.at(i).getEstTime(), procList.at(i).getTTtime());
            ui->pendingProcGL->addWidget(pendProc);
            interruption = false;
        }
    }
}

void MainWindow::delay(const int &seg)
{
    QTime betweenTime = QTime::currentTime().addSecs(seg);
    while (QTime::currentTime() < betweenTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

int MainWindow::resolProc(const int &num1, const int &num2, const char op)
{
    int result;
    switch (op) {
        case '+':
            result = num1 + num2;
        break;

        case '-':
            result = num1 - num2;
        break;

        case '*':
            result = num1 * num2;
        break;

        case '/':
            result = num1 / num2;
        break;

        case '%':
            result = num1 % num2;
        break;
    }
    return result;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

   if(ui->stackedWidget->currentIndex() == 1){
       if(event->key() == Qt::Key_I && pause == false)
          interruption = true;
       if(event->key() == Qt::Key_E && pause == false)
          error = true;
       if(event->key() == Qt::Key_P && pause == false)
          pause = true;
       if(event->key() == Qt::Key_C && pause == true)
          continua = true;
   }
}
