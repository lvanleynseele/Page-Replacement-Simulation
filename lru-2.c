//
//  main.c
//  LRU
//
//  Created by Liam van Leynseele on 11/4/18.
//  Copyright © 2018 Liam van Leynseele. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    int available=atoi(argv[1]);   //takles in the number available frames from command line
    int frames[available];

    int faults=0;               //counts number of faults	
    int read=0;		//counts number of inputs

    char * input= NULL;
    size_t allocated=0;
    ssize_t readin;			//var for getline function
   
    while (readin=getline(&input, &allocated, stdin)!=-1) {
		int current_page, j;
        current_page=atoi(input);
		int found=available;
		read++;	//increments the number of page request read in from input file
        for (j=0; j<available; j++) {
            if (current_page==frames[j]) {
                found=j;
                break;
            }
        }
        if (found==available){
            faults++;
            fprintf(stderr,"%d\n",current_page);
            found--;//set to last index of array, available-1
        }
        for (j=found; j>0; j--) { //move every value up to found one spot forward
            frames[j]=frames[j-1];
        }
        frames[0]=current_page;
    }
    
    fprintf(stderr,"Number of faults %d\n",faults);	
    fprintf(stderr,"Hit rate = %f\n",(read-faults)/(double)read);
    return 0;
}

//3727
