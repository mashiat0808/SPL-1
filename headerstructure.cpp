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
    unsigned int redChannelBitmask; //bit mask for red channel
    unsigned int greenChannelBitmask; //bit mask for green channel
    unsigned int blueChannelBitmask;  //bit mask for blue channel
    unsigned int alphaChannelBitmask; //bit mask for alpha channel
    unsigned int colorSpaceType;    //sRGB default
};

struct bmpColorTable
{
    unsigned int colorDefinition[256];
};
