#include <stdio.h>
#include <assert.h>
#include <dirent.h>

typedef struct info
{
  int pid;
  int ppid;
  char name[100];
  int flag; //标志是否打印
  int rec;  //计算总父进程个数
  int root;//标记根
} info;

char dir[1024], str[1024];
struct dirent **namelist;
int total;
char pid_path[20], str[100], name[100];
info *proc;

//控制参数
int arg_n = 0;
int arg_p = 0;

//select the number file
int filter(const struct dirent *dir)
{
  int n = strlen(dir->d_name);
  for (int i = 0; i < n; i++)
  {
    if (!isdigit(dir->d_name[i]))
      return 0;
    else
      return 1;
  }
}

//得到pid
int my_getpid(char *str)
{
  int length = strlen(str);
    char num[10];
    int i, j, ret;
    if (strncmp(str, "Pid", 3) == 0)
    {
        for (i = 0; i < length; i++)
        {
            if (str[i] >= '0' && str[i] <= '9')
                break;
        } //获得str[i]中第一个数字位的i值
        for (j = 0; j < length - 1; j++)
            num[j] = str[i + j]; //将数字位复制于num
        ret = atoi(num);         //atoi函数将string类型转换为int类型
    }
    else
        ret = -1; //由于init的父进程为0 为了避免重复 我们返回－1
    return ret;   //返回pid的值
}

//my_getppid()函数原理同my_getpid()原理
int my_getppid(char *str)
{
  int len = strlen(str);
  char num[10];
  int i, j, ret;
  if (strncmp(str, "PPid ", 4) == 0)
  {
    //printf("%s",str);
    for (i = 0; i < len; i++)
    {
      if (str[i] >= '0' && str[i] <= '9')
        break;
    }
    //printf("len=%d,i=%d/n",len,i);
    for (j = 0; j < len - i; j++)
    {
      num[j] = str[i + j];
    }
    ret = atoi(num);
    //printf("ret=%d/n",ret);
  }
  else
    ret = -1;
  return ret; //返回ppid的值
}

//复制未学习！！！
int readfile()
{
  int ppid, pid, s1, s2, j, k, total;
  int t = 0;
  FILE *fp;

  total = scandir("./proc", &namelist, filter, alphasort); //extract number file
  assert(total);

  for (int i = 0; i < total; i++)
  {
    strcpy(pid_path, "/proc/");
    strcat(pid_path, namelist[i]->d_name);
    strcat(pid_path, "/status");
    fp = fopen(pid_path, "r");
    assert(fp);

    while (!feof(fp)) //feof()函数读取文件，如果文件到达结尾,就返回非0值
    {
      fgets(str, 1024, fp);
      if ((s1 = my_getpid(str)) != -1)
        pid = s1;
      if ((s2 = my_getppid(str)) != -1)
        ppid = s2;
      if (strncmp(str, "Name", 4) == 0) //原理与my_getppid()相同
      {
        for (j = 4; j < strlen(str); j++)
        {
          if (str[j] >= 'a' && str[j] <= 'z')
            break;
        }
        for (k = j; k < strlen(str); k++)
        {
          name[k - j] = str[k];
        }
        name[k - j - 1] = '/0';
      }
      //将得到的赋值于proc
      proc = (info *)malloc(sizeof(info) * (total + 1));
      proc[t].pid = pid;
      proc[t].ppid = ppid;
      strcpy(proc[t].name, name);
    }
    fclose(fp); //关闭文件
    //printf("%d %d %s/n",proc[t].ppid,proc[t].pid,proc[t].name);
    t++;
  }
  return proc;
}

int pstree_n()
{
}

int pstree_p()
{
}

int main(int argc, char *argv[])
{
  //命令行参数选择
  int i;
  for (i = 0; i < argc; i++)
  {
    if (argv[i][0] == '-')
    {
      if (argv[i][1] == '-')
      {
        if (strcmp(argv[i], "--numeric-sort") == 0)
        {
          arg_n = 1;
        }
        else if (strcmp(argv[i], "--show-pids") == 0)
        {
          arg_p = 1;
        }
        else if (strcmp(argv[i], "--version") == 0)
        {
          printf("pstree for OSLab M1\n");
          return 0;
        }
      }
      else
      {
        for (int j = 1; j < strlen(argv[i]); j++)
        {
          if (argv[i][j] == 'n')
          {
            arg_n = 1;
          }
          else if (argv[i][j] == 'p')
          {
            arg_p = 1;
          }
          else if (argv[i][j] == 'V')
          {
            printf("pstree for OSLab M1\n");
            return 0;
          }
        }
      }
    }
  }
  assert(!argv[argc]);
  readfile();

  free(proc);
}
