#include "header2.h"

void commit(int id)
{
long int x;
struct var_data *data=(struct var_data*)malloc(sizeof(struct var_data));


x= VAR_DATA_OFFSET + id*OFFSET;
fseek(fp,x,SEEK_SET);
fread(data,sizeof(struct var_data),1,fp);


data->status=COMMITTED;
fseek(fp,x,SEEK_SET);
fwrite(data,sizeof(struct var_data),1,fp);


free(data);
return;
}
