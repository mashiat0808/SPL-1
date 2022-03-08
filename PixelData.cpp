#include <fstream>
#include <iomanip>
#include <cmath>
#include "header.h"
using namespace std;


int pixels[10000000][3]={0};
void readImage(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader)
{
     ifstream inputFile;
    inputFile.open("x.bmp",ios:: binary);
    if(inputFile.eof()) throw runtime_error("File not found");
    inputFile.seekg(0,ios::beg);
    inputFile.read((char*)&signature,sizeof(signature));
    inputFile.read((char*)&fileHeader,sizeof(fileHeader));
    inputFile.read((char*)&infoHeader,sizeof(infoHeader));
    inputFile.read((char*)&colorHeader,sizeof(colorHeader));
    
    int width=infoHeader.width;
    int height= infoHeader.height;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            unsigned char color[3];
            inputFile.read(reinterpret_cast<char*>(color),3);
            pixels[i*width+j][0] = static_cast<float>(color[2]); //red
            pixels[i*width+j][1] = static_cast<float>(color[1]); //green
            pixels[i*width+j][2] = static_cast<float>(color[0]); //blue
        }
    }

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
           cout<<"<"<<pixels[i*width+j][2]<<","<<pixels[i*width+j][1]<<","<<pixels[i*width+j][0]<<"> ";
           cout<<"\t";
        }
        cout<<endl<<endl;
    }
    inputFile.close();
}


