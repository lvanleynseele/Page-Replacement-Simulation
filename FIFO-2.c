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
		int current_page, i, found;
		int next_to_replace=0;    	
		current_page=atoi(input);
		read++;
		for(i=0;i<available;i++){
			if(frames[i]==current_page){
				found=1;
			}
		}
		if(found==0){
			faults++;
			fprintf(stderr,"%d\n",current_page);
			for (i=available-1; i>0; i--) {
                frames[i]=frames[i-1];
            }		    
			frames[0]=current_page;
		}	
    }

	fprintf(stderr,"Number of faults %d\n",faults);	
	fprintf(stderr,"Hit rate = %f\n",(read-faults)/(double)read);
	return 0;
}

//3731
