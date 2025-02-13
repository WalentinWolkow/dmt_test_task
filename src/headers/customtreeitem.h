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

    CustomTreeItem(QList<QVariant> &data, CustomTreeItem *parent = nullptr);
    CustomTreeItem(TypeA &data, CustomTreeItem *parent = nullptr);
    CustomTreeItem(TypeB &data, CustomTreeItem *parent = nullptr);
    CustomTreeItem(TypeC &data, CustomTreeItem *parent = nullptr);

    ~CustomTreeItem();

    void appendChild(CustomTreeItem *child);
    CustomTreeItem * child(int row);
    int childsCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    CustomTreeItem * parent();
    int row() const;
    bool setData(int column, const QVariant &data);
    ItemType type() const;

private:
    CustomTreeItem *mParent;
    QList<CustomTreeItem *> mChilds;

    ItemType mItemType;
    QList<QVariant> mItemData;
};

#endif // CUSTOMTREEITEM_H
