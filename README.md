# Page-Replacement-Simulation
In this code, I simulate 3 page replacement algorithms (FIFO, LRU, and Second Chance), to gain experience with Operating Systems

The goal of this lab was to gain experience and an understanding of page replacement, and some of the underlying algorithms they rely on, by implementing a First In First Out (FIFO), Least Recently Used (LRU), and Second Chance page replacement program that would simulate each technique on a given input file. I started this assignment by tackling two common problems amongst all three algorithms, reading in the simulated page frames from a text file and creating an array of a size passed in by the user in the command line to store the pages in frames. I actually created my integer array, “frames”, first by converting argv[1] to an integer value with an atoi() call, storing it in a variable “available”, and creating an array with that size. After creating the “frames” array to store pages in, I tackled pulling in the page value from the input file, “in.txt”. To do so, I used a while loop that repeated a getline function that would terminate when no new line was read in, which ensured I read the entire file. As the incoming page values were in string format, I once again used atoi() to convert it to an integer value so that it could be stored in “frames”, and to ensure any extra spaces or characters in a line were disregarded. Once I was able to create arrays of the right size, and pull in the page values, I was ready to conquer the implementation of the actual replacement algorithms.

I started by implementing the FIFO algorithm as it is the most straightforward. The basic idea was to create an array that would push in new pages on one end and remove them from the other, while tallying both the number of pages read in and the number of and faults, or incoming pages that were not currently stored in “frames”. When a new page was read in by the while loop, I ran a for loop to check to see if that page value was currently in the array. If it was, nothing happened. If it was not found, however, my faults counter was incremented, the value of the page fault was outputted to a text file, every page was moved one spot forward by the for loop, “ for(i=available-1; i>0; i--){ frames[i]=frames[i-1];}”, effectively dropping the page in the last frame, and then the new page was inserted in the zeroth position.

Next, I implemented the LRU algorithm. It wound up being somewhat similar to my FIFO algorithm in the sense that new pages would enter at one end and leave from the other, and a fault would occur when the incoming page was not already stored in the array. Where this algorithm differed, however, was that if the new page was found in the array, it was moved to the front. So, whereas in FIFO I initialized the variable “found” to 0 and would set it to 1 if the page was in the array, in LRU, “found” was initialized to available and was set to the index of the page if it was found. This approach allowed me to have a single for loop for both the case that the page was or was not found, and, using a similar for loop to the one I used in FIFO, everything from index 0 to “found” was moved a space forward. I have an additional conditional for the case that the page was not found which would increment the faults counter and print the fault value. The last thing to do was simply add the new page to the zeroth position of the array.

The last algorithm I implemented was Second Chance. This wound up being somewhat challenging for me, as it took me awhile to gain intuition on the algorithm. The premise of this algorithm was similar to FIFO, however, it had the added complication of storing a second chance bit along with the page value. Also, if a page got to the end of the array and it still had a second chance, I had to find the first page from the end that did not, drop this page, and set the second chance bit for every page between to zero. To solve the problem of storing a page’s second chance bit, I created a second array, “second_chance_bits”, of size “available”, which would store a 1 if the page had a second chance, and a 0 if not. Every page value would have the same index in “frames” as it would in the “second_chance_bits” array. Like FIFO, when a new page was read in in my while loop, I checked the array for the value and set “found” to its index if it was. If the page was found, I simply had to ensure its second chance bit was set to one by calling “second_chance_bits[found]=1”. If the page was not found in “frames”, however, things got a bit more complicated. First, like in FIFO, I incremented the faults counter, and outputted the fault value. Next, I had to find the next page to replace, which I did with the while loop, “while(second_chance_bits[next_to_replace]==1){ second_chance_bits[next_to_replace--]=0;}”. This loop not only found the correct index, described above, of the next frame to replace, but set every second chance bit for frames that were skipped to zero. Then, like in LRU, I used a for loop from “next_to_replace” to zero to increment every page one spot forward, drop the correct page, and insert the new page at the beginning. I tested the correctness of my algorithms by checking my output of the page fault values against the output values posted in the discussion board with the diff function. After checking that each was outputting the right page faults, I deduced that they were all running correctly. I then looked into how well each algorithm performed by looking at the hit rates ((readfaults)/ read) for each, simulating every multiple of 25 between 25 and 500, and graphing the results as seen below.


Available Frames FIFO LRU SC
25 0.5883 0.5884 0.5824
50 0.6039 0.6058 0.6007
75 0.6159 0.6164 0.6137
100 0.627 0.6274 0.6257
125 0.6343 0.6345 0.6336
150 0.6417 0.6403 0.6408
175 0.6442 0.6455 0.6433
200 0.6483 0.6496 0.6476
225 0.6558 0.6559 0.6556
250 0.6606 0.6597 0.6603
275 0.6688 0.6662 0.6681
300 0.6738 0.6719 0.6732
325 0.6808 0.6797 0.6807
350 0.6902 0.686 0.69
375 0.6953 0.6931 0.6955
400 0.697 0.6963 0.6964
425 0.6996 0.7019 0.6995
450 0.7007 0.7042 0.7006
475 0.7026 0.707 0.7023
500 0.7047 0.71 0.7043
 
I was surprised to see that one algorithm did not significantly outperform any of the others. Overall, I feel like this lab forced me to learn a lot about page replacement, and I certainly have come away with a greater intuition for the topic.
