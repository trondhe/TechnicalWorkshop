#include "iimage.h"

bool ImageEntry::operator<(const ImageEntry& rhs) const {
    return id < rhs.id;
}
