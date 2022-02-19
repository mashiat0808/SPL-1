#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct bmpFileHeader{
    uint16_t fileType{0x4D42}; //bmpfiletype is 0x4D42
    uint32_t fileSize{0};       // size of file in byte
    uint16_t reserved1{0};      //reserved
    uint16_t reserved2{0};      //reserved
    uint32_t offsetData{0};     //pixel data start
};

struct bmpInfoHeader{
    uint32_t headerSize{0};           //header size in byte
    int32_t width{0};           //width of image in px
    int 32_t height{0};         //height of image in px (if positive, bottom up, else, top down)

    uint_t numOfPlanes{1};         //number of planes in the target device (?)
    uint16_t NumOfBitCount{0};          //bits per pixel
    uint32_t compression{0};        //0 uncompressed, 3 compressed
    uint32_t sizeImage{0};
    int32_t xPxPMeter{0};
    int32_t yPxPMeter{0};
    uint32_t colors{0};             //number of color indexes
    uint32_t colorsImportant{0};    //number of color used

};


struct bmpColorHeader{
    uint32_t redMask{0x00ff0000};           //red channel bitmask
    uint32_t greenMask{0x00ff0000};         //green channel bitmask
    uint32_t blueMask{0x00ff0000};          //blue channel bitmask
    uint32_t alphaMask{0x00ff0000};         //alpha channel bitmask
    uint32_t colorSpaceType{0x73524742};    //sRGB default
    uint32_t unused[16]{0};                 //unused data for sRGB
}

struct bmp{
    bmpFileHeader fileHeader;
    bmpInfoHeader infoHeader;
    bmpColorHeader colorHeader;
    std:: vector<uint8_t> data;


    bmp(const char *filename){
        read(filename);
    }

    void readbmp(const char *filename)
    {

    }
    bmp(int32_t width, int32_t height, bool has_alpha=true)
    {

    }

    void writebmp(const char *filename)
    {
        
    }
}