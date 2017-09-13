#include <stdio.h>
#include <stdlib.h>

//represents a single pixel object
typedef struct Pixel {
  unsigned char r, g, b;
}Pixel;

//this struct is used to store the entire image data, along with the width and height
typedef struct Image {
  int width, height;
}Image;

int checkFile(char* file_in){
	FILE * file;
	file = fopen(file_in, "r");
	if (file){
	   fclose(file);
	   return 1;
	}
	else{
	   return 0;
	}
}

int p3_to_p6(char* in){
    FILE *src, *dest;
    char *outputFilename;
    char magicNumber[3];
    int height, width, depth;
    unsigned char red, green, blue;
	char c;
    int i, j, widthCounter = 1;

    if (!checkFile(in))
    {
        printf("FILE ERROR!");
        return -1;
    }
    else
        src = fopen(in, "r");
	//while((c = fgetc(src)) != EOF) {
    //    if (c == 'b') {
    //        putchar(c);
    //    }
    //}
	fscanf(src, "%s", &magicNumber);
    if (strcmp(magicNumber, "P6") != 0){
		printf("NOT IN MAGIC NUM");
		printf("%s", magicNumber);
		fclose(src);
        return -1;
	}
	printf("%s", magicNumber);
	fclose(src);
}

int main(int argc, char* argv[]){
	//FILE *fh_out = fopen(argv[2]);
	p3_to_p6(argv[2]);
}