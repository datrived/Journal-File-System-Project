#include "header2.h"

void mark_point_announce(int id)
{
long int x;
struct var_data *data=(struct var_data*)malloc(sizeof(struct var_data));


x= VAR_DATA_OFFSET + id*OFFSET;
fseek(fp,x,SEEK_SET);
fread(data,sizeof(struct var_data),1,fp);


data->mark_status=1;
fseek(fp,x,SEEK_SET);
fwrite(data,sizeof(struct var_data),1,fp);


free(data);
return;
}
