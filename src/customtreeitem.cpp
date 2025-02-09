#include "customtreeitem.h"

CustomTreeItem::CustomTreeItem(QList<QVariant> &data, CustomTreeItem *parent)
{
    mParent = parent;
    mItemData = data;
}

CustomTreeItem::~CustomTreeItem()
{
    qDeleteAll(mChilds);
}


void CustomTreeItem::appendChild(CustomTreeItem *child)
{
    mChilds.append(child);
}

CustomTreeItem * CustomTreeItem::child(int row)
{
    return mChilds.value(row, nullptr);
}

int CustomTreeItem::childsCount() const
{
    return mChilds.size();
}

int CustomTreeItem::columnCount() const
{
    return mItemData.size();
}

QVariant CustomTreeItem::data(int column) const
{
    return mItemData.value(column, QVariant());
}

CustomTreeItem * CustomTreeItem::parent()
{
    return mParent;
}

int CustomTreeItem::row() const
{
    return mParent ? mParent->mChilds.indexOf(const_cast<CustomTreeItem *>(this)) : 0;
}
