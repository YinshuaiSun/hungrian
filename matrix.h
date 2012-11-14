/**
 * Function for finding minimal element in row 'b' matrix 'a'
 * in its' first 'm' columns
 */
int rmin ( int a [ RW ][ CL ] , int b , int m ) 
{
  int j , r ;
  
  r = a [ b ][ 0 ] ;
  
  for ( j = 0 ; j < m ; j++ )
    r = ( a [ b ][ j ] < r ) ? a [ b ][ j ] : r ;
  
  return r ;
}

/**
 * Function for finding minimal element in column 'b' matrix 'a'
 * in its' first 'n' rows
 */
int cmin ( int a [ RW ][ CL ] , int b , int n ) 
{
  int i , r ;
  
  r = a [ 0 ][ b ] ;
  
  for ( i = 0 ; i < n ; i++ )
    r = ( a [ i ][ b ] < r ) ? a [ i ][ b ] : r ;
  
  return r ;
}

/**
 * Function for finding element 'f' in row 'b' matrix 'a'
 * in columns with number > 'l'
 * -1 - element is not found
 * n - column's number of first element
 */
int inrw ( int a [ RW ][ CL ] , int b , int f , int l , int m )
{
  int j ;
  
  for ( j = 0 ; j < m ; j++ )
    if ( ( a [ b ][ j ] == f ) && ( j > l ) ) return j ; 
  
  return -1 ;
}

/**
 * Function for finding element 'f' in column 'b' matrix 'a'
 * in rows with number <> 'l'
 * -1 - element is not found
 * n - row's number of first element
 */
int incl ( int a [ RW ][ CL ] , int b , int f , int l , int n )
{
  int i ;
  
  for ( i = l ; i < n ; i++ )
    if ( ( a [ i ][ b ] == f ) && ( i != l ) )  return i ; 
  
  return -1 ;
}

/**
 * Function for finding element 'f' in array 'a'
 * -1 - element is not found
 * n - an index of first element
 */
int inar ( int a [ CL ] , int f , int m ) 
{
  int j ;
  
  for ( j = 0 ; j < m ; j++ )
    if ( a [ j ] == f ) return j ;
    
  return -1 ;
}
