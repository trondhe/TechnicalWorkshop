#ifndef IMAGESTORAGE_H
#define IMAGESTORAGE_H

#include "iimage.h"

class ImageStorage : public QObject, IImageStorage
{
    Q_OBJECT
public:
    explicit ImageStorage(QObject *parent = nullptr);
    void fetch(QUrl url) override;
    void store(QUrl url, QImage &image) override;

signals:
    void image_fetched(ImageFetchResponse response) override;
};

#endif // IMAGESTORAGE_H
