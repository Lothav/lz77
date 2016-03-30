#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    FILE *file_in, *file_out;
   
    char *buffer;
    long filelen;
    int c;
    
    file_in = fopen(argv[1],"r");

    
    if (fseek( file_in, 0, SEEK_END ) != 0) {                                 
        fclose( file_in );
        return 0;
    }
    filelen = ftell(file_in);
    rewind(file_in);
    
    buffer = (char *)malloc((filelen+1)*sizeof(char)); 
    fread(buffer, filelen+1, 1, file_in); 
    
    for(c = 0; c < filelen; c++){
        for (int i = 7; i >= 0; --i){
            printf("%c", (buffer[c] & (1 << i)) ? '1' : '0' );
        }
    }
    
    fclose(file_in);
    
    return (EXIT_SUCCESS);
}