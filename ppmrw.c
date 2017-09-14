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

int p3_p6(FILE* input_file, FILE* output_file){
	int line_num = 0;
	char line[256], tmp_width[256]="", tmp_height[256]="", tmp_max[256]="";
	char magic_num[3];
	int data_count = 0;
	header ppm_header;
	int field = 1;
	// If the ppm file does not start with P6 or P3
	fgets(line, 256, input_file);
	if(line[0] != 'P'){
		if(line[1] != '3'){
			printf("ERROR");
		}		
		printf("ERROR");
	}
	else{
		// grab the header
		if(field == 1){
			ppm_header.magic_num = malloc(3);
			sprintf(magic_num, "%c%c", line[0], line[1]);
			strcpy(ppm_header.magic_num, magic_num);
			//printf(ppm_header.magic_num);
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
						// fill width;
						//printf("%c", line[i]);
					}
					if(field == 3){
						tmp_height[strlen(tmp_height)] = line[i];
						// fill height
						//printf("%c", line[i]);
					}
					if(field == 4){
						tmp_max[strlen(tmp_max)] = line[i];
						// fill max size
						//printf("%c", line[i]);
					}
					i++;
				}
				field++;
				//printf("\n");
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
				//printf("%s", line);
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
			printf("ERROR Not 8 bit color");
			return -1;
		}
		else{
			ppm_header.data = (Pixel *)malloc(sizeof(Pixel) * ppm_header.width * ppm_header.height);
			ppm_header.max_num = atoi(tmp_max);
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
			fwrite(ppm_header.data, 2 * ppm_header.width, ppm_header.height, output_file);
			return 0;
		}
		printf("%d\n", ppm_header.width);
		printf("%d\n", ppm_header.height);
		printf("%d\n", ppm_header.max_num);
	}	//parse_data(input_file);
}
int p6_p3(FILE* input_file, FILE* output_file){
	int line_num = 0;
	char line[256], tmp_width[256]="", tmp_height[256]="", tmp_max[256]="";
	char magic_num[3];
	int data_count = 0;
	header ppm_header;
	int field = 1;
	// If the ppm file does not start with P6 or P3
	fgets(line, 256, input_file);
	if(line[0] != 'P'){
		if(line[1] != '6' || line[1] != '3'){
			printf("ERROR");
		}		
		printf("ERROR");
	}
	else{
		// grab the header
		if(field == 1){
			ppm_header.magic_num = malloc(3);
			sprintf(magic_num, "%c%c", line[0], line[1]);
			strcpy(ppm_header.magic_num, magic_num);
			//printf(ppm_header.magic_num);
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
						// fill width;
						//printf("%c", line[i]);
					}
					if(field == 3){
						tmp_height[strlen(tmp_height)] = line[i];
						// fill height
						//printf("%c", line[i]);
					}
					if(field == 4){
						tmp_max[strlen(tmp_max)] = line[i];
						// fill max size
						//printf("%c", line[i]);
					}
					i++;
				}
				field++;
				//printf("\n");
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
				//printf("%s", line);
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
			printf("ERROR Not 8 bit color");
			return -1;
		}
		else{
			ppm_header.data = (Pixel *)malloc(sizeof(Pixel) * ppm_header.width * ppm_header.height);
			ppm_header.max_num = atoi(tmp_max);
			fprintf(output_file, "%u %u\n%u\n", ppm_header.width, ppm_header.height, ppm_header.max_num);
			//read the image into the buffer
			fread(ppm_header.data, sizeof(Pixel), ppm_header.width * ppm_header.height, input_file);
			int counter = 1;
			//write out to the ascii file
			for (i = 0; i < ppm_header.width * ppm_header.height; i++){
				fprintf(output_file, "%d %d %d ", ppm_header.data[i].r, ppm_header.data[i].g, ppm_header.data[i].b);

				// If the counter is at the end of the width of the ppm
				if(counter == ppm_header.width) {
					fprintf(output_file, "\n");
					counter = 1;
				}
				else counter += 1;
			}
			return 0;
		}
		printf("%d\n", ppm_header.width);
		printf("%d\n", ppm_header.height);
		printf("%d\n", ppm_header.max_num);
	}	//parse_data(input_file);
}


int main(int argc, char *argv[]){
	FILE *output_file = fopen(argv[3], "wb");
	FILE *input_file = fopen(argv[2], "rb");
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