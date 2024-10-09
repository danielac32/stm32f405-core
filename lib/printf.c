/* printf.c - printf*/

#include <xinu.h>
 
extern void _fdoprnt(char *, va_list, int (*)(did32, char), int);
//extern void _fdoprnt2(char *, va_list, int (*)(int,did32, char), int,int);
//extern int xinu_putc(did32, char);


 
/*------------------------------------------------------------------------
 *  printf  -  standard C printf function
 *------------------------------------------------------------------------
 */


/*
static int __putc(int c, int b){
    __syscall8(0,0,b);//
    //kputc(b);
    return OK;
}*/


/*
int printf2(const char *fmt, ...){

    va_list ap;

    va_start(ap, fmt);
    __syscall(XINU_TEST2,(char *)fmt, ap);
    va_end(ap);
    return OK;
}
*/ 



 

extern  void    _doprnt(char *, va_list, int (*)(int));
extern syscall kputc(byte  c);
int printf(
      const char        *fmt,
      ...
    )
{
    va_list ap;

    va_start(ap, fmt);
   // _fdoprnt((char *)fmt, ap, syscallp.putc, stdout);
    _doprnt(fmt, ap, (int (*)(int))kputc);
    va_end(ap);

    return 0;
}


 