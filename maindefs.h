#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RW 4
#define CL 4

#define DBG  0
#define DBG1 0


static int matrix [ RW ][ CL ] = {
  { 1 , 2 , 3 , 4 } ,
  { 4 , 3 , 2 , 1 } ,
  { 1 , 2 , 3 , 4 } ,
  { 4 , 3 , 3 , 4 }
} ;

/*
static int matrix [ RW ][ CL ] = {
  { 1 , 2 , 2 , 4 } ,
  { 4 , 3 , 3 , 1 } ,
  { 1 , 2 , 2 , 4 } ,
  { 4 , 1 , 3 , 3 }
} ;
*/

typedef struct {
  int indx ;
  int mnvl ;
  int* jndx ; 
} elem ;

typedef struct {
  struct lnod* prev ;
  struct lnod* next ;
  void* data ;
} lnod ;

typedef struct {
  lnod* head ;
  int cntr ;
} list ;
