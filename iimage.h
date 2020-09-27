#ifndef IENTRYLOADER_H
#define IENTRYLOADER_H

#include <QVector>
#include <QUrl>
#include <QImage>

#include <optional>

enum class ImageFetchResponseStatus
{
    Success,
    Error,
};

struct ImageFetchResponse
{
    QUrl url;
    QImage &image;
    ImageFetchResponseStatus status;
};

class IImageFetcher
{
public:
    virtual void fetch(QUrl url) = 0;
    virtual void image_fetched(ImageFetchResponse response) = 0;
};

class IImageStorage : public IImageFetcher
{
public:
    virtual void store(QUrl url, QImage &image) = 0;
};

struct ImageEntry
{
    int id = 0;
    int album_id = 0;
    QUrl url;
    QUrl thumbnail_url;
};

class IEntryLoader
{
public:
    virtual bool load() = 0;
    virtual const QVector<ImageEntry>& all() = 0;
    virtual std::optional<const ImageEntry> view(QUrl url) = 0;
};

#endif // IENTRYLOADER_H
