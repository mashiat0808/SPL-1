#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;


int pixels[10000000][3]={0};


void readImage(bmpSignature signature,bmpFileHeader fileHeader,bmpInfoHeader infoHeader, bmpColorHeader colorHeader){
     ifstream iFile;
    iFile.open("x.bmp",ios:: binary);
    if(iFile.eof()) throw runtime_error("File not found");
    iFile.seekg(0,ios::beg);
    iFile.read((char*)&signature,sizeof(signature));
    iFile.read((char*)&fileHeader,sizeof(fileHeader));
    iFile.read((char*)&infoHeader,sizeof(infoHeader));
    iFile.read((char*)&colorHeader,sizeof(colorHeader));
    
    int width=infoHeader.width;
    int height= infoHeader.height;

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
        
            unsigned char color[3];
            iFile.read(reinterpret_cast<char*>(color),3);

            pixels[i*width+j][0] = static_cast<float>(color[2]);
            pixels[i*width+j][1] = static_cast<float>(color[1]);
            pixels[i*width+j][2] = static_cast<float>(color[0]);
        }
    }

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
           cout<<"<" <<pixels[i*width+j][0]<<" "<<pixels[i*width+j][1]<<" "<<pixels[i*width+j][2]<<">    ";
        }
        cout<<endl;
    }
    iFile.close();
}


