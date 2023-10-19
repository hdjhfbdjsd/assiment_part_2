// Program: demo2.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Mohammad El-Ramly
// Date:    30 March 2018
// Version: 1.0
// mostsfa197khaled@gmail.com      Mostafa khaled mohamed fahim     ----> 20220422
// mhmwdhany132@gmail.com          Mahmoud Hany Mahmoud Abd Alhamed ----> 20221139
// mahmoudganafy66@gmail.com       Mahmoud Hanafy Mahmoud           ----> 20220316
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include"bmplib.h"
#include"bmplib.cpp"

using namespace std;
//unsigned char ans[SIZE][SIZE];
unsigned char image[SIZE][SIZE];
unsigned char image1[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char image3[SIZE][SIZE];
unsigned char shrinkage[SIZE][SIZE];
void loadImage ();
void saveImage ();
void doSomethingForImage ();
void loadImage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}
void loadImage2 () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image2);
}

//_
void saveimage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

void Detect_Image() {
        unsigned char imageR[SIZE][SIZE];

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if ((image[i][j]) > 127) {
                    image[i][j] = 255;
                    imageR[i][j] = 255;
                } else {
                    image[i][j] = 0;
                    imageR[i][j] = 0;
                }
            }
        }

        for (int i = 1; i < SIZE-1; i++) {
            for (int j = 1; j< SIZE-1; j++) {
                if(image[i][j]==0) {
                    if( image[i-1][j-1]==0&&image[i-1][j]==0&&image[i-1][j+1]==0&&
                        image[i][j-1]==0&&                    image[i][j+1]==0&&
                        image[i+1][j-1]==0&&image[i+1][j]==0&&image[i+1][j+1]==0) {

                        imageR[i][j] = 255;
                    }
                }

            }
        }

        for (int i =0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j]+=imageR[i][j];
            }
        }
    };
void Enlarge_Image() {
    //  Enlarge Image
    unsigned char image2[SIZE][SIZE];

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image2[i][j] = 255;


        }

    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image2[i][j] = image[i / 2][j / 2];

        }
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = image2[i][j];
        }
    }
}


void Shrink() {
    unsigned char image1[SIZE][SIZE];
    char imageFileName[100];
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image1);

    int num;
    cout << "Enter num (2,3,4): ";
    cin >> num;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i < SIZE / num && j < SIZE / num) {
                image[i][j] = image1[i * num][j * num];
            } else {
                image[i][j] = 255;
            }
        }
    }
}
void Mirror_Image() {
    for (int q = 0; q < SIZE; q++) {
        for (int j = 0; j< SIZE; j++) {

            image[q][j] =image[255-q][j];
        }
    }
}
unsigned char shuffled[SIZE][SIZE];

void moveQuarter(int idx, int i, int j)
{
    int quarterSize = SIZE / 2;
    int sourceI, sourceJ;

    for (int k = 0; k < quarterSize; k++){
        sourceI = (idx <= 2) ? i + k : i + k + quarterSize;
        for (int z = 0; z < quarterSize; z++){
            sourceJ = (idx % 2 == 0) ? j + z + quarterSize : j + z;
            shuffled[i + k][j + z] = image[sourceI][sourceJ];
        }
    }
}

void shuffle_Image(){
    int order[4];
    cout << "Enter the order of quarters you want (1-4): ";
    for (int i = 0; i < 4; i++){
        cin >> order[i];
    }
    int positions[4][2] = {{0, 0}, {0, SIZE / 2}, {SIZE / 2, 0}, {SIZE / 2, SIZE / 2}};
    for (int i = 0; i < 4; i++){
        moveQuarter(order[i], positions[i][0], positions[i][1]);
    }
}


void Blur_Image() {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {


            image[i][j] = ((image[i + i][j] + image[i - 1][j]) + (image[i + 1][j - 1] + image[i - 1][j + 1]) +
                           (image[i][j + 1] + image[i][j - 1]) + (image[i - 1][j + 1] + image[i + 1][j - 1])) / 9;


        }
    }
}
void cut_Image(){


    //Custom Size (محمود) Hoda ------ > Variable
    short h, o, d, a;
    cin >> h >> o >> d >> a;


    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = 255;
        }
    }


    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < o; ++j) {
            image[i][j] = 255;
        }
    }

    for (int i = h + a; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = 255;
        }
    }

    for (int k = 0; k < SIZE; ++k) {
        for (int j = o + d; j < SIZE; ++j) {
            image[k][j] = 255;
        }
    }
}
void skew() {


    cout<<" to skew right press 1 , to skew up press 0 : ";
    int direction;
    cin>>direction;
    double rad;
    cout<<"what degree of skew ? ";
    cin>>rad;
    rad = 30;
    rad = (rad*22)/(180*7);
    double left =256 *(1-tan(rad));
    double high= 256 * tan(rad);
    double moving= high/256 ;
    if(direction){
        for(int i = 0 ;i < SIZE;++i){
            for(int j = 0 ; j < 127 ; ++j){
                image2[i][j] = image[i][(int)(j*255)/127];
            }
        }

        for(int i = 0 ;i < SIZE;++i){
            for(int j = 0 ; j < SIZE ; ++j){
                image3[i][j] = 255;
            }
        }

        for(int i = 0 ;i < SIZE;++i){
            for(int j = high ; j < high +left; ++j){
                image3[i][j] = image2[i][j-(int)high];

            }
            high-= moving;
        }
    }

    else{
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image1[i][j] = image[SIZE - 1 - i][SIZE - 1 - j];
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = image1[i][SIZE-1-j];
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                shrinkage[i][j] = image[i][j];
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = shrinkage[SIZE - j - 1][i];
            }
        }


        for(int i = 0 ;i < SIZE;++i){
            for(int j = 0 ; j < SIZE ; ++j){
                image3[i][j] = 255;
            }
        }


        for(int i = 0 ;i < SIZE;++i){
            for(int j = 0 ; j < 127 ; ++j){
                image2[i][j] = image[i][(int)(j*255)/127];
            }
        }


        for(int i = 0 ;i < SIZE;++i){
            for(int j = high ; j < high + left ; ++j){
                image3[j][i] = image2[i][j-(int)high];

            }
            high-= moving;
        }
    }
}

int main() {
    char key;
    cout << "hallo sir " << "\n";
    cout << "load image to start edit " << "\n";
    
    
    loadImage();
     cout << "choice from list  number of  fillter  or letter" << "\n";
    while (true) {
        cout << "7-: Detect Image Edges\n"
                "8- Enlarge Image\n"
                "9- Shrink Image \n"
                "a-  Mirror Image\n"
                "b-  Shuffle Image\n"
                "c-  Blur Image\n"
                "d- Crop Image\n"
                "e/f- Skew Horizontally / Vertically\n"
                "0- Exit" << "\n";
        cin >> key;
        if (key == '7') {
            loadImage();
            Detect_Image();
            saveimage();
        } else if (key == '8') {
            loadImage();
            Enlarge_Image();
            saveimage();
        } else if (key == '9') {
            loadImage2();
            Shrink();
            saveimage();
        } else if (key == 'a') {
            loadImage();
            Mirror_Image();
            saveimage();

        } else if (key == 'b') {
            loadImage();
            shuffle_Image();
            saveimage();

        } else if (key == 'c') {
            loadImage();
            Blur_Image();
            saveimage();

        } else if (key == 'd') {
            loadImage();
            cut_Image();
        } else if (key == 'e' || key == 'f') {
            loadImage();
            skew();
            saveimage();

        }
        else break;
    }

}