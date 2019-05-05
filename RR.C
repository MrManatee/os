#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define JOB 3
#define WAIT "wait"
#define RUN "run"
#define FINISH "finish"
typedef struct{
    char jobname[10];  //作业名
    int arrivetime;  //到达时间
    int runtime;     //需要运行时间
    int starttime;  //开始时间
    int finishtime;  //结束时间
    int zztime;  //周转时间
    float  dqzztime;  //带权周转时间
    char jobstatus[10];  //作业状态
    int flag;
    }JCB;
int priority[JOB]={0};
static int currenttime=0;  //当前时间
static int  finishnumber=0;  //作业完成数
static int time=0;
int needtime[JOB]={0}; //判断是否运行了所需要的时间
//创建JCB
void createJCB(JCB  *job)
{  int i,j,a,r;
   printf("请输入时间片： ");
   scanf("%d",&time);
   for(i=0;i<JOB;i++)
   { 
      printf("请输入第%d个任务的作业名:  ",i+1);
      scanf("%s",job[i].jobname);
      printf("到达时间: ");
      scanf("%d",&job[i].arrivetime);
      printf("运行所需时间: ");
      scanf("%d",&job[i].runtime);
      job[i].starttime=0;
      job[i].finishtime=0;
      job[i].zztime=0;
      job[i].dqzztime=0;
      job[i].flag=0;
      strcpy(job[i].jobstatus,WAIT);
   }
 printf("-------oooooo------------------------------------------\n\n\n");
}



//打印
void show(JCB *job)
{  int i=0;
   printf("当前时间为 %d\n",currenttime);
   printf("作业名 到达时间 需要运行时间 开始时间 完成时间 周转时间 带权周转时间  进程状态\n");
   for(;i<JOB;i++)
   {  if(strcmp(job[i].jobstatus,WAIT)==0)
	 printf("%-6s %-8d %-12d 未开始   NULL     %-8d %-12.2f %-8s\n",job[i].jobname,job[i].arrivetime,job[i].runtime,job[i].zztime,job[i].dqzztime,job[i].jobstatus);
      if(strcmp(job[i].jobstatus,FINISH)==0)
	  printf("%-6s %-8d %-12d %-8d %-8d %-8d %-12.2f %-8s\n",job[i].jobname,job[i].arrivetime,job[i].runtime,job[i].starttime,job[i].finishtime,job[i].zztime,job[i].dqzztime,job[i].jobstatus);
      if(strcmp(job[i].jobstatus,RUN)==0)
	  printf("%-6s %-8d %-12d %-8d 运行中   %-8d %-12.2f %-8s\n",job[i].jobname,job[i].arrivetime,job[i].runtime,job[i].starttime,job[i].zztime,job[i].dqzztime,job[i].jobstatus);
   }
  printf("------------------------------------------------\n\n");
}


void ssort(JCB *job)
{
   int i,k,j,n;
   for(i=0;i<JOB;i++)
   {  k=100;
      n=i;
      for(j=0;j<JOB;j++)
      {
         if(job[j].arrivetime<k&&job[j].flag!=1) {k=job[j].arrivetime,n=j;}
      }
      priority[i]=n;
      job[n].flag=1;
   }
}

//时间片轮转
void RR(JCB *job)
{
   int i=0,j=0;
	for(i=0;i<=JOB;i++) 
	{
	 if(i>=JOB)i=0;
	 if(finishnumber==JOB)break;
	 if(strcmp(job[priority[i]].jobstatus,FINISH)==0) continue;
	 if(job[priority[i]].arrivetime>currenttime){i=-1;show(job); currenttime++; continue;}
          run(job,priority[i]);
        }

   }

   


//作业运行
void run(JCB *job,int i)
{  
   int j;
   if(strcmp(job[i].jobstatus,WAIT)==0)  //如果是第一次执行
   {
      strcpy(job[i].jobstatus,RUN);
      job[i].starttime=currenttime;
}
   for(j=0;j<time;j++)
   {
      if(needtime[i]==job[i].runtime &&  strcmp(job[i].jobstatus,FINISH)!=0) //如果运行时间达到了所需时间则执行完毕
      {
      strcpy(job[i].jobstatus,FINISH);
      job[i].zztime=currenttime-job[i].arrivetime;
      job[i].finishtime=currenttime;
      job[i].dqzztime=(job[i].zztime*1.0)/(job[i].runtime*1.0);
      finishnumber++;
      show(job);
      currenttime++;
      break;
      }
   else { needtime[i]++; //运行时间增加
  show(job); 
  currenttime++; //当前时间增加
   }
  }

}

main()
{
   JCB j[JOB];
   printf("--------------------------\n");
   printf("|			 |\n");
   printf("| 时间片轮转调度算法   |\n");
   printf("|			 |\n");
   printf("--------------------------\n\n\n");
   createJCB(j);
   ssort(j);
   RR(j);
   
}
