#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <Windows.h>
struct _finddata_t fd;
int isFileOrDir();
int findkey(char file_path[],char data[],int t);
char buf[BUFSIZ]; 
FILE *rfp,*wfp;
void FileSearch(char file_path[])
{
	
	char buf[BUFSIZ];
	char data[BUFSIZ];
	scanf("%s",data);//check,temporary
	
	int i=0,check=0,t=0;
    intptr_t handle;
    char file_path2[_MAX_PATH];
 
    strcat(file_path, "\\");
    strcpy(file_path2, file_path);
    strcat(file_path, "*");
 
    if ((handle = _findfirst(file_path, &fd)) == -1)
    {
        printf("No such file or directory\n");
        return;
    }
    while (_findnext(handle, &fd) == 0)
    {
        char file_pt[_MAX_PATH];
        strcpy(file_pt, file_path2);
        strcat(file_pt, fd.name);
        check = isFileOrDir();    //file or dir
        if (check == 0 && fd.name[0] != '.')
        {
            FileSearch(file_pt);    //하위 디렉토리 검색 재귀함수
        }
        else if (check == 1 && fd.size != 0 && fd.name[0] != '.')
        //if (check == 1 && fd.size != 0 && fd.name[0] != '.')
		{
			printf("----------------------------------------\n");
            printf("file name : %s, size:%d\n", file_pt, fd.size);
            char *ptr1 = strstr(file_pt, ".c");
            char *ptr2 = strstr(file_pt, ".txt");
            //printf("%s",fd.name); //filename
			int yun;	
			if(ptr1){
				t=1;	
				if(yun=findkey(file_pt,data,t)){
					wfp = fopen("C:\\Users\\카르\\Desktop\\new\\save\\hh.c", "w+");
					if ((rfp = fopen(file_pt, "r"))== NULL){  
						perror("error"); 
						exit(1);  
					}
					while(fgets(buf,BUFSIZ,rfp)!=NULL){
						fputs(buf,wfp);
						//printf("correct");
					}
					fclose(wfp);
				}
			}
			else if(ptr2){
				t=2;
				if(yun=findkey(file_pt,data,t)){
					printf("correct");
				}	
			}
			printf("\n\n");
		}
	}
    printf("%d",i);
    _findclose(handle);
}
int main()
{
    char file_path[_MAX_PATH] = "C:\\Users\\카르\\Desktop\\new";    //C:\ path
    FileSearch(file_path);
    int n;
    while(1) //check,temporary
    scanf("%d",n);//check,temporary
    return 0;
}
int isFileOrDir()
{
    if (fd.attrib & _A_SUBDIR)
        return 0; // dir==0
    else
        return 1; // else== It does not exist file==1
}
int findkey(char file_pt[],char data[],int t){
	int truefalse=-1;
	if ((rfp = fopen(file_pt, "r")) == NULL){ //path 
		perror("error"); 
		exit(1);  
	}
	while(fgets(buf,BUFSIZ,rfp)!=NULL){
		char *ptr3=strstr(buf,data);
		if(ptr3){
			if(t==1){
				printf("c language file: %s \n",ptr3);
				return 1;}
			else if(t==2){
				printf("i am text file: %s \n",ptr3);
				return 1;}
		}
	}
	return 0;
	
}
