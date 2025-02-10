#ifndef CUSTOMTREEITEM_H
#define CUSTOMTREEITEM_H

#include <datatypes.h>

#include <QList>
#include <QVariant>

class CustomTreeItem
{
public:
    typedef enum {
        TYPE_A,
        TYPE_B,
        TYPE_C,
        DEFAULT
    } ItemType;

    CustomTreeItem(QList<QVariant> &, CustomTreeItem * = nullptr);
    CustomTreeItem(TypeA &, CustomTreeItem * = nullptr);
    CustomTreeItem(TypeB &, CustomTreeItem * = nullptr);
    CustomTreeItem(TypeC &, CustomTreeItem * = nullptr);

    ~CustomTreeItem();

    void appendChild(CustomTreeItem *);
    CustomTreeItem * child(int);
    int childsCount() const;
    int columnCount() const;
    QVariant data(int) const;
    CustomTreeItem * parent();
    int row() const;
    bool setData(int, const QVariant &);
    ItemType type() const;

private:
    CustomTreeItem *mParent;
    QList<CustomTreeItem *> mChilds;

    ItemType mItemType;
    QList<QVariant> mItemData;
};

#endif // CUSTOMTREEITEM_H
