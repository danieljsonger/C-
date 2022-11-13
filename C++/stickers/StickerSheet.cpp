#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image & picture, unsigned max)
    : max(max),
      count(0)
{
    sheet = new Image*[max];
    xVal = new unsigned[max];
    yVal = new unsigned[max];
    base = new Image(picture);

}

StickerSheet::StickerSheet(const StickerSheet & other)
{
    this->copy(other);
}

StickerSheet::~StickerSheet()
{
    clear();
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other)
{
    clear();
    copy(other);

    return *this;
}

void StickerSheet::clear() 
{
    delete base;
    delete [] xVal;
    delete [] yVal;

    for (unsigned i = 0; i < max; i++){
        sheet[i] = NULL;
    }
    delete [] sheet;
}

void StickerSheet::copy(const StickerSheet & other){
    max = other.max;
    base = new Image(*other.base);
    count = other.count;

    sheet = new Image*[other.max];
    xVal = new unsigned[other.max];
    yVal = new unsigned[other.max];

    for (unsigned i = 0; i < max; i++){
        sheet[i] = new Image(*other.sheet[i]);
        xVal[i] = other.xVal[i];
        yVal[i] = other.yVal[i];
    std::cout << "here" << std::endl;
    }

}

void StickerSheet::changeMaxStickers(unsigned nMax)
{

    if (max == nMax) return;

    StickerSheet temp(*base, nMax);

    unsigned useThis = 0;
    if (nMax <= max){
        useThis = nMax;
    } else {
        useThis = max;
    }

    if (nMax < count){
        count = nMax;
    }

    for (unsigned i = 0; i < useThis; i++)
    {

        temp.sheet[i] = this->sheet[i];
        temp.xVal[i] = this->xVal[i];
        temp.yVal[i] = this->yVal[i];
    }

    clear();
    copy(temp);
    std::cout << "here" << std::endl;
    
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y)
{
    if (count < this->max){
        this->sheet[count] = & sticker;
        translate(count,x,y);
        count++;
    } else {
        return -1;
    }
    return count-1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y)
{
    if ((index < count) || (index < 0)){
        xVal[index] = x;
        yVal[index] = y;
        return true;
    } else {
        return false;
    }
}

void StickerSheet::removeSticker(unsigned index)
{
    if(index < count){
        for (unsigned i = index; i < count-1; i++){
            *this->sheet[i] = *this->sheet[i+1];
            xVal[i] = xVal[i+1];
            yVal[i] = yVal[i+1];
        }
        delete sheet[count];
        count--;
        this->sheet[count] = NULL;
    }
}

Image * StickerSheet::getSticker(unsigned index) const
{
    if(index < count){ return *& this->sheet[index]; }
    return NULL;
}

Image StickerSheet::render() const
{
    unsigned maxX = 0;
    unsigned maxY = 0;
    for(unsigned i = 0; i < count; i++){
        if(xVal[i]+sheet[i]->width() > maxX) {maxX = xVal[i]+sheet[i]->width();}
        if(yVal[i]+sheet[i]->height() > maxY) {maxY = yVal[i]+sheet[i]->height();}

    }

    if (base->width() > maxX){
        maxX = base->width();
    }
    if (base->height() > maxY){
        maxY = base->height();
    }


    Image finalImage;
    finalImage.resize(maxX,maxY);

    for (unsigned i = 0; i < base->width(); i++){
        for (unsigned j = 0; j < base->height(); j++){

            HSLAPixel & basePix = finalImage.getPixel(i,j);
            HSLAPixel & newPix = base->getPixel(i,j);

            basePix = newPix;

        }
    }

    for(unsigned index = 0; index < count; index++){

        if(sheet[index]->height() == 0){continue;}

        for(unsigned i = 0; i < sheet[index]->width(); i++){
            for(unsigned j = 0; j < sheet[index]->height(); j++){
                HSLAPixel & pix = finalImage.getPixel(20+i,200+j);
                HSLAPixel & writePix = sheet[index]->getPixel(i,j);
                if (writePix.a != 0){
                    pix = writePix;
                }

            }
        }

    }

    return finalImage;
}
