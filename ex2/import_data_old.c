#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*functions declerations*/
void free_lines_arr(char** lines,const int number_of_lines);
int import_stream_to_lines_arr(FILE* stream, char** lines, int* number_of_lines);

int main(int argc, char *argv[]){
  FILE* ptr_file=NULL;
  FILE* stream;
  char** lines;
  int i=0;
  int number_of_lines=0;


  /*this section need to be in main function*/
  if (argc == 2){
  ptr_file=fopen(argv[1],"r");
  if (ptr_file==NULL){
    fprintf(stderr,"file not exist\n");
    return 1;
  }
  stream=ptr_file;
  }
  
  else {
    stream=stdin;
  }
  /**********************************/

  import_stream_to_lines_arr(stream,lines,&number_of_lines);
  //DEBUG
  printf("number of lines is:%d\n", number_of_lines);
  printf("line %d: %s",0, lines[0]);
   
  for(i=0;i<number_of_lines; i++){
    printf("line %d: %s",i+1, lines[0]);
  }
  /*
  printf("enter free\n");
  free_lines_arr(lines,number_of_lines);
  */  
return 0;
}

void free_lines_arr(char** lines,int number_of_lines){
  int i=0;
  printf("enter free");
  for(i=0;i<number_of_lines; i++){
    free(lines[i]);
  }
  printf("exit free");
}

//lines and number_of_lines are uninitialized vars
int import_stream_to_lines_arr(FILE* stream, char** lines, int* number_of_lines){
  size_t size=10;
  int status=0;
  int i=0;
 

   lines = (char**)malloc(sizeof(char*));
   lines[0]=NULL;
   char* line;
   line=NULL;
   line= (char *)malloc(sizeof(char)*10);
   status=getline(&line,&size,stream);
   lines[0]=line;
   i=1;

   /*
  while(true){
    lines[i]=NULL;
    status=getline(&lines[i],&size,stream);
    if (status == EOF){
      //free extra line
      free(lines[i]);
      break;
    }

    printf("read from stream:%s\n",lines[i]);
    i++;
    lines=(char**)realloc(lines, sizeof(char*)*i);
    if (lines==NULL){
      fprintf(stderr,"realloc() failed\n");
      return 1;
    }
  }
   */

  *number_of_lines=i;
  //DEBUG:
  printf("number of lines is:%d\n",*number_of_lines);
  for(i=0;i<*number_of_lines; i++){
    printf("loop\n");
    printf("line %d: %s",i+1, lines[i]);
  }
  printf("end function\n");


  return 0;
}

