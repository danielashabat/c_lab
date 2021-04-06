#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*functions declerations*/
void free_lines_arr(char** lines,const int number_of_lines);
int import_stream_to_lines_arr(FILE* stream, char*** lines, int* number_of_lines);

int main(int argc, char *argv[]){
  FILE* stream=NULL;
  char** lines=NULL;
  int i=0;
  int number_of_lines=0;


  /*this section need to be in main function*/
  if (argc == 2){
    stream=fopen(argv[1],"r");
    if (stream==NULL){
       fprintf(stderr,"file not exist\n");
        return 1;
    }
  }
  else {
    stream=stdin;
  }
  /**********************************/

  import_stream_to_lines_arr(stream,&lines,&number_of_lines);
  //DEBUG
  printf("number of lines is: %d\n",number_of_lines);
  for(i=0;i<number_of_lines; i++){
    printf("line %d: %s",i+1, lines[i]);
  }

  free_lines_arr(lines,number_of_lines);
  return 0;
}

void free_lines_arr(char** lines,int number_of_lines){
  int i=0;
  for(i=0;i<number_of_lines; i++){
    free(lines[i]);
  }
}

//lines and number_of_lines are uninitialized vars
int import_stream_to_lines_arr(FILE* stream, char*** lines, int* number_of_lines){
  size_t size=10;
  int status=0;
  int i=0;
  char** array=NULL;
 

   array = (char**)malloc(sizeof(char*));
  
  while(true){
    array[i]=NULL;
    status=getline(&array[i],&size,stream);
    if (status == EOF){
      //free extra line
      free(lines[i]);
      break;
    }

    printf("read from stream:%s\n",array[i]);
    i++;
    array =(char**)realloc(array, sizeof(char*)*(i+1));
    if (array==NULL){
      fprintf(stderr,"realloc() failed\n");
      return 1;
    }
  }
  
  *lines=array;
  *number_of_lines=i;
  return 0;
}

