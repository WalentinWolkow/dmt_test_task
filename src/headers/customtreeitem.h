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

private:
    CustomTreeItem *mParent;
    QList<CustomTreeItem *> mChilds;

    ItemType mItemType;
    QList<QVariant> mItemData;
};

#endif // CUSTOMTREEITEM_H
