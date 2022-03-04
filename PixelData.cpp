#include <fstream>
#include <iomanip>
#include <cmath>
#include <iostream>
using namespace std;

void pixelData(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader)
{
    ifstream iFile;
    int input;
    iFile.open("x.bmp",ios:: binary);
    if(iFile.eof()) return;

    iFile.seekg(fileHeader.dataOffset, ios::beg);
}
