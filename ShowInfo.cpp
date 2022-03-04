#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

void ReadHeaderAndPrint(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader)
{
    ifstream iFile;
    iFile.open("x.bmp",ios:: binary);
    if(iFile.eof()) return;

    iFile.seekg(0,ios::beg);
    iFile.read((char*)&signature,sizeof(signature)); // memory allocation problem if signature is in fileHeader.Char and int///////
    iFile.read((char*)&fileHeader,sizeof(fileHeader));
    iFile.read((char*)&infoHeader,sizeof(infoHeader));
    iFile.read((char*)&colorHeader,sizeof(colorHeader));

    //colorTableSize = infoHeader.colorsInColorTable;

    bmpColorTable colorTable;
    iFile.read((char*)&colorTable,sizeof(colorTable));

    iFile.close();

    cout <<"BMP Header\n"<<endl;

    cout <<"BMP Signature                  : "<<signature.signatureData[0]<<signature.signatureData[1]<<endl;
    cout <<"BMP file size                  : "<<fileHeader.fileSize<<" bytes"<<endl;
    cout <<"BMP reserved1                  : "<<fileHeader.reserved1<<endl;
    cout <<"BMP reserved2                  : "<<fileHeader.reserved2<<endl;
    cout <<"BMP dataOffset                 : "<<fileHeader.dataOffset<<" bytes"<<endl;

    cout <<"\nInfo  Header\n"<<endl;

    cout <<"BMP file size              : "<<infoHeader.headerSize<<" bytes"<<endl;
    cout <<" bmp width                  : "<<infoHeader.width<<" bytes"<<endl;
    cout <<" bmp height                 : "<<infoHeader.height<<" bytes"<<endl;
    cout <<" bmp planes                  : "<<infoHeader.planes<<" bytes"<<endl;
    cout <<" bmp bit per pixel          : "<<infoHeader.bpPixels<<" bytes"<<endl;
    cout <<" bmp compression            : "<<infoHeader.compression<<" bytes"<<endl;
    cout <<" bmp image size             : "<<infoHeader.imageSize<<" bytes"<<endl;
    cout <<" bmp X axis pixel per meter : "<<infoHeader.pixelPerMeterX<<" bytes"<<endl;
    cout <<" bmp Y axis pixel per meter : "<<infoHeader.pixelPerMeterY<<" bytes"<<endl;
    cout <<" bmp colorsInColorTable     : "<<infoHeader.colorsInColorTable<<" bytes"<<endl;
    cout <<" bmp important color Count  : "<<infoHeader.importantcolorCount<<" bytes"<<endl;
    cout <<" bmp red channel bit mask   : "<<colorHeader.redChannelBitmask<<" bytes"<<endl;
    cout <<" bmp green channel bit mask : "<<colorHeader.greenChannelBitmask<<" bytes"<<endl;
    cout <<" bmp blue channel bit mask  : "<<colorHeader.blueChannelBitmask<<" bytes"<<endl;
    cout <<" bmp alpha channel bit mask : "<<colorHeader.alphaChannelBitmask<<" bytes"<<endl;
    cout <<" bmp color space type       : "<<colorHeader.colorSpaceType<<" bytes"<<endl;
 

}