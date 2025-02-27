#include "custommodel.h"

#include <customtreeitem.h>

CustomModel::CustomModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    {
        QList<QVariant> rootData;
        rootData << "One" << "Two" << "Three" << "Four";
        rootItem = new CustomTreeItem(rootData);
    }

    {
        TypeA structA;
        structA.name = "A1";
        structA.data = 1234;

        CustomTreeItem *itemA = new CustomTreeItem(structA, rootItem);
        rootItem->appendChild(itemA);

        {
            QDateTime dt = QDateTime::currentDateTime();

            TypeB structB;
            structB.title = TitleB_1;
            structB.date = dt.date();
            structB.timeBegin = dt.time();
            structB.timeEnd = dt.addSecs(30 * 60).time();

            CustomTreeItem *itemB = new CustomTreeItem(structB, itemA);
            itemA->appendChild(itemB);

            {
                TypeC structC;
                structC.XCoord = 12345678;
                structC.YCoord = 87654321;

                itemB->appendChild(new CustomTreeItem(structC, itemB));
            }

            {
                TypeC structC;
                structC.XCoord = 56781234;
                structC.YCoord = 43218765;

                itemB->appendChild(new CustomTreeItem(structC, itemB));
            }

            {
                TypeC structC;
                structC.XCoord = 12783456;
                structC.YCoord = 65438721;

                itemB->appendChild(new CustomTreeItem(structC, itemB));
            }
        }

        {
            QDateTime dt = QDateTime::currentDateTime();

            TypeB structB;
            structB.title = TitleB_2;
            structB.date = dt.date();
            structB.timeBegin = dt.time();
            structB.timeEnd = dt.addSecs(180 * 60).time();

            CustomTreeItem *itemB = new CustomTreeItem(structB, itemA);
            itemA->appendChild(itemB);

            {
                TypeC structC;
                structC.XCoord = 12345678;
                structC.YCoord = 87654321;

                itemB->appendChild(new CustomTreeItem(structC, itemB));
            }

            {
                TypeC structC;
                structC.XCoord = 56781234;
                structC.YCoord = 43218765;

                itemB->appendChild(new CustomTreeItem(structC, itemB));
            }

            {
                TypeC structC;
                structC.XCoord = 12783456;
                structC.YCoord = 65438721;

                itemB->appendChild(new CustomTreeItem(structC, itemB));
            }
        }
    }

    {
        TypeA structA;
        structA.name = "A2";
        structA.data = 8765;

        CustomTreeItem *itemA = new CustomTreeItem(structA, rootItem);
        rootItem->appendChild(itemA);

        {
            QDateTime dt = QDateTime::currentDateTime();

            TypeB structB;
            structB.title = TitleB_3;
            structB.date = dt.date();
            structB.timeBegin = dt.time();
            structB.timeEnd = dt.addSecs(60 * 60).time();

            CustomTreeItem *itemB = new CustomTreeItem(structB, itemA);
            itemA->appendChild(itemB);
        }

        {
            QDateTime dt = QDateTime::currentDateTime();

            TypeB structB;
            structB.title = TitleB_4;
            structB.date = dt.date();
            structB.timeBegin = dt.time();
            structB.timeEnd = dt.addSecs(240 * 60).time();

            CustomTreeItem *itemB = new CustomTreeItem(structB, itemA);
            itemA->appendChild(itemB);
        }
    }
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
