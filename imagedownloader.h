#ifndef IMAGEDOWNLOADER_H
#define IMAGEDOWNLOADER_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>

#include "iimage.h"

class ImageDownloader : public QObject, IImageFetcher
{
    Q_OBJECT
public:
    explicit ImageDownloader(QObject *parent = nullptr);
    void fetch(QUrl photo_url) override;

signals:
    void image_fetched(ImageFetchResponse response) override;

private slots:
    void request_complete(QNetworkReply *reply);

private:
    QNetworkAccessManager nam_;
};

#endif // IMAGEDOWNLOADER_H
