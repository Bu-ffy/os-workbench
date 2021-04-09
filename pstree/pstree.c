#include <stdio.h>
#include <assert.h>
#include <dirent.h>

//select the number file 
int filter(const struct dirent *dir){

}

int option(str argv){
  if(argv=="-p" || argv=="--show-pids")
      pstree_p();
  else if (argv=="-V" || argv=="version")
  {
        /* code */
  }
  else if (argv=="n" || argv=="--numeric-sort")
  {
        /* code */
  }
}

int get_pid()
{

}

int pstree_n(){

}

int pstree_v(){

}

int pstree_p(){

}

int main(int argc, char *argv[]) {
  int i,j,k;
  char dir[1024],str[1024];
  struct dirent **namelist;
  int total=scandir("./proc",&namelist,filter,alphasort);//tiqu number file


  for (int i = 0; i < argc; i++) {
    assert(argv[i]);
    if(argv[0]=="./pstree-32")
    {
     option(argv[1]);
    }
    else if (argv[0]=="./pstree-64")
    {
      /* code */
    }
    else
      return printf("error");
  }
  assert(!argv[argc]);

}
