#include "ircclient.h"
#include "ui_ircclient.h"

#include "bitcoingui.h"
#include "guiutil.h"

#include <QApplication>
#include "../../../../libcommuni-master/examples/client/ircclient.h"

IrcClient::IrcClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IrcClient)
{
    ui->setupUi(this);

    //QApplication app(1,reinterpret_cast<char *>('1'));
    IrcClient client;
    client.resize(800, 480);
    client.show();
    //app.exec();
}


/*
IrcClient::IrcClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IrcClient)

{
    ui->setupUi(this);

    // Create socket
    socket = new QTcpSocket(this);

    // Connect signals and slots!
    connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
    connect(ui->disconnectButton, SIGNAL(clicked()), this, SLOT(disconnectFromServer()));
    connect(ui->nickBox,SIGNAL(textChanged(QString)),this,SLOT(nicknameChanged(QString)));
    connect(ui->chattextBox,SIGNAL(returnPressed()),this,SLOT(sendChatLine()));

}

void IrcClient::sendChatLine() {
    QString chatline = ui->chattextBox->text();
    //QByteArray sendtext1("PRIVMSG #test_room :");
    QByteArray sendtext1("PRIVMSG #quarkuniverse :");
    QByteArray sendtext3(" \r\n");

    socket->write(sendtext1.append(chatline.toLocal8Bit().append(sendtext3)));
    ui->chattextBox->setText("");

    //Does not echo, so do it manually here
    QByteArray youtyped("You typed: ");
    ui->textEdit->append(youtyped.append(chatline.toLocal8Bit().append(sendtext3)));
}

void IrcClient::nicknameChanged(QString nickname) {
    newnick = nickname;
}

void IrcClient::connectToServer() {
    socket->connectToHost(QString("chat.freenode.net"), 6667);
    // USER, NICK, and JOIN commands
    //var nickname = nickBox;

    QByteArray nick1("NICK ");
    QByteArray nick3(" \r\n");

    socket->write(nick1.append(newnick.toLocal8Bit()).append(nick3));
    socket->write("USER quarkuser quarkuser quarkuser :quarkuser quarkuser \r\n");
    socket->write("JOIN #quarkuniverse \r\n");
    //socket->write("JOIN #test_room \r\n");
    // Now we are successfully connected to IRC SERVER...
    ui->connectButton->setEnabled(false);
    ui->disconnectButton->setEnabled(true);
}

void IrcClient::readData() {
    QString readLine = socket->readLine();
    // Something with readLine
    //if(readLine.contains("hello")) {
    //    socket->write("PRIVMSG #test_room :hellow world \r\n");
    //}

    // Add to output
    ui->textEdit->append(readLine);
    // Next data??
    if(socket->canReadLine()) readData();
}

void IrcClient::disconnectFromServer() {
    // Disconnect
    socket->write("QUIT Good bye \r\n");
    socket->flush();
    socket->disconnect();
    ui->connectButton->setEnabled(true);
    ui->disconnectButton->setEnabled(false);
}
*/

IrcClient::~IrcClient()
{
    delete ui;
}

void IrcClient::done(int retval)
{
    if(returnValue.isEmpty())
    {
        // If no address entry selected, return rejected
        retval = Rejected;
    }

    QDialog::done(retval);
}
