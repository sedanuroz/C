#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct file {
    int ID; // kullanýcýdan alýnacak unique olacak
    char name[25]; // kullanýcýdan alýnacak
    char filePath[30]; // kullanýcýdan alýnacak
    int numberofRead; // The initial value is 0. Bir dosya en fazla 2 farklý program tarafýndan okunur.
    int numberOfWrite;// The initial value is 0. Bir dosyaya en fazla 1 program yazabilir.
    int maxNumberOfRead;
    int maxNumberofWritten;
    bool isRead;// The initial value is False.
    bool isWritten ;// The initial value is False.
} file;

typedef struct program {
    int ID; // kullanýcýdan alýnacak unique olacak
    char name[25]; // kullanýcýdan alýnacak
    int readFileID; // bir program sadece 1 tane dosyayý okuyabilir
    int writeFileID; // bir program sadece 1 tane dosyaya yazabilir
    // bir program ayný anda hem dosya okuyup hem dosyaya yazabilir (ayný dosya olmamak þartýyla)
} program;


void CreateNewFile(file files[],int count,int ID, char name[], char filePath[]);
void CreateNewProgram(program programs[],int count,int ID, char name[]);
void ReadFile(file *file, program *program, int fileId, int programId);
void WriteToFile(file *file, program *program, int fileId, int programId);
void ReleaseReadingFile(program *program,file *file);//Bir program okuduðu dosya üzerinde okuma iþlemini bitirmek istediðinde bu iþlev çalýþtýrýlýr)
void ReleaseWritingFile(program *program,file *file);
void CloseAllFilesForTheProgram(program *program,file *file);
void DisplayAllFiles(file files[],int size);
void DisplayAllPrograms(program programs[],int size);
void ShutDownTheComputer();

void Menu();
bool IsExistTheFile(file files[],int count,int fileId);
bool IsExistTheProgram(program programs[] ,int count,int programId);
int findFileIndex(file files[],int arrSize,int fileID);
int findProgramIndex(program programs[],int arrSize,int programId);

int main() {

    file newFile;
    program newProgram;
    int selection ;//kullanıcının ana menu için girdiği değer

    int fileSize=4;//baslangicta en fazla 4 er tane dosya ve program olusturulabilir 4 den fazla istenirse 2 katına çıkar
    int programSize=4;

    file *files;//bunlar bizim arrayımız olacak boyutunu değiştirebilmek için calloc kullanacağim
    program *programs;//bu nedenle pointer turunden belirlemeliydim

    files=(file*)calloc(fileSize, sizeof(file));//basta belirlenen değer kadar bellekte yer acıldı(boyut*4 aslında)
    programs=(program *)calloc(programSize, sizeof(program));

    int countForFiles=0;//files obje arrayýnýn indeksini tutacak
    int countForPrograms=0;//progrmas obje arrrayýnýn indexsini tutacak
    int fileID;
    int programID;
    int iFile,iProgram;//idi deðeri bilinen bir file/program ýn kendi arrayinde kaçýncý ýndexde olduðu bilgisini tutacak

    files[countForFiles++] = (file){1, "Lab4.pptx", "C:\\LabNotes\\", 0, 0, 2, 1 , false, false};//struct içinde belirlediğim yazma sırasına göre değerlerini yerleştirdim
    files[countForFiles++] = (file){2, "Notes.txt", "C:\\LabNotes\\", 0, 0, 2, 1 , false, false};

    programs[countForPrograms++] = (program){1, "OS", -1, -1};
    programs[countForPrograms++] = (program){2, "Kernel", -1, -1};

    do {
        Menu();
        scanf("%d", &selection);

        switch(selection){
            case 1:
                printf("Enter new file id: ");
                scanf("%d", &newFile.ID);
                printf("Enter new file name: ");
                scanf("%24s", newFile.name);
                printf("Enter new file path: ");
                scanf("%29s", newFile.filePath);
                if(IsExistTheFile(files,countForFiles,newFile.ID)){
                        printf("There is a file already with the given id!!!\n");

                }else{
                    if (fileSize == countForFiles) {
                    // array dolduysa kapasitesini 2 katına çıkarmalıyız
                    fileSize *= 2; // file size değerini iki katına çıkardık
                    files = realloc(files, fileSize * sizeof(file));

                        if (files== NULL) {
                           printf("************************ERROR!!!************************* \n");
                           free(files); // Bellek serbest bırakıldı
                           break;
                       }else{
                           printf("**********File memory is full!!!*************\n");
                           printf("File memory is expended....\nNew file memory size is: %d\n", fileSize);
                           printf("*********************************************\n");
                       }
                   }

                     CreateNewFile(files,countForFiles,newFile.ID, newFile.name, newFile.filePath);
                     countForFiles++;
                }

                break;
            case 2:

                printf("Enter new program id: ");
                scanf("%d", &newProgram.ID);
                printf("Enter new program name: ");
                scanf("%24s", newProgram.name);
                if(IsExistTheProgram(programs,countForPrograms,newProgram.ID)){
                    printf("There is a program already with the given id!!!\n");
                }else{
                    if(programSize==countForPrograms){
                        programSize*=2;
                        programs = realloc(programs, programSize * sizeof(program));
                        if (programs== NULL) {
                           printf("************************ERROR!!!************************* \n");
                           free(programs); // Bellek serbest bırakıldı
                           break;
                        }else{
                           printf("**********Program memory is full!!!*************\n");
                           printf("Program memory is expended....\nNew program memory size is: %d\n", programSize);
                           printf("*********************************************\n");
                       }
                    }
                     CreateNewProgram(programs,countForPrograms,newProgram.ID,newProgram.name);
                     countForPrograms++;
                }

                break;
            case 3:

               printf("Enter id to read file:");
               scanf("%d",&fileID);
               printf("Enter program id:");
               scanf("%d",&programID);
               iFile=findFileIndex(files,countForFiles,fileID);
               iProgram=findProgramIndex(programs,countForPrograms,programID);
               if(iFile!=-1 && iProgram!=-1 ){
                    ReadFile(&files[iFile], &programs[iProgram], fileID, programID);

               }
                break;
            case 4:
               printf("Enter id to write file :");
               scanf("%d",&fileID);
               printf("Enter program id:");
               scanf("%d",&programID);
               iFile=findFileIndex(files,countForFiles,fileID);
               iProgram=findProgramIndex(programs,countForPrograms,programID);
               if(iFile!=-1 && iProgram!=-1){
                   WriteToFile(&files[iFile], &programs[iProgram], fileID, programID);
               }
               break;
            case 5:
                printf("Enter program id to release reading file :");
                 scanf("%d",&programID);
                 iProgram=findProgramIndex(programs,countForPrograms,programID);
                 if(iProgram!=-1){
                        if( programs[iProgram].readFileID==-1){//eger bir dosya okumuyorsa (deðeri default hali olan -1 olarak kaldýysa
                           printf("This program does not read any file!!!\n");
                        }else{
                            iFile=findFileIndex(files,countForFiles,programs[iProgram].readFileID);
                            ReleaseReadingFile(&programs[iProgram],&files[iFile]);
                        }
                }
                break;
            case 6:
                 printf("Enter program id to release writing file :");
                 scanf("%d",&programID);
                 iProgram=findProgramIndex(programs,countForPrograms,programID);
                 if(iProgram!=-1){
                        if( programs[iProgram].writeFileID==-1){//eger bir dosya yazmýyorsa (deðeri default hali olan -1 olarak kaldýysa
                           printf("This program does not write to any file!!!\n");
                        }else{
                            iFile=findFileIndex(files,countForFiles,programs[iProgram].writeFileID);
                            ReleaseWritingFile(&programs[iProgram],&files[iFile]);
                        }
                }

                break;
            case 7:
                printf("Enter program id to close all files :");
                scanf("%d",&programID);
                iProgram=findProgramIndex(programs,countForPrograms,programID);
                if(iProgram!=-1){

                        iFile=findFileIndex(files,countForFiles,programs[iProgram].writeFileID);

                        if( programs[iProgram].writeFileID==-1){//eger bir dosya yazmýyorsa (deðeri default hali olan -1 olarak kaldýysa
                           printf("This program does not write to any file!!!\n");
                        }
                        else{
                            ReleaseWritingFile(&programs[iProgram],&files[iFile]);
                        }


                        if(programs[iProgram].readFileID==-1){
                             printf("This program does not read any file!!!\n");
                        }else{
                             ReleaseReadingFile(&programs[iProgram],&files[iFile]);
                        }
                }

                break;
            case 8:
                DisplayAllFiles( files,countForFiles);
                break;
            case 9:
                DisplayAllPrograms(programs,countForPrograms);
                break;
            case 10://döngüden çýkýlacak
                free(files); // Bellek serbest bırakıldı
                free(programs);

                break;
            default:
                printf("Invalid selection. Please try again.\n");
                break;
        }

        printf("**************************************************\n");
    } while (selection != 10);


    return 0;
}

void Menu() {
    printf("Create new file (1)\n"
           "Create new program (2)\n"
           "Read file (3)\n"
           "Write to file (4)\n"
           "Release reading file (5)\n"
           "Release writing file (6)\n"
           "Close all files for the program (7)\n"
           "Display all files (8)\n"
           "Display all programs (9)\n"
           "Exit (10)\n"
           "Enter your selection: ");
}
bool IsExistTheFile(file files[] , int count,int fileId){
     for(int i = 0; i < count; i++) {
        if(files[i].ID == fileId) {
            return true;
        }
    }
    return false;
}
bool IsExistTheProgram(program programs[] ,int count,int programId){
     for(int i = 0; i < count; i++) {
        if(programs[i].ID == programId) {
            return true;
        }
    }
    return false;

}
void CreateNewFile(file files[],int count,int ID, char name[], char filePath[]){
    //ilk atamalarını yapacağım için pointer kullanmadım ama değerlerini değiştiriyor olsaydım kulanmalıydım
    files[count].ID = ID;
    strcpy(files[count].name, name);
    strcpy(files[count].filePath, filePath);
    files[count].maxNumberOfRead=2;//struct içinde direk atama yapamadýðým  için atamalarý burada ferçekleþtirdim
    files[count].maxNumberofWritten=1;
    files[count].numberofRead=0;
    files[count].numberOfWrite=0;
    files[count].isRead=false;
    files[count].isWritten=false;

}
void CreateNewProgram(program programs[],int count,int ID, char name[]){
    programs[count].ID = ID;
    strcpy(programs[count].name, name);
    programs[count].readFileID=-1;
    programs[count].writeFileID=-1;
}
int findFileIndex(file files[],int arrSize,int fileID){
      for(int i = 0; i < arrSize; i++){
        if(files[i].ID==fileID){
            return i;
            break;
        }
      }
      printf("File is not found\n");
      return -1;

}

int findProgramIndex(program programs[],int arrSize,int programId){
      for(int i = 0; i < arrSize; i++){
        if(programs[i].ID==programId){
            return i;
            break;

        }
      }
       printf("There is no such program!!!\n");
      return -1;

}


void ReadFile(file *file, program *program, int fileId, int programId) {
    if (! (*file).isWritten && ( (*file).numberofRead <=  (*file).maxNumberOfRead)) {
        printf("The file is being read by the program\n");
        (*file).numberofRead++;
        (*file).isRead = true;
        (*program).readFileID = fileId;
    }
}

void WriteToFile(file *file, program *program, int fileId, int programId) {
    if (! (*file).isRead && ( (*file).numberOfWrite <=  (*file).maxNumberofWritten)) {
        printf("The file is being written by the program\n");
        (*file).numberOfWrite++;
        (*file).isWritten = true;
        (*program).writeFileID = fileId;
    }
}
void DisplayAllFiles(file files[],int size){
      for(int i = 0; i < size; i++){
        printf("File %d\n",i+1);
        printf("File ID :%d\n",files[i].ID);
        printf("File name :%s\n",files[i].name);
        printf("File path :%s\n",files[i].filePath);
        printf("Number of read :%d\n",files[i].numberofRead);
        printf("Number of write :%d\n",files[i].numberOfWrite);

        printf("Is the file being read? : ");
        if(files[i].isRead){
           printf("Yes\n");
        }else{
        printf("No\n");
        }

        printf("Is the file being written? :");
        if(files[i].isWritten){
           printf("Yes\n");
        }else{
        printf("No\n");
        }


        printf("-------------------------\n");

      }
}

void DisplayAllPrograms(program programs[],int size){
     for(int i = 0; i < size; i++){
        printf("Program %d\n",i+1);
        printf("Program ID :%d\n",programs[i].ID);
        printf("Program name :%s\n",programs[i].name);
        printf("Reading file ID :%d\n",programs[i].readFileID);
        printf("Writing file ID :%d\n",programs[i].writeFileID);
        printf("-------------------------\n");
     }

}

void ReleaseReadingFile(program *program,file *file){
       (*program).readFileID=-1;
       (*file).isRead=false;
}
void ReleaseWritingFile(program *program,file *file){
    (*program).writeFileID=-1;
       (*file).isWritten=false;
}
void CloseAllFilesForTheProgram(program *program,file *file){
    ReleaseReadingFile(&program,&file);
    ReleaseWritingFile(&program,&file);

}
