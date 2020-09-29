#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QObject>
#include <QDir>
#include <QMap>
#include <qqml.h>

#include "iimage.h"

class ImageManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageManager( QObject *parent = nullptr);
    Q_PROPERTY(int image_data_length READ image_data_length NOTIFY image_data_length_changed)

//    void init(IEntryLoader *loader, IImageFetcher *web_download, IImageStorage *file_storage);
    int image_data_length();
    void init();


signals:
    void image_data_length_changed();

private:
    IEntryLoader* loader_;
    IImageFetcher* download_;
    IImageStorage* storage_;
    QMap<ImageEntry, QImage> image_data_;

    void initialize();
    void image_received(ImageFetchResponse response);
};

#endif // IMAGEMANAGER_H
