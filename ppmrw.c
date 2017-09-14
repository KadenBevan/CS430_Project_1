#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Pixel {
  unsigned char r, g, b;
}Pixel;

typedef struct Header{
	char *magic_num;
	int height;
	int width;
	int max_num;
	Pixel *data;
}header;

int p3_p6(FILE*, FILE*);
int p6_p3(FILE*, FILE*);

/*
 * Function:  p3_p6 
 * --------------------
 * Converts a P3 (.ppm) file into a P6 (.ppm) file
 *
 * Args:
 *  input_file: P3 .ppm file
 *	output_file: P6 .ppm file
 *
 *
 *  returns:
 *          returns -1 on error.
 *
 *  Output: 
 *			P6 .ppm file with the name specified in commandline argument.
 *			Error message on error.
 *			 
 */

int p3_p6(FILE* input_file, FILE* output_file){
	printf("Parsing input...\n");
	int line_num = 0;
	char line[256], tmp_width[256]= "", tmp_height[256]= "", tmp_max[256]= "";
	char magic_num[3];
	header ppm_header;
	int field = 1;
	// If the ppm file does not start with P6 or P3
	fgets(line, 256, input_file);
	// If the file is already in P6 format.
	if(line[0] == 'P' && line[1] == '6'){
		printf("HEADER ERROR: The file you have provided is already in P6 .ppm format.\n");
		return 0;
	}
	if(line[0] != 'P' || line[1] != '3'){
		printf("HEADER ERROR: Please check the header in the input file.\n");	
		return -1;
	}
	// Magic number correct
	else{
		// grab the header
		if(field == 1){
			ppm_header.magic_num = malloc(3);
			sprintf(magic_num, "%c%c", line[0], line[1]);
			strcpy(ppm_header.magic_num, magic_num);
			fprintf(output_file, "P6\n");
			free(ppm_header.magic_num);
			field++;
		}
		int i = 2;
		int header_lines=0;
		while(i < strlen(line)){
			if(isdigit(line[i])){
				while(isdigit(line[i])){
					if(field == 2){
						tmp_width[strlen(tmp_width)] = line[i];
					}
					if(field == 3){
						tmp_height[strlen(tmp_height)] = line[i];
					}
					if(field == 4){
						tmp_max[strlen(tmp_max)] = line[i];
					}
					i++;
				}
				field++;
			}
			// eat a character if it is a space
			if(line[i] == ' '){
				i++;
				continue;
			}
			// if its a newline or comment go to the next line.
			if(line[i] == '\n' || line[i] == '#'){
				fgets(line, 256, input_file);
				header_lines++;
				i=0;
				continue;
			}
			i++;
		}
		// Finish building string
		tmp_width[strlen(tmp_width)+1] = '\0';
		tmp_height[strlen(tmp_height)+1] = '\0';
		tmp_max[strlen(tmp_max)+1] = '\0';
		
		ppm_header.width = atoi(tmp_width);
		ppm_header.height = atoi(tmp_height);
		
		if(atoi(tmp_max) != 255){
			printf("ERROR: 8 bit per channel required. See README.md for help.\n");
			return -1;
		}
		else{
			printf("Writing output...\n");
			ppm_header.max_num = atoi(tmp_max);
			ppm_header.data = (Pixel *)malloc(sizeof(Pixel) * ppm_header.width * ppm_header.height);
			fprintf(output_file, "%u %u\n%u\n", ppm_header.width, ppm_header.height, ppm_header.max_num);
			//read the image into the buffer
			fread(ppm_header.data, sizeof(Pixel), ppm_header.width * ppm_header.height, input_file);
			for (i = 0; i < ppm_header.width * ppm_header.height; i++){
				int c_byte;
				fscanf(input_file, "%d", &c_byte);
				ppm_header.data[i].r = c_byte;
				fscanf(input_file, "%d", &c_byte);
				ppm_header.data[i].g = c_byte;
				fscanf(input_file, "%d", &c_byte);
				ppm_header.data[i].b = c_byte;

			}
			//write the binary out
			
			fwrite(ppm_header.data, 3*ppm_header.width, ppm_header.height, output_file);
			fclose(output_file);
			free(ppm_header.data);
			return 0;
		}
	}
}
/*
 * Function:  p6_p3 
 * --------------------
 * Converts a P6 (.ppm) file into a P3 (.ppm) file
 *
 *	Args:
 *  		input_file: P6 .ppm file
 *			output_file: P3 .ppm file
 *
 *
 *  returns:
 *          returns -1 on error.
 *
 *  Output: 
 *			P3 .ppm file with the name specified in commandline argument.
 *			Error message on error.
 *			 
 */
 
int p6_p3(FILE* input_file, FILE* output_file){
	printf("Parsing input...\n");
	int line_num = 0;
	char line[256], tmp_width[256]="", tmp_height[256]="", tmp_max[256]="";
	char magic_num[3];
	int data_count = 0;
	header ppm_header;
	int field = 1;
	// If the ppm file does not start with P6 or P3
	fgets(line, 256, input_file);
	if(line[0] == 'P' && line[1] == '3'){
		printf("HEADER ERROR: The file you have provided is already in P3 .ppm format.\n");
		return 0;
	}
	if(line[0] != 'P' || line[1] != '6'){
		printf("HEADER ERROR: Please check the header in the input file.\n");	
		return -1;
	}
	else{
		// grab the header
		if(field == 1){
			ppm_header.magic_num = malloc(3);
			sprintf(magic_num, "%c%c", line[0], line[1]);
			strcpy(ppm_header.magic_num, magic_num);
			fprintf(output_file, "P3\n");
			free(ppm_header.magic_num);
			field++;
		}
		int i = 2;
		int header_lines=0;
		while(i < strlen(line)){
			if(isdigit(line[i])){
				while(isdigit(line[i])){
					if(field == 2){
						tmp_width[strlen(tmp_width)] = line[i];
					}
					if(field == 3){
						tmp_height[strlen(tmp_height)] = line[i];
					}
					if(field == 4){
						tmp_max[strlen(tmp_max)] = line[i];
					}
					i++;
				}
				field++;
			}
			// eat a character if it is a space
			if(line[i] == ' '){
				i++;
				continue;
			}
			// if its a newline or comment go to the next line.
			if(line[i] == '\n' || line[i] == '#'){
				fgets(line, 256, input_file);
				header_lines++;
				i=0;
				continue;
			}
			i++;
		}
		// Finish building string
		tmp_width[strlen(tmp_width)+1] = '\0';
		tmp_height[strlen(tmp_height)+1] = '\0';
		tmp_max[strlen(tmp_max)+1] = '\0';
		ppm_header.width = atoi(tmp_width);
		ppm_header.height = atoi(tmp_height);
		// not 8 bit color
		if(atoi(tmp_max) != 255){
			printf("ERROR: 8 bit per channel required. See README.md for help.\n");
			return -1;
		}
		else{
			printf("Writing output...\n");
			ppm_header.max_num = atoi(tmp_max);
			// allocate memory for data.
			ppm_header.data = (Pixel *)malloc(sizeof(Pixel) * 10 * ppm_header.width * ppm_header.height);
			// output header
			fprintf(output_file, "%u %u\n%u\n", ppm_header.width, ppm_header.height, ppm_header.max_num);
			//read the image into the buffer
			fread(ppm_header.data, sizeof(Pixel), ppm_header.width * ppm_header.height, input_file);
			int counter = 1;
			for (i = 0; i < ppm_header.width * ppm_header.height; i++){
				fprintf(output_file, "%d %d %d ", ppm_header.data[i].r, ppm_header.data[i].g, ppm_header.data[i].b);

				// If the counter is at the end of the width of the ppm
				if(counter == ppm_header.width) {
					fprintf(output_file, "\n");
					counter = 1;
				}
				else counter += 1;
			}
		}
		free(ppm_header.data);
		return 0;
	}
}

/*
 * Function:  main 
 * --------------------
 * Calls the appropriate conversion method based on users input.
 *
 * Args:
 *  	Commandline:
 *			Arg[1]: Type of output ppm file (3 or 6)
 *			Arg[2]: Name of existing ppm file. Must be .ppm
 *			Arg[3]: Name of file for output. Must be .ppm.
 *
 *
 *  returns:
 *          returns -1 on error.
 *
 *  Output: 
 * 			Error message on error.
 *			
 * 
 */
 
int main(int argc, char *argv[]){
	FILE *output_file = fopen(argv[3], "wb");
	FILE *input_file = fopen(argv[2], "rb");
  	// Check for correct number of arguments
	if(argc != 4){
		// ERROR: This program takes 3 and only 3 arguments.
		// Close Files
		printf("ERROR: The amount of arguments passed does not reflect usage.\nSee README.md for help.\n");
		fclose(output_file);
		fclose(input_file);
		return -1;
	}
	// Check for correct file types
	if(strstr(argv[2], ".ppm") == NULL || strstr(argv[3], ".ppm") == NULL){
		// Input file is the correct file type. Continue as normal.
		fclose(output_file);
		fclose(input_file);
		printf("ERROR: One or both of the files passed in is not .ppm format.\nSee README.md for help.\n");
		return -1;
	}
	// Call correct write function
	if( (strcmp(argv[1], "6") == 0) || (strcmp(argv[1], "3") == 0) ){
		if(strcmp(argv[1], "6") == 0){
			// write P3 --> P6  
			if(p3_p6(input_file, output_file) == 0){
				printf("Done!\n");
			}
		}
		if(strcmp(argv[1], "3") == 0){
			// write P6 --> P3
			if(p6_p3(input_file, output_file) == 0){
				printf("Done!\n");
			}
		}
	}
	else{
		// ERROR: This program is only set up to convert P6 --> P3 or vice-versa.
		// Close Files
		printf("ERROR: This program is only set up to convert P6 --> P3 or vice-versa.\nCheck the first argument or see README.md for help.\n");
		fclose(input_file);
		fclose(output_file);
		return -1;
	}
	
	fclose(input_file);
	fclose(output_file);
}