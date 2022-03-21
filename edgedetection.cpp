#include <fstream>
#include <iomanip>
#include <cmath>
#include "header.h"
#include <math.h>
using namespace std;


void edgedetection(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader)
{
     ifstream inputFile;
     ofstream outputFile;


    int gx[3][3];
    int gy[3][3];

    gx[0][0] = 1;
    gx[0][1] = 0;
    gx[0][2] = -1;

    gx[1][0] = 2;
    gx[1][1] = 0;
    gx[1][2] = -2;

    gx[2][0] = -1;
    gx[2][1] = 0;
    gx[2][2] = 1;


    gy[0][0] = 1;
    gy[0][1] = 2;
    gy[0][2] = 1;

    gy[1][0] = 0;
    gy[1][1] = 0;
    gy[1][2] = 0;

    gy[2][0] = -1;
    gy[2][1] = -2;
    gy[2][2] = -1;

    int gxValBlue;
    int gyValBlue;

    int gxValGreen;
    int gyValGreen;

    int gxValRed;
    int gyValRed;

    int squaredBlue;
    int squaredGreen;
    int squaredRed;

    inputFile.open("meah.bmp",ios:: binary);
    outputFile.open("meahedge2.bmp", ios :: binary);
    
    
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
    unsigned char color[3];
   

   //greyscaling
    //getting all pixel data
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            unsigned char color[3];
            inputFile.read(reinterpret_cast<char*>(color),3);
            pixels[i][j][0] = static_cast<float>(color[2]); //red
            pixels[i][j][1] = static_cast<float>(color[1]); //green
            pixels[i][j][2] = static_cast<float>(color[0]); //blue
        }
    }
        float grey;

    //greyscalling pixel data
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            grey= (pixels[i][j][0] + pixels[i][j][1] + pixels[i][j][2])/3;
            pixels[i][j][0] = grey;
            pixels[i][j][1] = grey;
            pixels[i][j][2] = grey;
        }
    }

    //edge detection
    for(int i=0;i<height; i++)
    {
        for(int j=0; j<width;j++)
        {
            if (i !=0 && i != height && j != 0 && j != width)
            {
            gxValBlue = (pixels[i-1][j-1][0] * gx[0][0] + pixels[i-1][j][0] * gx[0][1] + pixels[i-1][j+1][0] * gx[0][2] + pixels[i][j-1][0] * gx[1][0] + pixels[i][j][0] * gx[1][1] + pixels[i][j+1][0] * gx[1][2] + pixels[i-1][j-1][0] * gx[2][0] + pixels[i+1][j][0] * gx[2][1] + pixels[i+1][j+1][0] * gx[2][2]);
            gyValBlue = (pixels[i-1][j-1][0] * gy[0][0] + pixels[i-1][j][0] * gy[0][1] + pixels[i-1][j+1][0] * gy[0][2] + pixels[i][j-1][0] * gy[1][0] + pixels[i][j][0] * gy[1][1] + pixels[i][j+1][0] * gy[1][2] + pixels[i-1][j-1][0] * gy[2][0] + pixels[i+1][j][0] * gy[2][1] + pixels[i+1][j+1][0] * gy[2][2]);

            gxValGreen = (pixels[i-1][j-1][1] * gx[0][0] + pixels[i-1][j][1] * gx[0][1] + pixels[i-1][j+1][1] * gx[0][2] + pixels[i][j-1][1] * gx[1][0] + pixels[i][j][1] * gx[1][1] + pixels[i][j+1][1] * gx[1][2] + pixels[i-1][j-1][1] * gx[2][0] + pixels[i+1][j][1] * gx[2][1] + pixels[i+1][j+1][1] * gx[2][2]);
            gyValGreen = (pixels[i-1][j-1][1] * gy[0][0] + pixels[i-1][j][1] * gy[0][1] + pixels[i-1][j+1][1] * gy[0][2] + pixels[i][j-1][1] * gy[1][0] + pixels[i][j][1] * gy[1][1] + pixels[i][j+1][1] * gy[1][2] + pixels[i-1][j-1][1] * gy[2][0] + pixels[i+1][j][1] * gy[2][1] + pixels[i+1][j+1][1] * gy[2][2]);

            gxValRed = (pixels[i-1][j-1][2] * gx[0][0] + pixels[i-1][j][2] * gx[0][1] + pixels[i-1][j+1][2] * gx[0][2] + pixels[i][j-1][2] * gx[1][0] + pixels[i][j][2] * gx[1][1] + pixels[i][j+1][2] * gx[1][2] + pixels[i-1][j-1][2] * gx[2][0] + pixels[i+1][j][2] * gx[2][1] + pixels[i+1][j+1][2] * gx[2][2]);
            gyValRed = (pixels[i-1][j-1][2] * gy[0][0] + pixels[i-1][j][2] * gy[0][1] + pixels[i-1][j+1][2] * gy[0][2] + pixels[i][j-1][2] * gy[1][0] + pixels[i][j][2] * gy[1][1] + pixels[i][j+1][2] * gy[1][2] + pixels[i-1][j-1][2] * gy[2][0] + pixels[i+1][j][2] * gy[2][1] + pixels[i+1][j+1][2] * gy[2][2]);
            
            squaredBlue = (int)sqrt(gxValBlue*gxValBlue + gyValBlue*gyValBlue);
            squaredRed = (int)sqrt(gxValRed*gxValRed + gyValRed*gyValRed);
            squaredGreen = (int)sqrt(gxValGreen*gxValGreen + gyValGreen*gyValGreen);


                if (squaredBlue > 50) color[2] = 255;
                else color[2] = 0;

                if (squaredRed > 50) color[0] = 255;
                else color[0] = 0;

                if (squaredGreen > 50) color[1] = 255;
                else color[1] = 0;
            }
            else    // bottom
            {
                color[0] = 0;
                color[1] = 0;
                color[2] = 0;
            }

            outputFile.write(reinterpret_cast<char*>(color),3);
        }

    }

    bmpColorTable colorTable;
    inputFile.read((char*)&colorTable,sizeof(colorTable));
    outputFile.write((char*)&colorTable,sizeof(colorTable));
    inputFile.close();
    outputFile.close();
}


