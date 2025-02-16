#ifndef DATATYPES_H
#define DATATYPES_H

#include <QString>
#include <QDate>
#include <QTime>

#define TITLES_OF_TYPE_B_NUMBER 4
extern const char * titlesOfTypeB[TITLES_OF_TYPE_B_NUMBER];

typedef enum {
    TitleB_1,
    TitleB_2,
    TitleB_3,
    TitleB_4
} TitleB;


typedef struct stA {
    QString name;
    int data;

    stA() : data(0) {}
} TypeA;

typedef struct stB {
    TitleB title;
    QDate date;
    QTime timeBegin;
    QTime timeEnd;

    stB() : title(TitleB::TitleB_1)
    {
        QDateTime dt = QDateTime::currentDateTime();
        date = dt.date();
        timeBegin = timeEnd = dt.time();
    }
} TypeB;

typedef struct stC {
    int XCoord;
    int YCoord;

    stC() : XCoord(0), YCoord(0) {}
} TypeC;

#endif // DATATYPES_H
