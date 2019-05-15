#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <Windows.h>
struct _finddata_t fd;
int isFileOrDir();
int findkey(char file_path[],char data[],int t);
int encode(char text[]);
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
            FileSearch(file_pt);    //���� �����丮 �˻� �����Լ�
        }
        else if (check == 1 && fd.size != 0 && fd.name[0] != '.')
        //if (check == 1 && fd.size != 0 && fd.name[0] != '.')
		{
			printf("----------------------------------------\n");
            printf("file name : %s, size:%d\n", file_pt, fd.size);
            char *ptr1 = strstr(file_pt, ".c");
            char *ptr2 = strstr(file_pt, ".txt");
            char savefilepath[BUFSIZ];
            int bbb;
            //printf("%s",fd.name); //filename
			int yun;
			if(ptr1){
				t=1;
				int i=0,j=0;
				char text[900];
				if(yun=findkey(file_pt,data,t)){
					sprintf(savefilepath,"c:\\save\\%s",fd.name);
					wfp = fopen(savefilepath, "w+");
					if ((rfp = fopen(file_pt, "r"))== NULL){
						perror("error");
						exit(1);
					}
					while(fgets(buf,BUFSIZ,rfp)!=NULL){
						encode(buf);
					//	fputs(buf,wfp);
					//	sprintf("correct");
					}
//					for(i=0;i<j;i++)
//						fprintf(wfp,"%d\n",buf);
					//while((bbb=fgetc(rfp))!=EOF){
						
					//	fprintf(wfp,"%d",bbb);
						//sprintf("correct");
					//}
//					while((bbb=fgetc(rfp))!=EOF){
//						char text[]=bbb;
//						printf(wfp,"%c",bbb);
//						//sprintf("correct");
//					}
					
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
    char file_path[_MAX_PATH] = "C:\\Users\\ī��\\Desktop\\try";    //C:\ path
	system("mkdir C:\\save");
    FileSearch(file_path);
    int n;
	while(1) //check,temporary
    scanf("%d",n);//check
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
int encode(char text[]){
	//fputs(buf,wfp);
	int i=0;
	int bf;
	for(i=0;i<strlen(text)+1;i++){
		bf=(int)text[i];
		bf=bf+1;
		text[i]=(char)bf;
		printf("%c",text[i]);
	}
	printf("\n");
}
