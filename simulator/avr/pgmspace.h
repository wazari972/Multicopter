#ifdef __cplusplus
extern "C"{
#endif

  char * utoa(unsigned int n, char * buffer, int radix) ;
  char *ultoa(long n,  char * buffer, int radix) ;
  char *itoa(int n,  char * buffer, int radix) ;
  char *ltoa(int n,  char * buffer, int radix) ;

#ifdef __cplusplus
}
#endif
