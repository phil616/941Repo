/*
 OJ auto test program provide a auto input / output test methods in windows platform
 like online judge system;
 User provide a executable program as the first parameter like `data.exe`, and then 
 this program will check if the input content is as same as the expect output.
 the input file `data.in` and output file `data.out` should exist in program directory
 defore run this test.
 if the content is the same, program will print AC, otherwise it will show WA.
 a feature in this program is that this program doesn't care the crlf and last empty line,

 NOTICE: all the malloc memories are not free due to this program is very small

 the input argc are format like `data.exe`, abs path like "C:\\Users\\administrator\\a.exe"
 are not supported.


 compile command: (deploy)
 gcc oj_auto_test.c -o oj_auto_test.exe
 debug compile command (with a macro variable switch _DEBUGLOG):
 gcc -std=c99 oj_auto_test.c -o oj_auto_test.exe -D_DEBUGLOG

*/

#include <stdio.h>
#include <Windows.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>
#define NPE "Null Pointer Exception"
#define MAE "Memory Allocate Exception"
#define FOE "File Open Exception"
#define INFILE_SUFFIX ".in"
#define OUTFILE_SUFFIX ".out"
#define TMP_OUTFILE_SUFFIX ".tmp"

#define MAX_LINE_LENGTH 1024
int isspace_c(char s){
    if (s == ' ') return 1;
    else return 0;
}
char* process_file(FILE* file) {
    char line[MAX_LINE_LENGTH];
    char* result = NULL;
    size_t result_size = 0;
    int is_first_line = 1;

    while (fgets(line, sizeof(line), file)) {
        // remove space char in first line
        char* start = line;
        while (isspace_c(*start)) {
            start++;
        }

        // remove tail line's space and crlf
        char* end = start + strlen(start) - 1;
        while (end > start && (isspace_c(*end) || *end == '\n' || *end == '\r')) {
            end--;
        }
        *(end + 1) = '\0';

        // if not first line, add crlf
        if (!is_first_line) {
            result = realloc(result, result_size + 2);
            result[result_size++] = '\r';
            result[result_size++] = '\n';
        }
        is_first_line = 0;

        // add to result
        size_t line_length = strlen(start);
        result = realloc(result, result_size + line_length);
        memcpy(result + result_size, start, line_length);
        result_size += line_length;
    }

    // if lastline is empty ,remove crlf
    if (result_size >= 2 && result[result_size - 2] == '\r' && result[result_size - 1] == '\n') {
        result_size -= 2;
    }

    // add a \0
    result = realloc(result, result_size + 1);
    result[result_size] = '\0';
    #ifdef _DEBUGLOG
        printf("[%s] result of file process = %s\n",__func__,result);
    #endif
    return result;
}

char *strconcate(char *des,char* source){
    char *p;
    p = des;
    int length = strlen(des) + strlen(source) + 1;
    #ifdef _DEBUGLOG
        printf("[%s] total length = %d \n",__func__,length);
    #endif
    char *concate = (char *)malloc(length);
    memset(concate,'\0',length);
    int idx = 0;
    while(*p != '\0'){
    #ifdef _DEBUGLOG
        printf("[%s] current loop p = %c \n",__func__,*p);
    #endif
        concate[idx++] = *p;
        p++;
    }
    p = source;
    while(*p != '\0'){
    #ifdef _DEBUGLOG
        printf("[%s] current loop p = %c \n",__func__,*p);
    #endif
        concate[idx++] = *p;
        p++;
    }
    #ifdef _DEBUGLOG
        printf("[%s] merged string %s\n",__func__,concate);
    #endif
    return concate;
}
char *fileNameHeap(char *str){
    char *p = str;
    if(p == NULL){
        printf(NPE);
        exit(-1);
    }
    int stringCharacterCount = 0;
    while(*p != '\0'){
        p++;
        stringCharacterCount++;
    }
    char *fileNameHeapSeg = (char*)malloc(stringCharacterCount + 1);
    if (fileNameHeapSeg == NULL){
        printf(MAE);
        exit(-1);
    }
    p = str;
    int idx = 0;
    while(*p != '\0'){
        fileNameHeapSeg[idx++] = *p;
    }
    fileNameHeapSeg[idx] = '\0';
    return fileNameHeapSeg;
}

char *extractFileName(char *str){
    char *p = str;
    while(*p != '\0')
        p++;

    // get position of last dot '.'
    while(*p != '.')
        p--;

    char *sentinel = p;
    char *filename = NULL;
    p = str;
    int length = sentinel - p;

    char *filenameHeapSeg = (char*)malloc(length + 1);  // +1 include character '\0'
    if (filenameHeapSeg == NULL){
        printf(MAE);
        exit(-1);
    }
    #ifdef _DEBUGLOG
        printf("[%s] p at %c %p sentinel at %c %p\n",__func__,*p,p,*sentinel,sentinel);
    #endif
     // memset(filename,'\0',length + 1); // make sure heap is string style empty
    int idx = 0;
    while(p != sentinel){
    filenameHeapSeg[idx++] = *p;
        p++;
    #ifdef _DEBUGLOG
        printf("[%s] current copying input %c\n",__func__,*p);
    #endif
    }
    filenameHeapSeg[idx+1] = '\0';
    

    #ifdef _DEBUGLOG
        printf("[%s] filename heap seg equals \"%s\"\n",__func__,filenameHeapSeg);
    #endif

    return filenameHeapSeg;
}

char *getInputFileName(char *filename){
    int totalLength = 0; // the length include filename and suffix "data.in"
    char *p = filename;
    while(*p != '\0'){
        p++;
        totalLength++;
    }

    const char *c_str_infile_suffix = INFILE_SUFFIX;
    totalLength += (int)strlen(c_str_infile_suffix);
    #ifdef _DEBUGLOG
        printf("[%s] total length %d\n",__func__,totalLength);
    #endif
    char *inputFileName = (char *)malloc(totalLength + 1);
    if (inputFileName == NULL){
        printf(MAE);
        exit(-1);
    }
    return strconcate(filename,INFILE_SUFFIX);

}

char *getOutputFileName(char *filename){
    int totalLength = 0; // the length include filename and suffix "data.in"
    char *p = filename;
    while(*p != '\0'){
        p++;
        totalLength++;
    }

    const char *c_str_outfile_suffix = OUTFILE_SUFFIX;
    totalLength += (int)strlen(c_str_outfile_suffix);
    #ifdef _DEBUGLOG
        printf("[%s] total length %d\n",__func__,totalLength);
    #endif
    char *outputFileName = (char *)malloc(totalLength + 1);
    if (outputFileName == NULL){
        printf(MAE);
        exit(-1);
    }
    return strconcate(filename,OUTFILE_SUFFIX);
}
char *getTempOutputFilename(char *filename){
    char *p = filename;
    int length = strlen(filename);
    length += strlen(TMP_OUTFILE_SUFFIX);
    length += strlen(OUTFILE_SUFFIX);
    length += 1;
    char *tmp = (char *)malloc(length);
    if(tmp == NULL){
        printf(MAE);
        exit(-1);
    }
    char *prefix = strconcate(filename,TMP_OUTFILE_SUFFIX);
    char *total = strconcate(prefix,OUTFILE_SUFFIX);
    #ifdef _DEBUGLOG
        printf("[%s] current tmp filename is %s \n",__func__,total);
    #endif
    return total;
}
int main(int argc,char **argv){
    char *inputProgramName = NULL;
    inputProgramName = argv[1];

    if(strlen(inputProgramName) < 1){
        printf("NO INPUT");
        exit(0);
    }

    char *filename = extractFileName(inputProgramName);
    char *tmpout = getTempOutputFilename(filename);
    char *out = getOutputFileName(filename);
    char *in = getInputFileName(filename);
    char *precommand =  
    strconcate(
        strconcate(
            strconcate(
                strconcate(inputProgramName," > "),
                tmpout
            ),
            " < "
        ),
        in
    );
    #ifdef _DEBUGLOG
        printf("[%s] precommand = \"%s\" \n",__func__,precommand);
    #endif
    int res_sys_call = system(precommand);
    #ifdef _DEBUGLOG
        printf("precommand run success res = %d\n",res_sys_call);
    #endif
    FILE *tmpOutFp = NULL;
    FILE *outFp = NULL;
    tmpOutFp = fopen(tmpout,"r");
    outFp = fopen(out,"r");
    if (tmpOutFp == NULL || outFp == NULL){
        printf(FOE);
        fclose(tmpOutFp);
        fclose(outFp);
        exit(-1);
    }
    char *tmpOutFpString = process_file(tmpOutFp);
    char *outFpString = process_file(outFp);
    fclose(tmpOutFp);
    fclose(outFp);
    int oj_res = strcmp(tmpOutFpString,outFpString);
    if (oj_res == 0){
        printf("Accpectd !\n");
        printf("press any key to close");
        getch();
    }else{
        printf("Wrong Answer !\n");
        printf("press any key to close");
        getch();
    }
    int deleteTmpFileRes = system(strconcate("del ",tmpout));
    #ifdef _DEBUGLOG
        printf("precommand run success res = %d\n",deleteTmpFileRes);
    #endif


}