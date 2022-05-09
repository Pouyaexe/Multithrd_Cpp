
#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<pthread.h>
#include<dos.h>
#include<unistd.h>
void *wait(void *tm)
{
   int i;
   long tm_id;
   tm_id=(long)tm;
   sleep(1);
   cout<<"Sleeping in the thread\n";
   cout<<"Thread having id: "<<tm_id<<"  ...exiting from this\n";
   pthread_exit(NULL);
}
void main()
{
   clrscr();
   int rc, i;
   pthread_t threads[5];
   pthread_attr_t attr;
   void *status;
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
   for(i=0;i<5; i++)
   {
      cout<<"main(): creating the thread, "<<i<<"\n";
      rc=pthread_create(&threads[i], NULL, wait, (void *)i);
      if(rc)
      {
         cout<<"Error: unable to create thread, "<<rc<<"\n";
         exit(-1);
      }
   }
   pthread_attr_destroy(&attr);
   for(i=0; i<5; i++)
   {
      rc=pthread_join(threads[i], &status);
      if(rc)
      {
         cout<<"Error: unable to join, "<<rc<<"\n";
         exit(-1);
      }
      cout<<"Main: completed thread id: "<<i;
      cout<<"  exiting with status: "<<status<<"\n";
   }
   cout<<"Main: program exiting.\n";
   pthread_exit(NULL);
   getch();
}