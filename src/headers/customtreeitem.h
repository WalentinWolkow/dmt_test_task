#ifndef CUSTOMTREEITEM_H
#define CUSTOMTREEITEM_H

#include <QDateTime>
#include <QVariant>

#include <misc.h>

typedef enum {
    TitleB_1,
    TitleB_2,
    TitleB_3,
    TitleB_4
} TitleB;


typedef struct stA {
    QString name;
    int data;

    stA() : name('A' + (char)customRand('Z' - 'A')), data(customRand(9999)) {}
} TypeA;

typedef struct stB {
    TitleB title;
    QDate date;
    QTime timeBegin;
    QTime timeEnd;

    stB() : title((TitleB)customRand((int)TitleB_4))
    {
        QDateTime dt = QDateTime::currentDateTime();
        date = dt.date();
        timeBegin = dt.time();
        timeEnd = dt.addSecs(customRand(60 * 90)).time();
    }
} TypeB;

typedef struct stC {
    int XCoord;
    int YCoord;

    stC() : XCoord(customRand(99999999)), YCoord(customRand(99999999)) {}
} TypeC;



class CustomTreeItem
{
public:
    typedef enum {
        TYPE_A,
        TYPE_B,
        TYPE_C,
        TYPE_ROOT
    } ItemType;

    CustomTreeItem(const QList<QVariant> &data = QList<QVariant>(), CustomTreeItem *parent = nullptr);
    CustomTreeItem(const TypeA &data, CustomTreeItem *parent = nullptr);
    CustomTreeItem(const TypeB &data, CustomTreeItem *parent = nullptr);
    CustomTreeItem(const TypeC &data, CustomTreeItem *parent = nullptr);
    CustomTreeItem(const CustomTreeItem &other);

    ~CustomTreeItem();

    void appendChild(CustomTreeItem *child);
    CustomTreeItem * child(int row);
    int childsCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool insertChilds(int row, int count);
    bool insertColumns(int column, int count);
    CustomTreeItem * parent();
    bool removeChilds(int row, int count);
    bool removeColumns(int column, int count);
    int row() const;
    bool setData(int column, const QVariant &data);
    ItemType type() const;

    CustomTreeItem & operator=(const CustomTreeItem &other);

    static const char * getTitleOfTypeB(int i);
    static int titlesOfBCount();

private:
    CustomTreeItem *mParent;
    QList<CustomTreeItem *> mChilds;

    ItemType mItemType;
    QList<QVariant> mItemData;

    static const char * titlesOfTypeB[];
};

#endif // CUSTOMTREEITEM_H
