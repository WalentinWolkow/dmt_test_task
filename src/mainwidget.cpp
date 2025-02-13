#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <custommodel.h>
#include <customdelegate.h>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    , model(new CustomModel(this))
{
    ui->setupUi(this);

    ui->treeView->setModel(model);
    ui->treeView->setItemDelegate(new CustomDelegate(this));
}

MainWidget::~MainWidget()
{
    delete ui;
}

