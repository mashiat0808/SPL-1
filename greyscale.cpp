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
    

    
    int width=infoHeader.width;
    int height= infoHeader.height;    
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            unsigned char color[3];
            inputFile.read(reinterpret_cast<char*>(color),3);
            pixels[i][j][0] = static_cast<float>(color[2]); //red
            pixels[i][j][1] = static_cast<float>(color[1]); //green
            pixels[i][j][2] = static_cast<float>(color[0]); //blue

            pixels[i][j][0] = (pixels[i][j][0] + pixels[i][j][1] + pixels[i][j][2])/3;
            pixels[i][j][1] = (pixels[i][j][0] + pixels[i][j][1] + pixels[i][j][2])/3;
            pixels[i][j][2] = (pixels[i][j][0] + pixels[i][j][1] + pixels[i][j][2])/3;
        }
    }

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            unsigned char color[3];
            color[0] = (pixels[i][j][0]);
            color[1] = (pixels[i][j][1]);
            color[2] = (pixels[i][j][2]);
            outputFile.write(reinterpret_cast<char*>(color),3);
        }
    }
 


    inputFile.close();
    outputFile.close();
}


