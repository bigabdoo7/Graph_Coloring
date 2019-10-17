#include<stdlib.h>
#include<stdio.h>
#include<string.h>
void printCols(int* cols, int nbColors, int vertex){
    int i;
    printf("%d :", vertex);
    for(i=1; i<=nbColors;i++){
        printf(" %d,", cols[i]);
    }
    printf("\n");
}
int readFile(char* file, int** vertices, char** edges, int* len){
    char url[256] = "./pb/";
    strcat(url, file);
    strcat(url, ".col");
    FILE* stream = fopen(url, "r");
    if(stream != NULL){
        printf("file read\n");
        char buffer[128];
        do{
            fgets(buffer, 127, stream);
        }while(buffer[0] == 'c');
        if(buffer[0] == 'p'){
            sscanf(buffer+7, "%i", len);
            *vertices = (int*) malloc(*len * sizeof(int));
            *edges = (char*) malloc(*len * *len *sizeof(char));
            int i,j;
            for(i=0;i < *len;i++){
                (*vertices)[i]=0;
                for(j=0;j < *len;j++){
                    (*edges)[i* *len + j] = 0;
                }
            }
        }
        else{
            printf("wrong file format\n");
            fclose(stream);
            return -1;
        }
        while(!feof(stream)){
            fgets(buffer, 127, stream);
            if (buffer[0] == 'e'){
                int start, finish;
                sscanf(buffer+2, "%d %d", &start, &finish);
                start--;finish--;
                (*edges)[start * *len + finish] = 1;
                (*edges)[finish * *len + start] = 1;
            }
            else{
                printf("wrong file format\n");
                fclose(stream);
                return -1;
            }
        }
        fclose(stream);
        return 0;
    }
    else{
        printf("wrong file name\n");
        return -1;
   }
}

int* getColors(int nbColors, int vertex, char* graph, int* colors, int size){
    //gets the colors of neighboors of a vertex in the form of a vector with the first index empty and each color has a binary flag indicating if the color has been used, note that if the number of colors given is smaller than the one in the vector, the function may return segmentation fault error.
    int i;
    int* cols = (int*)malloc(sizeof(int)*(nbColors + 1));
    for(i=0; i<(nbColors+1); i++)   cols[i]=0;
    for(i=0;i<size;i++){
        if(graph[vertex*size + i]==1){
            if(colors[i] != 0){
                cols[colors[i]] = 1;
            }
        }
    }
    return cols;
}

void greedy(char* edges, int* colors, int size, int* nbCols){
    int i, usedColors=0;
    for(i=0; i<size; i++){
        int j, available=0;
        int* cols = getColors(usedColors, i, edges, colors, size);
        for(j=1;j<(usedColors+1);j++){
            if(cols[j]==0){
                available=1;
                break;
            }
        }
        if(available){
            colors[i] = j;
        }
        else{
            usedColors++;
            colors[i] = usedColors;
        }
        free(cols);
    }
    *nbCols = usedColors;
}
int partialGreedy(int* order, char* edges, int* colors, int size, int startIndex){
    int i,usedColors = 1 ;
    //counting the number of colors of the first half.
    for(i=0;i<startIndex;i++){
        if(colors[order[i]]> usedColors)
            usedColors = colors[order[i]];
    }
    //emptying the second half.
    for(i=startIndex; i<size; i++){
        colors[order[i]]=0;
    }
    for(i=startIndex; i<size; i++){
        int j, available=0;
        //extracting the colors in the neighbourhood of the i^th ordered vertex.
        int* cols = getColors(usedColors, order[i], edges, colors, size);
        for(j=1;j<(usedColors+1);j++){
            if(cols[j]==0){
                available=1;
                break;
            }
        }
        if(available){
            colors[order[i]] = j;
        }
        else{
            usedColors++;
            colors[order[i]] = usedColors;
        }
        free(cols);
    }
    return usedColors;
}
void copySolution(int* src, int* dst, int size){
    int i;
    for(i=0;i<size;i++)
        dst[i] = src[i];
}
void invert(int* array, int step){
    int i;
    for(i=0; i<(step/2); i++){
        int tmp= array[i];
        array[i] = array[step -i -1];
        array[step -i -1] = tmp;
    }
}
