#include <fstream>
#include <iomanip>
#include <cmath>
#include "header.h"
using namespace std;


void brightening(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader)
{
     ifstream inputFile;
     ofstream outputFile;

    inputFile.open("blackbuck.bmp",ios:: binary);
    outputFile.open("bbbrightening.bmp", ios :: binary);
    
    
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

    cout<<"Input the brightness level between -255 to +255 : ";
    int level;
    cin>> level;
    if(level>255 || level<-255)
    {
        cout<<"Invalid brightness level";
        return;
    }
    else
    {
       for (int lin=0;lin<height;lin++)
        {   
        for (int col=0;col<width; col++)
        {

            int b = pixels[lin][col][0]; //blue
            b =b+min(level,(255-b));
            color[2] = max(0,b); 

            int g = pixels[lin][col][1]; //green
            g = g+min(level,(255-g));
            color[1] = max(0,g); 

            int r =  pixels[lin][col][2]; //red
            r = r+min(level,(255-r));
            color[0] = max(0,r); 

            outputFile.write(reinterpret_cast<char*>(color),3);
        }

    } 
    }
    
    bmpColorTable colorTable;
    inputFile.read((char*)&colorTable,sizeof(colorTable));
    outputFile.write((char*)&colorTable,sizeof(colorTable));
    inputFile.close();
    outputFile.close();
}
