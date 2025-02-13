#include "customtreeitem.h"

CustomTreeItem::CustomTreeItem(QList<QVariant> &data, CustomTreeItem *parent)
    : mParent(parent)
{
    mItemType = DEFAULT;
    mItemData = data;
}

CustomTreeItem::CustomTreeItem(TypeA &data, CustomTreeItem *parent)
    : mParent(parent)
{
    mItemType = TYPE_A;
    mItemData << data.name << data.data;
}

CustomTreeItem::CustomTreeItem(TypeB &data, CustomTreeItem *parent)
    : mParent(parent)
{
    mItemType = TYPE_B;
    mItemData << titlesOfTypeB[data.title] << data.date.toString(QStringLiteral("dd.MM.yyyy")) << data.timeBegin.toString(QStringLiteral("hh:mm:ss")) << data.timeEnd.toString(QStringLiteral("hh:mm:ss"));
}

CustomTreeItem::CustomTreeItem(TypeC &data, CustomTreeItem *parent)
    : mParent(parent)
{
    mItemType = TYPE_C;
    mItemData << data.XCoord << data.YCoord;
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

bool CustomTreeItem::setData(int column, const QVariant &data)
{
    if (column >= mItemData.size())
        return false;

    mItemData[column] = data;

    return true;
}

CustomTreeItem::ItemType CustomTreeItem::type() const
{
    return mItemType;
}
