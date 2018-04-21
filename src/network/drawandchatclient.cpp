#include "drawandchatclient.h"
#include "networkinfo.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include <functional>

DrawAndChatClient::DrawAndChatClient(QObject *parent):
    QObject(parent)
{
    connect(&_webSocket, &QWebSocket::connected, this, &DrawAndChatClient::onConnected);
    connect(&_webSocket, &QWebSocket::disconnected, this, &DrawAndChatClient::onDisconnected);
}

DrawAndChatClient::DrawAndChatClient(const QUrl &inUrl, QObject *parent) :
    DrawAndChatClient(parent)
{
    _url = inUrl;
    _webSocket.open(_url);
}

DrawAndChatClient::~DrawAndChatClient()
{
    _webSocket.close();
}

const QUrl &DrawAndChatClient::url()
{
    return _url;
}

const QString &DrawAndChatClient::userName()
{
    return _userName;
}

const QString &DrawAndChatClient::roomName()
{
    return _roomName;
}

void DrawAndChatClient::setUrl(const QUrl &inUrl)
{
    _url = inUrl;

    _webSocket.open(_url);
    urlChanged();
}

void DrawAndChatClient::setUserName(const QString &inUserName)
{
    _userName = inUserName;
    userNameChanged();
}

void DrawAndChatClient::setRoomName(const QString &inRoomName)
{
    _roomName = inRoomName;
    roomNameChanged();
}

bool DrawAndChatClient::isConnected()
{
    return _webSocket.state() == QAbstractSocket::ConnectedState;
}

QJsonDocument DrawAndChatClient::MakeClientJson(const QString& operation, const QJsonObject& arguments)
{
    return QJsonDocument
    {
        QJsonObject
        {
            { "name", NetworkInfo::ClientName },
            { "version",  NetworkInfo::ClientVersion },
            { "operation", operation },
            { "arguments", arguments }
        }
    };
}

void DrawAndChatClient::onConnected()
{
    connect(&_webSocket, &QWebSocket::binaryMessageReceived, this, &DrawAndChatClient::onMessageReceived);
    connected();
}

void DrawAndChatClient::onDisconnected()
{
    disconnected();
}

void DrawAndChatClient::onMessageReceived(const QByteArray &message)
{
    QJsonParseError error;
    QJsonDocument json = QJsonDocument::fromJson(message, &error);

    if(error.error == QJsonParseError::NoError)
    {
        if(json["name"] == NetworkInfo::ServerName && json["version"] == NetworkInfo::ServerVersion)
        {
            static QMap<QString, std::function<void(const QJsonObject&)>> operationFunctions{
                {"userLoginRoomResponse", [this](const QJsonObject& arg){
                    userLoginRoomResponse(arg["state"].toInt());
                }},
                {"userCreateRoomResponse", [this](const QJsonObject& arg){
                    userCreateRoomResponse(arg["state"].toInt());
                }},
                {"userPushPaintResponse", [this](const QJsonObject& arg){
                    userPushPaintResponse(arg["state"].toInt(), arg["id"].toInt());
                }},
                {"userRemovePaintResponse", [this](const QJsonObject& arg){
                    userRemovePaintResponse(arg["state"].toInt());
                }},
                {"userSendMessageResponse", [this](const QJsonObject& arg){
                    userSendMessageResponse(arg["state"].toInt());
                }},
                {"otherLoginRoom", [this](const QJsonObject& arg){
                    otherLoginRoom(arg["userName"].toString());
                }},
                {"otherPushPaint", [this](const QJsonObject& arg){
                    otherPushPaint(arg["id"].toInt(), (DrawBoard::StateType)arg["paintState"].toInt(), arg["paintArguments"].toObject());
                }},
                {"otherRemovePaint", [this](const QJsonObject& arg){
                    otherRemovePaint(arg["id"].toInt());
                }},
                {"otherSendMessage", [this](const QJsonObject& arg){
                    otherSendMessage(arg["userName"].toString(), arg["message"].toString());
                }},
                {"otherLogoutRoom", [this](const QJsonObject& arg){
                    otherLogoutRoom(arg["userName"].toString());
                }}
            };

            auto found = operationFunctions.find(json["operation"].toString());
            if(found != operationFunctions.cend())
            {
                (*found)(json["arguments"].toObject());
            }
        }
    }
}

void DrawAndChatClient::userLoginRoom(const QString &inUserName, const QString &inRoomName, const QString &roomPassword)
{
    setUserName(inUserName);
    setRoomName(inRoomName);

    QJsonDocument json = MakeClientJson("userLoginRoom",QJsonObject{
                                            {"userName", inUserName},
                                            {"roomName", inRoomName},
                                            {"roomPassword", roomPassword}
                                        });

    _webSocket.sendBinaryMessage(json.toJson());
}

void DrawAndChatClient::userCreateRoom(const QString &inUserName, const QString &inRoomName, const QString &roomPassword)
{
    setUserName(inUserName);
    setRoomName(inRoomName);

    QJsonDocument json = MakeClientJson("userCreateRoom",QJsonObject{
                                            {"userName", inUserName},
                                            {"roomName", inRoomName},
                                            {"roomPassword", roomPassword}
                                        });

    _webSocket.sendBinaryMessage(json.toJson());
}

void DrawAndChatClient::userPushPaint(DrawBoard::StateType state, const QJsonObject &argList)
{
    QJsonDocument json = MakeClientJson("userPushPaint",QJsonObject{
                                            {"paintState", (int)state},
                                            {"paintArguments", argList}
                                        });

    _webSocket.sendBinaryMessage(json.toJson());
}

void DrawAndChatClient::userRemovePaint(int id)
{
    QJsonDocument json = MakeClientJson("userRemovePaint",QJsonObject{
                                            {"paintId", id}
                                        });

    _webSocket.sendBinaryMessage(json.toJson());
}

void DrawAndChatClient::userSendMessage(const QString &message)
{
    QJsonDocument json = MakeClientJson("userSendMessage",QJsonObject{
                                            {"message", message}
                                        });

    _webSocket.sendBinaryMessage(json.toJson());
}

void DrawAndChatClient::userLogoutRoom()
{
    QJsonDocument json = MakeClientJson("userLogoutRoom",QJsonObject{});

    _webSocket.sendBinaryMessage(json.toJson());
}

void DrawAndChatClient::otherLoginRoomResponse()
{

}

void DrawAndChatClient::otherPushPaintResponse()
{

}

void DrawAndChatClient::otherRemovePaintResponse()
{

}

void DrawAndChatClient::otherSendMessageResponse()
{

}
