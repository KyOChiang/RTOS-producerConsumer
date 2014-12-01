#ifndef TYPE_H
#define TYPE_H
#if !(defined(__XC) || defined(__18CXX))
typedef int                 int32;
typedef short int           int16;
typedef char                int8;
typedef unsigned short int  uint16;
typedef unsigned int        uint32;
typedef unsigned char       uint8;
#else
typedef int             int16;
typedef long            int32;
typedef char            int8;
typedef unsigned int    uint16;
typedef unsigned long   uint32;
typedef unsigned char   uint8;
#endif // !defined(__XC||__18CXX)



#endif
