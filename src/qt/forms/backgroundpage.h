#ifndef BACKGROUNDPAGE_H
#define BACKGROUNDPAGE_H

#include <QMainWindow>

namespace Ui {
class backgroundpage;
}

class backgroundpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit backgroundpage(QWidget *parent = 0);
    ~backgroundpage();

private:
    Ui::backgroundpage *ui;
};

#endif // BACKGROUNDPAGE_H
