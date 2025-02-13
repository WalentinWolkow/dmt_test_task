#include "customdelegate.h"

#include <QSpinBox>
#include <QComboBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QLineEdit>

#include <customtreeitem.h>

CustomDelegate::CustomDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget * CustomDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &index) const
{
    int column = index.column();
    CustomTreeItem::ItemType itemType;
    {
        CustomTreeItem *treeItem = static_cast<CustomTreeItem *>(index.internalPointer());
        if (column >= treeItem->columnCount())
            return nullptr;

        itemType = treeItem->type();
    }

    if (itemType == CustomTreeItem::TYPE_A && column == 1)
    {
        QSpinBox *sb = new QSpinBox(parent);
        sb->setMaximum(9999);

        return static_cast<QWidget *>(sb);
    }

    if (itemType == CustomTreeItem::TYPE_B)
    {
        if (column == 0)
        {
            QComboBox *cb = new QComboBox(parent);
            for (size_t i = 0; i < sizeof(titlesOfTypeB) / sizeof(titlesOfTypeB[0]); ++i)
                cb->addItem(titlesOfTypeB[i]);

            cb->setCurrentText(index.data().toString());

            return static_cast<QWidget *>(cb);
        }

        if (column == 1)
        {
            QDateEdit *de = new QDateEdit(parent);
            de->setCalendarPopup(true);
            de->setDisplayFormat(QStringLiteral("dd.MM.yyyy"));

            return static_cast<QWidget *>(de);
        }

        QTimeEdit *te = new QTimeEdit(parent);
        te->setDisplayFormat(QStringLiteral("hh:mm:ss"));

        return static_cast<QWidget *>(te);
    }

    if (itemType == CustomTreeItem::TYPE_C)
    {
        QSpinBox *sb = new QSpinBox(parent);
        sb->setMaximum(99999999);

        return static_cast<QWidget *>(sb);
    }

    return static_cast<QWidget *>(new QLineEdit(parent));
}

void CustomDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int column = index.column();
    CustomTreeItem::ItemType itemType;
    {
        CustomTreeItem *treeItem = static_cast<CustomTreeItem *>(index.internalPointer());
        if (column >= treeItem->columnCount())
            return;

        itemType = treeItem->type();
    }

    int dataInt;
    QString dataStr;
    {
        QVariant data = index.data();
        dataInt = data.toInt();
        dataStr = data.toString();
    }

    if (itemType == CustomTreeItem::TYPE_A && column == 1)
    {
        static_cast<QSpinBox *>(editor)->setValue(dataInt);
        return;
    }

    if (itemType == CustomTreeItem::TYPE_B)
    {
        if (column == 0)
        {
            static_cast<QComboBox *>(editor)->setCurrentText(dataStr);
            return;
        }

        if (column == 1)
            static_cast<QDateEdit *>(editor)->setDate(QDate::fromString(dataStr, QStringLiteral("dd.MM.yyyy")));
        else
            static_cast<QTimeEdit *>(editor)->setTime(QTime::fromString(dataStr, QStringLiteral("hh:mm:ss")));

        return;
    }

    if (itemType == CustomTreeItem::TYPE_C)
    {
        static_cast<QSpinBox *>(editor)->setValue(dataInt);
        return;
    }

    static_cast<QLineEdit *>(editor)->setText(dataStr);
}

void CustomDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (static_cast<CustomTreeItem *>(index.internalPointer())->type() != CustomTreeItem::TYPE_C)
        return QStyledItemDelegate::setModelData(editor, model, index);

    model->setData(index, QVariant(static_cast<QSpinBox *>(editor)->value()));
}

void CustomDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const
{
    if (editor != nullptr)
        editor->setGeometry(option.rect);
}
