#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <Windows.h>
struct _finddata_t fd;
int isFileOrDir();
int findkey(char file_path[],char data[],int t);

char *encoding(char *dest, char *src);
char *decoding(char *dest, char *enstr);

int encodestart(char text[]);
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
            FileSearch(file_pt);    //ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ä¸® ï¿½Ë»ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ô¼ï¿½
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
					while(fgets(buf,BUFSIZ,rfp)!=NULL){//ÀÎÄÚµù ºÎ ºÐ 
						encodestart(buf);
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
	
    //char file_path[_MAX_PATH] = "C:\\Users\\Ä«¸£\\Desktop\\try";    //C:\ path
	char file_path[_MAX_PATH] = "C:\\Users\\Ä«¸£\\Desktop\\new";
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
int encodestart(char source[]){ //name change
    char en[100];
    char de[100];
 	int i=0;
    //printf("source: %s\n", source);
    encoding(en, source);//Encoding
    for(i=0;i<strlen(en);i++){
		printf("%d ",en[i]);
	}
	printf("\n");
    //printf("%s",en); //Encoding print 
    decoding(de, en); //decoding
    printf("%s", de); //decoding print
 	printf("\n");
    return 0;
}

char *encoding(char *dest, char *src) //caesar cipher Encoding
{
    char *origin;
    for (origin = dest; *src; dest++, src++)//Á¾·á ¹®ÀÚ¸¦ ¸¸³¯ ¶§±îÁö ¹Ýº¹
    {
        if (isupper(*src))//capital letter
        {
            *dest = (*src - 'A' + 8) % 26 + 'A';//8push 
        }
        if (islower(*src))//small letter
        {
            *dest = (*src - 'a' + 13) % 26 + 'a';//13push
        }
        if (isdigit(*src))//num
        {
            *dest = (*src - '0' + 4) % 10 + '0';//4push
        }
        if (isalnum(*src) == 0)
        {
            *dest = *src;
        }
    }
    *dest = '\0';
    return origin;
}
char *decoding(char *dest, char *en) //decoding  
{
    char *origin;
    for (origin = dest; *en; dest++, en++)//Á¾·á ¹®ÀÚ¸¦ ¸¸³¯ ¶§±îÁö ¹Ýº¹
    {
        if (isupper(*en))//capital letter
        {
            *dest = (*en - 'A' + 18) % 26 + 'A';//18push
        }
        if (islower(*en))//small letter
        {
            *dest = (*en - 'a' + 13) % 26 + 'a';//13push
        }
        if (isdigit(*en))//num
        {
            *dest = (*en - '0' + 6) % 10 + '0';//6push
        }
        if (isalnum(*en) == 0)
        {
            *dest = *en;
        }
    }
    *dest = '\0';
    return origin;

}


	   
