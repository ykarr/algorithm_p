#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <Windows.h>
struct _finddata_t fd;
int isFileOrDir()
{
    if (fd.attrib & _A_SUBDIR)
        return 0; // dir==0
    else
        return 1; // else== It does not exist file==1
}
void FileSearch(char file_path[])
{
	int i=0;
    intptr_t handle;
    int check = 0;
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
        //if (check == 0 && fd.name[0] != '.')
        //{
        //    FileSearch(file_pt);    //하위 디렉토리 검색 재귀함수
        //}
        //else if (check == 1 && fd.size != 0 && fd.name[0] != '.')
        if (check == 1 && fd.size != 0 && fd.name[0] != '.')
		{
			printf("----------------------------------------\n");
            printf("file name : %s, size:%d\n", file_pt, fd.size);
            char *ptr1 = strstr(file_pt, ".c");
            char *ptr2 = strstr(file_pt, ".txt");
			printf("c language file %s \n",ptr1);
            printf("txt file %s",ptr2);
		    printf("\n\n");
        }
        i++;
    }
    printf("%d",i);
    _findclose(handle);
}
int main()
{
    char file_path[_MAX_PATH] = "C:\\Users\\카르\\Desktop\\new";    //C:\ 경로 탐색
    FileSearch(file_path);
    int n;
    while(1) //check,temporary
    scanf("%d",n);//check,temporary
    return 0;
}

