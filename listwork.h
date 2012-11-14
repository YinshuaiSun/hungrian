/**
 * Function for init the list
 */
void ilst ( list* a )
{
   if ( a != NULL ) {
      a->cntr = 0 ;
      a->head = NULL ;
   }
}

/**
 * Function for add elem into the list
 */
lnod* ulst ( lnod* a , void* d )
{
   lnod* n = a ;
   lnod* c ;

   if ( a != NULL ) {
      if ( a->next != NULL )
         while ( a->next != ( struct lnod* ) n ) a = ( lnod* ) a->next ;

      c = a ;
      a->next = ( struct lnod* ) malloc ( sizeof ( lnod ) ) ;
      a = ( lnod* ) a->next ;
      a->data = d ;
      a->prev = ( struct lnod* ) c ;
      a->next = ( struct lnod* ) n ;
      n->prev = ( struct lnod* ) a ;

      return n ;
   } else {
      a = ( lnod* ) malloc ( sizeof ( lnod ) ) ;
      a->prev = a->next = NULL ;
      a->data = d ;
      return a ;
   }
}

/**
 * Function for read the list
 */
void rlst ( lnod* a , char* s )
{
   lnod* n = a ; char* c ; char b [ 64 ] ; char buf [ 512 ] ;
   int i = 0 , j = 0 ;

   if ( a == NULL ) return ;
   else {
      if ( n->next == NULL ) { 
	rlmn ( n->data , buf ) ;
	sprintf ( s , "list [ 0 ] = %s\n" , buf ) ;
      } else {	 
         c = ( char* ) malloc ( sizeof ( char ) ) ;
         do {
	   rlmn ( n->data , buf ) ;
           sprintf ( b , "list [ %d ] = %s\n" , i , buf ) ;
           c = realloc ( c , ( j + strlen ( b ) ) * sizeof ( char ) ) ;
           strcpy ( c + j , b ) ;
           j += strlen ( b ) ; i++ ;
           n = ( lnod* ) n->next ;
         } while ( n != a ) ;
         sprintf ( s , "%s" , c ) ;
         free ( c ) ;
      }
   }
}

/**
 * Function fo finding element in list
 */
lnod* fnls ( lnod* a , void* d )
{
   lnod* n = a ;
   long* x ;

   if ( n->next == NULL ) {
      x = d ;
      if ( x == n->data ) return n ;
   } else {
      do {
         x = d ;
         if ( x == n->data ) return n ;
         n = ( lnod* ) n->next ;
      } while ( n != a ) ;
   }
   return NULL ;
}

/**
 * Function for delete element from list
 */
lnod* dlst ( lnod* a , void* d , list* l )
{
   lnod* n = ( lnod* ) malloc ( sizeof ( lnod ) ) ;
   lnod* p , * x , * r ;

   r = a ;
   n =  fnls ( a , d ) ;

   if ( n != NULL ) {
      if ( n->next == NULL ) r = NULL ;
      else {
         p = ( lnod* ) n->prev ;
         x = ( lnod* ) n->next ;

         if ( n == a ) {
            r = ( lnod* ) a->next ;
            if ( x->next == ( struct lnod* ) a && p->prev == ( struct lnod* ) a ) {
               r->prev = r->next = NULL ;
            } else {
               p->next = ( struct lnod* ) x ;
               x->prev = ( struct lnod* ) p ;
            }
         } else {
            if ( n->next == ( struct lnod* ) a && n->prev == ( struct lnod* ) a ) {
               r->prev = r->next = NULL ;
            } else {
               p->next = ( struct lnod* ) x ;
               x->prev = ( struct lnod* ) p ;
            }
         }
      }
      l->cntr-- ;
      free ( n ) ;
   }

   return r ;
}

/**
 * Function for free list node
 */
lnod* frnd ( lnod* a )
{
   lnod* n = ( lnod* ) a->next ;
   free ( a ) ;
   return n ;
}

/**
 * Function for free list
 */
void frls ( lnod* a , list* l )
{
   lnod* n = a ;

   if ( a == NULL ) return ; 
   else if ( n->next != NULL ) {
           do {
              n = frnd ( n ) ;
           } while ( n != a ) ;
        }

   free ( n ) ;
   l->cntr = 0 ;
   l->head = NULL ;
}
