#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
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
        readbmp(filename);
    }

    void readbmp(const char *filename)
    {
        std::ifstream input{filename, std::ios_base::binary};
        if(input)
        {   //check if filetype is bmp
            input.readbmp((char*)&fileHeader,sizeof(fileHeader));
            if(fileHeader.fileType!= 0x4D42)
            {
                throw std::runtime_error("Unrecognized file format! Please enter .BMP file.");
            }
            input.readbmp((char*)&infoHeader, sizeof(infoHeader));

            //bmpColorHeader used for transparent image
            if(infoHeader.NumOfBitCount==32)
            {
                //checking for color mask info
                if(infoHeader.headerSize >=(sizeof(bmpInfoHeader)+sizeof(bmpColorHeader)))
                {
                    input.readbmp((char*)&colorHeader, sizeof(colorHeader));
                    //check is pixel data is BGRA and color space type is sRGB
                    checkColorHeader(colorHeader);
                }
                else{
                    str::cerr<< "Error! the file does not contain bitmask information!";
                    throw std::runtime_error("Unrecognized file format!");
                }
            }

            //jump to pixel data location
            input.seekg(fileHeader.offsetData, input.beg);


            //saving header and data
            if(infoHeader.NumOfBitCount==32)
            {
                infoHeader.headerSize= sizeof(bmpInfoHeader)+sizeof(bmpColorHeader);
                fileHeader.offsetData= sizeof(bmpFileHeader) + sizeof(bmpInfoHeader)+sizeof(bmpColorHeader);
            }
            else
            {
                infoHeader.HeaderSize= sizeof(bmpInfoHeader);
                fileHeader.offsetData= sizeof(bmpFileHeader) + sizeof(bmpInfoHeader);
            }
            fileHeader.fileSize=fileHeader.offsetData;

            if(infoHeader.height<0)
            {
                throw std::runtime_error("Error!");
            }

            data.resize(infoHeader.width * infoHeader.height *infoHeader.NumOfBitCount /8);

            //checking row padding
            if(infoHeader.width %4==0)
            {
                input.readbmp((char*)data.data(), data.size());
                fileHeader.fileSize += static_cast<uint32_t>(data.size());
            }
            else
            {
                rowStride= infoHeader.width  *infoHeader.NumOfBitCount /8;
                uint32_t newStride =makeStrideAligned(4);
                std::vector<uint8_t> paddingRow(newStride -rowStride);

                for(int y=0;y< infoHeader.height;++y)
                {
                    input.readbmp((char*)(data.data()+rowStride *y), rowStride);
                    input.readbmp((char*)paddingRow.data(),paddingRow.size());
                }
                fileHeader.fileSize +=static_cast<uint32_t>(data.size())+ infoHeader.height * static_cast<uint32_t>(paddingRow.size());

            }


        }
        else 
        {
            throw std::runtime_error("Unable to open file!");
        }
    }

    bmp(int32_t width, int32_t height, bool has_alpha=true)
    {
        if(width<=0 || height <=0)
        {
            throw std::runtime_error("Image cannot be processed.").
        }
        infoHeader.width=width;
        infoHeader.height=height;
        if(has_alpha)
        {
            infoHeader.size=sizeof(bmpInfoHeader);
            fileHeader,offsetData=sizeof(bmpFileHeader)+sizeof(bmpInfoHeader);

            infoHeader.NumOfBitCount=32;
            infoHeader.compression=3;
            rowStride= width * 4;
            data.resize(rowStride * height);
            fileHeader.fileSize = fileHeader.offsetData +data.size();
        }
        else
        {
            infoHeader.size=sizeof(bmpInfoHeader);
            fileHeader.offsetData= sizeof(bmpFileHEader)+sizeof(bmpInfoHeader);

            inforHeader.NumOfBitCount=24;
            infoHeader.compression=0;
            rowStride=width*3;
            data.resize(rowStride * height);

            uint32_t newStride= makeStrideAligned(4);
            fileHeader.fileSize=fileHeader.offsetData +static_cast<uint32_t>(data.size())+infoHeader.height* (newStride- rowStride);
        }

    }

    void write(const char *filename){
        std::ofstream of{ filename, std::iosBase::binary};
        if (of)
        {
            if (infoHeader.NumOfBitCount==32)
            {
                writeHeadersAndData(of);
            }
            else if(infoHeader.NumOfBitCount==24)
            {
                if(infoHeader.width%4==0)
                {
                    writeHeadersAndData(of);
                }
                else
                {
                    uint32_t newStride= makeStrideAligned(4);
                    std::vector<uint8_t> paddingRow()
                }
            }
        }
    }

    checkColorHeader(colorHeader);
    void writebmp(const char *filename)
    {
        
    }
    
}