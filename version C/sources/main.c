#include "stdafx.h"
#include "print_msg.h"
#include "myfunc.h"
#include "rc4.h"

#define LINE_LEN 1024

/* Modes available */
typedef enum {
	CIPHER,
	DECIPHER
} MODE;

/* Help menu */
void print_help()
{
	printf("Usage: rc4.exe -m <mode> -i <input file> -o <output file> -k <crypt key> [-h]\n"\
	"-m                    Mode \"cipher\" (default) or \"decipher\"\n"\
	"-i <input file>       Full path to input file\n"\
    "-o <output file>      Full path to output file\n"\
    "-k <crypt key>        Crypt key\n"\
    "-h                    Display this help and exit\n");
}

int main(int argc, char * argv[])
{
    int i, c, len, f_len;
	MODE mode;
	char line[LINE_LEN];
    unsigned char *key, *input, *output;	
	char *inputFile, *outputFile;
	FILE *fd1, *fd2;

	/* Init */
	mode = CIPHER;
	i = c = len = f_len = 0;
	key =  input = output = NULL;
	inputFile = outputFile = NULL;
	fd1 = fd2 = NULL;
	
	/* Read parameters */
	for(i = 1; i < argc; i++)
	{
		if(!strcmp(argv[i], "-i")){
			if(i >= argc-1)
				break;
			inputFile = argv[++i];
		}
		else if(!strcmp(argv[i], "-o")){
			if(i >= argc - 1)
				break;
			outputFile = argv[++i];
		}else if(!strcmp(argv[i], "-k")){
			if(i >= argc - 1)
				break;
			key = argv[++i];
		}
		else if(!strcmp(argv[i], "-m")){
			if(i >= argc - 1)
				break;
			if (!strcmp(argv[++i], "decipher"))
				mode = DECIPHER;
			else
				mode = CIPHER;
		}		
		else if(!strcmp(argv[i], "-h")){
			print_help();
			return -1;
		}else{
			print_msg(LOG_LEVEL_ERROR, "Invalid option \"%s\"", argv[i]);
			print_help();
			return -1;
		}

	}

	/* check parameters */
	if ((inputFile == NULL) || (outputFile == NULL) || (key == NULL))
	{
		print_msg(LOG_LEVEL_ERROR, "Missing required option");
		print_help();
		return -1;
	}
	
	/* open input file */
	if ((fd1 = fopen(inputFile, "rb")) == NULL){
		print_msg(LOG_LEVEL_ERROR, "Failed to open input file");
		goto exit;
	}
	
	/* open output file */
	if ((fd2 = fopen(outputFile, "wb")) == NULL){
		print_msg(LOG_LEVEL_ERROR, "Failed to open output file");
		goto exit;
	}

	/* read input file */
	if (mode == DECIPHER)
	{
		fseek(fd1, 0, SEEK_END);
		f_len = ftell(fd1) / 2;
		fseek(fd1, SEEK_SET, 0);
		input = (char *) malloc(sizeof(unsigned char) * f_len + 1);
		if (input == NULL)
		{
				printf("error : memory allocation failed\n");
				goto exit;
		}		
		i = 0;
		while (fscanf(fd1, "%02X", &c) > 0 && i < f_len)
			input[i++] = (unsigned char) c;
		input[i] = '\0';
	}
	else
	{
		input = (char *) calloc(1,1);
		if (input == NULL)
		{
				printf("error : memory allocation failed\n");
				goto exit;
		}		
		while (fgets(line, LINE_LEN, fd1) != NULL)
		{
			input = (char *) realloc(input, strlen(input) + strlen(line) + 1);
			if (input == NULL)
			{
				printf("error : memory allocation failed\n");
				goto exit;
			}
			strcat(input, line);
		}
	}
	len = strlen(input);
	input[len] = '\0';
	
	/* allocation for the output buffer */
	output = (char *) malloc(len + 1);
	if (output == NULL)
	{
		printf("error : memory allocation failed\n");
		goto exit;
	}
	memset(output, 0, len + 1);

	/* RC4 */
	rc4(key, input, output);
	
	/* write in the output file */
	if (mode == DECIPHER)
		fprintf(fd2, output);
	else
	{
		for(i = 0; i < len; i++)
		{
			if (output[i] < 16)
				fprintf(fd2, "0%X", output[i]);
			else
				fprintf(fd2, "%X", output[i]);
		}	
	}
	
exit:
	if (fd1 != NULL)
		fclose(fd1);
	if (fd2 != NULL)
		fclose(fd2);
	if (input != NULL)
	{
		memset(input, 0, len + 1);
		free(input);
		input = NULL;
	}
	if (output != NULL)
	{
		memset(output, 0, len + 1);
		free(output);
		output = NULL;
	}
	memset(line, 0, LINE_LEN);
	i = c = len = f_len = mode = 0;
    return 0;	
}
