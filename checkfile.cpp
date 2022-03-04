#include <fstream>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace std;
void checkFile(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader)
{
    ifstream iFile;
    iFile.open("x.bmp",ios:: binary);
    if(iFile.eof()) throw runtime_error("File not found");
    iFile.seekg(0,ios::beg);
    iFile.read((char*)&signature,sizeof(signature));
    iFile.read((char*)&fileHeader,sizeof(fileHeader));
    iFile.read((char*)&infoHeader,sizeof(infoHeader));
    iFile.read((char*)&colorHeader,sizeof(colorHeader));
    iFile.close();

      if(iFile)
    {
         //check if file is bmp
        if(signature.signatureData[0]!='B' || signature.signatureData[1]!='M')
        {
            throw runtime_error("File is not a bmp file");
        } 
        //check if height and width are positive
        if(infoHeader.height<0 || infoHeader.width<0)
        {
            throw runtime_error("Height and width must be positive");
        }
        
    }
    else
    {
        cout<<"File not found"<<endl;
    }



}
