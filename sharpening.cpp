#include <fstream>
#include <iomanip>
#include <cmath>
#include "header.h"
using namespace std;


void sharpening(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader)
{
     ifstream inputFile;
     ofstream outputFile;

    inputFile.open("blackbuck.bmp",ios:: binary);
    outputFile.open("bbsharpening.bmp", ios :: binary);
    
    
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
   
   for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            inputFile.read(reinterpret_cast<char*>(color),3);
            pixels[i][j][0] = static_cast<float>(color[2]); //red
            pixels[i][j][1] = static_cast<float>(color[1]); //green
            pixels[i][j][2] = static_cast<float>(color[0]); //blue
        }
    }

    //sharpening
    double filter[3][3] =
{  {-1, -1, -1},
   {-1,  9, -1},
   {-1, -1, -1}
};
    int filterSize = 3;
    int filterOffset = (filterSize - 1) / 2;
    int filterSum = 0;
    for (int i = 0; i < filterSize; i++)
    {
        for (int j = 0; j < filterSize; j++)
        {
            filterSum += filter[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = 0;
            float green = 0;
            float blue = 0;
            for (int k = -filterOffset; k <= filterOffset; k++)
            {
                for (int l = -filterOffset; l <= filterOffset; l++)
                {
                    int x = i + k;
                    int y = j + l;
                    if (x < 0)
                    {
                        x = 0;
                    }
                    if (x >= height)
                    {
                        x = height - 1;
                    }
                    if (y < 0)
                    {
                        y = 0;
                    }
                    if (y >= width)
                    {
                        y = width - 1;
                    }
                    red += filter[k + filterOffset][l + filterOffset] * pixels[x][y][0];
                    green += filter[k + filterOffset][l + filterOffset] * pixels[x][y][1];
                    blue += filter[k + filterOffset][l + filterOffset] * pixels[x][y][2];
                }
            }
            red = red / filterSum;
            green = green / filterSum;
            blue = blue / filterSum;
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            if (red < 0)
            {
                red = 0;
            }
            if (green < 0)
            {
                green = 0;
            }
            if (blue < 0)
            {
                blue = 0;
            }

            color[0] = static_cast<unsigned char>(blue);
            color[1] = static_cast<unsigned char>(green);
            color[2] = static_cast<unsigned char>(red);
            outputFile.write(reinterpret_cast<char*>(color), 3);
        }

    }
    bmpColorTable colorTable;
    inputFile.read((char*)&colorTable,sizeof(colorTable));
    outputFile.write((char*)&colorTable,sizeof(colorTable));
    inputFile.close();
    outputFile.close();

    




}