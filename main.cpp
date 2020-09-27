#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "jsonloader.h"

const QString projectPath = PROJECT_PATH;
const QString filePath = projectPath + "/photos.json";

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    QDir photos(filePath);
    JsonLoader loader(photos);

    return app.exec();
}
