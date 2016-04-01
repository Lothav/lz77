#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define LIMIT_BUFFER_SIZE 32768
#define SEARCH_BUFFER_SIZE 3
#define BYTE_SIZE 1

typedef struct{
    int pos;
    char *buffer;
}Buffer;

typedef struct{
    int pos;
    char output[];
}Output;

Buffer* setBuffer(){
    Buffer* buffer = NULL;
    buffer = (Buffer *) malloc(sizeof(Buffer));
    buffer->pos = 0;
    buffer->buffer = (char *)malloc(LIMIT_BUFFER_SIZE + SEARCH_BUFFER_SIZE + BYTE_SIZE);
    return buffer;
}

Output* setOutput(){
    Output* output = NULL;
    output = (Output *) malloc(sizeof(Output));
    output->pos = 0;
    output->output[0] = (char)malloc(1);
    return output;
}

long getFileLength(FILE* file_in){

    long file_length;

    if (fseek( file_in, 0, SEEK_END ) != 0) {
        fclose( file_in );
        return 0;
    }
    file_length = ftell(file_in);
    rewind(file_in);
    return file_length;
}

void updateSearchBuffer(char* search_buffer, char char_read){
    search_buffer[0] = search_buffer[1];
    search_buffer[1] = search_buffer[2];
    search_buffer[2] = char_read;
}

int main(int argc, char** argv) {

    FILE* file_in = NULL;
    Buffer* buffer = NULL;
    Output* output = NULL;

    long file_length;
    char* search_buffer;
    char* char_read;

    file_in = fopen(argv[1],"r");
    file_length = getFileLength(file_in);
    if(!file_length)
        return (EXIT_FAILURE);

    setvbuf(file_in, NULL, _IOFBF, (size_t)file_length);

    buffer = setBuffer();
    output = setOutput();

    search_buffer = (char*) malloc(sizeof(SEARCH_BUFFER_SIZE));
    char_read = (char*) malloc(BYTE_SIZE);

    fread(search_buffer, BYTE_SIZE, (size_t)(SEARCH_BUFFER_SIZE), file_in);
    strcpy(buffer->buffer, search_buffer);
    buffer->pos = SEARCH_BUFFER_SIZE;

    for(int c = 0; c < file_length; c++){
        fread(char_read, BYTE_SIZE, (size_t)(BYTE_SIZE), file_in);
        updateSearchBuffer(search_buffer,*char_read);
        strcat(buffer->buffer, char_read);
        buffer->pos += BYTE_SIZE;
    }

    /*for(c = 0; c < filelen; c++){
        for (int i = 7; i >= 0; --i){
            printf("%c", (buffer[c] & (1 << i)) ? '1' : '0' );
        }
    }*/

    fclose(file_in);
    return (EXIT_SUCCESS);
}