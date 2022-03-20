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

    inputFile.open("greyscaleofbaboon2.bmp",ios:: binary);
    outputFile.open("edgeofbb.bmp", ios :: binary);
    
    
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
unsigned char greyColor[3];
    //greyscale
  /*  for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            unsigned char color[3];
            inputFile.read(reinterpret_cast<char*>(color),3);
            float grey = (static_cast<float>(color[0]) + static_cast<float>(color[1]) + static_cast<float>(color[2]))/3;
            
            greyColor[0] = static_cast<unsigned char>(grey);
            greyColor[1] = static_cast<unsigned char>(grey);
            greyColor[2] = static_cast<unsigned char>(grey);
            outputFile.write(reinterpret_cast<char*>(greyColor),3);
        }
    }    
*/
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

    for (int lin = 0; lin < height; ++lin)
    {
        for (int col = 0; col < width; ++col)
        {
            if (lin !=0 && lin != height && col != 0 && col != width)
            {
            gxValBlue = (pixels[lin-1][col-1][0] * gx[0][0] + pixels[lin-1][col][0] * gx[0][1] + pixels[lin-1][col+1][0] * gx[0][2] + pixels[lin][col-1][0] * gx[1][0] + pixels[lin][col][0] * gx[1][1] + pixels[lin][col+1][0] * gx[1][2] + pixels[lin-1][col-1][0] * gx[2][0] + pixels[lin+1][col][0] * gx[2][1] + pixels[lin+1][col+1][0] * gx[2][2]);
            gyValBlue = (pixels[lin-1][col-1][0] * gy[0][0] + pixels[lin-1][col][0] * gy[0][1] + pixels[lin-1][col+1][0] * gy[0][2] + pixels[lin][col-1][0] * gy[1][0] + pixels[lin][col][0] * gy[1][1] + pixels[lin][col+1][0] * gy[1][2] + pixels[lin-1][col-1][0] * gy[2][0] + pixels[lin+1][col][0] * gy[2][1] + pixels[lin+1][col+1][0] * gy[2][2]);

            squaredBlue = (int)sqrt(gxValBlue*gxValBlue + gyValBlue*gyValBlue);

            gxValGreen = (pixels[lin-1][col-1][1] * gx[0][0] + pixels[lin-1][col][1] * gx[0][1] + pixels[lin-1][col+1][1] * gx[0][2] + pixels[lin][col-1][1] * gx[1][0] + pixels[lin][col][1] * gx[1][1] + pixels[lin][col+1][1] * gx[1][2] + pixels[lin-1][col-1][1] * gx[2][0] + pixels[lin+1][col][1] * gx[2][1] + pixels[lin+1][col+1][1] * gx[2][2]);
            gyValGreen = (pixels[lin-1][col-1][1] * gy[0][0] + pixels[lin-1][col][1] * gy[0][1] + pixels[lin-1][col+1][1] * gy[0][2] + pixels[lin][col-1][1] * gy[1][0] + pixels[lin][col][1] * gy[1][1] + pixels[lin][col+1][1] * gy[1][2] + pixels[lin-1][col-1][1] * gy[2][0] + pixels[lin+1][col][1] * gy[2][1] + pixels[lin+1][col+1][1] * gy[2][2]);

            squaredGreen = (int)sqrt(gxValGreen*gxValGreen + gyValGreen*gyValGreen);

            gxValRed = (pixels[lin-1][col-1][2] * gx[0][0] + pixels[lin-1][col][2] * gx[0][1] + pixels[lin-1][col+1][2] * gx[0][2] + pixels[lin][col-1][2] * gx[1][0] + pixels[lin][col][2] * gx[1][1] + pixels[lin][col+1][2] * gx[1][2] + pixels[lin-1][col-1][2] * gx[2][0] + pixels[lin+1][col][2] * gx[2][1] + pixels[lin+1][col+1][2] * gx[2][2]);
            gyValRed = (pixels[lin-1][col-1][2] * gy[0][0] + pixels[lin-1][col][2] * gy[0][1] + pixels[lin-1][col+1][2] * gy[0][2] + pixels[lin][col-1][2] * gy[1][0] + pixels[lin][col][2] * gy[1][1] + pixels[lin][col+1][2] * gy[1][2] + pixels[lin-1][col-1][2] * gy[2][0] + pixels[lin+1][col][2] * gy[2][1] + pixels[lin+1][col+1][2] * gy[2][2]);

            squaredRed = (int)sqrt(gxValRed*gxValRed + gyValRed*gyValRed);



                if (squaredBlue > 100)
                {
                    greyColor[2] = 255;
                }
                else
                {
                    greyColor[2] = 0;
                }



                if (squaredGreen > 100)
                {
                    greyColor[1] = 255;
                }
                else
                {
                    greyColor[1] = 0;
                }


                if (squaredRed > 100)
                {
                    greyColor[0] = 255;
                }
                else
                {
                    greyColor[0] = 0;
                }

            }
            else    // bottom
            {


                greyColor[0] = 0;
                greyColor[1] = 0;
                greyColor[2] = 0;


            }
            outputFile.write(reinterpret_cast<char*>(greyColor),3);
        }

    }

    bmpColorTable colorTable;
    inputFile.read((char*)&colorTable,sizeof(colorTable));
    outputFile.write((char*)&colorTable,sizeof(colorTable));
    inputFile.close();
    outputFile.close();
}


