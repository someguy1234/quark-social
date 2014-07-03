#ifndef BACKGROUNDWINDOW_H
#define BACKGROUNDWINDOW_H

#include <QWidget>

namespace Ui {
class BackgroundWindow;
}

class BackgroundWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BackgroundWindow(QWidget *parent = 0);
    ~BackgroundWindow();

private:
    Ui::BackgroundWindow *ui;
};

#endif // BACKGROUNDWINDOW_H
