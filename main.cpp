#include<iostream>
#include<fstream>
#include <cmath>

#include "HeaderStructure.cpp"
#include "ShowInfo.cpp"
#include "checkfile.cpp"

using namespace std;

int main ()
{

    bmpSignature signature;
    bmpFileHeader fileHeader;
    bmpInfoHeader infoHeader;

    checkFile(signature,fileHeader,infoHeader);
    ReadHeaderAndPrint(signature,fileHeader,infoHeader);
    

    return 0;
}