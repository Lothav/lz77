#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define LIMIT_BUFFER_SIZE 32768
#define SEARCH_BUFFER_SIZE 3
#define BYTE_SIZE 1
#define START_INDEX 0

typedef struct{
    int start;
    int end;
    char *buffer;
}Buffer;

Buffer* setFileBuffer(){
    Buffer* file_buffer = NULL;
    file_buffer = (Buffer *) malloc(sizeof(Buffer));
    file_buffer->buffer = (char *)malloc(LIMIT_BUFFER_SIZE + SEARCH_BUFFER_SIZE);
    file_buffer->start = START_INDEX;
    file_buffer->end = SEARCH_BUFFER_SIZE;
    return file_buffer;
}

long getFileLength(FILE* file_in){

    long file_length;

    if (fseek( file_in, START_INDEX, SEEK_END )) {
        fclose( file_in );
        return 0;
    }
    file_length = ftell(file_in);
    rewind(file_in);
    return file_length;
}

void pointersWalk(Buffer *file_buffer){
    file_buffer->end += BYTE_SIZE;
    file_buffer->end = file_buffer->end % LIMIT_BUFFER_SIZE;

    if(!(file_buffer->start - file_buffer->end)){
        file_buffer->start += BYTE_SIZE;
        file_buffer->start = file_buffer->start % LIMIT_BUFFER_SIZE;
    }
}

/**
 *    Walks 'File Buffer' and 'Search Buffer' 1 byte to Right
 * */
void buffersWalk(Buffer* file_buffer, char *search_buffer, char *char_read){

    // walk search buffer simple way
    search_buffer[0] = search_buffer[1];
    search_buffer[1] = search_buffer[2];
    search_buffer[2] = *char_read;

    // walk file buffer mod LIMIT_BUFFER_SIZE
    pointersWalk(file_buffer);

    file_buffer->buffer[file_buffer->end] = *char_read;
}

int main(int argc, char** argv) {

    FILE* file_in = NULL;
    Buffer* file_buffer = NULL;

    long file_length;
    char* search_buffer = NULL;
    char* char_read = NULL;

    file_in = fopen(argv[1],"r");
    file_length = getFileLength(file_in);
    if(!file_length)
        return (EXIT_FAILURE);

    setvbuf(file_in, NULL, _IOFBF, (size_t)file_length);
    file_buffer = setFileBuffer();

    char_read = (char*) malloc(BYTE_SIZE);

    // get first 3 chars to Search Buffer
    search_buffer = (char*) malloc(sizeof(SEARCH_BUFFER_SIZE));
    fread(search_buffer, BYTE_SIZE, (size_t)(SEARCH_BUFFER_SIZE), file_in);

    // set first 3 charts to File Buffer
    strcpy(file_buffer->buffer, search_buffer);

    // loop while != EOF
    while(fread(char_read, BYTE_SIZE, (size_t)(BYTE_SIZE), file_in)){

        buffersWalk(file_buffer, search_buffer, char_read);

        // 'c' is  the delimiter of File Buffer
        for(int c = file_buffer->start; c != file_buffer->end; (c%LIMIT_BUFFER_SIZE)++){

            if(search_buffer[START_INDEX] == file_buffer->buffer[c]){

            }

            for(int sb = START_INDEX; sb < SEARCH_BUFFER_SIZE; sb++){
                // compare brute force chars buffers

            }


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