#include "header2.h"



pthread_t tid[2];
pthread_mutex_t lock;
pthread_mutex_t lock1;


int main()
{
int amt;
int k;
int id,id2,err,i=0;
int data;
int n=5;
fp=fopen("cell_storage.dsk","wb+");

printf("\n initial debit value: 3000");
printf("\n initial credit value: 3000");
//printf("\n Trying to transfer 250 from debit to credit account:\n\n\n ");
printf("\n There are two threads running trying to transfer 500 from debit to credit:");
printf("\n Please provide ctrl+c to interrupt thread. That will interrupt only one thread:");
printf("\n Please wait some time for threadto complete:");

boot_cell_storage();


allocate();
allocate();
allocate();
//printf("\n Please enter amount to transfer from debit to credit account");
printf("\n Enter ctrl-c to iterrupt the transaction:");
//printf("\n enter 0 to close the transaction:");
//scanf("%d",&amt);

/*while(amt>0)
{

transfer(DEBIT,CREDIT,amt);
data=read_current_value(2,n);
printf("\n Debit is: %d",data);
data=read_current_value(3,n+1);
printf("\n Credit is: %d",data);
n=n+3;

printf("\n Please enter another amount:");
scanf("%d",&amt);
}*/
pthread_mutex_init(&lock,NULL);

/*if(pthread_mutex_init(&lock1,NULL)!=0)
{
printf("\n mutex initialization fails...");
}
*/
pthread_create(&(tid[0]),NULL,&application,NULL);
pthread_create(&(tid[1]),NULL,&application,NULL);
//transfer(DEBIT,CREDIT,500);
//transfer(DEBIT,CREDIT,500);
sleep(2); 
pthread_join(tid[0],NULL);
pthread_join(tid[1],NULL);
//pthread_mutex_destroy(&lock);
//`pthread_mutex_destroy(&lock1);
/*data=read_current_value(2,9);
printf("\n debit is:%d",data);
data=read_current_value(3,9);
printf("\n credit is:%d",data);
printf("\n hello.....");*/
fclose(fp);
return 0;
}




void boot_cell_storage()
{
long int x= 1024*10240;
fseek(fp,x, SEEK_SET);
fputc('\n',fp);

return;
}

