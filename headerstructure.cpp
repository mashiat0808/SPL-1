#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

struct bmpSignature
{
    unsigned char signatureData[2]; //BM is .bmp file
};


struct bmpFileHeader
{
    unsigned int fileSize; //filesize in byte
    unsigned short reserved1; //reserved 
    unsigned short reserved2; //reserved
    unsigned int dataOffset; //start of pixel data
};

struct bmpInfoHeader
{
    unsigned int headerSize; //headersize in byte
    unsigned int width; //image width in px
    unsigned int height; //image height in px
    unsigned short planes;  //number of planes 
    unsigned short bpPixels; //number of bits per pixel
    unsigned int compression; //compression type 0 is uncompressed
    unsigned int imageSize; 
    unsigned int pixelPerMeterX; //pixel per meter along x axis
    unsigned int pixelPerMeterY; //pixel per meter along y axis
    unsigned int colorsInColorTable; //number of colors in color table
    unsigned int importantcolorCount; //number of colors used
};

struct bmpColorHeader{
    unsigned int redChannelBitmask; //red channel bitmask
    unsigned int greenChannelBitmask; //green channel bitmask
    unsigned int blueChannelBitmask; //blue channel bitmask
    unsigned int alphaChannelBitmask; //alpha channel bitmask
    unsigned int colorSpaceType;    //color space type usually sRGB default
};


struct bmpColorTable
{
    unsigned int colorDefinition[256];
};
