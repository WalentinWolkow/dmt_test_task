#include "customtreeitem.h"

const char * CustomTreeItem::titlesOfTypeB[] = {
    "Гадюка",
    "Кобра",
    "Удав",
    "Питон"
};


CustomTreeItem::CustomTreeItem(const QList<QVariant> &data, CustomTreeItem *parent)
    : mParent(parent)
{
    mItemType = TYPE_ROOT;
    mItemData = data;
}

CustomTreeItem::CustomTreeItem(const TypeA &data, CustomTreeItem *parent)
    : mParent(parent)
{
    mItemType = TYPE_A;
    mItemData << data.name << data.data;
}

CustomTreeItem::CustomTreeItem(const TypeB &data, CustomTreeItem *parent)
    : mParent(parent)
{
    mItemType = TYPE_B;
    mItemData << titlesOfTypeB[data.title] << data.date.toString(QStringLiteral("dd.MM.yyyy")) << data.timeBegin.toString(QStringLiteral("hh:mm:ss")) << data.timeEnd.toString(QStringLiteral("hh:mm:ss"));
}

CustomTreeItem::CustomTreeItem(const TypeC &data, CustomTreeItem *parent)
    : mParent(parent)
{
    mItemType = TYPE_C;
    mItemData << data.XCoord << data.YCoord;
}

CustomTreeItem::CustomTreeItem(const CustomTreeItem &other)
{
    mParent = other.mParent;
    mItemData = other.mItemData;
    mItemType = other.mItemType;
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

bool CustomTreeItem::insertChilds(int row, int count)
{
    CustomTreeItem item;
    if (mItemType == TYPE_ROOT)
        item = CustomTreeItem(stA(), this);
    else if (mItemType == TYPE_A)
        item = CustomTreeItem(stB(), this);
    else if (mItemType == TYPE_B)
        item = CustomTreeItem(stC(), this);
    else
        return false;

    for (int r = row; r < row + count; ++r)
        mChilds.insert(row, new CustomTreeItem(item));

    return true;
}

bool CustomTreeItem::insertColumns(int column, int count)
{
    for (int i = 0; i < count; ++i)
        mItemData.insert(column,  QVariant());

    return true;
}

CustomTreeItem * CustomTreeItem::parent()
{
    return mParent;
}

bool CustomTreeItem::removeChilds(int row, int count)
{
    int end = row + count;
    {
        int size = mChilds.size();
        end = end > size ? size : end;
    }

    for (int r = row; r < end; ++r)
    {
        delete mChilds[row];
        mChilds.removeAt(row);
    }

    return true;
}

bool CustomTreeItem::removeColumns(int column, int count)
{
    QList<QVariant>::iterator itBegin = mItemData.begin() + column;
    mItemData.erase(itBegin, itBegin + count);

    return true;
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

CustomTreeItem & CustomTreeItem::operator=(const CustomTreeItem &other)
{
    mItemData = other.mItemData;
    mItemType = other.mItemType;
    mParent = other.mParent;

    return *this;
}


const char * CustomTreeItem::getTitleOfTypeB(int i)
{
    if (i >= sizeof(titlesOfTypeB) / sizeof(titlesOfTypeB[0]))
        return titlesOfTypeB[0];

    return titlesOfTypeB[i];
}

int CustomTreeItem::titlesOfBCount()
{
    return sizeof(titlesOfTypeB) / sizeof(titlesOfTypeB[0]);
}
