#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
void CreateFile(char *info);
void Cat(char *info);
void Insert(char *info);
void Remove(char *info);
void Copy(char *info);
void Cut(char *info);
void Paste(char *info);
void Find(char *info);
void ClosingPair(char *info);
void TextComparator(char *info);
void Tree(char *info);
void AllTree(char *Address);
void TreeWithDepth(char *Address,int maxdepth,int currentdepth);
void Grep(char *info);
void NormalGrep(char *FileAddress,char *Pattern);
int GrepWithC(char *FileAddress,char *Pattern);
void GrepWithL(char *FileAddres,char *Pattern);
void Undo(char *info);
void BackUp(char *fileAddress);

void NormalFind(char *WhatIWantToFind, char *FileAddress);

void FindWithCount(char *WhatIWantToFind, char *FileAddress);

void FindWithAt(char *WhatIWantToFind, char *FileAddress, int pos);

void FindByWord(char *WhatIWantToFind,char *FileAddress);

void FindAll(char *WhatIWantToFind,char *FileAddress,int mode);

void Replace(char *info);

void NormalReplace(char *ContentsOfFile,char *WhatIWantToFind,char *WhatIWantToReplace,char *FileAddress);

void ReplaceWithAt(char *ContentsOfFile, char *WhatIWantToFind, char *WhatIWantToReplace, char *FileAddress,int at);

void ReplaceAll(char *ContentsOfFile, char *WhatIWantToFind, char *WhatIWantToReplace, char *FileAddress);



int main() {
    mkdir("root");

    char Commend[1000]={0};


    while (1)
    {
        char FirstWord[1000];


        fgets(Commend,1000,stdin);
        sscanf(Commend,"%s",FirstWord);


        if (strcmp(FirstWord, "createfile") == 0)
            CreateFile(Commend);

        else if (strcmp(FirstWord,"cat")==0)
        Cat(Commend);

        else if (strcmp(FirstWord,"insertstr")==0)
            Insert(Commend);
        else if (strcmp(FirstWord,"removetstr")==0)
            Remove(Commend);
        else if (strcmp(FirstWord,"copystr")==0)
            Copy(Commend);
        else if (strcmp(FirstWord,"cutstr")==0)
            Cut(Commend);
        else if (strcmp(FirstWord,"pastestr")==0)
            Paste(Commend);
        else if (strcmp(FirstWord,"find")==0)
            Find(Commend);
        else if (strcmp(FirstWord,"auto-indent")==0)
            ClosingPair(Commend);
        else if(strcmp(FirstWord,"compare")==0)
            TextComparator(Commend);
        else if(strcmp(FirstWord,"tree")==0)
            Tree(Commend);
        else if(strcmp(FirstWord,"grep")==0)
            Grep(Commend);
        else if(strcmp(FirstWord,"find")==0)
            Find(Commend);
        else if(strcmp(FirstWord,"replace")==0)
            Replace(Commend);
        else if (strcmp(FirstWord,"exit") == 0) {
            break;
        }
        else
            printf("invalid command");
    }
    return 0;
}

void CreateFile(char *info)
{
    char FunctionName[10];
    char FullAddress[10000];
    char UntilNow[10000];

    sscanf(info,"%s",FunctionName);
    strcpy(FullAddress,(info+25));




    int j=0;

    for (int i = 0; i < strlen(FullAddress); ++i) {
        if(FullAddress[i]=='\n')
            break;

        else if(FullAddress[i]!='/'&&FullAddress[i]!='\n')
        {
           UntilNow[j]=FullAddress[i];
           j++;
        }


        else
        {

            struct stat st = {0};
            if (stat(UntilNow, &st) == -1) {
                mkdir(UntilNow);
            }
            UntilNow[j]='/';
            j++;
        }
    }

   FILE *ads =fopen(UntilNow,"r");
    if(ads) {
        printf("File Already Exists");
        fclose(ads);
    }
    else {
        fclose(ads);
        ads=fopen(UntilNow, "w");
        fclose(ads);
    }


}

void Cat(char *info)
{
    char FunctionName[15];
    char FileAddress[1000]={0};
    char Data;
    strcpy(FileAddress,(info+10));
    FileAddress[strlen(FileAddress)-1]='\0';


    FILE *Source= fopen(FileAddress,"r");

    if(Source==NULL)
        printf("Error Occurred while Opening the File!");
    else
    {
        while(1) {
            char c = fgetc(Source);
            if( feof(Source) ) {
                break;
            }
            printf("%c", c);
        }
        printf("\n");
    }
    fclose(Source);

}

void Insert(char *info)
{
    char Function[9];
    char FileAdress[1000];
    char str[1000];
    char CurrentLine[1000];
    int line,position;
    char StrWeWantToAdd[1000];
    sscanf(info,"%s %s %s %s %s %s %d%c%d",Function,Function,FileAdress,Function,StrWeWantToAdd,Function,&line,&Function[0],&position);
    FILE *Fileforhelp = fopen("help.txt","w+");
    FILE* MainFile = fopen(FileAdress,"r");

    for (int i = 1; i <line ; ++i) {
        fgets(str,1000,MainFile);
        fputs(str,Fileforhelp);
    }
    fgets(CurrentLine,1000,MainFile);
    char TheNewStr[1000];
    for (int i = 0; i < position; ++i) {
        TheNewStr[i]=CurrentLine[i];
    }
    strcpy(TheNewStr+position,StrWeWantToAdd);
    strcpy(TheNewStr+position+ strlen(StrWeWantToAdd),CurrentLine+position);
    fputs(TheNewStr,Fileforhelp);
    while(1)
    {
        fgets(str,1000,MainFile);
        fputs(str,Fileforhelp);
        if(feof(MainFile))
            break;
    }
    rewind(Fileforhelp);
    FILE *mainFile = fopen(FileAdress,"w");
    while (1)
    {
        fgets(str,1000,Fileforhelp);
        fputs(str,mainFile);
        if(feof(Fileforhelp))
            break;
    }
    fclose(mainFile);
    fclose(Fileforhelp);
    remove("help.txt");
}

void Remove(char * info)
{
    char Fileaddress[1000],Junk[1000],Side;
    int Line,Pos,Size;
    sscanf(info,"%s %s %s %s %d%c%d %s %d %c%c ",Junk,Junk,Fileaddress,Junk,&Line,&Side,&Pos,Junk,&Size,&Side,&Side);

    int CurrentLine=1,CurrentPos=0;
    char c;
    FILE *MainFile= fopen(Fileaddress,"r");
    char NewContent[10000];

    for (int i = 0;; ++i) {
        if (CurrentLine == Line && CurrentPos == Pos)
        {
            if(Side=='f')
            {
                for (int j = 0; j < Size; ++j) {
                    c= getc(MainFile);
                }
            }
            else
            {
                for (int j = Size; j >0 ; --j) {
                    NewContent[i-j] = getc(MainFile);
                }
            }
        }

        c= getc(MainFile);
        if(c=='\n')
        {
            CurrentLine++;
            CurrentPos=-1;
        }
        else if( feof(MainFile))
            break;
        CurrentPos++;
        NewContent[i]=c;
    }



    fclose(MainFile);
    FILE *NewFile= fopen(Fileaddress,"w");
    fputs(NewContent,NewFile);
    fclose(NewFile);
}

void Copy(char *info) {
    char Fileaddress[1000], Junk[1000], Side;
    int Line, Pos, Size;
    sscanf(info, "%s %s %s %s %d%c%d %s %d %c%c ", Junk, Junk, Fileaddress, Junk, &Line, &Side, &Pos, Junk, &Size,
           &Side, &Side);
    int CurrentLine = 1, CurrentPos = 0;
    char c;
    FILE *MainFile = fopen(Fileaddress, "r");
    char WhatIWantToCopy[10000];


    while (1) {
        if (CurrentLine == Line && CurrentPos == Pos) {
            if (Side == 'f') {
                for (int j = 0; j < Size; ++j)
                    WhatIWantToCopy[j] = getc(MainFile);
                break;
            } else {
                fseek(MainFile, -Size-1, SEEK_CUR);


                for (int j = 0; j < Size; ++j)
                    WhatIWantToCopy[j] = getc(MainFile);
                break;


            }
        }

        c = getc(MainFile);


        if (c == '\n') {
            CurrentLine++;
            CurrentPos = -1;
        }
        else if (feof(MainFile))
            break;
        CurrentPos++;
    }
    FILE *ClipBoard= fopen("clipboard.txt","w");
    fputs(WhatIWantToCopy,ClipBoard);
    fclose(ClipBoard);
}

void Cut(char *info)
{
    Copy(info);
    Remove(info);
}

void Paste(char *info)
{
    char Junk[20],FileAddress[1000],Stop,WhatIWantToAdd[1000];
    int Line,Pos;
    sscanf(info,"%s %s %s %s %d%c%d",Junk,Junk,FileAddress,Junk,&Line,&Stop,&Pos);
    FILE *Clip= fopen("clipboard.txt","r");
    for (int i = 0;; ++i) {
        WhatIWantToAdd[i] = getc(Clip);
                if(feof(Clip))
                    break;
    }
    int CurrentLine =1,CurrentPos=0;
    FILE *WhereIWantToAdd= fopen(FileAddress,"r");
    char  c, NewContent[10000];

        for (int i = 0;; ++i) {
            if (CurrentLine == Line && CurrentPos == Pos)
            {
                strcat(NewContent,WhatIWantToAdd);
                i+= strlen(WhatIWantToAdd)-1;
            }

            c= getc(WhereIWantToAdd);
            if(c=='\n')
            {
                CurrentLine++;
                CurrentPos=-1;
            }
            else if( feof(WhereIWantToAdd))
                break;
            CurrentPos++;
            NewContent[i]=c;
        }


    FILE *where= fopen(FileAddress,"w");
    fputs(NewContent,where);
    fclose(where);
    }

void Find(char *info)
{
    char FileAddress[10000],WhatIWantToFind[10000],Junk[100];
    int mode[5],WithQuote=0;
    mode[0]=1;
       char c=info[10];
    if(c=='\"') {
        WithQuote=1;
        int i=11;
        int j=0;
        while(1)
        {
            c=info[i];
            if(c=='"')
                break;
            WhatIWantToFind[j]=c;
            i++;
            j++;
        }
        sscanf(&info[i+8],"%s",FileAddress);


    }
    else
    {
        sscanf(info,"%s %s %s %s %s ",Junk,Junk,WhatIWantToFind,Junk,FileAddress);
    }
    char ContentsOfFile[10000];
    int i=0;
    int pos;
    FILE *MainAddress= fopen(FileAddress,"r");
    while(1)
    {
        if(feof(MainAddress))
            break;
        c= getc(MainAddress);
        ContentsOfFile[i]=c;
        i++;
    }

    if(strstr(WhatIWantToFind,"*")&&!WithQuote) {
        for (int j = 0; j < strlen(WhatIWantToFind); ++j) {
            if (WhatIWantToFind[j] == '*') {
                if (WhatIWantToFind[j - 1] != '\\') {
                    for (int k = j + 1; k <= strlen(WhatIWantToFind); ++k) {
                        WhatIWantToFind[k - 1] = WhatIWantToFind[k];
                    }
                }
                else {
                    for (int k = j; k <= strlen(WhatIWantToFind); ++k) {
                        WhatIWantToFind[k - 1] = WhatIWantToFind[k];
                    }
                }
            }
        }
    }
//    else if(strstr(WhatIWantToFind,"*")&&WithQuote) {
//
//    }
//    else
//    {
        if(strstr(info,"-count"))
        {
            mode[1]=1;
        }
        if(strstr(info,"-at"))
        {
            mode[2]=1;
            char *help;
            help= strstr(info,"-at");
            sscanf(help,"%s %d",Junk,&pos);
        }
        if(strstr(info,"-byword"))
        {
            mode[3]=1;
        }
        if(strstr(info,"-all"))
        {
            mode[4]=1;
        }
        if(mode[2]&&mode[4])
        {
            printf("invalid combination");
            return;
        }
        if(mode[1]+mode[2]+mode[3]+mode[4]==0)
        {
            NormalFind(WhatIWantToFind,FileAddress);
            return;
        }
        if(mode[4])
        {
            if(mode[3])
                FindAll(WhatIWantToFind,FileAddress,0);
            else
                FindAll(WhatIWantToFind,FileAddress,1);
            return;
        }
        if(mode[1])
        {
            FindWithCount(WhatIWantToFind,FileAddress);
        }
        if(mode[2])
        {
            FindWithAt(WhatIWantToFind,FileAddress,pos);
        }

        if(mode[3])
        {
            FindByWord(WhatIWantToFind,FileAddress);
        }
    }

void FindWithAt(char *WhatIWantToFind, char *FileAddress, int pos) {
    FILE *file = fopen(FileAddress,"r");
    if(file==NULL) {
        printf("There is no file with this name");
        return;
    }
    char ContentsOfFile[1000];
    memset(ContentsOfFile,'\0',1000);
    char c='\n';
    ContentsOfFile[0]= fgetc(file);
    int i=1,count=0;
    while(!feof(file))
    {
        if(c!='\n')
        {
            ContentsOfFile[i]=c;
            i++;
        }
        c= fgetc(file);
    }
    char *p= strstr(ContentsOfFile,WhatIWantToFind);
    if(p==NULL)
    {
        printf("the thing you are looking for don't exist in the file\n");
        return;
    }
    else {
        count++;
        while(1)
        {
            p=strstr((p+ strlen(WhatIWantToFind)),WhatIWantToFind);
            if(p==NULL)
                break;
            count++;
            {
                if(count==(pos))
                {
                    printf("%d\n", strlen(ContentsOfFile)- strlen(p));
                    return;
                }
            }
        }
        printf("invalid at\n");
    }
}

void FindWithCount(char *WhatIWantToFind, char *FileAddress) {
    FILE *file = fopen(FileAddress,"r");
    if(file==NULL)
        printf("There is no file with this name");
    char ContentsOfFile[1000];
    memset(ContentsOfFile,'\0',1000);
    char c='\n';
    ContentsOfFile[0]= fgetc(file);
    int i=1,count=0;
    while(!feof(file))
    {
        if(c!='\n')
        {
            ContentsOfFile[i]=c;
            i++;
        }
        c= fgetc(file);
    }
    char *p= strstr(ContentsOfFile,WhatIWantToFind);
    if(p==NULL)
    {
        printf("the thing you are looking for don't exist in the file ");
        return;
    }
    else
    {
        count++;
        while(1)
        {
            p=strstr((p+ strlen(WhatIWantToFind)),WhatIWantToFind);
            if(p==NULL)
                break;
            count++;

        }
        printf("%d\n",count);
    }

}

void NormalFind(char *WhatIWantToFind, char *FileAddress) {

    FILE *file = fopen(FileAddress,"r");
    if(file==NULL) {
        printf("There is no file with this name");
        return;
    }
        char ContentsOfFile[1000];
    memset(ContentsOfFile,'\0',1000);
    char c='\n';
    ContentsOfFile[0]= fgetc(file);
    int i=1;
    while(!feof(file))
    {
        if(c!='\n')
        {
            ContentsOfFile[i]=c;
            i++;
        }
        c= fgetc(file);
    }
    char *p= strstr(ContentsOfFile,WhatIWantToFind);
    if(p==NULL)
    {
        printf("the thing you are looking for don't exist in the file ");
        return;
    }
    else
    {
        int result = strlen(ContentsOfFile);
        result-= strlen(p);
        printf("%d\n",result );
    }
}

void FindByWord(char *WhatIWantToFind,char *FileAddress)
{
    FILE *file = fopen(FileAddress,"r");
    if(file==NULL) {
        printf("There is no file with this name");
        return;
    }
    char ContentsOfFile[1000];
    memset(ContentsOfFile,'\0',1000);
    char c='\n';
    ContentsOfFile[0]= fgetc(file);
    int i=1;
    while(!feof(file))
    {
        if(c!='\n')
        {
            ContentsOfFile[i]=c;
            i++;
        }
        c= fgetc(file);
    }
    char *p= strstr(ContentsOfFile,WhatIWantToFind);
    if(p==NULL)
    {
        printf("the thing you are looking for don't exist in the file ");
        return;
    }
    else
    {
        int result = strlen(ContentsOfFile);
        result-= strlen(p);
        int count=1;
        for (int j = 0; j < result; ++j) {
            if(ContentsOfFile[j]==' ')
                count++;
        }
        printf("%d\n",count);
    }
}

void FindAll(char *WhatIWantToFind,char *FileAddress,int mode)
{
    FILE *file = fopen(FileAddress,"r");
    if(file==NULL)
        printf("There is no file with this name");
    char ContentsOfFile[1000];
    memset(ContentsOfFile,'\0',1000);
    char c='\n';
    ContentsOfFile[0]= fgetc(file);
    int i=1,count=0;
    while(!feof(file))
    {
        if(c!='\n')
        {
            ContentsOfFile[i]=c;
            i++;
        }
        c= fgetc(file);
    }
    char *p= strstr(ContentsOfFile,WhatIWantToFind);
    if(p==NULL)
    {
        printf("the thing you are looking for don't exist in the file ");
        return;
    }
    else
    {
        if(mode==1)
        {
            printf("%d ", strlen(ContentsOfFile)- strlen(p));
        }
        else
        {
            int Count=1;
            for (int j = 0; j < strlen(ContentsOfFile)- strlen(p); ++j)
                if(ContentsOfFile[j]==' ')
                    count++;
            printf("%d",Count);
        }


        while(1)
        {
            p=strstr((p+ strlen(WhatIWantToFind)),WhatIWantToFind);
            if(p==NULL)
                break;
            if(mode==1)
            {
                printf(" %d ", strlen(ContentsOfFile)- strlen(p));
            }
            else
            {
                int Count=1;
                for (int j = 0; j < strlen(ContentsOfFile)- strlen(p); ++j)
                    if(ContentsOfFile[j]==' ')
                        Count++;
                printf(" %d",Count);
            }
        }
    }
}

void Replace(char *info) {
    char WhatIWantToFind[100];
    int at=0;

    char WhatIWantToReplace[100];
    char FileAddress[100];

    char c;

    char *p;
    p = strstr(info, "-str1");
    int i, j;
    c=p[6];
        if (c == '"') {
            i = 7;
            j = 0;
            while (1) {
                c=p[i];
                if (c == '"')
                    break;
                WhatIWantToFind[j] = c;
                i++;
                j++;
            }
        }

        else {
            i = 6;
            j = 0;
            while (1) {
                c=p[i];
                if (c == " ")
                    break;
                WhatIWantToFind[j] = c;
                i++;
                j++;
            }

        }

    p = strstr(info, "-str2");
        c= p[6];
    if (c == '"') {
        i = 7;
        j = 0;
        while (1) {
            c=p[i];
            if (c == '"')
                break;
            WhatIWantToReplace[j] = c;
            i++;
            j++;
        }
    }

    else {
        i = 6;
        j = 0;
        while (1) {
            c=p[i];
            if (c == " ")
                break;
            WhatIWantToReplace[j] = p[i];
            i++;
            j++;
        }
    }

    p = strstr(info, "-file");

    sscanf(p+6,"%s ",FileAddress);

    if(strstr(info,"-at"))
    {
        p=strstr(info,"-at");
        sscanf(p+4,"%d",&at);
    }


    //take contents

    char ContentsOfFile[10000];
    int k=0;
    int pos;
    FILE *MainAddress= fopen(FileAddress,"r");
    while(1)
    {
        c= getc(MainAddress);
        if(feof(MainAddress)) {
            break;
        }
        ContentsOfFile[k]=c;
        k++;
    }

    if(strstr(info,"-at"))
        ReplaceWithAt(ContentsOfFile,WhatIWantToFind,WhatIWantToReplace,FileAddress,at);
    else if (strstr(info,"-all"))
        ReplaceAll(ContentsOfFile,WhatIWantToFind,WhatIWantToReplace,FileAddress);
    else
        NormalReplace(WhatIWantToFind,WhatIWantToReplace,FileAddress);
}

void NormalReplace(char *ContentsOfFile, char *WhatIWantToFind, char *WhatIWantToReplace, char *FileAddress) {

    char NewContent[1000],help[1000];
    char *x;
    x=strstr(ContentsOfFile,WhatIWantToFind);
    int size=strlen(ContentsOfFile)- strlen(x);

    for (int l = 0; l < size ; ++l) {
        NewContent[l]=ContentsOfFile[l];
    }
    strcat(NewContent,WhatIWantToReplace);
    strcat(NewContent,ContentsOfFile+size+ strlen(WhatIWantToFind));
    FILE *file= fopen(FileAddress,"w");
    fputs(NewContent,file);
    fclose(file);

}

void ReplaceWithAt(char *ContentsOfFile, char *WhatIWantToFind, char *WhatIWantToReplace, char *FileAddress,int at) {

    char NewContent[1000];
    char *x;
    int count=0;
    x=strstr(ContentsOfFile,WhatIWantToFind);
    if(x==NULL)
    {
        printf("the thing you are looking for don't exist in the file\n");
        return;
    }
    else {
        count++;
        if(count==at) {
            int size = strlen(ContentsOfFile) - strlen(x);
            for (int l = 0; l < size; ++l) {
                NewContent[l] = ContentsOfFile[l];
            }
            strcat(NewContent, WhatIWantToReplace);
            strcat(NewContent, ContentsOfFile + size + strlen(WhatIWantToFind));

        }
        else {
            while (1) {
                x = strstr((x + strlen(WhatIWantToFind)), WhatIWantToFind);
                if (x == NULL)
                    break;
                count++;
                {
                    if (count == (at)) {
                        int size = strlen(ContentsOfFile) - strlen(x);

                        for (int l = 0; l < size; ++l) {
                            NewContent[l] = ContentsOfFile[l];
                        }
                        strcat(NewContent, WhatIWantToReplace);
                        strcat(NewContent, ContentsOfFile + size + strlen(WhatIWantToFind));
                        FILE *file= fopen(FileAddress,"w");
                        fputs(NewContent,file);
                        fclose(file);
                        return;
                    }
                }
            }
        }
    }
    printf("invalid at");
    return;


}

void ReplaceAll(char *ContentsOfFile, char *WhatIWantToFind, char *WhatIWantToReplace, char *FileAddress){
    char NewContent[1000],NewNewContent[1000];
    char *x;
    int count=0;
    x=strstr(ContentsOfFile,WhatIWantToFind);
    if(x==NULL)
    {
        printf("the thing you are looking for don't exist in the file\n");
        return;
    }
    else {
        int size = strlen(ContentsOfFile) - strlen(x);

        for (int l = 0; l < size; ++l) {
            NewContent[l] = ContentsOfFile[l];
        }
        strcat(NewContent, WhatIWantToReplace);
        strcat(NewContent, ContentsOfFile + size + strlen(WhatIWantToFind));
        strcpy(x,NewContent);

        while (1) {
            x = strstr(x, WhatIWantToFind);
            if (x == NULL)
                break;

            int size = strlen(NewContent) - strlen(x);
            memset(NewNewContent,'\0',1000);
            for (int l = 0; l < size; ++l) {
                NewNewContent[l] = NewContent[l];
            }
            strcat(NewNewContent, WhatIWantToReplace);
            strcat(NewNewContent, NewContent + size + strlen(WhatIWantToFind));
            strcpy(NewContent,NewNewContent);
            strcpy(x,NewContent);
        }
    }
    FILE *file= fopen(FileAddress,"w");
    fputs(NewContent,file);
    fclose(file);

}

void ClosingPair(char *info) {
    char Trash[11],FileAddress[1000];
    sscanf(info,"%s %s",Trash,FileAddress);


    //reading the file
    char Contents[1000];
    memset(Contents,'\0',1000);
    FILE *FileTHatIWantToFix = fopen(FileAddress,"r");
    int i=0,Countclose=0,Brace=0,countopen=0;
    while (1) {
        char c= fgetc(FileTHatIWantToFix);
        if(feof(FileTHatIWantToFix))
            break;
        Contents[i]=c;
        //puting space before '{'
        if(Contents[i]=='{' && Contents[i-1]!=' ' &&i!=0)
        {
            Contents[i]=' ';
            Contents[i+1]='{';
            i++;
        }

        if(Contents[i]=='{') {
            Brace++;
            countopen++;
            //removing spaces after

            while (1) {
                c = fgetc(FileTHatIWantToFix);
                if (c != ' ')
                    break;
            }
            fseek(FileTHatIWantToFix, -1, SEEK_CUR);


            //removing spaces before
            if(countopen==1) {
                int before = 1;
                while (1) {
                    if (Contents[i - before] != ' ') {
                        break;
                    }
                    before++;
                }

                if (before > 2) {
                    for (int j = i - before + 2; j <= i; ++j) {
                        Contents[j] = Contents[j + before - 2];
                    }
                    i = i - before + 2;
                }
            }
            //fixing \n and 4space

            Contents[i+1]='\n';
            for (int j = 0; j < Brace*4; ++j)
                Contents[i+j+2]=' ';
            i+=Brace*4+1;



        }

        else if(Contents[i]=='}')
        {
            Countclose++;
            //spaces after
            while (1) {
                c = fgetc(FileTHatIWantToFix);
                if (c != ' ')
                    break;
            }
            if(c!=-1)
                fseek(FileTHatIWantToFix, -1, SEEK_CUR);


            //spaces before the first
            if(Countclose==1)
            {
                int before=1;
                while(1)
                {
                    if(Contents[i-before]!=' ') {
                        break;
                    }
                    before++;
                }

                if(before>2)
                {
                    for (int j = i-before+1; j <=i ; ++j) {
                        Contents[j]=Contents[j+before-1];
                    }
                    i=i-before+1;
                }

            }
            Brace--;
            Contents[i]='\n';
            for (int j = 0; j < Brace*4; ++j)
                Contents[i+j+1]=' ';
            Contents[i+Brace*4+1]='}';
            i+=Brace*4+1;
            Contents[i+1]='\n';
            i+=1;
        }


        i++;
    }

    fclose(FileTHatIWantToFix);
    FileTHatIWantToFix= fopen(FileAddress,"w");
    fputs(Contents,FileTHatIWantToFix);
    fclose(FileTHatIWantToFix);

}

void Undo(char *info) {
}
void BackUp(char *fileAddress) {
}

void TextComparator(char *info) {
    char FileAddress1[1000],FileAddress2[1000],trash[7];
    sscanf(info,"%s %s %s",trash,FileAddress1,FileAddress2);
    int File1Line=0,File2Line=0,count=0;
    char FileOneInfo[1000],FileTwoInfo[1000];
    int mode;
    FILE *file1= fopen(FileAddress1,"r");
    FILE *file2= fopen(FileAddress2,"r");
    //count the \n in file 1
    char c;
    while(1)
    {
        c= getc(file1);
        if(c=='\n')
            File1Line++;
        if(feof(file1))
            break;
    }
    //count the \n in file 2
    while(1)
    {
        c= getc(file2);
        if(c=='\n')
            File2Line++;
        if(feof(file2))
            break;
    }
    fseek(file1,0,SEEK_SET);
    fseek(file2,0,SEEK_SET);
    while(1) {
        fgets(FileOneInfo, 1000, file1);
        fgets(FileTwoInfo, 1000, file2);
        count++;
        if(strcmp(FileOneInfo,FileTwoInfo))
        {
            printf("\n============ #%d ============\n",count);
            puts(FileOneInfo);
            printf("\n");
            puts(FileTwoInfo);
            printf("\n");
        }
        if (feof(file1)) {
            break;
        }
        else if (feof(file2)) {
            break;
        }
    }
    while(1)
    {
        if(File2Line>File1Line)
        {
            printf(">>>>>>>>>>>> #%d - #%d>>>>>>>>>>>>\n",count+1,File2Line+1);
            fgets(FileTwoInfo,1000,file2);
            puts(FileTwoInfo);
            if(feof(file2))
                break;
            printf("\n");
        }
        else if(File2Line<File1Line)
        {
            printf("<<<<<<<<<<<< #%d - #%d<<<<<<<<<<<<\n",count+1,File2Line+1);
            fgets(FileOneInfo,1000,file1);
            puts(FileOneInfo);
            if(feof(file1))
                break;
            printf("\n");
        }
    }
}

void Tree(char *info) {
    char trash[4];
    int depth;
    sscanf(info,"%s %d",trash,&depth);
    if(depth<-1)
        printf("invalid depth");
    if(depth==-1)
    {
        AllTree("\Root");
    }
    else
    {
        TreeWithDepth("\Root",depth,0);

    }


}

void AllTree(char *Address) {        //www.ibm.com
    DIR *dir;
    struct dirent *entry;
    char FilePath[1000];
    char EntryName[1000];

    dir = opendir(Address);
            if (!dir)
            return;

    while ((entry = readdir(dir)) != NULL) {
        strcpy(EntryName,entry->d_name);
        if (strcmp(entry->d_name, ".") != 0&&strcmp(entry->d_name, "..") != 0) {
            strcpy(FilePath, Address);
            strcat(FilePath, "\\");
            strcat(FilePath, entry->d_name);
            printf("%s\n", FilePath);
            AllTree(FilePath);
        }
    }
    closedir(dir);
}

void TreeWithDepth(char *Address, int maxdepth,int currentdepth) {
    DIR *dir;
    struct dirent *entry;
    char FilePath[1000];
    char EntryName[1000];

    dir = opendir(Address);
    if (!dir)
        return;

    while ((entry = readdir(dir)) != NULL) {
        strcpy(EntryName,entry->d_name);
        if (strcmp(entry->d_name, ".") != 0&&strcmp(entry->d_name, "..") != 0) {
            if(currentdepth<=maxdepth) {
                strcpy(FilePath, Address);
                strcat(FilePath, "\\");
                strcat(FilePath, entry->d_name);
                printf("%s\n", FilePath);
                TreeWithDepth(FilePath,maxdepth,currentdepth+1);
            }
        }
    }
    closedir(dir);
}

void Grep(char *info) {

    char BackUpInfo[1000];
    strcpy(BackUpInfo,info);
    char *token = strtok(info, " ");
    char Pattern[100];
    char FileAddreses[100];
    char c=34;
    int count=0,ForC=0;
    while (token != NULL) {
//        printf("%s\n",token);
        if(strstr(token,"\""))
        {
            strcpy(Pattern,(token+1));
            Pattern[strlen(Pattern)-1]='\0';
        }
        else if(strstr(token,".txt"))
        {
            strcpy(FileAddreses,token);
            if(strstr(BackUpInfo,"-c"))
            {
                count+= GrepWithC(FileAddreses,Pattern);
                ForC=1;
            }
            else if (strstr(BackUpInfo,"-l"))
            {
                GrepWithL(FileAddreses,Pattern);
            }
            else
                NormalGrep(FileAddreses,Pattern);
        }
        token = strtok(NULL, " ");
    }
    if(ForC==1)
        printf("%d\n", count);
}

void NormalGrep(char *FileAddress,char *Pattern){
    char p[1000];
    if(strstr(FileAddress,"\n"))
    FileAddress[strlen(FileAddress)-1]='\0';
    FILE *file = fopen(FileAddress,"r");
    printf("%s:\n",FileAddress);
    while(1)
    {
        fgets(p,1000,file);
        if(strstr(p,Pattern))
        {
            printf("%s\n",p);
        }
        if(feof(file))
            break;
    }
}

int GrepWithC(char *FileAddress,char *Pattern)
{
    int count=0;
    char p[1000];
    if(strstr(FileAddress,"\n"))
        FileAddress[strlen(FileAddress)-1]='\0';
    FILE *file = fopen(FileAddress,"r");
    while(1)
    {
        fgets(p,1000,file);
        if(strstr(p,Pattern))
        {
            count++;
        }
        if(feof(file))
            break;
    }
    return count;
}

void GrepWithL(char *FileAddress,char *Pattern)
{
    char p[1000];
    if(strstr(FileAddress,"\n"))
        FileAddress[strlen(FileAddress)-1]='\0';
    FILE *file = fopen(FileAddress,"r");
//    printf("%s:\n",FileAddress);
    while(1)
    {
        fgets(p,1000,file);
        if(strstr(p,Pattern))
        {
            printf("%s\n",FileAddress);
            break;
        }
        if(feof(file))
            break;
    }
}
