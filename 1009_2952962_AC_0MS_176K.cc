// POJ 1009 Edge Detection http://poj.org/problem?id=1009
/**
1. Data Structure defined in global variables with comments
2. edgeFilter method calclate only the one pixel we foucs on in 
   others words the pixel in (0, 0) postion and run min length
   to a new position (x, y).
3. advance move to the postion that maybe have changed to the 
   new value(even sometimes the postion trigged nothing).
4. minRun calculate the advance length.
 - 4.1 if it is the first node in the run sequence, advance 1
 - 4.2 if it is the last node in the run sequence which means
       minAfter is equal to 0, advance 1
 - 4.3 otherwise, find the minimal leftInRun[r] of the 3 rows
5. Do please see the comments which explain the code in details.
6. A brute force solution that attempts to compute an output 
   value for every individual pixel will likely fail due to space
   or time constraints. 
7. It is going into computational algorithm world from this problem. 
*/
#include <stdio.h>
const int MAXRUNS = 1000; 
long imageWidth;
long runLength[MAXRUNS + 2]; // runs
int pixVal[MAXRUNS + 2]; // pixel values in runs
int lastRunIndex;
int  runIndex[3]; // index of run containing pixel
long leftInRun[3]; // number of further pixels in the run
long column; // column of pixel in center of filter, 0 to imagewidth - 1
int firstInRun(int r) {
    return (leftInRun[r] == runLength[runIndex[r]] - 1);
}
void advance(long nTot) {
    column = (column + nTot) % imageWidth;
    for (int r = 0; r < 3; r++)
        for (long n = nTot; n > 0; ) 
            if (n <= leftInRun[r]) {
                leftInRun[r] -= n;
                n = 0;
            }
            else {
                n -= (leftInRun[r]+1);
                runIndex[r]++;
                leftInRun[r] = runLength[runIndex[r]]-1;
            }
}

int updateMax(int runI, int mid, int max) {
    int dif = pixVal[runI] - mid;
    if (dif < 0) dif = -dif;
    return (dif > max) ? dif : max;
}

int edgeFilter() {
    int mid = pixVal[runIndex[1]];
    int max = 0;
    for (int r = 0; r < 3; r++) 
        if (runIndex[r] > 0 && runIndex[r] <= lastRunIndex) {  // skip dummy rows
            max = updateMax(runIndex[r], mid, max);  // use pixel value in row
            if (column > 0 && firstInRun(r)) // refer back to previous run if must 
                max = updateMax(runIndex[r]-1, mid, max); // for pixel before 
            if (column < imageWidth -1 && leftInRun[r] == 0) // see next run if must
                max = updateMax(runIndex[r]+1, mid, max);       // for pixel after
        }
        return max;
}

long minRun() {
    long minAfter = 2000000000;  
    for (int r = 0; r < 3; r++) { 
        if (firstInRun(r)) return 1;
        if (minAfter > leftInRun[r]) minAfter = leftInRun[r];
    }
    if (minAfter == 0) return 1;
    return minAfter; 
}

int main () {
    scanf("%d", &imageWidth) ;
    printf("%d\n", imageWidth) ;

    while (imageWidth > 0) { // assume end sentinal is 0 image width
        // read, initialize image data
        runLength[0] = 2*imageWidth;  // add initial border 
        lastRunIndex = 0;
        do {
            lastRunIndex++;
            scanf("%d %d", &(pixVal[lastRunIndex]), &(runLength[lastRunIndex])) ;
        } while (runLength[lastRunIndex] > 0);  // assume dataset ends with 0 run length
        runLength[lastRunIndex] = 2*imageWidth; // add end border two lines wide 
        lastRunIndex--;  // border not counted in real run indices

        column = 0; 
        // set up pixel to be filtered as first pixel in image in two steps:
        // simplest to place all pixels before first real row
        for (int r = 0; r < 3; r++) {
            runIndex[r] = 0;  // dummy run index before actual image
            leftInRun[r] = (3-r)*imageWidth - 1;// pixels -3,-2,-1 rows into image 
        }
        advance(2*imageWidth); // +2 rows to first pixels -1,0,1 rows into image                    

        // first time, initialize output buffer variables
        int outBufferPixVal = edgeFilter();  // apply filter
        long outBufferRun = minRun();// same filtered value for at least this int
        advance(outBufferRun);  // skip past all the pixels calculated
        while (runIndex[1] <= lastRunIndex) {// while center before end of image
            int outPixVal = edgeFilter(); // same three steps as above
            long outRun = minRun();       //   but with different
            advance(outRun);              //   run variables   
            if (outPixVal == outBufferPixVal) // combine runs with equal values
                outBufferRun += outRun;
            else {  // output old runLength, save new one
                printf("%d %d\n", outBufferPixVal, outBufferRun) ;
                outBufferPixVal = outPixVal;
                outBufferRun = outRun;
            }
        }  // end of loop processing the input image

        // check input integrity -- integral number of rows
        if (column != 0) /*cout << " not multiple of width " << imageWidth << endl;*/
            printf(" not multiple of width %d\n", imageWidth) ;

        //cout << outBufferPixVal << " " << outBufferRun << endl; // clear buffer
        //cout << 0 << " " << 0 << endl; // assume same sentinal format as input 
        printf("%d %d\n", outBufferPixVal, outBufferRun) ;
        printf("0 0\n", outBufferPixVal, outBufferRun) ;
        scanf("%d", &imageWidth) ;
        printf("%d\n", imageWidth) ;
    } // end of all data sets
    return 0;
}