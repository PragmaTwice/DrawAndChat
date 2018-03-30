#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuickControls2>

#include "draw/drawboard.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Material");

    qmlRegisterType<DrawBoard>("component.interface", 1, 0, "DrawBoard");

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
