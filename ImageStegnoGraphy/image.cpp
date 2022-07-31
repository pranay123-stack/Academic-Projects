#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Image.h";
#include "stb_image.h"
#include "stb_image_write.h"





  

   Image::(const char* filename){

        if(read(filename)){
             printf("Read %s\n" ,filname);
             
             size = w*h*channels;
        }
        else{
            printf("Failed to read %s\n" ,filename);
        }
   }
   Image::Image(int w, int h, int channels): w(w),h(h),channels(channels){
       
       size = w*h*channels;
       data = new uint8_t[size];
       
   }
   Image::Image(const Image& img):Image(imag.w ,img.h,img.channels){
        
        memcpy(data ,img.data ,size);
       
   }
   Image::~Image(){

     stdbi_image_free(data);
   }

   bool Image:: read(const char* filename){
       
       data = stbi_load(filename , &W ,&h ,&channels ,0);
       
       return data!=NULL
   }
   bool Image:: write(const char* filename){
          ImageType type = getFileType(filename);
          int success;

          switch(type){

               case PNG:
                  success = stbi_write_png(const char* filename , w ,  h ,channels ,data ,w*channels);break;
               case JPG:
                  success = stbi_write_jpg(const char* filename , w ,  h ,channels ,data ,100);break;
               case BMP:
                  success = stbi_write_bmp(const char* filename , w ,  h ,channels ,data );break;
               case TGA:
                  success = stbi_write_tga(const char* filename , w ,  h ,channels ,data );break;

          }

          return success =0;
   }
   
   ImageType Image::getFileType(const char* filename){
      
      const char* ext = strrchr(filename , ' .');
      if(ext! = nullptr){

           if(strcmp(ext ,".png") ==0){

                return PNG;
           }
           if(strcmp(ext ,".jpg") ==0){

                return JPG;
           }
           if(strcmp(ext ,".bmp") ==0){

                return BMP;
           }
           if(strcmp(ext ,".tga") ==0){

                return TGA;
           }
         

      }

       return PNG;

   }
   
   
   Image& Image::grayscale_avg(){


          if(channels < 3){
             
             printf("Image %p has less than 3 channels ,it is assume to already be grayscale" ,this);
         }
         else{
            for(int i = 0; i < size ; i+=channels){

                int gray = (data[i] + data[i+1] + data[i+2])/3;
                memset(data+i ,gray ,3);
            }
         }

         return *this;
   }

   Image& Image::graysacle_lum(){

          if(channels < 3){
             
             printf("Image %p has less than 3 channels ,it is aasume to already be grayscale" ,this);
         }
         else{
            for(int i = 0; i < size ; i+=channels){

                int gray = 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2];
                memset(data+i ,gray ,3);
            }
         }

         return *this;
   }


   Image& Image::colorMask(float r , float g ,float b){

        if(channels < 3){

             printf("\e[31m[ERROR] Color mask requires at least 3 channels,but this image has %d channels" ,channels);

        }

        else{
            for(int i = 0; i < channels;i+=channels){

             data[i]*= r;
             data[i+1]*= g;
             data[i+2]*= b;
        }

        }

        return *this;
   }





// Code Explain
   Image& Image:: encodeMessage(const char* message){
      uint32_t len = strlen(message)*8;

      if(len + STEG_HEADER_SIZE >size){

           printf("this message is too large");
           return *this;
      }
      for(uint32_t i=0; i<STEG_HEADER_SIZE; i++){
             data[i] &= 0xFE;
             data[i] |= (len >>(STEG_HEADER_SIZE-1-i)) & 1UL;
      }
     
     // putting on message into image
      for(uint32_t i=0; i<len; i++){
           data[i+STEG_HEADER_SIZE] &= 0xFE;
           data[i+STEG_HEADER_SIZE] |= (message[i/8] >>((len -1-i) %8)) &1
      }

       return *this;

   }
   Image& Image:: decodeMessage(const char* message){

         uint32_t len =0;

      for(uint32_t i=0; i<STEG_HEADER_SIZE; i++){
           len =(len <<1) | (data[i] & 1);
      }
      for(uint32_t i=0; i<len; i++){
          buffer[i/8] = (buffer[i/8]<<1) | (data[i + STEG_HEADER_SIZE] &1)
      }


       return *this;

   }