#include "header2.h"

void write_new_value(int did,int new_value,int cid)
{
int cid1;
long int x;
struct var_data *data1=(struct var_data*)malloc(sizeof(struct var_data));


x= VAR_DATA_OFFSET + cid*OFFSET;
fseek(fp,x,SEEK_SET);
fread(data1,sizeof(struct var_data),1,fp);
data1->data=new_value;
fseek(fp,x,SEEK_SET);
fwrite(data1,sizeof(struct var_data),1,fp);

free(data1);
return;
}
