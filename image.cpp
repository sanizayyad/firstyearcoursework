#include "image.h"

Image::Image()
{

}
int Image::load(char *path)
{
    FILE* f = fopen(path, "r+b");
    if (!f)
        return 0;


    fread(&bfh, sizeof(bfh), 1, f);
    fread(&bih, sizeof(bih), 1, f);

    if (bfh.bfReserved1 != 0 ||
            (bih.biSize != 40 && bih.biSize != 108 && bih.biSize != 124) ||
            bih.biWidth < 1 || bih.biWidth > 10000 ||
            bih.biHeight < 1 || bih.biHeight > 10000 ||
            bih.biCompression != 0 ||
            bih.biBitCount != 24)
    {
        fclose(f);
        return 0;
    }

    is_load = true;
    size_t padding = (4 - (bih.biWidth * 3) % 4) % 4;
    max = bih.biHeight;
        if (max < bih.biWidth)
            max = bih.biWidth;

    picture = new PIXEL*[max];
    for (int i = 0; i < max; i++) {
         picture[i] = new PIXEL[max + 1];
    }

    fseek(f, static_cast<long>(bfh.bfOffBits), SEEK_SET);
       for (int i = 0; i < bih.biHeight; i++) {
           for (int j = 0; j < bih.biWidth; j++)
               fread(&picture[bih.biHeight - 1 - i][j], 3, 1, f);
           fread(&picture[bih.biHeight - 1 - i][bih.biWidth], padding, 1, f);
       }

       fclose(f);
   return 1;

}

int Image::save(const char *path)
{
    FILE* f;
    f = fopen(path, "w+b");
    fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, f);
    fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, f);

    size_t padding = (4 - (3 * bih.biWidth) % 4) % 4;
    fseek(f, static_cast<long>(bfh.bfOffBits), SEEK_SET);
    for (int i = 0; i < bih.biHeight; i++)
    {
        for (int j = 0; j < bih.biWidth; j++)
            fwrite(&picture[bih.biHeight - 1 - i][j], 1, 3, f);
        fwrite(&picture[bih.biHeight - 1 - i][bih.biWidth], padding, 1, f);
    }
    qDebug()<<"error save";


    fclose(f);
    return 1;
}

void Image::createNew()
{
    memset(&bih, 0, sizeof(bih));
    memset(&bfh, 0, sizeof(bfh));

    bih.biWidth = 600;
    bih.biHeight = 400;
    bih.biSize = sizeof(bih);
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bfh.bfOffBits = 14 + sizeof(bih);
    bfh.bfType = 0x4d42;
    bfh.bfSize = static_cast<DWORD>(54 + bih.biHeight * bih.biWidth);
    max = 750;

    picture = new PIXEL*[max];
    for (int i = 0; i < max; i++)
        picture[i] = new PIXEL[max];

    is_load =true;

    for (int i = 0; i < bih.biHeight; i++)
        for (int j = 0; j < bih.biWidth; j++)
        picture[i][j] = {255, 255, 255};
}

QPixmap Image::getPixmap()
{
    QImage pict(bih.biWidth, bih.biHeight, QImage::Format_RGB888);
    QPixmap pix;

    for (int i = 0; i < bih.biHeight; i++)
    {
        for (int j = 0; j < bih.biWidth; j++)
        {
            QColor tmp_clr(picture[i][j].r, picture[i][j].g, picture[i][j].b);
            pict.setPixel(j, i, tmp_clr.rgb());
        }
    }
    pix.convertFromImage(pict);

    return pix;
}

int Image::pictureHeight()
{
    return bih.biHeight;
}

int Image::pictureWidth()
{
    return bih.biWidth;
}

PIXEL **Image::getPixelsArr()
{
    return picture;
}

bool Image::isNull()
{
    return !is_load;
}

QString Image::info() const
{
    QString information;
    QString n = QString::number(static_cast<double>(bfh.bfSize) / 1048576, 'g', 3);
    information.sprintf("File format: .bmp\nFile resolution: %ld x %ld\n", bih.biWidth, bih.biHeight);
    information += "Size on disk: " + n + " Mb\n";
    information += "Bit count: " + QString::number(bih.biBitCount);
    return information;
}

int Image::save3(const char* file_name,int numX,int numY,int vertical,int horizontal)
{

    auto my_bin=bih;
    my_bin.biWidth=bih.biWidth/horizontal;
    my_bin.biHeight=bih.biHeight/vertical;

    size_t padding = 0;
    FILE *f = fopen(file_name, "w+b");

    if (!f)
        return -1;

    fwrite(&bfh, sizeof(bfh), 1, f);
    fwrite(&my_bin, static_cast<size_t>(bfh.bfOffBits - 14), 1, f);

    if ((my_bin.biWidth * 3) % 4)
        padding = 4 - (my_bin.biWidth * 3) % 4;

    fseek(f, static_cast<long>(bfh.bfOffBits), SEEK_SET);


    for(int i = 0; i < my_bin.biHeight ; i++) {
        int j;
        for (j = 0; j < my_bin.biWidth; j++){
            fwrite(&picture[my_bin.biHeight - 1 - i + my_bin.biHeight*numY][j+my_bin.biWidth*numX], sizeof(PIXEL), 1, f);
        }
        if (padding)
            fwrite(&picture[i][j+1], padding, 1, f);
       }



    fclose(f);
    return 0;
}


void Image:: createImages(const char *string, int vertical,int horizontal){

    int count = 1;


    for (int i=0;i<vertical;i++) {
        for (int j=0;j<horizontal;j++) {
            qDebug()<<"number of times"<<count;
            std::string str = string + std::to_string(count) + ".bmp";
            char* save_name = new char[str.length() + 1];
            strcpy(save_name, str.c_str());
            save3(save_name,j,i,vertical,horizontal);
            free(save_name);
            count++;

        }
    }

}

void Image::defense(const char *string, int vertical, int horizontal,int type)
{
    int count = 0;
    horizontal *=2;

    for (int i=0;i<vertical;i++) {
        for (int j=0;j<horizontal;j++) {
            qDebug()<<"number of times"<<count;
            std::string str = string + std::to_string(count) + ".bmp";
            char* save_name = new char[str.length() + 1];
            strcpy(save_name, str.c_str());
            defenseSave(save_name,j,i,vertical,horizontal,count);
            free(save_name);
            count++;

        }
    }
}

int Image::defenseSave(const char *file_name, int numX, int numY, int vertical, int horizontal,int type)
{
    auto my_bin=bih;
    my_bin.biWidth=bih.biWidth/horizontal;
    my_bin.biHeight=bih.biHeight/vertical;

    size_t padding = 0;
    FILE *f = fopen(file_name, "w+b");

    if (!f)
        return -1;

    fwrite(&bfh, sizeof(bfh), 1, f);
    fwrite(&my_bin, static_cast<size_t>(bfh.bfOffBits - 14), 1, f);

    if ((my_bin.biWidth * 3) % 4)
        padding = 4 - (my_bin.biWidth * 3) % 4;

    fseek(f, static_cast<long>(bfh.bfOffBits), SEEK_SET);

   if (type % 2 != 0){
       for(int y = 0; y < my_bin.biHeight ; y++) {
           float mainX = y * my_bin.biWidth/my_bin.biHeight;
           for (int x = 0; x < mainX; x++){
               drawPixel(my_bin.biHeight - 1 - y + my_bin.biHeight*numY,x+my_bin.biWidth*numX,QColor::fromRgb(255,255,255));
           }
       }
   }else{
       for(int y = 0; y < my_bin.biHeight ; y++) {
           float mainX = y*my_bin.biWidth/my_bin.biHeight;
           for (int x = 0; x < my_bin.biWidth; x++){
               if(x<mainX){
                   drawPixel(my_bin.biHeight - 1 - y + my_bin.biHeight*numY,x+my_bin.biWidth*numX,QColor::fromRgb(
                          picture[my_bin.biHeight - 1 - y + my_bin.biHeight*numY][x+my_bin.biWidth*numX].r,
                           picture[my_bin.biHeight - 1 - y + my_bin.biHeight*numY][x+my_bin.biWidth*numX].g,
                           picture[my_bin.biHeight - 1 - y + my_bin.biHeight*numY][x+my_bin.biWidth*numX].b));
               }else{
                   drawPixel(my_bin.biHeight - 1 - y + my_bin.biHeight*numY,x+my_bin.biWidth*numX,QColor::fromRgb(255,255,255));
               }
           }
       }

   }


    for(int i = 0; i < my_bin.biHeight ; i++) {
        int j;
        for (j = 0; j < my_bin.biWidth; j++){
            fwrite(&picture[my_bin.biHeight - 1 - i + my_bin.biHeight*numY][j+my_bin.biWidth*numX], sizeof(PIXEL), 1, f);
        }
        if (padding)
            fwrite(&picture[i][j+1], padding, 1, f);
       }






    fclose(f);
    return 0;
}
void Image::drawPixel(int y, int x, QColor currentLineColor)
{
    picture[y][x].r = static_cast<unsigned char>(currentLineColor.red());
    picture[y][x].g = static_cast<unsigned char>(currentLineColor.green());
    picture[y][x].b = static_cast<unsigned char>(currentLineColor.blue());
}
