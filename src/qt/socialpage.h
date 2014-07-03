#ifndef SOCIALPAGE_H
#define SOCIALPAGE_H

#include <QDialog>
#include <QtNetwork/QtcpSocket>

namespace Ui {
    class IrcClient;
}

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE


class IrcClient : public QDialog
{
    Q_OBJECT


public slots:
    void done(int retval);

public:
    explicit IrcClient(QWidget *parent = 0);
    ~IrcClient();
    QString qString1;

private:
    Ui::IrcClient *ui;
    QString returnValue;

};

/*
#include <QDialog>
#include <QtNetwork/QtcpSocket>

namespace Ui {
    class IrcClient;
}

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

/ Widget that shows the IRC chat.
  /
class IrcClient : public QDialog
{
    Q_OBJECT

public:
    explicit IrcClient(QWidget *parent = 0);
    ~IrcClient();

    const QString &getReturnValue() const { return returnValue; }

    QString newnick = "quarklearner";

public slots:
    void done(int retval);

private:
    Ui::IrcClient *ui;
    QTcpSocket *socket;
    QString returnValue;
    QAction *deleteAction; // to be able to explicitly disable it

private slots:
    void readData();
    void connectToServer();
    void disconnectFromServer();
    void nicknameChanged(QString nickname);
    void sendChatLine();

signals:

};

*/

#endif // SOCIALPAGE_H
