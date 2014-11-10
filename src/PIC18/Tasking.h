#ifndef Tasking_H
#define Tasking_H

#define initTasking(x) ((x)->state = 0)
#define startTasking(x)  switch(x) { case 0:
#define yield(x) (x)=__LINE__; return; case __LINE__:
#define endTasking()  }

#endif // Tasking_H