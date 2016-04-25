#include "header2.h"



int read_current_value(int did,int cid)
{
int id,j;
long int x;
int s;
int i=1;
struct var_data *node=(struct var_data*)malloc(sizeof(struct var_data));


id=get_caller_id();

x= VAR_DATA_OFFSET + i*OFFSET;
fseek(fp,x,SEEK_SET);
fread(node,sizeof(struct var_data),1,fp);

while(node->caller_id!=id)
{
i++;
x= VAR_DATA_OFFSET + i*OFFSET;
fseek(fp,x,SEEK_SET);
fread(node,sizeof(struct var_data),1,fp);

}

x= VAR_DATA_OFFSET + i*OFFSET;
fseek(fp,x,SEEK_SET);
fread(node,sizeof(struct var_data),1,fp);

if(node->data_id==did && node->caller_id==cid)
{
s=node->status;
if(s==2)
{
j=node->data;
//printf("\n reading caller id: %d",node->caller_id);
free(node);
return j;
}

}
while(node->caller_id!=1)
{
i--;
x= VAR_DATA_OFFSET + i*OFFSET;
fseek(fp,x,SEEK_SET);
fread(node,sizeof(struct var_data),1,fp);

if(node->data_id==did)
{
s=node->status;

if(s==2)
{
j=node->data;
//printf("\n reading caller id: %d",node->caller_id);
free(node);
return j;
}
else
{
continue;
}
}


}
printf("\n Tried to read an uninitialized variable...");

free(node);
exit(0);
}
