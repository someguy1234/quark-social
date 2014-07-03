#include "backgroundpage.h"
#include "ui_backgroundpage.h"

backgroundpage::backgroundpage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::backgroundpage)
{
    ui->setupUi(this);
}

backgroundpage::~backgroundpage()
{
    delete ui;
}
