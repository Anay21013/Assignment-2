#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <pthread.h>
int main(int argc, char *argv[]){
	pid_t rc;
	int s1;
	struct timespec start1, end1, start2, end2, start3, end3;
	clock_gettime(CLOCK_REALTIME,&start1);
	rc = fork();
	if (rc == 0){
		struct sched_param p1;
		s1 = sched_setscheduler(rc,SCHED_OTHER,&p1);
		char *a[]={"./b1.sh", NULL};
		if (execvp("./b1.sh",a) == -1){
			printf("ERROR\n");
		}

	}
	else if(rc<0){
		printf("unsuccessful \n");
	}
	pid_t rc1;
	int s2;
	clock_gettime(CLOCK_REALTIME,&start2);
	rc1 = fork();
	if (rc1 == 0){
		struct sched_param p2;
		p2.sched_priority = 19;
		s2 = sched_setscheduler(rc1,SCHED_RR,&p2);
		char *a[]={"./b1.sh",NULL};
		if (execvp("./b1.sh",a) == -1){
			printf("ERROR\n");
		}
	}
	else if(rc1<0){
		printf("unsuccessful\n");
	}
	pid_t rc2;
	int s3;
	clock_gettime(CLOCK_REALTIME,&start3);
	rc2 = fork();
	if (rc2 == 0){
		struct sched_param p3;
		p3.sched_priority = 19;
		s3 = sched_setscheduler(rc2,SCHED_FIFO,&p3);
		char *a[]={"./b1.sh",NULL};
		if (execvp("./b1.sh",a)==-1){
			printf("ERROR\n");
		}
	}
	else if(rc2<0){
		printf("unsuccessful\n");
	}
	int r1,r2,r3;
	r1=waitpid(-1,NULL,0);
	if (r1==rc)
	{
		clock_gettime(CLOCK_REALTIME,&end1);
	}
	else if(r1==rc1){
		clock_gettime(CLOCK_REALTIME,&end2);
	}
	else if(r1==rc2){
		clock_gettime(CLOCK_REALTIME,&end3);
	}
	r2=waitpid(-1,NULL,0);
	if (r2==rc)
	{
		clock_gettime(CLOCK_REALTIME,&end1);
	}
	else if(r2==rc1){
		clock_gettime(CLOCK_REALTIME,&end2);
	}
	else if(r2==rc2){
		clock_gettime(CLOCK_REALTIME,&end3);
	}
	r3=waitpid(-1,NULL,0);
	if (r3==rc)
	{
		clock_gettime(CLOCK_REALTIME,&end1);
	}
	else if(r3==rc1){
		clock_gettime(CLOCK_REALTIME,&end2);
	}
	else if(r3==rc2){
		clock_gettime(CLOCK_REALTIME,&end3);
	}
}
