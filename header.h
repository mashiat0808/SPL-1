#include <fstream>
#include <iomanip>
#include <cmath>


void ReadHeaderAndPrint(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader);
void checkFile(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader);
void readImage(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader);