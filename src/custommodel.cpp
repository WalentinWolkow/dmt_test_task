#include "custommodel.h"
#include <customtreeitem.h>

CustomModel::CustomModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "One" << "Two" << "Three" << "Four";
    rootItem = new CustomTreeItem(rootData);
}

CustomModel::~CustomModel()
{
    delete rootItem;
}


QVariant CustomModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return orientation == Qt::Horizontal && role == Qt::DisplayRole ? rootItem->data(section) : QVariant();
}

bool CustomModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (role != Qt::EditRole || value == headerData(section, orientation, Qt::DisplayRole))
        return false;

    if (!rootItem->setData(section, value))
        return false;

    emit headerDataChanged(orientation, section, section);

    return true;
}

QModelIndex CustomModel::index(int row, int column, const QModelIndex &parent) const
{
    CustomTreeItem *item = (parent.isValid() ? static_cast<CustomTreeItem *>(parent.internalPointer()) : rootItem)->child(row);

    return item && column < item->columnCount() ? createIndex(row, column, item) : QModelIndex();
}

QModelIndex CustomModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    CustomTreeItem *parentItem = static_cast<CustomTreeItem *>(index.internalPointer())->parent();

    return parentItem == rootItem ? QModelIndex() : createIndex(parentItem->row(), 0, parentItem);
}

int CustomModel::rowCount(const QModelIndex &parent) const
{
    return (parent.isValid() ? static_cast<CustomTreeItem *>(parent.internalPointer()) : rootItem)->childsCount();
}

int CustomModel::columnCount(const QModelIndex &parent) const
{
    return (parent.isValid() ? static_cast<CustomTreeItem *>(parent.internalPointer()) : rootItem)->columnCount();
}

bool CustomModel::hasChildren(const QModelIndex &parent) const
{
    return (parent.isValid() ? static_cast<CustomTreeItem *>(parent.internalPointer()) : rootItem)->childsCount() != 0;
}

QVariant CustomModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    return static_cast<CustomTreeItem *>(index.internalPointer())->data(index.column());
}

bool CustomModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole || data(index, Qt::DisplayRole) == value)
        return false;

    if (!static_cast<CustomTreeItem *>(index.internalPointer())->setData(index.column(), value))
        return false;

    emit dataChanged(index, index, QVector<int>() << role);

    return true;
}

Qt::ItemFlags CustomModel::flags(const QModelIndex &index) const
{
    return index.isValid() ? Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable : Qt::ItemIsDropEnabled;
}

bool CustomModel::canInsertRows(const QModelIndex &parent) const
{
    CustomTreeItem *item = parent.isValid() ? static_cast<CustomTreeItem *>(parent.internalPointer()) : rootItem;
    return item->childsCount() < maxChildsCount[item->type()];
}

bool CustomModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);

    CustomTreeItem *item = parent.isValid() ? static_cast<CustomTreeItem *>(parent.internalPointer()) : rootItem;
    bool res = item->insertChilds(row, count);

    endInsertRows();

    return res;
}

bool CustomModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);

    for (int row = 0, rows = rowCount(parent); row < rows; ++row)
        static_cast<CustomTreeItem *>(index(row, 0, parent).internalPointer())->insertColumns(column, count);

    endInsertColumns();

    return true;
}

bool CustomModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);

    CustomTreeItem *item = parent.isValid() ? static_cast<CustomTreeItem *>(parent.internalPointer()) : rootItem;
    bool res = item->removeChilds(row, count);

    endRemoveRows();

    return res;
}

bool CustomModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);

    for (int row = 0, rows = rowCount(parent); row < rows; ++row)
    {
        QModelIndex curIndex = index(row, column, parent);
        if (curIndex.isValid())
            static_cast<CustomTreeItem *>(curIndex.internalPointer())->removeColumns(column, count);
    }

    endRemoveColumns();

    return true;
}


const int CustomModel::maxChildsCount[] = {
    LAYER_A_MAX_CHILDS_COUNT,
    LAYER_B_MAX_CHILDS_COUNT,
    LAYER_C_MAX_CHILDS_COUNT,
    ROOT_MAX_CHILDS_COUNT
};
