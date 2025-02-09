#include "custommodel.h"

#include <customtreeitem.h>

static const Record records[] = {
    { 1, 0, "Group1" },
    { 2, 1, "Group1.1" },
    { 3, 1, "Group1.2" },
    { 4, 0, "Group2" },
    { 5, 4, "Group2.1" },
    { 6, 1, "Group1.3" },
    { 7, 0, "Group3" },
    { 8, 7, "Group3.1" },
    { 9, 8, "Group3.1.1" },
    { 10, 8, "Group3.1.2" }
};

CustomModel::CustomModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "ID" << "Name" << "Parent ID";
    rootItem = new CustomTreeItem(rootData);

    QList<QVariant> itemData;
    {
        const Record &r = records[0];
        itemData << r.id << r.name << r.parentId;
    }
    CustomTreeItem *item = new CustomTreeItem(itemData, rootItem);
    rootItem->appendChild(item);

    itemData.clear();
    {
        const Record &r = records[1];
        itemData << r.id << r.name << r.parentId;
    }
    item->appendChild(new CustomTreeItem(itemData, item));

    itemData.clear();
    {
        const Record &r = records[2];
        itemData << r.id << r.name << r.parentId;
    }
    item->appendChild(new CustomTreeItem(itemData, item));

    itemData.clear();
    {
        const Record &r = records[5];
        itemData << r.id << r.name << r.parentId;
    }
    item->appendChild(new CustomTreeItem(itemData, item));

    itemData.clear();
    {
        const Record &r = records[3];
        itemData << r.id << r.name << r.parentId;
    }
    item = new CustomTreeItem(itemData, rootItem);
    rootItem->appendChild(item);

    itemData.clear();
    {
        const Record &r = records[4];
        itemData << r.id << r.name << r.parentId;
    }
    item->appendChild(new CustomTreeItem(itemData, item));

    itemData.clear();
    {
        const Record &r = records[6];
        itemData << r.id << r.name << r.parentId;
    }
    item = new CustomTreeItem(itemData, rootItem);
    rootItem->appendChild(item);

    itemData.clear();
    {
        const Record &r = records[7];
        itemData << r.id << r.name << r.parentId;
    }
    CustomTreeItem *itemm = new CustomTreeItem(itemData, item);
    item->appendChild(itemm);

    itemData.clear();
    {
        const Record &r = records[8];
        itemData << r.id << r.name << r.parentId;
    }
    itemm->appendChild(new CustomTreeItem(itemData, itemm));

    itemData.clear();
    {
        const Record &r = records[9];
        itemData << r.id << r.name << r.parentId;
    }
    itemm->appendChild(new CustomTreeItem(itemData, itemm));
}

CustomModel::~CustomModel()
{
    delete rootItem;
}

QVariant CustomModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return orientation == Qt::Horizontal && role == Qt::DisplayRole ? rootItem->data(section) : QVariant();
}

/*bool CustomModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}*/

QModelIndex CustomModel::index(int row, int column, const QModelIndex &parent) const
{
    CustomTreeItem *item = (parent.isValid() ? static_cast<CustomTreeItem *>(parent.internalPointer()) : rootItem)->child(row);

    return item ? createIndex(row, column, item) : QModelIndex();
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

/*bool CustomModel::hasChildren(const QModelIndex &parent) const
{
    // FIXME: Implement me!
}*/

/*bool CustomModel::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}*/

/*void CustomModel::fetchMore(const QModelIndex &parent)
{
    // FIXME: Implement me!
}*/

QVariant CustomModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    return static_cast<CustomTreeItem *>(index.internalPointer())->data(index.column());
}

/*bool CustomModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}*/

Qt::ItemFlags CustomModel::flags(const QModelIndex &index) const
{
    return index.isValid() ? Qt::ItemIsEnabled | Qt::ItemIsSelectable : Qt::ItemIsDropEnabled;
}

/*bool CustomModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}*/

/*bool CustomModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endInsertColumns();
}*/

/*bool CustomModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}*/

/*bool CustomModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endRemoveColumns();
}*/


// Private:
/*QVector<int> CustomModel::childIds(int parentId) const
{
    QVector<int> ret;
    for (int i = 0; i < 10; ++i)
        if (records[i].parentId == parentId)
            ret.push_back(records[i].id);

    return ret;
}*/

/*const Record & CustomModel::recordById(int id) const
{
    for (int i = 0; i < 10; ++i)
        if (records[i].id == id)
            return records[i];
}*/

/*QModelIndex CustomModel::indexById(int id) const
{
    if (id == 0)
        return QModelIndex();

    int parentId = recordById(id).parentId;

    return index(childIds(parentId).indexOf(id), 0, indexById(parentId));
}*/
