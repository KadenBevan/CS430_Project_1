#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void removeSpaces(char* source)
{
  char* in = source;
  char* j = source;
  while(*j != 0)
  {
    *in = *j++;
    if(*in != ' ')
      in++;
  }
  *in = 0;
}
int test(char *filename){
	char *source = NULL;
	FILE *fp = fopen(filename, "r");
	char *magic_number;
	// File open error check
	if (fp != NULL) {
		if (fseek(fp, 0L, SEEK_END) == 0) {
			long bufsize = ftell(fp);
			// File is empty
			if (bufsize == -1) { 
				return -1;
			}
			// allocate buffer memory
			source = malloc(sizeof(char) * (bufsize + 1));
			if (fseek(fp, 0L, SEEK_SET) != 0) {
				return -1;
			}
			
			size_t newLen = fread(source, sizeof(char), bufsize, fp);
			if ( ferror( fp ) != 0 ) {
				fputs("Error reading file", stderr);
			} 
			else {
				source[newLen++] = '\0';
			}
		}
		fclose(fp);
	}
	//printf("%s\n", source);
	//removeSpaces(source);
	//printf("%c\n", source[0]);
	//magic_number = malloc(strlen(source[0])+1);
	//printf("%s", magic_number);
	if(source[0] != 'P' || source[1] != '6'){
		if(source[1] != '3')
		{
			//ERROR
			printf("ERROR");
		}
	}
	else{
		printf("ALL GOOD!");	
	}
	free(source); /* Don't forget to call free() later! */
}
int p3_p6(char *filename){
	char * buffer = 0;
	long length;
	FILE * fh = fopen (filename, "rb");
	if (fh){
		fseek(fh, 0, SEEK_END);
		length = ftell(fh);
		fseek(fh, 0, SEEK_SET);
		buffer = malloc(length);
		if (buffer)
		{
			fread(buffer, 1, length, fh);
		}
		fclose(fh);
	}
	if (buffer)
	{
		//P6 --> P3
		printf("%s\n", buffer);
		printf("%d\n", length);
		removeSpaces(buffer);
		printf("%d\n", strlen(buffer));
		printf("%s\n", buffer);
	}
	//int x,y;
	//int width,height,red,green,blue;
    //
	//printf("P6\n");
	//printf("# created by Eric R. Weeks using a C program\n");
	//printf("%d %d\n",width,height);
	//printf("255\n");
    //
	///* Do this for the whole picture now */
	//for (y = 0;y < height;y++)  {
	//	for (x = 0;x < width;x++)  {
    //
	//		fputc((char)red,stdout);
	//		fputc((char)green,stdout);
	//		fputc((char)blue,stdout);
	//	}
	//}
}
int main(int argc, char* argv[]) {
	test(argv[2]);
}
