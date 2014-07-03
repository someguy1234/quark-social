#include "backgroundwindow.h"
#include "ui_backgroundwindow.h"

backgroundwindow::backgroundwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::backgroundwindow)
{
    ui->setupUi(this);
}

backgroundwindow::~backgroundwindow()
{
    delete ui;
}
