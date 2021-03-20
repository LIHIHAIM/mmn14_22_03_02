#include <ctype.h>
#include "bool.h"
#include "statmentType.h"

#define DIRECTIVE -1
#define LINE 81

static boolean isBlank(char *);
static void delComments(char *);
static int jumpLabel(char *,int);

/* getSenType(): This function get a line Assembly code and return which sentence type is the line:
 comment, blank (spaces), order or directive */
statType getStatType(char *line){
     int i = 0;

     if(isBlank(line) == TRUE) /* if the line is a blank one */
          return blank;
     delComments();
     if(isBlank(line) == TRUE)
          return comment;
     while(line[i] != '\0' && isspace(line[i]))
          i++;
     if((i = jumpLabel(i)) == DIRECTIVE) /* jumps over the optional label in the start of the sentence */
          return directive;
     return order;
}

/* isBlank(): This function return if the only characters in a characters array are spaces 
 (tabs, enters, vertical tabs etc.) */
static boolean isBlank(char *line){
     int i = 0;
     while(line[i] != '\0'){
          if(!isspace(line[i]))
               return FALSE;
          i++;
     }
     return TRUE;
}

/* delComments(): This function delets all the comments (in the form " ;comment ") 
 from a character array. The comment is from the character ';' untill the end of the line. */
static void delComments(char *line){
     int i = 0;
     while(line[i] != '\0' && line[i] != ';')
          i++;
     if(i+1 < LINE){
          line[i] = '\n';
          line[i+1] = '\0';
     }
     return;
}

/* jumpLabel(): Jumps to the index after the label (label is in the form " :lable ") */
static int jumpLabel(char *line, int i){
     char curr; 
     while(!isspace(curr = line[i]) && curr != '\0'){
          if(curr == '.') /* no label */
               return DIRECTIVE;
          /*if(curr == ':'){
               while((curr = line[i]) != '.'){
                    if(curr == '\0')
                         return 0;
                    i++;
               }
               return DIRECTIVE;
          }*/
          i++;
     }
     return 0;
}
