#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "jsonloader.h"
#include "imagedownloader.h"
#include "imagestorage.h"
#include "imagemanager.h"

const QString projectPath = PROJECT_PATH;
const QString filePath = projectPath + "/photos.json";

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    qmlRegisterType<ImageManager>("tw.ImageManager",1,0,"ImageManagerQML");

    QDir photos(filePath);
    JsonLoader loader(photos);
    ImageDownloader downloader;
    ImageStorage storage;

    ImageManager manager(loader, downloader, storage);

    return app.exec();
}
