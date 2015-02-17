#include <stdio.h>

void open_file(char * filename)
{
 FILE *fp;
 printf("%s\n",filename );
 fp = fopen(filename, "r");
 char username[9];  /* One extra for nul char. */
 while (fscanf(fp, "%s", username) != EOF) {
  if (username == '\n')
    printf("%s\n" );
  printf( "%s ", username);
}
char line[100];
    /* assume line is a char array */
    while (fgets(line, sizeof line, fp)) {
        size_t len = strlen(line); 
        printf("%s\n",line[len] );
        if (len && (line[len - 1] != '\n')) {
            /* incomplete line */
        }
        /* possibly remove trailing newline ... and */
        /* deal with line */
    }

 

}


main(int argc, char *argv[])
{
  open_file(argv[1]);



}