#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pixel {
  unsigned char r, g, b;
}Pixel;

typedef struct Image {
  int width, height;
}Image;


int p3_p6(FILE* input_file, FILE* output_file){

}
int p6_p3(FILE* input_file, FILE* output_file){
	char *buffer, *fh;
	fh = (char*)malloc(sizeof(char) * 256);
	fh = fgets(buffer, 256, input_file);
	// If the file is empty
	if(fh == NULL){
		// ERROR: File is empty.
		printf("ERROR");
	}
	// If the ppm file does not start with P6
	// If the magic number is not correct.
	if(buffer[0] != 'P' || buffer[1] != '6'){
		// Still output the correct magic number.
		// Let the user know that their file might be bad.
		fprintf(output_file, "P3\n");
		printf("ERROR");
	}
	else{
		// remove the magic number from buffer and output it to the new file.
		*(buffer+=2);
		fprintf(output_file, "P3\n");
		//printf("%c", buffer[0]);
		if(){
			*(buffer += 1);
			printf("didnt crash");
			//buffer+=1;
		}
		//while(n == ' ' || n == '\n'){
		//	//buffer += 1;
		//	printf("wtf");
		//}
		//while(getc(buffer) == '\n'){
		//	buffer++;
		//}
		printf("%c", buffer[0]);
	}
}
int main(int argc, char *argv[]){
	FILE *output_file = fopen(argv[3], "wb");
	FILE *input_file = fopen(argv[2], "rb");
  
	char fh[256];
	// Check for correct number of arguments
	if(argc != 4){
		// ERROR: This program takes 3 and only 3 arguments.
		// Close Files
		printf("ERROR. 1");
		fclose(output_file);
		fclose(input_file);
		return -1;
	}
	else{
		// Number of arguments is correct. Continue as normal.
		printf("Parsing Input.");
	}
	// Check for correct file types
	if(strstr(argv[2], ".ppm") != NULL){
		// Input file is the correct file type. Continue as normal.
		printf("..\n");
	}
	else{
		// ERROR: Not the correct filetype.
		// Close Files
		fclose(output_file);
		fclose(input_file);
		return -1;
	}
	
	// Call correct write function
	if( (strcmp(argv[1], "6") == 0) || (strcmp(argv[1], "3") == 0) ){
		if(strcmp(argv[1], "6") == 0){
			// write P3 --> P6  
			p3_p6(input_file, output_file);
		}
		if(strcmp(argv[1], "3") == 0){
			// write P6 --> P3
			p6_p3(input_file, output_file);
		}
	}
	else{
		// ERROR: This program is only set up to convert P6 --> P3 or vice-versa.
		// Close Files
		fclose(input_file);
		fclose(output_file);
		return -1;
	}
	fclose(input_file);
	fclose(output_file);
}