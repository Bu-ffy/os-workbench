#include <stdio.h>
#include <assert.h>
#include <dirent.h>

typedef struct pro_info
{
  int pid;
  int ppid;
  char name[100];
  int flag; //标志是否打印
  int rec;  //计算总父进程个数
} info;

char dir[1024], str[1024];
struct dirent **namelist;
int total;
char pid_path[20], str[100], name[100];
info proc[1024];

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

int option(char argv)
{
  if (argv == "-p" || argv == "--show-pids")
    pstree_p();
  else if (argv == "-V" || argv == "version")
  {
    /* code */
  }
  else if (argv == "n" || argv == "--numeric-sort")
  {
    /* code */
  }
}

//复制未学习！！！
int readfile()
{
  int ppid, pid, s1, s2, j,k;
  int t = 0;
  FILE *fp;
  
  total = scandir("./proc", &namelist, filter, alphasort); //extract number file
  for (int i = 0; i < total; i++)
  {
    strcpy(pid_path, "/proc/");
    strcat(pid_path, namelist[i]->d_name);
    strcat(pid_path, "/status");
    fp = fopen(pid_path, "r");

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
      //将得到的赋值于struct
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

int get_pid()
{
}

int pstree_n()
{
}

int pstree_v()
{
}

int pstree_p()
{
}

int main(int argc, char *argv[])
{
  readfile();
  //命令行参数选择
  for (int i = 0; i < argc; i++)
  {
    assert(argv[i]);
    if (argv[0] == "./pstree-32")
    {
      option(argv[1]);
    }
    else if (argv[0] == "./pstree-64")
    {
      /* code */
    }
    else
      return printf("error");
  }
  assert(!argv[argc]);
  
}
