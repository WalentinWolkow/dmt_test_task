#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <custommodel.h>
#include <customdelegate.h>
#include <customthread.h>

#include <iostream>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    , model(new CustomModel(this))
{
    ui->setupUi(this);

    ui->treeView->setModel(model);
    ui->treeView->setItemDelegate(new CustomDelegate(this));

    new CustomThreadOne(model, this);
    new CustomThreadTwo(model, this);
}

MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::slotCheckBox(bool val)
{
    QCheckBox *checkBox = static_cast<QCheckBox* >(sender());
    std::cout << __PRETTY_FUNCTION__ << "\nName = \'" << checkBox->objectName().toStdString() << "\'\nValue = " << val << '.' << std::endl;

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

    std::cout << "Not implemented yet!" << std::endl;
}

void MainWidget::slotLineEdit(QString str)
{
    std::cout << __PRETTY_FUNCTION__ << "\nEdit string = \'" << str.toStdString() << "\'.\nNot implemented yet!" << std::endl;
}
