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
    Q_PROPERTY(int image_data_length READ image_data_length NOTIFY image_data_length_changed)
    QML_ELEMENT

public:
    explicit ImageManager(IEntryLoader &loader, IImageFetcher &web_download, IImageStorage &file_storage, QObject *parent = nullptr);

    void initialize();
    int image_data_length();


signals:
    void image_data_changed();
    void image_data_length_changed();

private slots:
    void image_fetched(ImageFetchResponse response);

private:
    IEntryLoader &loader_;
    IImageFetcher &download_;
    IImageStorage &storage_;

    QMap<ImageEntry, QImage> image_data_;
};

#endif // IMAGEMANAGER_H
