#ifndef IENTRYLOADER_H
#define IENTRYLOADER_H

#include <QVector>
#include <QUrl>
#include <QImage>
#include <QtPlugin>

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


class IImageFetcher : public QObject
{
    Q_OBJECT
public:
    virtual void fetch(QUrl url) = 0;
    virtual void image_fetched(ImageFetchResponse response) = 0;
};
#define IImageFetcher_iid "TW.IImageFetcher/1.0"
Q_DECLARE_INTERFACE(IImageFetcher, IImageFetcher_iid)


class IImageStorage : public IImageFetcher
{
public:
    virtual void store(QUrl url, QImage &image) = 0;
};
#define IImageStorage_iid "TW.IImageFetcher/1.0"
Q_DECLARE_INTERFACE(IImageStorage, IImageStorage_iid)


struct ImageEntry
{
    int id = 0;
    int album_id = 0;
    QUrl url;
    QUrl thumbnail_url;

    bool operator<(const ImageEntry& rhs) const;
};

class IEntryLoader
{
public:
    virtual bool load() = 0;
    virtual const QVector<ImageEntry>& all() = 0;
    virtual std::optional<const ImageEntry> view(QUrl url) = 0;
};
#define IEntryLoader_iid "TW.IImageFetcher/1.0"
Q_DECLARE_INTERFACE(IEntryLoader, IEntryLoader_iid)


#endif // IENTRYLOADER_H
