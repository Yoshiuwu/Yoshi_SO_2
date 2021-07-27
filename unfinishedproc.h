#ifndef UNFINISHEDPROC_H
#define UNFINISHEDPROC_H

#include <QWidget>

namespace Ui {
class unfinishedProc;
}

class unfinishedProc : public QWidget
{
    Q_OBJECT

public:
    explicit unfinishedProc(QWidget *parent = nullptr);
    ~unfinishedProc();

    void setFormat(const int &id, const int &time, const int &tt);

private:
    Ui::unfinishedProc *ui;
};

#endif // UNFINISHEDPROC_H
