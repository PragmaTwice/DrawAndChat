#ifndef DRAWANDCHATCLIENT_H
#define DRAWANDCHATCLIENT_H

#include <QtWebSockets/QWebSocket>
#include "../draw/drawboard.h"

class DrawAndChatClient : public QObject
{
    Q_OBJECT

    Q_PROPERTY(const QUrl url READ url)
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString roomName READ roomName WRITE setRoomName NOTIFY roomNameChanged)

public:
    explicit DrawAndChatClient(const QUrl &inUrl, QObject *parent = nullptr);

    const QUrl& url();

    const QString& userName();
    const QString& roomName();

    void setUserName(const QString& inUserName);
    void setRoomName(const QString& inRoomName);

    bool isConnected();

private:
    QWebSocket _webSocket;

    const QUrl _url;
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

    void userNameChanged();
    void roomNameChanged();

    void userLoginRoomResponse(int state);
    void userCreateRoomResponse(int state);
    void userPushPaintResponse(int state, int id);
    void userRemovePaintResponse(int state);
    void userSendMessageResponse(int state);

    void otherLoginRoom(const QString& inUserName);
    void otherPushPaint(int id, DrawBoard::StateType state, const QJsonObject &argList);
    void otherRemovePaint(int id);
    void otherSendMessage(const QString& inUserName, const QString& message);
    void otherLogoutRoom(const QString& inUserName);

    void requestErrorMessageResponse(const QString& errorString);

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

    void requestErrorMessage(int errorState);

};

#endif // DRAWANDCHATCLIENT_H