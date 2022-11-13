#pragma once

#include "Image.h"

 class StickerSheet
 {

    public:

      // ctors and dtors
      StickerSheet(const Image & picture, unsigned max);
      StickerSheet(const StickerSheet & other);
      ~StickerSheet();

      // Operators
      const StickerSheet & operator=(const StickerSheet & other);
      void clear();
      void copy(const StickerSheet & other);

      // Member functions
      void changeMaxStickers(unsigned max);
      int addSticker(Image & sticker, unsigned x, unsigned y);
      bool translate(unsigned index, unsigned x, unsigned y);
      void removeSticker(unsigned index);
      Image * getSticker(unsigned index) const;
      Image render() const;

    private:

      Image * base;
      Image ** sheet; // the array of images to be the sticker sheet
      unsigned * xVal;
      unsigned * yVal;
      unsigned max;
      unsigned count;

 };
