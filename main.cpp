#include<iostream>
#include<fstream>
#include <cmath>

#include "HeaderStructure.cpp"
#include "ShowInfo.cpp"
#include "checkfile.cpp"
#include "PixelData.cpp"

using namespace std;

int main ()
{

    bmpSignature signature;
    bmpFileHeader fileHeader;
    bmpInfoHeader infoHeader;
    bmpColorHeader colorHeader;

    checkFile(signature,fileHeader,infoHeader, colorHeader);
    ReadHeaderAndPrint(signature,fileHeader,infoHeader, colorHeader);
    readImage(signature,fileHeader,infoHeader, colorHeader);
   
   
    return 0;
}