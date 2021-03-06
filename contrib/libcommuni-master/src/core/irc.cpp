/*
  Copyright (C) 2008-2014 The Communi Project

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holder nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "irc.h"
#include "irccommand.h"
#include "ircconnection.h"
#include "ircmessage_p.h"
#include <QMetaEnum>
#include <QDebug>

IRC_BEGIN_NAMESPACE

/*!
    \file irc.h
    \brief \#include &lt;Irc&gt;
 */

/*!
    \namespace Irc
    \ingroup core
    \brief Miscellaneous identifiers used throughout the library.
 */

/*!
    Returns the version number of Communi at run-time as a string (for example, "1.2.3").
    This may be a different version than the version the application was compiled against.

    \sa IRC_VERSION, IRC_VERSION_STR
 */
QString Irc::version()
{
    return QLatin1String(IRC_VERSION_STR);
}

/*!
    Returns the numeric \a code as a string or a null string if the code is unknown.

    \sa Irc::Code, IrcNumericMessage::code()
 */
QString Irc::codeToString(int code)
{
    const int index = Irc::staticMetaObject.indexOfEnumerator("Code");
    QMetaEnum enumerator = Irc::staticMetaObject.enumerator(index);
    return QLatin1String(enumerator.valueToKey(code));
}

/*!
    Returns the nick part of the specified \a prefix.

    Nick part of a prefix as specified in RFC 1459:
    <pre>
    <b>&lt;nick&gt;</b> [ '!' &lt;ident&gt; ] [ '@' &lt;host&gt; ]
    </pre>

    \sa IrcMessage::prefix, IrcMessage::nick
 */
QString Irc::nickFromPrefix(const QString& prefix)
{
    QString nick;
    IrcMessagePrivate::parsePrefix(prefix, &nick, 0, 0);
    return nick;
}

/*!
    Returns the ident part of the specified \a prefix.

    Ident part of a prefix as specified in RFC 1459:
    <pre>
    &lt;nick&gt; [ '!' <b>&lt;ident&gt;</b> ] [ '@' &lt;host&gt; ]
    </pre>

    \sa IrcMessage::prefix, IrcMessage::ident
 */
QString Irc::identFromPrefix(const QString& prefix)
{
    QString ident;
    IrcMessagePrivate::parsePrefix(prefix, 0, &ident, 0);
    return ident;
}

/*!
    Returns the host part of the specified \a prefix.

    Host part of a prefix as specified in RFC 1459:
    <pre>
    &lt;nick&gt; [ '!' &lt;ident&gt; ] [ '@' <b>&lt;host&gt;</b> ]
    </pre>

    \sa IrcMessage::prefix, IrcMessage::host
 */
QString Irc::hostFromPrefix(const QString& prefix)
{
    QString host;
    IrcMessagePrivate::parsePrefix(prefix, 0, 0, &host);
    return host;
}

/*!
    Registers IrcCore types to the %Qt meta-system.

    \sa qRegisterMetaType()
 */
void Irc::registerMetaTypes()
{
    qRegisterMetaType<Irc::Color>("Irc::Color");
    qRegisterMetaType<Irc::DataRole>("Irc::DataRole");
    qRegisterMetaType<Irc::SortMethod>("Irc::SortMethod");
    qRegisterMetaType<Irc::Code>("Irc::Code");

    qRegisterMetaType<IrcConnection*>("IrcConnection*");
    qRegisterMetaType<IrcConnection::Status>("IrcConnection::Status");

    qRegisterMetaType<IrcNetwork*>("IrcNetwork*");

    qRegisterMetaType<IrcCommand*>("IrcCommand*");
    qRegisterMetaType<IrcCommand::Type>("IrcCommand::Type");

    qRegisterMetaType<IrcMessage*>("IrcMessage*");
    qRegisterMetaType<IrcMessage::Type>("IrcMessage::Type");

    qRegisterMetaType<IrcCapabilityMessage*>("IrcCapabilityMessage*");
    qRegisterMetaType<IrcErrorMessage*>("IrcErrorMessage*");
    qRegisterMetaType<IrcInviteMessage*>("IrcInviteMessage*");
    qRegisterMetaType<IrcJoinMessage*>("IrcJoinMessage*");
    qRegisterMetaType<IrcKickMessage*>("IrcKickMessage*");
    qRegisterMetaType<IrcModeMessage*>("IrcModeMessage*");
    qRegisterMetaType<IrcNamesMessage*>("IrcNamesMessage*");
    qRegisterMetaType<IrcNickMessage*>("IrcNickMessage*");
    qRegisterMetaType<IrcNoticeMessage*>("IrcNoticeMessage*");
    qRegisterMetaType<IrcNumericMessage*>("IrcNumericMessage*");
    qRegisterMetaType<IrcMotdMessage*>("IrcMotdMessage*");
    qRegisterMetaType<IrcPartMessage*>("IrcPartMessage*");
    qRegisterMetaType<IrcPingMessage*>("IrcPingMessage*");
    qRegisterMetaType<IrcPongMessage*>("IrcPongMessage*");
    qRegisterMetaType<IrcPrivateMessage*>("IrcPrivateMessage*");
    qRegisterMetaType<IrcQuitMessage*>("IrcQuitMessage*");
    qRegisterMetaType<IrcTopicMessage*>("IrcTopicMessage*");
    qRegisterMetaType<IrcWhoReplyMessage*>("IrcWhoReplyMessage*");

}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug debug, Irc::Code code)
{
    const int index = Irc::staticMetaObject.indexOfEnumerator("Code");
    QMetaEnum enumerator = Irc::staticMetaObject.enumerator(index);
    const char* key = enumerator.valueToKey(code);
    debug << (key ? key : "Unknown");
    return debug;
}

QDebug operator<<(QDebug debug, Irc::DataRole role)
{
    const int index = Irc::staticMetaObject.indexOfEnumerator("DataRole");
    QMetaEnum enumerator = Irc::staticMetaObject.enumerator(index);
    const char* key = enumerator.valueToKey(role);
    debug << (key ? key : "Unknown");
    return debug;
}

QDebug operator<<(QDebug debug, Irc::Color color)
{
    const int index = Irc::staticMetaObject.indexOfEnumerator("Color");
    QMetaEnum enumerator = Irc::staticMetaObject.enumerator(index);
    const char* key = enumerator.valueToKey(color);
    debug << (key ? key : "Unknown");
    return debug;
}

QDebug operator<<(QDebug debug, Irc::SortMethod method)
{
    const int index = Irc::staticMetaObject.indexOfEnumerator("SortMethod");
    QMetaEnum enumerator = Irc::staticMetaObject.enumerator(index);
    const char* key = enumerator.valueToKey(method);
    debug << (key ? key : "Unknown");
    return debug;
}
#endif // QT_NO_DEBUG_STREAM

#include "moc_irc.cpp"

IRC_END_NAMESPACE
