#include "unfinishedproc.h"
#include "ui_unfinishedproc.h"

unfinishedProc::unfinishedProc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::unfinishedProc)
{
    ui->setupUi(this);
}

unfinishedProc::~unfinishedProc()
{
    delete ui;
}

void unfinishedProc::setFormat(const int &id, const int &time, const int &tt)
{
    ui->idLB->setNum(id);
    ui->timeLB->setNum(time);
    ui->ttLb->setNum(tt);
}
