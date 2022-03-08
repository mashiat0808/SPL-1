#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

void readHeaderAndPrint(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader)
{
    ifstream inputFile;
    inputFile.open("x.bmp",ios:: binary);
    if(inputFile.eof()) return;

    inputFile.seekg(0,ios::beg);
    inputFile.read((char*)&signature,sizeof(signature)); // memory allocation problem if signature is in fileHeader.Char and int///////
    inputFile.read((char*)&fileHeader,sizeof(fileHeader));
    inputFile.read((char*)&infoHeader,sizeof(infoHeader));
    inputFile.read((char*)&colorHeader,sizeof(colorHeader));

    //colorTableSize = infoHeader.colorsInColorTable;

    bmpColorTable colorTable;
    inputFile.read((char*)&colorTable,sizeof(colorTable));

    inputFile.close();

    cout <<"BMP Header\n"<<endl;

    cout <<"BMP Signature       : "<<signature.signatureData[0]<<signature.signatureData[1]<<endl;
    cout <<"BMP file size       : "<<fileHeader.fileSize<<" bytes"<<endl;
    cout <<"BMP reserved1       : "<<fileHeader.reserved1<<endl;
    cout <<"BMP reserved2       : "<<fileHeader.reserved2<<endl;
    cout <<"BMP dataOffset      : "<<fileHeader.dataOffset<<" bytes"<<endl;

    cout <<"\nInfo  Header\n"<<endl;

    cout <<"BMP file size             : "<<infoHeader.headerSize<<" bytes"<<endl;
    cout <<" BMP width                : "<<infoHeader.width<<" bytes"<<endl;
    cout <<" BMP height               : "<<infoHeader.height<<" bytes"<<endl;
    cout <<" BMP planes               : "<<infoHeader.planes<<" bytes"<<endl;
    cout <<" BMP bit per pixel        : "<<infoHeader.bpPixels<<" bytes"<<endl;
    cout <<" BMP compression          : "<<infoHeader.compression<<" bytes"<<endl;
    cout <<" BMP image size           : "<<infoHeader.imageSize<<" bytes"<<endl;
    cout <<" BMP important color Count: "<<infoHeader.importantcolorCount<<" bytes"<<endl;

    cout<<"\nColor Header\n"<<endl;
    cout <<" BMP red channel bit mask   : "<<colorHeader.redChannelBitmask<<endl;
    cout <<" BMP green channel bit mask : "<<colorHeader.greenChannelBitmask<<endl;
    cout <<" BMP blue channel bit mask  : "<<colorHeader.blueChannelBitmask<<endl;
    cout <<" BMP alpha channel bit mask : "<<colorHeader.alphaChannelBitmask<<endl;
    cout <<" BMP color space type       : "<<colorHeader.colorSpaceType<<endl;

}
