#ifndef DRAWANDCHATCLIENT_H
#define DRAWANDCHATCLIENT_H

#include <QtWebSockets/QWebSocket>
#include "../draw/drawboard.h"

class DrawAndChatClient : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString roomName READ roomName WRITE setRoomName NOTIFY roomNameChanged)

public:
    explicit DrawAndChatClient(QObject *parent = nullptr);
    DrawAndChatClient(const QUrl &inUrl, QObject *parent = nullptr);

    ~DrawAndChatClient();

    const QUrl& url();

    const QString& userName();
    const QString& roomName();

    void setUrl(const QUrl& inUrl);
    void setUserName(const QString& inUserName);
    void setRoomName(const QString& inRoomName);

    Q_INVOKABLE bool isConnected();

private:
    QWebSocket _webSocket;

    QUrl _url;
    QString _userName;
    QString _roomName;

    static QJsonDocument MakeClientJson(const QString &operation, const QJsonObject &arguments);

private slots:
    void onConnected();
    void onDisconnected();

    void onMessageReceived(const QByteArray &message);

signals:
    void connected();
    void disconnected();

    void urlChanged();
    void userNameChanged();
    void roomNameChanged();

    void userLoginRoomResponse(int state, const QString& error);
    void userCreateRoomResponse(int state, const QString& error);
    void userPushPaintResponse(int state, const QString& error, int id);
    void userRemovePaintResponse(int state, const QString& error);
    void userSendMessageResponse(int state, const QString& error);

    void otherLoginRoom(const QString& inUserName);
    void otherPushPaint(int id, DrawBoard::StateType state, const QJsonObject &argList);
    void otherRemovePaint(int id);
    void otherSendMessage(const QString& inUserName, const QString& message);
    void otherLogoutRoom(const QString& inUserName);

public slots:
    void userLoginRoom(const QString& inUserName, const QString& inRoomName, const QString& roomPassword);
    void userCreateRoom(const QString& inUserName, const QString& inRoomName, const QString& roomPassword);
    void userPushPaint(DrawBoard::StateType state, const QJsonObject &argList);
    void userRemovePaint(int id);
    void userSendMessage(const QString& message);
    void userLogoutRoom();

    void otherLoginRoomResponse();
    void otherPushPaintResponse();
    void otherRemovePaintResponse();
    void otherSendMessageResponse();

};

#endif // DRAWANDCHATCLIENT_H
