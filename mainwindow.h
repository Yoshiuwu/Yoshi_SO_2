#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <iostream>
#include <QRegExp>
#include <QMessageBox>
#include "proc.h"
#include "batchseparator.h"
#include "finishedproc.h"
#include "unfinishedproc.h"
#include <QKeyEvent>
#include <time.h>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_noProcLE_textChanged(const QString &arg1);

    void on_noProcePB_clicked();

    void on_startPB_clicked();

protected:

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;

    int contProc;
    int contBatch = 0;
    int contGlob = 0;
    bool interruption = false;
    bool error = false;
    bool pause = false;
    bool continua = false;
    QList<Proc> procList;

    void setProce(const int &totalProc);
    void startProc();
    void delay(const int &seg);
    int resolProc(const int &num1, const int &num2, const char op);
};
#endif // MAINWINDOW_H
