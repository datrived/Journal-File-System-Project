#ifndef HEAD

#define HEAD

#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<pthread.h>
#include<signal.h>
//#include<dos.h>
#define SIZE_OF_CELL_STORAGE 1024*10240


#define VAR_DATA_OFFSET 1024

#define PENDING 1
#define COMMITTED 2
#define ABORTED 3

#define DEBIT 2
#define CREDIT 3


#define OFFSET 1024


extern pthread_t tid[2];
extern int id1;
extern int data_id1;
extern pthread_mutex_t lock;
extern pthread_mutex_t lock1;
extern int i_sig;

FILE *fp;



struct var_data
{

int data_id;
int data;
int status;
int caller_id;
int action_id;
int mark_status;
};




extern void boot_cell_storage();

extern int new_version(int did,int cid);
extern void allocate();

extern int get_caller_id();


extern int begin_transaction(int did);
extern int new_outcome_record(int s,int did);




extern void mark_point_announce(int id);
extern void abort1(int id);
extern void commit(int id);


extern int read_current_value(int did,int cid);
extern void write_new_value(int did,int value,int cid);
extern void sig_handler(int i);

extern void transfer(int daccount,int caccount,int amount);
extern void* application(void *arg);
extern void* application1(void *arg);
#endif

