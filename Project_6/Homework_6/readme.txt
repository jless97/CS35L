//CS 35L - Professor Eggert
//Lab 4 - TA Isha Verma
//Project 6 - Multithreaded Performance
//Homework  
//readme.txt

The homework portion of this week consisted of implementing multithreading to a program
to get it to run faster on a multicore machine. This process only involved modifying
main.c of the SRT implementation, and then linking the pthread library in the Makefile
file, so that the source files could use the pthread header file. 

The original main.c implementation only utilized a single thread, and thus, for this
program was not able to run as fast as it was capable of doing. Because Allen only
allowed for a single thread to be used, the process of calculating pixel colors, and then
printing them out was all done in the main function. Moreover, this process of calculating
the colors involved a series of nested for-loops, in which the performance could 
definitely be increased by using multithreading to have each thread do a portion of the
color calculation.

The primary problem for the homework was to decide how to implement the multithreading.
After looking through the main source file, I decided that the code in the main function,
like stated previously, called for multithreading, and moved the code into a function
where the threading could take place. Therefore, the only think left for the main function
to do was to create and free the threads, and to regroup (after calculating the pixelation
colors) to print it all out. 

After having an idea of what to do, the next hurdle was to decide how to store the data
being calculated in Allen's main function code to be printed out later. Towards the 
bottom of the function, I noticed that the final color values for a given pixel was being
stored in a float array of size three. By using multithreading, this process could be 
done much faster with each thread doing a portion of the calculation, and then storing
the three values for a given pixel in a 3D array.

As shown in the make-log.txt file, it was clear that multithreading greatly increased the
performance of the program. The make clean check created the appropriate files, but also
relayed the performances of the program using 1, 2, 4, and 8 threads using the time
command. The times clearly showed that as the threads increased, the real time of the
program greatly decreased. This was to be expected as the calculations being done by a 
single thread were then being split up to be done concurrently by multiple threads, and
hence, an improvement in performance. 

Below are the four real times of using 1, 2, 4, and 8 threads respectively:

real    0m52.095s
real    0m26.200s
real    0m13.637s
real    0m7.271s

As can be seen above, as the number of threads increased, the performance also increased.
Also of note, is that the single threaded implementation was significantly slower than the
8 threaded one, and that as the number of threads doubled, the real time execution was
nearly halved.
