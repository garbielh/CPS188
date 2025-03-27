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

void comparison(double avg[], int *x, int start, int end) {     // finds maximum value
    double max = avg[0];
    int c = 0;
    for (int i = start; i < end; i++) {
        if (avg[i] > max) {
            max = avg[i];
            c = i;
        }
    }
    *x = c;
}

int main (void) {
    
    FILE *data = fopen("testData.txt", "r");

    // q1
    int numyear, num_elements, n;
    int tyear[MAX], tday[MAX];
    char buff[70];
    double tsup[MAX], tmich[MAX], thur[MAX], terie[MAX], tont[MAX], tstclr[MAX], tGLT[MAX];
    double *test[7] = {tsup, tmich, thur, terie, tont, tstclr, tGLT};
    double avg[14]; // first 6 avg, second 6 avg, yr1, yr2

    // q2
    int max1, min1, max2, min2;

    //q3
    int maxLake;
    const char *names[] = {"Superior", "Michigan", "Huron", "Erie", "Ontario", "St. Clair"};

    // q4
    double allLakesMax[6];
    double absMax;

    // file initialization and reading of data
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

    // Question 1
    printf("Question 1\n\n");

    num_elements = nonzero(tyear, MAX);     // find number of non-zero elements
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

    // averages for the Great Lakes
    for (int i = 0; i < 6; i++) {   // first year
        avg[i] = average(real[i], 0, numyear);
    }

    for (int i = 0; i < 6; i++) {   // second year
        avg[i+6] = average(real[i], numyear, num_elements);
    }

    // averages for the Great Lakes Total
    avg[12] = average(real[6], 0, numyear);
    avg[13] = average(real[6], numyear, num_elements);

    printf("         Superior Michigan Huron    Erie     Ontario  St. Clair | GLT\n");
    printf("2023:    %8f %8f %8f %8f %8f %8f  | %lf\n", avg[0], avg[1], avg[2], avg[3], avg[4], avg[5], avg[12]);
    printf("2024:    %8f %8f %8f %8f %8f %8f | %lf\n", avg[6], avg[7], avg[8], avg[9], avg[10], avg[11], avg[13]);
    printf("\n\n");


    // Question 2
    printf("Question 2\n");
    comparison(avg, &max1, 0, 6);        // first year
    comparison(avg, &max2, 6, 12);       // second year

    printf("Lake %s had the highest ice concentration in 2023.\n", names[max1]);
    printf("Lake %s had the highest ice concentration in 2024.\n", names[max2 - 6]);

    printf("\n\n");


    // Question 3
    printf("Question 3\n");
    for (int c = 0; c < 6; c++) {
        comparison(real[c], &maxLake, 0, num_elements); // find the max value of lake and location
        double m = real[c][maxLake];        // max value of that lake
        allLakesMax[c] = m;     // store in separate "max" array
        printf("Highest ice concentration at Lake %s: %.2f%% at ", names[c], m);
    
        for(int i = 0, check = 0; i < num_elements; i++) {      // finds any duplicate dates and prints them
            if (real[c][i] == m) {
                if (check != 0) {
                    printf(", ");
                }
                printf("day %d, %d", day[i], year[i]);
                check = 1;
            }
        }
        printf("\n");
        
        
    }
    
    /* uncomment this to print out maximum values of the lakes */ 
    // printf("allLakesMax: ");
    //     for (int i = 0; i < 6; i++) {
    //         printf("%lf ", allLakesMax[i]);
    //     }
    printf("\n\n");


    // Question 4
    printf("Question 4\n");
    comparison(allLakesMax, &maxLake, 0, 6);       // find the largest "largest value" from each lake
    absMax = allLakesMax[maxLake];      // store ABSOLUTE maximum value

    printf("The highest ice concentration percentage was found at Lake %s with a %.2f%% on ", names[maxLake], absMax);
    for(int i = 0, check = 0; i < num_elements; i++) {      // finds any duplicate dates and prints them
        if (real[maxLake][i] == absMax) {
            if (check != 0) {
                printf(", ");
            }
            printf("day %d, %d", day[i], year[i]);
            check = 1;
        }
    }
    printf("\n\n");

    fclose(data);
    return 0;
}