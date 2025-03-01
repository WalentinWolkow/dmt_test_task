#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <custommodel.h>
#include <customdelegate.h>
#include <customthread.h>
#include <customtreeitem.h>

#include <QStack>

#include <iostream>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    , mModel(new CustomModel(this))
{
    ui->setupUi(this);

    ui->treeView->setModel(mModel);
    ui->treeView->setItemDelegate(new CustomDelegate(this));
    ui->treeView->expandAll();

    new CustomThreadOne(mModel, this);
    new CustomThreadTwo(mModel, this);
}

MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::slotCheckBox(bool val)
{
    QCheckBox *checkBox = static_cast<QCheckBox *>(sender());
    if (checkBox == nullptr)
        return;

    if (checkBox == ui->checkBoxAll)
    {
        if (val)
        {
            ui->checkBoxA->setCheckState(Qt::Checked);
            ui->checkBoxB->setCheckState(Qt::Checked);
            ui->checkBoxC->setCheckState(Qt::Checked);
        }

        return;
    }

    if (checkBox->checkState() == Qt::Unchecked)
        ui->checkBoxAll->setCheckState(Qt::Unchecked);

    bool isHidden[3];
    isHidden[0] = ui->checkBoxA->checkState() == Qt::Unchecked;
    isHidden[1] = ui->checkBoxB->checkState() == Qt::Unchecked;
    isHidden[2] = ui->checkBoxC->checkState() == Qt::Unchecked;

    QStack<QModelIndex> stack;
    for (int row = 0, rowCount = mModel->rowCount(); row < rowCount; ++row)
        stack.push(mModel->index(row, 0));

    for ( ; !stack.isEmpty(); )
    {
        QModelIndex index = stack.pop();

        for (int row = 0, rowCount = mModel->rowCount(index); row < rowCount; ++row)
            stack.push(mModel->index(row, 0, index));

        ui->treeView->setRowHidden(index.row(), index.parent(), isHidden[static_cast<CustomTreeItem *>(index.internalPointer())->type()]);
    }
}

void MainWidget::slotLineEdit(QString str)
{
    std::cout << __PRETTY_FUNCTION__ << "\nEdit string = \'" << str.toStdString() << "\'.\nNot implemented yet!" << std::endl;
}
