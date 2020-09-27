#ifndef JSONLOADER_H
#define JSONLOADER_H

#include <QObject>
#include <QDir>

#include "iimage.h"

class JsonLoader
        : public QObject,
        public IEntryLoader
{
    Q_OBJECT
    Q_INTERFACES(IEntryLoader)
public:
    explicit JsonLoader(QDir file_path, QObject *parent = nullptr);
    bool load() override;
    const QVector<ImageEntry>& all() override;
    std::optional<const ImageEntry> view(QUrl url) override;

private:
    QDir file_path_;
    QVector<ImageEntry> list_;

    QJsonDocument readJsonFile();
    void populate();
};

#endif // JSONLOADER_H
