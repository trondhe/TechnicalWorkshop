#include "imagemanager.h"

#include <QDebug>

#include "jsonloader.h"
#include "imagedownloader.h"
#include "imagestorage.h"

const QString projectPath = PROJECT_PATH;
const QString filePath = projectPath + "/photos.json";


ImageManager::ImageManager(QObject *parent)
    : QObject(parent)
{
    qWarning() << "IM constructor called\n";
    init();
}

void ImageManager::init()
{
    QDir photos(filePath);
    loader_ = new JsonLoader(photos);
    download_ = new ImageDownloader;
    storage_ = new ImageStorage;

    // Save to local storage
    connect(this->download_, &IImageFetcher::image_fetched, [this](ImageFetchResponse response) {
        storage_->store(response.url, response.image);
    });

    // Save in memory data
    connect(this->download_, &IImageFetcher::image_fetched, [this](ImageFetchResponse response) {
        image_received(response);
    });

    initialize();
}

void ImageManager::initialize()
{
    bool hasLoaded = loader_->load();
    if (!hasLoaded) {
        qWarning() << "Could not load entry data\n";
        return;
    }
    for (const auto& entry : loader_->all()) {
        // TODO: Skip every in local storage
        download_->fetch(entry.url);
    }
}

int ImageManager::image_data_length()
{
    return image_data_.size();
}

void ImageManager::image_received(ImageFetchResponse response)
{
    if (ImageFetchResponseStatus::Error == response.status) {
        qWarning() << "Image response with error\n";
        return;
    }
    auto entry = loader_->view(response.url);
    if (!entry) {
        qWarning() << "Response url not in json entry list, should not happen, fire the intern\n";
        return;
    }
    image_data_.insert(entry.value(), response.image);
    emit image_data_length_changed();
}
