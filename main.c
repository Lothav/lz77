#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define LIMIT_BUFFER_SIZE 32768
#define SEARCH_BUFFER_SIZE 3
#define BYTE_SIZE 1

typedef struct{
    int start;
    int end;
    char *buffer;
}Buffer;

Buffer* setBuffer(){
    Buffer* buffer = NULL;
    buffer = (Buffer *) malloc(sizeof(Buffer));
    buffer->buffer = (char *)malloc(LIMIT_BUFFER_SIZE + SEARCH_BUFFER_SIZE + BYTE_SIZE);
    return buffer;
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

void moveBuffersOne2Rigth(Buffer* buffer, char *search_buffer, char *char_read){
    updateSearchBuffer(search_buffer,*char_read);
    strcat(buffer->buffer, char_read);
    buffer->end += BYTE_SIZE;
    if(buffer->end > LIMIT_BUFFER_SIZE) buffer->start += BYTE_SIZE;
}

int main(int argc, char** argv) {

    FILE* file_in = NULL;
    Buffer* buffer = NULL;

    long file_length;
    char* search_buffer;
    char* char_read;

    file_in = fopen(argv[1],"r");
    file_length = getFileLength(file_in);
    if(!file_length)
        return (EXIT_FAILURE);

    setvbuf(file_in, NULL, _IOFBF, (size_t)file_length);

    buffer = setBuffer();

    search_buffer = (char*) malloc(sizeof(SEARCH_BUFFER_SIZE));
    char_read = (char*) malloc(BYTE_SIZE);

    fread(search_buffer, BYTE_SIZE, (size_t)(SEARCH_BUFFER_SIZE), file_in);
    strcpy(buffer->buffer, search_buffer);
    buffer->start = 0;
    buffer->end = SEARCH_BUFFER_SIZE;

    while(fread(char_read, BYTE_SIZE, (size_t)(BYTE_SIZE), file_in)){

        moveBuffersOne2Rigth(buffer,search_buffer,char_read);

        // O c será o delimitador do Search Buffer
        for(int c = buffer->start; c < buffer->end; c++){


        }
    }

    /*for(c = 0; c < filelen; c++){
        for (int i = 7; i >= 0; --i){
            printf("%c", (buffer[c] & (1 << i)) ? '1' : '0' );
        }
    }*/

    fclose(file_in);
    return (EXIT_SUCCESS);
}