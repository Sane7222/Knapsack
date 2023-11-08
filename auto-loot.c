/*
 *      Matias Moseley     11/6/2022     CS 450     Auto-loot     C Programming Language
 *      
 *      NOTE: I don't know if this matters, but I though I would put it in here anyway
 *      I have been using diff on linux and I cannot get my output to match with sample output exactly
 *      I asked the instructor about it and he said not to worry as this won't affect my grade.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void main(int argc, char *argv[]){
        clock_t start = clock();

        int carryCap, w[128], v[128], numItems = 0;
        char *n[128], *buf = NULL;
        size_t bufSize = 150;

        fscanf(stdin, "%d\n", &carryCap); // Read from stdin
        while(getline(&buf, &bufSize, stdin) != EOF){
                n[numItems] = strdup(strtok(buf, ";"));
                w[numItems] = atoi(strtok(NULL, ";"));
                v[numItems++] = atoi(strtok(NULL, "\n")); }
        free(buf);

        int knap[numItems + 1][carryCap + 1]; // Can make 2D array 1 size bigger instead of indexing at 1 for each array
        for(int i = 0; i <= numItems; i++) for(int j = 0; j <= carryCap; j++){
                if(!i || !j) knap[i][j] = 0; // Set zeros
                else if(w[i-1] > j) knap[i][j] = knap[i-1][j]; // Not enough room
                else knap[i][j] = (v[i-1]+knap[i-1][j - w[i-1]] > knap[i-1][j]) ? v[i-1]+knap[i-1][j - w[i-1]] : knap[i-1][j]; } // Add best value

        int out[128], count = 0;
        int tempW = carryCap;
        for(int i = numItems; i > 0; i--){ // Iterate through 2D array to find best indexes of items
                if(tempW < 1) break;
                if(knap[i][tempW] != knap[i-1][tempW]){
                        out[count++] = i-1;
                        tempW -= w[i-1]; } }

        for(int i = count-1; i > -1; i--){ // Print items in the order we recieved them to stdout
                fprintf(stdout, "%s, ", n[out[i]]);
                fprintf(stdout, "%d, ", w[out[i]]);
                fprintf(stdout, "%d\n", v[out[i]]); }

        fprintf(stdout, "final weight: %d\n", carryCap - tempW); // Total weight and value
        fprintf(stdout, "final value: %d\n", knap[numItems][carryCap]);

        for(int i = 0; i < numItems; i++) free(n[i]); // Free memory

        double time_taken_in_seconds = (double)(clock() - start) / CLOCKS_PER_SEC; // Print time in microseconds to stdout
        double time_taken_in_microseconds = time_taken_in_seconds * 1000000.0;
        fprintf(stdout, "total time in microseconds: %f\n", time_taken_in_microseconds);
}