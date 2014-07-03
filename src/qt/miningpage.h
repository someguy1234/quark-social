#ifndef MININGPAGE_H
#define MININGPAGE_H

#include <QDialog>
#include <QSettings>

namespace Ui {
    class MiningPage;
}

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

class MiningPage : public QDialog
{
    Q_OBJECT

public:
    explicit MiningPage(QWidget *parent = 0);
    ~MiningPage();

   // const QString &getReturnValue() const { return returnValue; }

public slots:
    void done(int retval);

private:
    QString returnValue;
    QAction *deleteAction; // to be able to explicitly disable it
    //QString cpuName;
    int coreCount;
    QString miningCores;
    int sliderValue;
    Ui::MiningPage *ui;

private slots:
    void startMining();
    void stopMining();
    //QString ProcNameRead();
    void setAllocatedCores();

signals:

};
#endif // MININGPAGE_H
