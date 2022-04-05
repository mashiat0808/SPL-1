#pragma once
#include <fstream>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <stdexcept>

#include "headerstructure.cpp"
#include "ShowInfo.cpp"
#include "checkfile.cpp"
#include "PixelData.cpp"
#include "writeimage.cpp"
#include "compression.cpp"
#include "greyscale.cpp"
#include "edgedetection.cpp"
#include "brightening.cpp"
#include "sharpening.cpp"
#include "smoothing.cpp"
//#include "decimaltohexadecimal.cpp"

void readHeaderAndPrint(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader);
void checkFile(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader);
void readImage(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader);
void compressImageFile(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader);
void copyImageFile();
void greyscale(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader);
void edgedetection(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader);
string intToString(unsigned int value);
void brightening(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader);
void sharpening(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader);
void insertionSort(int arr[], int n);
void smoothing(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader);

///string decToHexa(int n);