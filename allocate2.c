#include "header2.h"



int id1=0;
int data_id1=0;



void allocate()
{
long int x;

struct var_data *node2=(struct var_data*)malloc(sizeof(struct var_data));

node2->data_id=data_id1+1;
data_id1=data_id1+1;
node2->action_id=1;
node2->caller_id=id1+1;
id1=id1+1;

node2->status=COMMITTED;
node2->data=3000;
node2->mark_status=0;

x=VAR_DATA_OFFSET + (node2->caller_id)*OFFSET;
fseek(fp,x,SEEK_SET);

fwrite(node2,sizeof(struct var_data),1,fp);


free(node2);
return;
}





int begin_transaction(int did)
{
int i;
int id;
long int x;
struct var_data *node=(struct var_data*)malloc(sizeof(struct var_data));

id=new_outcome_record(PENDING,did);
//printf("\n id:%d is created:",id);
i=id;
x=VAR_DATA_OFFSET + i*OFFSET;
fseek(fp,x,SEEK_SET);
fread(node,sizeof(struct var_data),1,fp);
while(node->caller_id!=1)
{
i--;
x=VAR_DATA_OFFSET + i*OFFSET;
fseek(fp,x,SEEK_SET);
fread(node,sizeof(struct var_data),1,fp);
if(node->data_id==did)
{
break;
}
}


/*while(node->mark_status==1 || (node->status==PENDING))
{
usleep(1000000);
fseek(fp,x,SEEK_SET);
fread(node,sizeof(struct var_data),1,fp);

} */
free(node);
return id;
}






int new_outcome_record(int state,int did)
{
//pthread_mutex_lock(&lock);
long int x;
struct var_data *node=(struct var_data*)malloc(sizeof(struct var_data));


node->data=3000;
node->data_id=did;
node->action_id=1;
node->caller_id=id1+1;
id1=id1+1;

node->status=PENDING;
node->mark_status=0;

x=VAR_DATA_OFFSET+id1*OFFSET;
fseek(fp,x,SEEK_SET);
fwrite(node,sizeof(struct var_data),1,fp);

free(node);
//pthread_mutex_unlock(&lock);
//printf("\n node with id:%d is created",id1);
return id1;
}








int new_version(int did,int cid)
{
long int x;
int id;
struct var_data *node=(struct var_data*)malloc(sizeof(struct var_data));
struct var_data *data=(struct var_data*)malloc(sizeof(struct var_data));

x=VAR_DATA_OFFSET + cid*OFFSET;
fseek(fp,x,SEEK_SET);
fread(data,sizeof(struct var_data),1,fp);
if(data->mark_status==1)
{
printf("\n Tried to create new version after announcing mark point");
exit(0);
}
node->data=3000;
node->data_id=did;
node->action_id=cid;
node->caller_id=id1+1;
id1=id1+1;
node->status=PENDING;
node->mark_status=0;
x=VAR_DATA_OFFSET+id1*OFFSET;
fseek(fp,x,SEEK_SET);
fwrite(node,sizeof(struct var_data),1,fp);

free(data);
free(node);
//printf("\n id :%d is created:",id1);
return id1;
}



int get_caller_id()
{
return id1;
}
