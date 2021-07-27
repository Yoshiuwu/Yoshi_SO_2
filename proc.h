#ifndef PROC_H
#define PROC_H
#include <QString>

class Proc
{
public:
    Proc();

    int getNum1() const;
    void setNum1(int value);

    int getNum2() const;
    void setNum2(int value);

    char getOperator() const;
    void setOperator(char value);

    int getId() const;
    void setId(int value);

    int getEstTime() const;
    void setEstTime(int value);

    int getResult() const;
    void setResult(int value);


    int getTTtime() const;
    void setTTtime(int value);



private:

    int num1;
    int num2;
    char oper;
    int id;
    int estTime;
    int result;
    int tTtime;

};

#endif // PROC_H
