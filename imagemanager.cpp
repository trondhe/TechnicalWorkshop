#include "imagemanager.h"

#include <QDebug>

ImageManager::ImageManager(IEntryLoader &loader, IImageFetcher &web_download, IImageStorage &file_storage, QObject *parent)
    : QObject(parent), loader_(loader), download_(web_download), storage_(file_storage)
{
    connect(&this->download_, &IImageFetcher::image_fetched, &this->storage_, &IImageStorage::store);

}

void ImageManager::initialize()
{
    bool hasLoaded = loader_.load();
    if (!hasLoaded) {
        qWarning() << "Could not load entry data\n";
        return;
    }
    int counter = 0; // TODO: Temp while debugging, remove it later
    for (const auto& entry : loader_.all()) {
        // TODO: Skip every in local storage
        download_.fetch(entry.url);
        counter += 1;
        if (counter > 5) {
            break;
        }
    }
}

int ImageManager::image_data_length()
{
    return image_data_.size();
}

void ImageManager::image_fetched(ImageFetchResponse response)
{
    auto maybe_entry = loader_.view(response.url);
    if (!maybe_entry) {
        qWarning() << "Received data for image not in loader, cant happen at the time of writing, major booboo, blame the intern";
        return;
    }
    image_data_.insert(maybe_entry.value(), response.image);
    emit image_data_changed();
    emit image_data_length_changed();
}
