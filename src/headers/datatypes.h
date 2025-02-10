#ifndef DATATYPES_H
#define DATATYPES_H

#include <QString>
#include <QDate>
#include <QTime>

typedef struct {
    QString name;
    int data;
} TypeA;

typedef struct {
    QString name;
    QDate date;
    QTime timeBegin;
    QTime timeEnd;
} TypeB;

typedef struct {
    int XCoord;
    int YCoord;
} TypeC;

#endif // DATATYPES_H
