#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H

#include <QAbstractItemModel>

#define LAYER_A_MAX_CHILDS_COUNT    3
#define LAYER_B_MAX_CHILDS_COUNT    5
#define LAYER_C_MAX_CHILDS_COUNT    0
#define ROOT_MAX_CHILDS_COUNT       INT_MAX

class CustomTreeItem;

class CustomModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit CustomModel(QObject *parent = nullptr);
    ~CustomModel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const final;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) final;

    // Basic functionality:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const final;
    QModelIndex parent(const QModelIndex &index) const final;

    int rowCount(const QModelIndex &parent = QModelIndex()) const final;
    int columnCount(const QModelIndex &parent = QModelIndex()) const final;

    bool hasChildren(const QModelIndex &parent = QModelIndex()) const final;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const final;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) final;

    Qt::ItemFlags flags(const QModelIndex& index) const final;

    // Add data:
    bool canInsertRows(const QModelIndex &parent = QModelIndex()) const;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) final;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) final;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) final;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) final;

private:
    CustomTreeItem *rootItem;

    static const int maxChildsCount[];
};

#endif // CUSTOMMODEL_H
