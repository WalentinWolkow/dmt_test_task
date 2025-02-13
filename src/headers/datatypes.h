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


typedef struct {
    QString name;
    int data;
} TypeA;

typedef struct {
    TitleB title;
    QDate date;
    QTime timeBegin;
    QTime timeEnd;
} TypeB;

typedef struct {
    int XCoord;
    int YCoord;
} TypeC;

#endif // DATATYPES_H
