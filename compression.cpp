#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "header.h"
using namespace std;

string intToString(unsigned int value)
{

    stringstream strStream;
    string output;

    strStream << value;
    output = strStream.str();

    return output;
}


void compressImageFile(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader)
{

    unsigned int fileSize =0;
    unsigned int height =0;
    unsigned int width =0;
    unsigned int offset =0;
    unsigned long int pixelCompressedCounter=0;
    unsigned int colorTableSize =0;

    ifstream inputFile;
    ofstream oFile;

    inputFile.open("x.bmp",ios:: binary);
    if(inputFile.eof()) return;

    inputFile.seekg(0,ios::beg);
    inputFile.read((char*)&signature,sizeof(signature));
    inputFile.read((char*)&fileHeader,sizeof(fileHeader));
    inputFile.read((char*)&infoHeader,sizeof(infoHeader));
    inputFile.read((char*)&colorHeader,sizeof(colorHeader));

    fileSize =  fileHeader.fileSize;
    offset   =  fileHeader.dataOffset;
    height   =  infoHeader.height;
    width    =  infoHeader.width;

    inputFile.close();

    inputFile.open("x.bmp",ios:: binary);
    oFile.open("xcompressed.BMP",ios::binary);

    if(!inputFile.is_open() && !oFile.is_open()) return;

    unsigned char ch;
    unsigned char old;
    unsigned char present;
    unsigned int pixelCounter = 1;
    unsigned long int counter =0;
    unsigned long int limit = (width*height)+offset;

  while(!inputFile.eof())
    {
        ch = inputFile.get();
        
        oFile<<ch;
        counter++;
    if(pixelCounter>1)
    {
        oFile<<old;
        oFile<<pixelCounter;
    }

        if(counter<offset)
        {
            continue;
        }
        else
        
        {
           if(pixelCounter==1)
            {
                old = ch;
                pixelCounter++;
            }
            else 
            { 
                present = ch;
                if(old==present)
                {
                    pixelCounter++;
                }
                else
                {
                    oFile<<old;
                    oFile<<pixelCounter;
                    old = present;
                    pixelCounter = 1;
                }
            }
        }

         if(counter>=limit)
         {
             break;
         }
    }

   if(pixelCounter>1)
    {
        oFile<<old;
        oFile<<pixelCounter;
    }

    

    inputFile.close();
    oFile.close();
    cout<<"\t"<<pixelCompressedCounter<<endl;
    cout<<"++++++Image Compression Successful.+++++++"<<endl;
}