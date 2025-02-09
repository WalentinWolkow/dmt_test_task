#ifndef CUSTOMTREEITEM_H
#define CUSTOMTREEITEM_H

#include <QList>
#include <QVariant>

class CustomTreeItem
{
public:
    CustomTreeItem(QList<QVariant> &, CustomTreeItem * = nullptr);
    ~CustomTreeItem();

    void appendChild(CustomTreeItem *);
    CustomTreeItem * child(int);
    int childsCount() const;
    int columnCount() const;
    QVariant data(int) const;
    CustomTreeItem * parent();
    int row() const;

private:
    CustomTreeItem *mParent;
    QList<CustomTreeItem *> mChilds;

    QList<QVariant> mItemData;
};

#endif // CUSTOMTREEITEM_H
