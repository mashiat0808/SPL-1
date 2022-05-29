#include <fstream>
#include <iomanip>
#include <cmath>
#include "header.h"
#include <math.h>
using namespace std;

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


void smoothing(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader)
{
     ifstream inputFile;
     ofstream outputFile;

       inputFile.open("blackbuck.bmp",ios:: binary);
    outputFile.open("bbsmoothing.bmp", ios :: binary);
    
    
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
//smoothing algo
     int matrix[9];
     int sumr=0;
     int sumg=0;
     int sumb=0;
    for (int lin = 1; lin < height; ++lin)
    {  
        for (int col = 1; col < width; ++col)
        {         
            matrix[0] = pixels[lin-1][col-1][0];
            matrix[1] = pixels[lin-1][col][0];
            matrix[2] = pixels[lin-1][col+1][0];
            matrix[3] = pixels[lin][col-1][0];
            matrix[4] = pixels[lin][col][0];
            matrix[5] = pixels[lin][col+1][0];
            matrix[6] = pixels[lin+1][col-1][0];
            matrix[7] = pixels[lin+1][col][0];
            matrix[8] = pixels[lin+1][col+1][0];

            sumr=matrix[0]+matrix[1]+matrix[2]+matrix[3]+matrix[4]+matrix[5]+matrix[6]+matrix[7]+matrix[8];
            sumr=sumr/9;
            //put the median to the new image
            pixels[lin][col][0]=sumr;
        }
    }
    for (int lin = 1; lin < height; ++lin)
    {

        for (int col = 1; col < width; ++col)
        {
            
            matrix[0] = pixels[lin-1][col-1][1];
            matrix[1] = pixels[lin-1][col][1];
            matrix[2] = pixels[lin-1][col+1][1];
            matrix[3] = pixels[lin][col-1][1];
            matrix[4] = pixels[lin][col][1];
            matrix[5] = pixels[lin][col+1][1];
            matrix[6] = pixels[lin+1][col-1][1];
            matrix[7] = pixels[lin+1][col][1];
            matrix[8] = pixels[lin+1][col+1][1];

            sumg=matrix[0]+matrix[1]+matrix[2]+matrix[3]+matrix[4]+matrix[5]+matrix[6]+matrix[7]+matrix[8];
            sumg=sumg/9;
            //put the median to the new image
            pixels[lin][col][1]=sumg;
        }
    }
    for (int lin = 1; lin < height; ++lin)
    {
        for (int col = 1; col < width; ++col)
        {
            
            matrix[0] = pixels[lin-1][col-1][2];
            matrix[1] = pixels[lin-1][col][2];
            matrix[2] = pixels[lin-1][col+1][2];
            matrix[3] = pixels[lin][col-1][2];
            matrix[4] = pixels[lin][col][2];
            matrix[5] = pixels[lin][col+1][2];
            matrix[6] = pixels[lin+1][col-1][2];
            matrix[7] = pixels[lin+1][col][2];
            matrix[8] = pixels[lin+1][col+1][2];

            sumb=matrix[0]+matrix[1]+matrix[2]+matrix[3]+matrix[4]+matrix[5]+matrix[6]+matrix[7]+matrix[8];
            sumb=sumb/9;
            //put the median to the new image
            pixels[lin][col][2]=sumb;
        }
    }

    for (int lin = 0; lin < height; ++lin)
    {
        for (int col = 0; col < width; ++col)
        {
            color[0] = pixels[lin][col][2];
            color[1] = pixels[lin][col][1];
            color[2] = pixels[lin][col][0];
            outputFile.write(reinterpret_cast<char*>(color),3);
         //   outputFile.write(reinterpret_cast<char*>(pixels[lin][col]),3);
        }
    }

    bmpColorTable colorTable;
    inputFile.read((char*)&colorTable,sizeof(colorTable));
    outputFile.write((char*)&colorTable,sizeof(colorTable));
    inputFile.close();
    outputFile.close();





}