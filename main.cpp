#include "header.h"

using namespace std;

int main ()
{

    bmpSignature signature;
    bmpFileHeader fileHeader;
    bmpInfoHeader infoHeader;
    bmpColorHeader colorHeader;

    checkFile(signature,fileHeader,infoHeader, colorHeader);
    readHeaderAndPrint(signature,fileHeader,infoHeader, colorHeader);
   // readImage(signature,fileHeader,infoHeader, colorHeader);
   // copyImageFile();
   
    return 0;
}