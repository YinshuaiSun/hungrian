#include "maindefs.h"
#include "utilites.h"
#include "matrix.h"

int main ( int argc , char** argv )
{
  int mtrx [ RW ][ CL ] , i , j , m , i1 , j1 , s , c ;
  int rslt [ CL ] ;
  int* rsli , * rslj , rsi , rsj ;
  
  rsi = rsj = 0 ;
  
  // copy matrix
  for ( i = 0 ; i < RW ; i++ )
    for ( j = 0 ; j < CL ; j++ ) mtrx [ i ][ j ] = matrix [ i ][ j ] ;
  
  // print init matrix
  printf ( "Init\n" ) ;
  pmtr ( mtrx , RW , CL ) ;
  printf ( "\n\n" ) ;
  
  // Step 1. Find minimal elem in row and 
  // vichitaem from all elements of this row
 l5: 
  s = 1 ;
  for ( i = 0 ; i < RW ; i++ ) {
    m = rmin ( mtrx , i , CL ) ;
    for ( j = 0 ; j < CL ; j++ ) mtrx [ i ][ j ] -= m ;      
  }

  #if ( DBG == 1 )
    // print matrix
    printf ( "Step 1\n" ) ;
    pmtr ( mtrx , RW , CL ) ;
    printf ( "\n\n" ) ;
  #endif
  
 l0: 
  for ( j = 0 ; j < CL ; j++ ) rslt [ j ] = -1 ;
  
  // build result array
  for ( j = 0 ; j < CL ; j++ ) {
    for ( i = 0 ; i < RW ; i++ ) {
      
      if ( ( mtrx [ i ][ j ] == 0 ) && 
	       ( rslt [ j ] == -1 ) && 
		   ( inar ( rslt , i , CL ) == -1 ) ) {
		j1 = inrw ( mtrx , i , 0 , j , CL ) ;
		if ( j1 == -1 ) { rslt [ j ] = i ; break ; }
		if ( incl ( mtrx , j , 0 , i , RW ) == -1 ) { rslt [ j ] = i ; break; }
       l1:
		if ( incl ( mtrx , j1 , 0 , i , RW ) == -1 ) { rslt [ j1 ] = i ; break; }
		j1 = inrw ( mtrx , i , 0 , j1 , CL ) ;
		if ( j1 == -1 ) { rslt [ j ] = i ; break; }
		goto l1 ;
      }
      
    }
  }

  // check if task solved
  j1 = inar ( rslt , -1 , CL ) ;
  if ( j1 == -1 ) goto l99 ;   
  else if ( s == 2 ) goto l2 ;
  
  // Step 2. Use step for columns.
  s++ ;
  for ( j = j1 ; j < CL ; j++ ) {
    if ( rslt [ j ] != -1 ) continue ;
    m = cmin ( mtrx , j , RW ) ;
    for ( i = 0 ; i < RW ; i++ ) mtrx [ i ][ j ] -= m ;
  }

  #if ( DBG == 1 )
    printf ( "Step 2\n" ) ;
    pmtr ( mtrx , RW , CL ) ;
    printf ( "\n\n" ) ;
  #endif
  goto l0;

 l2: 
  // Step 3. Find unused rows
  c = 0 ;
  for ( i = 0 ; i < RW ; i++ ) 
	if ( inar ( rslt , i , CL ) == -1 ) {
  	  rsi++ ; c++ ;
	  if ( ( rsi - 1 ) == 0 ) {
  	    rsli = ( int* ) malloc ( rsi * sizeof ( *rsli ) ) ;
		*rsli = i ;
	  } else {
		rsli = realloc ( rsli , rsi * sizeof ( *rsli ) ) ;
		*( rsli + ( rsi - 1 ) ) = i ;
	  }
	}
  
  if ( c == 0 ) goto l4 ;
  
 l3: 
  // in all unused rows find columns' numbers with zero
  c = 0 ;
  for ( i = 0 ; i < rsi ; i++ ) {
	j1 = inrw ( mtrx , *( rsli + i ) , 0 , -1 , CL ) ;
	while ( j1 != -1 ) {
	  if ( !inpn ( rslj , j1 , rsj ) ) {
 	    rsj++ ; c++ ;
		if ( ( rsj - 1 ) == 0 ) {
		  rslj = ( int* ) malloc ( rsj * sizeof ( *rslj ) ) ;
		  *rslj = j1 ;
		} else {
		  rslj = realloc ( rslj , rsj * sizeof ( *rslj ) ) ;
		  *( rslj + ( rsj - 1 ) ) = j1 ;
		}
	  }
	  j1 = inrw ( mtrx , *( rsli + i ) , 0 , j1 , CL ) ;
	}
  }

  if ( c == 0 ) goto l4 ;
  
  // in all unused columns find rows' numbers with zero
  c = 0 ;
  for ( j = 0 ; j < rsj ; j++ ) {
    i1 = incl ( mtrx , *( rslj + j ) , 0 , -1 , RW ) ;
	while ( i1 != -1 ) {
	  if ( !inpn ( rsli , i1 , rsi ) ) {
	    rsi++ ; c++ ;
		rsli = realloc ( rsli , rsi * sizeof ( *rsli ) ) ;
		*( rsli + ( rsi - 1 ) ) = i1 ;
	  }
	  i1 = incl ( mtrx , *( rslj + j ) , 0 , i1 , RW ) ;
	}
  }
  if ( c ) goto l3 ;
  
 l4: 
  // Step 4. Vicherkivaem otmechennie stolbci 
  // i neotmechennie stroki
  // for i == rsli , j != rslj
  m = -1 ;
  for ( i = 0 ; i < RW ; i++ ) {
    if ( !inpn ( rsli , i , rsi ) ) continue ;
    for ( j = 0 ; j < CL ; j++ ) {
	  if ( inpn ( rslj , j , rsj ) ) continue ;
	  m = ( mtrx [ i ][ j ] < m || m < 0 ) ? mtrx [ i ][ j ] : m ;
	}
  }
  
  for ( i = 0 ; i < RW ; i++ ) {
    for ( j = 0 ; j < CL ; j++ ) {
      if ( inpn ( rsli , i , rsi ) && !inpn ( rslj , j , rsj ) ) 
	    mtrx [ i ][ j ] -= m ;
	  if ( !inpn ( rsli , i , rsi ) && inpn ( rslj , j , rsj ) )
	    mtrx [ i ][ j ] += m ;
	}
  }
  free ( rsli ) ; free ( rslj ) ; 
  rsi = rsj = 0 ;

  #if ( DBG == 1 )
    printf ( "Step 4\n" ) ;
    pmtr ( mtrx , RW , CL ) ;
    printf ( "\n\n" ) ;
  #endif
  goto l5 ;
  
 l99:
  for ( j = 0 ; j < CL ; j++ ) printf ( "For task: %d use worker:%d\n" , j , rslt [ j ] ) ;
  printf ( "\n" ) ;
  
  return 0 ;
}
