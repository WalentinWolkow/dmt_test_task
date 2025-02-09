#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <custommodel.h>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    ui->treeView->setModel(new CustomModel(this));
}

MainWidget::~MainWidget()
{
    delete ui;
}

