#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <Windows.h>
#define PATHSIZE 50

struct _finddata_t fd;
int isFileOrDir();
int findkey(char file_path[],char data[],int t);

char *encoding(char *dest, char *src);
char *decoding(char *dest, char *enstr);

int encodestart(char source[]);
int decodestart(char source[]);
char buf[BUFSIZ];
char file_path[50];
char PATH[50];
FILE *rfp,*wfp;
void FileSearch(char file_path[])
{
    char buf[BUFSIZ];
    char data[BUFSIZ];
    printf("what data do you want to find?\n->");
    scanf("%s",data);//check,temporary

    int check=0,t=0;
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
        if (fd.size != 0 && fd.name[0] != '.')
        {   
            printf("----------------------------------------\n");
            printf("file name : %s, size:%d\n", file_pt, fd.size);
            char *ptr1 = strstr(file_pt, ".c");
            char *ptr2 = strstr(file_pt, ".txt");
            char savefilepath[BUFSIZ];
            int bbb;
            int yun;
            if(ptr1){
               t=1;
               if(yun=findkey(file_pt,data,t)){
                     sprintf(savefilepath,"%s\\save\\%s",PATH,fd.name);
                     wfp = fopen(savefilepath, "w+");
                     if ((rfp = fopen(file_pt, "r"))== NULL){
                        perror("error");
                        exit(1);
                     }
                     int i=0;
                     while(fgets(buf,BUFSIZ,rfp)!=NULL){//인코딩 부 분 
                        encodestart(buf);
                           fprintf(wfp,"%s",buf);
                        i++;
                     }
                  fclose(rfp);
                   fclose(wfp);
               }
            }
            else if(ptr2){
               t=2;
               if(yun=findkey(file_pt,data,t)){
                  sprintf(savefilepath,"%s\\save\\%s",PATH,fd.name);
                  wfp=fopen(savefilepath,"w+");
                  if((rfp=fopen(file_pt,"r"))==NULL)
                  {
                     perror("error");
                     exit(1);
               }
               while(fgets(buf,BUFSIZ,rfp)!=NULL)
               {
                  encodestart(buf);
                  if(buf!=NULL);
                     fprintf(wfp,"%s\n",buf);
               }
               fclose(rfp);
               fclose(wfp);         
               }
            }
            printf("\n\n");
         }
      
   }
    _findclose(handle);
}
int main(int argc, char* argv[])
{
   int n;
    FILE *rf,*wf;   
   char system1[PATHSIZE];
   char system2[PATHSIZE];
   //char file_path[_MAX_PATH] = "C:\\Users\\카르\\Desktop\\try";    //C:\ path
    printf("find dir path:(ex)D:\\\\algorithm))\n->");
    scanf("%s",file_path);
    strcpy(PATH,file_path);
    sprintf(system1,"mkdir %s\\save",PATH);
    sprintf(system2,"mkdir %s\\decode",PATH);
   
   system(system1);
    system(system2);
    //FileSearch(file_path);

    while(1){ //check,temporary
    
      int select=0;
      int j=0;
      char decodefile[30];
      printf("what do you want?\n-encoding:1,decoding:2,exit:default\n");
      scanf("%d",&select);
      char debuf[BUFSIZ];
      char depath[BUFSIZ];
      char path[BUFSIZ];
      switch(select)
      {
         case 1:
            FileSearch(file_path);
            printf("Encoding is finished.\ncheck your save file\n");
            break;
         case 2:
            printf("what file do you want to decode?\n");
            scanf("%s",&decodefile);
            sprintf(depath,"%s\\decode\\%s",PATH,decodefile);
            sprintf(path,"%s\\save\\%s",PATH,decodefile);
            wf=fopen(depath,"w+");
            if((rf=fopen(path,"r"))==NULL)
               {
                  perror("error");
                  exit(1);
            }
            while(fgets(debuf,BUFSIZ,rf)!=NULL)
            {
               decodestart(debuf);
               fprintf(wf,"%s",debuf);
            }
            fclose(rf);
            fclose(wf);
            printf("Decoding is finished.\ncheck your decode file\n");
            break;
         default:
            printf("finished");
            return 0;
      }
   }
    return -1;
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
            printf("c language file: %s",ptr3);
            return 1;}
         else if(t==2){
            printf("i am text file: %s",ptr3);
            return 1;}
      }
   }
   return 0;

}
int encodestart(char source[]){ //name change
    char en[100];
   int i=0;
   
    char *een=encoding(en, source);//Encoding
    for(i=0;i<strlen(en)-1;i++){
         source[strlen(en)-2-i]=en[i];
    }
    return 0;
}
int decodestart(char source[])
{
   char de[100];
   
   int i=0;
   
   decoding(de,source);
   for(i=0;i<strlen(de)-1;i++){
      source[strlen(de)-2-i]=de[i];
   }
   return 0;
}
char *encoding(char *dest, char *src) //caesar cipher Encoding
{
    char *origin;
    for (origin = dest; *src; dest++, src++)//종료 문자를 만날 때까지 반복
    {
        if (isupper(*src))//capital letter        
            *dest = (*src - 'A' + 8) % 26 + 'A';//8push        
        if (islower(*src))//small letter       
            *dest = (*src - 'a' + 13) % 26 + 'a';//13push       
        if (isdigit(*src))//num     
            *dest = (*src - '0' + 4) % 10 + '0';//4push       
        if (isalnum(*src) == 0)     
            *dest = *src;      
    }
    *dest = '\0';
    return origin;
}
char *decoding(char *dest, char *en) //decoding  
{
    char *origin;
    for (origin = dest; *en; dest++, en++)//종료 문자를 만날 때까지 반복
    {
        if (isupper(*en))//capital letter        
            *dest = (*en - 'A' + 18) % 26 + 'A';//18push      
        if (islower(*en))//small letter    
            *dest = (*en - 'a' + 13) % 26 + 'a';//13push    
        if (isdigit(*en))//num      
            *dest = (*en - '0' + 6) % 10 + '0';//6push    
        if (isalnum(*en) == 0)      
            *dest = *en;
    }
    *dest = '\0';
    return origin;

}
