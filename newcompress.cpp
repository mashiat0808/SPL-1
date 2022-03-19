#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "header.h"
using namespace std;

void compressImage(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader)
{
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
    int padding = (width % 4);
    if (padding != 0) padding = 4-padding;
    BYTE *Input = new BYTE[width];       
    int *LineLengths = new int[height];

    BYTE **Output = (BYTE **) malloc( infoHeader.height * sizeof(BYTE *));
for (int i = 0; i < infoHeader.height; i++){
    Output[i] = (BYTE *) malloc(((infoHeader.width*2)+8) * sizeof(BYTE *));
    Output[i][infoHeader.width+1] = 0; 	// for EOL
    Output[i][infoHeader.width+2] = 0; 	// or EOF
    Output[i][infoHeader.width+3] = 0; 	// I am not sure 
                                               	// whether is this necessary
    Output[i][infoHeader.width+4] = 0;
    Output[i][infoHeader.width+5] = 0;
    Output[i][infoHeader.width+6] = 0;
    Output[i][infoHeader.width+7] = 0;
    LineLengths[i] = 0;
}
    int filesize = (256) + sizeof(fileHeader) + sizeof(infoHeader);

    int headersize = filesize;
register int Y, X;
int j;
int cnt;
bool uncompressed;
BYTE pixel;
for (Y = 0; Y < infoHeader.height; Y++){
   // read input scanline
   fread(Input, infoHeader.width, 1, f);
   // skip padding 
   for (X = 0; X < padding; X++)
      fgetc(f);  		// padding bytes, can be 0 or anything, do not test for 0
   // reset compression variables
   uncompressed = true;
   X = 0;
   j = 0;
   LineLengths[Y] =  0;
   while(uncompressed) 	// while end of scanline is reached
   {
     cnt = 0;  		// set repeats to 0
     pixel = Input[j]; 	// 1 pixel
     while ( (j < InputWidth) && (pixel == Input[j]) && (cnt < 255)){
        j++;    		// move forward
        cnt++;  		// increment repeats count (run)
     }
    if (j == InputWidth)
      uncompressed = false;	// if end of scanline is reached, set compressed to true
    Output[Y][X] = cnt;   	// write run length (repeats count)
    X++;   		// move forward
    Output[Y][X] = pixel; 	// write pixel vale (index)
    X++;   // move forward
    LineLengths[Y] = LineLengths[Y] +2; // we've written 2 bytes, incr. line l.
    filesize = filesize +2; 	// we've written 2 bytes, increase output filesize
   }
   Output[Y][X] = 0x00;  		// ESCAPE byte...
   if (Y ==  infoHeader.height-1)
      Output[Y][X+1] = 0x01;  	// denotes EOF with 0x01, when last scan is reached
   else  
      Output[Y][X+1] = 0x00;  	// EOL, else
  LineLengths[Y]+=2; 	// we written a 2 byte marker, increment output line length
  filesize+=2; // we increment filesize as well
}
infoHeader.compression =1;   //  1 = 8 bit compressed RLE
fileHeader.fileSize = filesize;  // set up filesize
bitmapinfoheader.biSizeImage = filesize - headersize; 	// compressed stream size        
                                                      	// != filesize. headers
                                                      	// size is not included
                                                      	// only scanlines with padd.
// write headers
fwrite(&bitmapfileheader, sizeof(bitmapfileheader), 1, fout);
fwrite(&bitmapinfoheader, sizeof(bitmapinfoheader), 1, fout);

// write palette
fwrite(paletteentries, sizeof(PALETTEENTRY), 256, fout);
// write compressed scanlines according to their line lengths
for (Y = 0; Y < infoHeader.height; Y++){          
     fwrite(Output[Y], LineLengths[Y], 1, fout); 	// write scanline
}

    inputFile.close();

    inputFile.open("x.bmp",ios:: binary);
    oFile.open("xcompressed.BMP",ios::binary);
}