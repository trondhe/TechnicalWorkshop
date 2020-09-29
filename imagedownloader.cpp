#include "imagedownloader.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QImage>

ImageDownloader::ImageDownloader()
{
    connect(&this->nam_, &QNetworkAccessManager::finished, this, &ImageDownloader::request_complete);
}

void ImageDownloader::fetch(QUrl photo_url)
{
    QNetworkRequest request(photo_url);
    nam_.get(request);
}

void ImageDownloader::request_complete(QNetworkReply *reply)
{
    QImage image;
    QUrl url = reply->url();
    if (reply->error() != QNetworkReply::NoError) {
        ImageFetchResponse resp = {
            .url = url,
            .image = image,
            .status = ImageFetchResponseStatus::Error,
        };
        image_fetched(resp);
        return;
    }
    image.loadFromData(reply->readAll());
    ImageFetchResponse resp = {
        .url = url,
        .image = image,
        .status = ImageFetchResponseStatus::Success,
    };
    emit IImageFetcher::image_fetched(resp);
}
