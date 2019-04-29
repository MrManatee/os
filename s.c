#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define JOB 5
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
    }JCB;
static int currenttime=0;  //当前时间
static int  finishnumber=0;  //作业完成数
float priority[JOB]={0};  //优先级
int needtime[JOB]={0}; //判断是否运行了所需要的时间


//创建JCB
void createJCB(JCB  *job)
{  int i,j,a,r;
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
      strcpy(job[i].jobstatus,WAIT);
   }
 printf("-------------------------------------------------\n\n\n");
}



//打印
void show(JCB *job)
{  int i=0;
   printf("当前时间为 %d\n",currenttime);
   printf("作业名 到达时间 需要运行时间 开始时间 完成时间 周转时间 带权周转时间 权值 进程状态\n");
   for(;i<JOB;i++)
   {  if(strcmp(job[i].jobstatus,WAIT)==0)
	 printf("%-6s %-8d %-12d 未开始   NULL     %-8d %-12.2f %-4.2f %-8s\n",job[i].jobname,job[i].arrivetime,job[i].runtime,job[i].zztime,job[i].dqzztime,priority[i],job[i].jobstatus);
      if(strcmp(job[i].jobstatus,FINISH)==0)
	  printf("%-6s %-8d %-12d %-8d %-8d %-8d %-12.2f %-4.2f %-8s\n",job[i].jobname,job[i].arrivetime,job[i].runtime,job[i].starttime,job[i].finishtime,job[i].zztime,job[i].dqzztime,priority[i],job[i].jobstatus);
      if(strcmp(job[i].jobstatus,RUN)==0)
	  printf("%-6s %-8d %-12d %-8d 运行中   %-8d %-12.2f %-4.2f %-8s\n",job[i].jobname,job[i].arrivetime,job[i].runtime,job[i].starttime,job[i].zztime,job[i].dqzztime,priority[i],job[i].jobstatus);
   }
  printf("------------------------------------------------\n\n");
}



//高响应比调度算法
void HRRN(JCB *job)
{
   int i=0,waittime=0,j;
   float maxpriority; //最高权
   int index=0; //存放准备执行的作业号
   while(finishnumber!=JOB) //判断是否都执行完了
    {  
      for(i=0,maxpriority=-1;i<JOB;i++) //遍历找出权值最大的作业号
      {	 
	 if(strcmp(job[i].jobstatus,FINISH)!=0)
	    {
	     waittime=(currenttime-job[i].arrivetime); //等待时间=当前时间-到达时间
	    priority[i]=(waittime+job[i].runtime)*1.0/job[i].runtime*1.0; //权值=（等待时间+运行所需时间）/运行所需要时间
	    if(priority[i]>maxpriority)
	    {
	       maxpriority=priority[i]; 
	       index=i;
	    }
	 }
	 else continue; //如果当前作业已完成则跳过
      }
      if(job[index].arrivetime>currenttime){show(job);currenttime++;  continue; }//如果当前时间没有任务到达则什么都不做
      run(job,index); //最高权的作业准备执行

   }
}



//作业运行
void run(JCB *job,int i)
{  
   
   if(needtime[i]==job[i].runtime) //如果运行时间达到了所需时间则执行完毕
   {
      strcpy(job[i].jobstatus,FINISH);
      job[i].zztime=currenttime-job[i].arrivetime;
      job[i].finishtime=currenttime;
      job[i].dqzztime=(job[i].zztime*1.0)/(job[i].runtime*1.0);
      finishnumber++;
   }
   else if(strcmp(job[i].jobstatus,WAIT)==0)  //如果是第一次执行
   {
      strcpy(job[i].jobstatus,RUN);
      job[i].starttime=currenttime;
      needtime[i]++;
   }
   else  needtime[i]++; //运行时间增加
  show(job); 
  currenttime++;  //当前时间增加
  }



main()
{
   JCB j[JOB];
   printf("--------------------------\n");
   printf("|			 |\n");
   printf("| 高响应比调度算法实验   |\n");
   printf("|			 |\n");
   printf("--------------------------\n\n\n");
   createJCB(j);
   HRRN(j);
   
}
