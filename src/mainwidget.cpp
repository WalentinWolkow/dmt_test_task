#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <custommodel.h>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    , model(new CustomModel(this))
{
    ui->setupUi(this);

    ui->treeView->setModel(model);
}

MainWidget::~MainWidget()
{
    delete ui;
}

