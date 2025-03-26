#include <stdio.h>
#define MAX 200

double average(double d[] /*array to average*/, int start /*number of non-zero elements in array*/, int end) {
    double a = 0;

    for (int i = start; i < end; i++) {
        a += d[i];
    }
    a /= (double)(end-start);
    return a;
}   

int nonzero(int year[], int size) {     // checks how many non-zero rows are in the file (will have to change later; currently checks for 2023-2024)
    int n = 0;
    for (int i = 0; i < size; i++) {
        if (year[i] == 2024 || year[i] == 2023) {
            n++;
        }
    }
    return n;
}

void transfer(double test[], double real[], int size) {     // transfers the input double array (size MAX) to proper array (size = rows)
    for (int i = 0; i < size; i++) {
        real[i] = test[i];
    }
}

void itransfer(int test[], int real[], int size) {          // same thing but with integer array
    for (int i = 0; i < size; i++) {
        real[i] = test[i];
    }
}

int yearSwitch(int a[], int size) {        // determines how many elements are in first year 
    for (int i = 1; i < size; i++) {
        if (a[i] != a[i-1]) {
            return i;
        }
    }
    return -1;
}



int main (void) {
    
    FILE *data = fopen("testData.txt", "r");

    int numyear, num_elements, n;
    int tyear[MAX], tday[MAX];
    char buff[70];
    double tsup[MAX], tmich[MAX], thur[MAX], terie[MAX], tont[MAX], tstclr[MAX], tGLT[MAX];
    double *test[7] = {tsup, tmich, thur, terie, tont, tstclr, tGLT};
    double avg[14]; // first 6 avg, second 6 avg, yr1, yr2

    

    if (data == NULL) {
        perror("Error opening file");
        return 1;
    }

    for (int i = 0; i <= 7; i++) {       // skip first 7 lines
        fgets(buff, 70, data);
    }

    for (int i = 0; !feof(data); i++) { // read the data 
        n++;
        fscanf(data, "%d", &tyear[i]);
        fscanf(data, "%d", &tday[i]);
        fscanf(data, "%lf", &tsup[i]);
        fscanf(data, "%lf", &tmich[i]);
        fscanf(data, "%lf", &thur[i]);
        fscanf(data, "%lf", &terie[i]);
        fscanf(data, "%lf", &tont[i]);
        fscanf(data, "%lf", &tstclr[i]);
        fscanf(data, "%lf", &tGLT[i]);
    }

    

    num_elements = nonzero(tyear, MAX);
    printf("n count: %d\n", n);
    printf("num_elements: %d\n", num_elements);
    double sup[num_elements], mich[num_elements], hur[num_elements], erie[num_elements], ont[num_elements], stclr[num_elements], GLT[num_elements];
    int year[num_elements], day[num_elements];

    // transfer all arrays to correct size
    itransfer(tyear, year, num_elements);
    itransfer(tday, day, num_elements);
    transfer(tsup, sup, num_elements);
    transfer(tmich, mich, num_elements);
    transfer(thur, hur, num_elements);
    transfer(terie, erie, num_elements);
    transfer(tont, ont, num_elements);
    transfer(tstclr, stclr, num_elements);
    transfer(tGLT, GLT, num_elements);

    // initialize pointer array for lake data for easier access
    double *real[7] = {sup, mich, hur, erie, ont, stclr, GLT};
    
    // uncomment this to print out the table
    // for (int i = 0; i < num_elements; i++) {
    //     printf("%4d %3d %7lf %7lf %7lf %7lf %7lf %7lf %7lf\n", year[i], day[i], sup[i], mich[i], hur[i], erie[i], ont[i], stclr[i], GLT[i]);
    // }

    numyear = yearSwitch(year, num_elements); // indicates when the year changes
    // printf("numyear: %d\n", numyear);

    for (int i = 0; i < 6; i++) {   // first year
        avg[i] = average(real[i], 0, numyear);
    }

    for (int i = 0; i < 6; i++) {   // second year
        avg[i+6] = average(real[i], numyear, num_elements);
    }

    avg[12] = average(real[6], 0, numyear);
    avg[13] = average(real[6], numyear, num_elements);

    printf("2023:    %lf %lf %lf %lf %lf %lf | GLT: %lf\n", avg[0], avg[1], avg[2], avg[3], avg[4], avg[5], avg[12]);
    printf("2024:    %lf %lf %lf %lf %lf %lf | GLT: %lf\n", avg[6], avg[7], avg[8], avg[9], avg[10], avg[11], avg[13]);

    return 0;
}