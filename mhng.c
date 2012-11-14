#include "maindefs.h"
#include "utilites.h"
#include "listwork.h"
#include "matrix.h"

int mtrx [ RW ][ CL ] ;
int rslt [ CL ] ;
list* mine ;

int inrs ( int i , int j ) 
{
  int k ; 
  if (( i < 0 ) && ( j < 0 )) {
    return 0 ;
  } else if ( i < 0 ) {
    if ( rslt [ j ] > -1 ) return 1 ;
  } else if ( j < 0 ) {
    for ( k = 0 ; k < CL ; k++ ) 
	  if ( rslt [ k ] == i ) return 1 ;
  } else {
    if ( rslt [ j ] == i ) return 1 ;
  }
  return 0 ;
}

int main ()
{
  int i , j , m , k , b , me , mj ;
  elem* lmnt ; 
  char s [ 1024 ] ;
  lnod* n , * p , * x ;

  //Initialisation ==================================================
  for ( i = 0 ; i < RW ; i++ )
    for ( j = 0 ; j < CL ; j++ ) mtrx [ i ][ j ] = matrix [ i ][ j ] ;
  
  for ( j = 0 ; j < CL ; j++ ) rslt [ j ] = -1 ; 
  
  mine = ( list* ) malloc ( sizeof ( list ) ) ;
  ilst ( mine ) ;
  
  // print init matrix
  printf ( "Init\n" ) ;
  pmtr ( mtrx , RW , CL ) ;
  printf ( "\n\n" ) ;
  //================================================== Initialisation
  
  //Step1. Build the list of minimal elements =======================
  for ( i = 0 ; i < RW ; i++ ) {
    m = rmin ( mtrx , i , CL ) ;
    lmnt = ( elem* ) malloc ( sizeof ( elem ) ) ;
    lmnt->indx = i ;
    lmnt->mnvl = m ;
    lmnt->jndx = NULL ; k = 0 ;
    for ( j = 0 ; j < CL ; j++ )
      if ( mtrx [ i ][ j ] == m ) {
	k++ ;
	if ( k == 1 ) {
	  lmnt->jndx = ( int* ) malloc ( sizeof ( int ) ) ;
	  *(lmnt->jndx) = j ;
	} else {
	  lmnt->jndx = realloc ( lmnt->jndx , k * sizeof ( int ) ) ;
	  *(lmnt->jndx + k - 1) = j ;
	}
      }
    k++ ;  
    lmnt->jndx = realloc ( lmnt->jndx , k * sizeof ( int ) ) ;
    *(lmnt->jndx + k - 1) = -1 ;
    mine->head = ulst ( mine->head , ( void* ) lmnt ) ;
    mine->cntr++ ;   
  }
  //========================================================== Step1.
  #if ( DBG1 == 1 )
    rlst ( mine->head , s ) ;
    printf ( "mine :\n%s\n" , s ) ;
  #endif
  
  //Step2. Find minimal element in mine =============================
 l0:
  me = -1 ;
  n = mine->head ; 
  if ( n->next == NULL ) { 
    me = (( elem* ) n->data)->mnvl ;
  } else {	 
    do {
      me = ( (( elem* ) n->data)->mnvl < me || me < 0 ) ? (( elem* ) n->data)->mnvl : me ;
      n = ( lnod* ) n->next ;
    } while ( n != mine->head ) ;
  }
  //========================================================== Step2.
  
  //Step3. Choose element with minimal value and delete it from the
  //list. ===========================================================
  n = mine->head ;
  if ( n->next == NULL ) {
    rslt [ *((( elem* ) n->data)->jndx) ] = (( elem* ) n->data)->indx ;
    goto l99 ;
  } else {
    do {
      if ( (( elem* ) n->data)->mnvl == me ) {
		mj = *((( elem* ) n->data)->jndx) ;
        rslt [ mj ] = (( elem* ) n->data)->indx ;   
	
		x = ( lnod* ) n->next ;
		p = ( lnod* ) n->prev ;
		if ( n == mine->head ) {
		  if ( x->next != ( struct lnod* ) n ) {
		    mine->head = ( lnod* ) x ;
		    mine->head->prev = ( struct lnod* ) p ;
		    p->next = ( struct lnod* ) x ;
		  } else {
		    mine->head = ( lnod* ) x ;
	        mine->head->next = mine->head->prev = NULL ;
	      }
	    } else {
	      if (( x == mine->head ) && ( p == mine->head )) {
	        mine->head->next = mine->head->prev = NULL ;
	      } else {
	        p->next = ( struct lnod* ) x ;
	        x->prev = ( struct lnod* ) p ;
	      }
	    }
	    mine->cntr-- ;
        free ( n ) ;
	    break ; 
      }
      n = ( lnod* ) n->next ;
    } while ( n != mine->head ) ;
  }
  //========================================================== Step3.
  if ( mine->cntr == 1 )  {
	lmnt = mine->head->data ;
	k = 0 ;
	while ( *(lmnt->jndx + k) != -1 ) {
	  if ( ! inrs ( -1 , *(lmnt->jndx + k) ) ) {
	    rslt [ *(lmnt->jndx + k) ] = lmnt->indx ;
	    break ;
	  }
	  k++ ;
	}
    goto l99 ;
  }
  
  
  //Step4. Rebuild the list =========================================
  n = mine->head ;
  do {
    //Find elements with the used 'j' in the rest of the list
	lmnt = n->data ;
	b = 0 ; k = 0 ;
	while ( *(lmnt->jndx + k) != -1 ) {
	  if ( *(lmnt->jndx + k) == mj ) {
	    b = 1 ; break ;
	  }
	  k++ ;
	}

	if ( b ) { 
	  m = -1 ;
      for ( j = 0 ; j < CL ; j++ ) {
	    if ( inrs ( -1 , j ) ) continue ;
		if ( m < 0 ) m = mtrx [ lmnt->indx ][ j ] ;
		else m = ( m <= mtrx [ lmnt->indx ][ j ] ) ? m : mtrx [ lmnt->indx ][ j ] ;
	  }
	  
	  if ( m > 0 ) {
	    free( lmnt->jndx ) ;
		lmnt->mnvl = m ;
		lmnt->jndx = NULL ;
		k = 0 ;
        for ( j = 0 ; j < CL ; j++ )
          if ( mtrx [ lmnt->indx ][ j ] == m ) {
		    k++ ;
  		    if ( k == 1 ) {
		      lmnt->jndx = ( int* ) malloc ( sizeof ( int ) ) ;
		      *(lmnt->jndx) = j ;
		    } else {
		      lmnt->jndx = realloc ( lmnt->jndx , k * sizeof ( int ) ) ;
		      *(lmnt->jndx + k - 1) = j ;
		    }
          }
        k++ ;  
        lmnt->jndx = realloc ( lmnt->jndx , k * sizeof ( int ) ) ;
        *(lmnt->jndx + k - 1) = -1 ; 
      }	  
	}
    n = ( lnod* ) n->next ;
  } while ( n != mine->head ) ;
  //========================================================== Step4.

  #if ( DBG1 == 1 )
    rlst ( mine->head , s ) ;
    printf ( "mine :\n%s\n" , s ) ;
    for ( i = 0 ; i < RW ; i++ ) {
      if ( inrs ( i , -1 ) ) continue ;
      for ( j = 0 ; j < CL ; j++ ) {
	    if ( inrs ( -1 , j ) ) continue ;
	    printf ( "%d   " , mtrx [ i ][ j ] ) ;
	  }
	  printf ( "\n" ) ;
    }	 
    printf ( "\nCntr = %d\n" , mine->cntr ) ;
  #endif
 
  if ( mine->cntr > 1 ) goto l0 ;
 
 l99:
  for ( j = 0 ; j < CL ; j++ ) printf ( "For task: %d use worker:%d\n" , j , rslt [ j ] ) ;
  printf ( "\n" ) ;
  return 0 ;
}
