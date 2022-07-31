#include<cstdio>
#include <stdint.h>
#define STEG_HEADER_SIZE sizeof(uint32_t)*8;

enum ImageType{
  
  PNG ,JPG ,BMP ,TGA
};


struct Image{
   
   uint8_t *data = NULL;
   size_t size =0;

   int w;
   int h;
   int channels;//how many color value per pixel //RGB -3 ,RGBA -4

   Image(const char* filename);
   Image(int w, int h, int channels);
   Image(const Image& img);
   ~Image(){



   bool read(const char* filename);
   bool  write(const char* filename);
         
   ImageType getFileType(const char* filename);

   Image& Image::grayscale_avg();
   Image& Image::grayscale_lum();

   Image& colorMask(float r ,float g ,float b);

   Image& encodeMessage(const char* message);
   Image& decodeMessage(const char* message);
};

  
   



