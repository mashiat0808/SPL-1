#include <fstream>
#include <iomanip>
#include <cmath>
#include "header.h"
using namespace std;


void greyscale(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader)
{
     ifstream inputFile;
     ofstream outputFile;

    inputFile.open("x.bmp",ios:: binary);
    outputFile.open("greyscale.bmp", ios :: binary);
    
    
    if(inputFile.eof()) throw runtime_error("File not found");
    inputFile.seekg(0,ios::beg);
    outputFile.seekp(0,ios::beg);

    inputFile.read((char*)&signature,sizeof(signature));
    inputFile.read((char*)&fileHeader,sizeof(fileHeader));
    inputFile.read((char*)&infoHeader,sizeof(infoHeader));
    inputFile.read((char*)&colorHeader,sizeof(colorHeader));


    outputFile.write((char*)&signature,sizeof(signature));
    outputFile.write((char*)&fileHeader,sizeof(fileHeader));
    outputFile.write((char*)&infoHeader,sizeof(infoHeader));
    outputFile.write((char*)&colorHeader,sizeof(colorHeader));
    
  
    int width=infoHeader.width;
    int height= infoHeader.height;

    //greyscale
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            unsigned char color[3];
            inputFile.read(reinterpret_cast<char*>(color),3);
            float grey = (static_cast<float>(color[0]) + static_cast<float>(color[1]) + static_cast<float>(color[2]))/3;
            unsigned char greyColor[3];
            greyColor[0] = static_cast<unsigned char>(grey);
            greyColor[1] = static_cast<unsigned char>(grey);
            greyColor[2] = static_cast<unsigned char>(grey);
            outputFile.write(reinterpret_cast<char*>(greyColor),3);
        }
    }    
   

    bmpColorTable colorTable;
    inputFile.read((char*)&colorTable,sizeof(colorTable));
    outputFile.write((char*)&colorTable,sizeof(colorTable));
    inputFile.close();
    outputFile.close();
}


