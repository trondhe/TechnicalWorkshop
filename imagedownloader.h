#ifndef IMAGEDOWNLOADER_H
#define IMAGEDOWNLOADER_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>

#include "iimage.h"

class ImageDownloader
        :
        public IImageFetcher
{
    Q_OBJECT
    Q_INTERFACES(IImageFetcher)
public:
    explicit ImageDownloader();
    void fetch(QUrl photo_url) override;

signals:
    void image_fetched(ImageFetchResponse response);

private slots:
    void request_complete(QNetworkReply *reply);

private:
    QNetworkAccessManager nam_;
};

#endif // IMAGEDOWNLOADER_H
