#include <stdio.h>
#include <stdlib.h>



int main(int argc, const char * argv[]) {
    int available=atoi(argv[1]);   //takles in the number available frames from command line
    int frames[available];
	int second_chance_bits[available];
	

    int faults=0;               //counts number of faults	
    int read=0;		//counts number of inputs

    char * input= NULL;
    size_t allocated=0;
    ssize_t readin;			//var for getline function
   
    
    
    while (readin=getline(&input, &allocated, stdin)!=-1) {
		int current_page, i;
		int next_to_replace=available-1;    	
		current_page=atoi(input);
		read++;
        int found=-1;
		for(i=0;i<available;i++){
			if(frames[i]==current_page){
				found=i;
				break;
			}
		}
		

		if(found==-1){
			faults++;
			fprintf(stderr,"%d\n",current_page);
			/*use this while loop to find the index of the first frame from the end that's second
			chance bit=0, set every second chance bit=1 to zero in between*/
			while(second_chance_bits[next_to_replace]==1){
				second_chance_bits[next_to_replace--]=0;				
			}			

			for(i=next_to_replace;i>0;i--){
				frames[i]=frames[i-1];
				second_chance_bits[i]=second_chance_bits[i-1];
			}

			frames[0]=current_page;
			second_chance_bits[0]=1;
		}	
		else{
			second_chance_bits[found]=1;
		}

    }
	fprintf(stderr,"Number of faults %d\n",faults);
	fprintf(stderr,"Hit rate = %f\n",(read-faults)/(double)read);
	return 0;
}

//3747
