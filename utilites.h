/**
 * Function for printing matrix
 */
void pmtr ( int a [ RW ][ CL ] , int n , int m )
{
  int i , j ; 
  
  for ( i = 0 ; i < n ; i++ ) {
    for ( j = 0 ; j < m ; j++ ) printf ( "%d\t" , a [ i ][ j ] ) ;
    printf ( "\n" ) ;
  }
  
  return ;
}

/**
 * Function for finding element in array
 */
int inpn ( int* a , int b , int c ) 
{
  int i ;
  
  for ( i = 0 ; i < c ; i++ )
	if ( *( a + i ) == b ) return 1 ;
	
  return 0 ;
}

/**
 * Function for reading structure 'elem'
 */
void rlmn ( void* a , char* b )
{
  elem* e = a ; int i = 0 ;
  
  sprintf ( b , "( indx = %d , mnvl = %d , jndx = [" , e->indx , e->mnvl ) ;
  
  while ( *(e->jndx + i) >= 0 ) {
    sprintf ( b , "%s %d" , b , *(e->jndx + i) ) ;
    i++ ;
  }
  
  sprintf ( b , "%s ] )" , b ) ;
  return ;
}
