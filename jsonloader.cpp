#include "jsonloader.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

JsonLoader::JsonLoader(QDir file_path, QObject *parent)
    : QObject(parent), file_path_(file_path)
{
}

bool JsonLoader::load()
{
    if (list_.isEmpty())
    {
        populate();
    }
    return !list_.isEmpty(); // If still empty, nothing was loaded
}

const QVector<ImageEntry> &JsonLoader::all()
{
    return list_;
}

std::optional<const ImageEntry> JsonLoader::view(QUrl url)
{
    for (const auto& entry : list_) {
        if (entry.url == url) {
            return {entry};
        }
    }
    return {};
}

void JsonLoader::populate()
{
    auto doc = readJsonFile();
    for (const auto &image_entry : doc.array())
    {
        ImageEntry entry = {
            .id = image_entry.toObject().value("id").toInt(),
            .album_id = image_entry.toObject().value("album_id").toInt(),
            .url = image_entry.toObject().value("url").toString(),
            .thumbnail_url = image_entry.toObject().value("thumbnail_url").toString(),
        };
        list_.append(entry);
    }
}

QJsonDocument JsonLoader::readJsonFile()
{
    QFile file(file_path_.path());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Could not open file with path " << file_path_.path();
    }
    QString json_as_string = file.readAll();
    file.close();
    return QJsonDocument::fromJson(json_as_string.toUtf8());
}


