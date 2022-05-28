#include "header.h"

using namespace std;

int main ()
{

    bmpSignature signature;
    bmpFileHeader fileHeader;
    bmpInfoHeader infoHeader;
    bmpColorHeader colorHeader;
 greyscale(signature,fileHeader,infoHeader, colorHeader);
 edgedetection(signature,fileHeader,infoHeader, colorHeader);
 brightening(signature,fileHeader,infoHeader, colorHeader);
  sharpening(signature,fileHeader,infoHeader, colorHeader);
  smoothing(signature,fileHeader,infoHeader, colorHeader);

    checkFile(signature,fileHeader,infoHeader, colorHeader);
  readHeaderAndPrint(signature,fileHeader,infoHeader, colorHeader);
  readImage(signature,fileHeader,infoHeader, colorHeader);
   compressImageFile(signature,fileHeader,infoHeader, colorHeader);
 

   copyImageFile();

    return 0;
}