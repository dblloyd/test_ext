#include "pxt.h"

namespace test_ext {

/**
 * the func
 */
//%
int _thefunc()
{
    return 43;
}

static void setCore(Image_ img, int x, int y, int c) {
    auto ptr = img->pix(x, y);
    if (img->bpp() == 4) {
        if (y & 1)
            *ptr = (*ptr & 0x0f) | (c << 4);
        else
            *ptr = (*ptr & 0xf0) | (c & 0xf);
    } else if (img->bpp() == 1) {
        uint8_t mask = 0x01 << (y & 7);
        if (c)
            *ptr |= mask;
        else
            *ptr &= ~mask;
    }
}

static int getCore(Image_ img, int x, int y) {
    auto ptr = img->pix(x, y);
    if (img->bpp() == 4) {
        if (y & 1)
            return *ptr >> 4;
        else
            return *ptr & 0x0f;
    } else if (img->bpp() == 1) {
        uint8_t mask = 0x01 << (y & 7);
        return (*ptr & mask) ? 1 : 0;
    }
    return 0;
}

/**
 * Returns a transposed image (with X/Y swapped)
 */
//%
Image_ _transposed(Image_ img) {
    Image_ r = mkImage(img->height(), img->width(), img->bpp());

    // this is quite slow
    for (int i = 0; i < img->width(); ++i) {
        for (int j = 0; j < img->height(); ++j) {
            setCore(r, j, i, getCore(img, i, j));
        }
    }

    return r;
}
 

} // namespace test_ext