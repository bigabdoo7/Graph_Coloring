#include"misc.h"

int main(int argc, char** argv){
    if (argc!=2){
        printf("specify a file name\n");
        return 0xffff;
    }
    int *vertices, len, *order, *bestSolution, *currentSolution, *currentOrder; 
    char* edges;
    int i, bestScore, currentScore,stepSize=7, ic=1;
    //reading the file containig the graph
    if ( ! readFile(argv[1], &vertices, &edges, &len) ){
        long debut = clock();
        double probability = 1., coolingFactor = 0.95;
        time_t t;
        order = (int*)malloc(sizeof(int)*len);
        bestSolution = (int*)malloc(sizeof(int)*len);
        currentSolution = (int*)malloc(sizeof(int)*len);
        currentOrder = (int*)malloc(sizeof(int)*len);
        for(i=0;i<len;i++){
            order[i]=i;
        }
        bestScore = currentScore = partialGreedy(order, edges, vertices, len, 0);
        copySolution(vertices, bestSolution, len);
        copySolution(vertices, currentSolution, len);
        copySolution(order, currentOrder, len);
        srand((unsigned) time(&t));
        while( (clock()-debut) < (CLOCKS_PER_SEC*59)){
            ic++;
            probability *= coolingFactor;
            int score,index = rand()%(len-stepSize);
            copySolution(currentSolution, vertices, len);
            copySolution(currentOrder, order, len);
            invert(order+index, stepSize);
            score = partialGreedy(order, edges, vertices, len, index);
            if(score < bestScore){
                copySolution(vertices, bestSolution, len);
                copySolution(vertices, currentSolution, len);
                copySolution(order, currentOrder, len);
                bestScore = currentScore = score;
            }
            else if(score < currentScore){
                copySolution(vertices, currentSolution, len);
                copySolution(order, currentOrder, len);
                currentScore = score;
            }
            else if((rand()/RAND_MAX)<probability ) {
                copySolution(vertices, currentSolution, len);
                copySolution(order, currentOrder, len);
                currentScore = score;
            }
        }
        printf("ran %d iterations, with a score of %d\n", ic, bestScore);
        char name[128]="";
        strcat(name, argv[1]);
        strcat(name, ".sol");
        FILE* sol = fopen(name, "w");
        for(i=0;i<len; i++){
            fprintf(sol, "%d\n", bestSolution[i]);
        }
        fclose(sol);
    }
    else{
        return -1;
    }
    return 0;
}
