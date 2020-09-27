#ifndef IMAGESTORAGE_H
#define IMAGESTORAGE_H

#include "iimage.h"

class ImageStorage
        : public IImageStorage
{
    Q_OBJECT
    Q_INTERFACES(IImageStorage)
public:
    explicit ImageStorage();
    void fetch(QUrl url) override;
    void store(QUrl url, QImage &image) override;

signals:
    void image_fetched(ImageFetchResponse response) override;
};

#endif // IMAGESTORAGE_H
