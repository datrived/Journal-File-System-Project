#include "header2.h"


int i_sig=0;


void sig_handler(int signal_no)
{
i_sig=0;
if(signal_no==SIGINT)
{
printf("\n THere is an interrupt:");
printf("\n transaction can't be committed:");
printf("\n Please try another transaction:");
i_sig=1;
}
}

void transfer(int daccount,int caccount,int amount)
{
int data;
int caller_id1,caller_id2,xvalue,yvalue,my_id;
my_id=begin_transaction(2);

caller_id1=new_version(daccount,my_id);
caller_id2=new_version(caccount,my_id);

mark_point_announce(my_id);



xvalue=read_current_value(daccount,caller_id2);
xvalue=xvalue-amount;
write_new_value(daccount,xvalue,caller_id1);



signal(SIGINT, sig_handler);
sleep(5);


yvalue=read_current_value(caccount,caller_id2);
yvalue=yvalue+amount;
write_new_value(caccount,yvalue,caller_id2);

if(xvalue>0 && i_sig!=1)
{
commit(caller_id2);
commit(caller_id1);
}
else
{
abort1(caller_id2);
abort1(caller_id1);

}
i_sig=0;
data=read_current_value(DEBIT,caller_id1);
printf("\n DEBIT is:%d",data);
data=read_current_value(CREDIT,caller_id2);
printf("\n CREDIT is:%d",data);
return;
}


void* application(void *arg)
{
unsigned long int k=0;
pthread_mutex_lock(&lock);
pthread_t id=pthread_self();
if(pthread_equal(id,tid[0]))
{
printf("\n First thread transaction is processing:");
}
else
{
printf("\n Second thread transaction is processing:");
}
printf("\n hi........");
transfer(DEBIT,CREDIT,500);
pthread_mutex_unlock(&lock);
return;
}
void* application1(void *arg)
{
transfer(DEBIT,CREDIT,500);
return;
}
