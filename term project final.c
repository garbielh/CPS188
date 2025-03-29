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

void comparison(double avg[], int *x, int *y, int start, int end) {     // finds maximum value
    double max = avg[0];
    double min = avg[0];
    int c = 0, t = 0;
    for (int i = start; i < end; i++) {
        if (avg[i] > max) {
            max = avg[i];
            c = i;
        }
        else if (avg[i] < min) {
            min = avg[i];
            t = i;
        }
    }
    *x = c;
    *y = t;
}

int main (void) {
    
    FILE *data = fopen("g2023_2024_ice.dat.txt", "r");
    FILE *data1 = fopen("g2021_2022_ice.dat.txt", "r");
    FILE *data2 = fopen("g2022_2023_ice.dat.txt", "r");

    //Files for question 5 and 6
    FILE *sup = fopen("supdailyavg.txt", "w");
    FILE *mich = fopen("michdailyavg.txt", "w");
    FILE *huron = fopen("hurondailyavg.txt", "w");
    FILE *erie = fopen("eriedailyavg.txt", "w");
    FILE *on = fopen("ondailyavg.txt", "w");
    FILE *cl = fopen("cldailyavg.txt", "w");
    FILE *combine = fopen("combinedailyavg.txt", "w");

    //Files for question 8
    FILE *sup8 = fopen("superior8.txt", "w");
    FILE *mich8 = fopen("michigan8.txt", "w");
    FILE *huron8 = fopen("huron8.txt", "w");
    FILE *erie8 = fopen("erie8.txt", "w");
    FILE *on8 = fopen("ontario8.txt", "w");
    FILE *cl8 = fopen("stclair8.txt", "w");

    // q1
    int numyear, num_elements, n = -1;
    int tyear[MAX], tday[MAX];
    char buff[70];
    double tsup[MAX], tmich[MAX], thur[MAX], terie[MAX], tont[MAX], tstclr[MAX], tGLT[MAX];
    double *test[7] = {tsup, tmich, thur, terie, tont, tstclr, tGLT};
    double avg[14]; // first 6 (0-5) avg of 2023, second 6 (6-11) avg of 2024, yr1 (12), yr2 (13)

    // q2
    int max1, min1, max2, min2;

    //q3
    int maxLake, dummy;
    const char *names[] = {"Superior", "Michigan", "Huron", "Erie", "Ontario", "St. Clair", "GL Average"};

    // q4
    double allLakesMax[6];
    double absMax;

    // Initialize variables for the row string, counting, average variables and arrays

    //Variable to store the entire row as a string
    char row[100];

    //counting variables, used in loops and calculating averages
    int year, count = 0, count21 = 0, count22 = -1, count221 = 0, count23 = -1 , count231 = 0, count24 = -1;

    //Reads the string and stores the numbers in these variables
    double day, savg, mavg, havg, eavg, oavg, clavg, total;

    //Variables for question 7 (calculating table)
    double avg21[7], avg22[7], avg221[7], avg23[7], avg231[7], avg24[7];

    // file initialization and reading of data
    if (data == NULL) {
        perror("Error opening file");
        return 1;
    }

    for(int i = 0; i<=7; i++){
        fgets(row, 100, data);
        fgets(row, 100, data1);
        fgets(row, 100, data2);
    }

    // storing data for 2023-2024
    while (!feof(data)) {               
        n++;
        fscanf(data, "%d", &tyear[n]);
        fscanf(data, "%d", &tday[n]);
        fscanf(data, "%lf", &tsup[n]);
        fscanf(data, "%lf", &tmich[n]);
        fscanf(data, "%lf", &thur[n]);
        fscanf(data, "%lf", &terie[n]);
        fscanf(data, "%lf", &tont[n]);
        fscanf(data, "%lf", &tstclr[n]);
        fscanf(data, "%lf", &tGLT[n]);
    }

    // averaging data for 2021-2022
    n = 0;
    while (!feof(data1)) {      
        fgets(row, 100, data1);
        sscanf(row, "%d %lf %lf %lf %lf %lf %lf %lf %lf", &year, &day, &savg, &mavg, &havg, &eavg, &oavg, &clavg, &total);
        //Summation of 2021 and 2022 data for q6
        if (year == 2021){
            count21++;
            avg21[0] += savg;
            avg21[1] += mavg;
            avg21[2] += havg;
            avg21[3] += eavg;
            avg21[4] += oavg;
            avg21[5] += clavg;
            avg21[6] += total;
        }
        if (year == 2022){
            count22++;
            avg22[0] += savg;
            avg22[1] += mavg;
            avg22[2] += havg;
            avg22[3] += eavg;
            avg22[4] += oavg;
            avg22[5] += clavg;
            avg22[6] += total;
        }
        n++;
    }
    n = 0;

    //averaging data for 2022-2023
    while (!feof(data2)){       
        fgets(row, 100, data2);
        sscanf(row, "%d %lf %lf %lf %lf %lf %lf %lf %lf", &year, &day, &savg, &mavg, &havg, &eavg, &oavg, &clavg, &total);
        //Summation of 2022 and 2023 data for q6
        if (year == 2022){
            count221++;
            avg221[0] += savg;
            avg221[1] += mavg;
            avg221[2] += havg;
            avg221[3] += eavg;
            avg221[4] += oavg;
            avg221[5] += clavg;
            avg221[6] += total;
        }
        if (year == 2023){
            count23++;
            avg23[0] += savg;
            avg23[1] += mavg;
            avg23[2] += havg;
            avg23[3] += eavg;
            avg23[4] += oavg;
            avg23[5] += clavg;
            avg23[6] += total;
        }
    }
    
    // Question 1
    printf("Question 1\n\n");

    num_elements = nonzero(tyear, MAX);     // find number of non-zero elements
    double super[num_elements], michig[num_elements], hur[num_elements], eri[num_elements], ontar[num_elements], stclr[num_elements], GLT[num_elements];
    int year1[num_elements], day1[num_elements];

    // transfer all arrays to correct size
    itransfer(tyear, year1, num_elements);
    itransfer(tday, day1, num_elements);
    transfer(tsup, super, num_elements);
    transfer(tmich, michig, num_elements);
    transfer(thur, hur, num_elements);
    transfer(terie, eri, num_elements);
    transfer(tont, ontar, num_elements);
    transfer(tstclr, stclr, num_elements);
    transfer(tGLT, GLT, num_elements);

    // initialize pointer array for lake data for easier access
    double *real[7] = {super, michig, hur, eri, ontar, stclr, GLT};
    
    // uncomment this to print out the table
    // for (int i = 0; i < num_elements; i++) {
    //     printf("%4d %3d %7lf %7lf %7lf %7lf %7lf %7lf %7lf\n", year1[i], day1[i], sup[i], mich[i], hur[i], erie[i], ont[i], stclr[i], GLT[i]);
    // }

    numyear = yearSwitch(year1, num_elements); // indicates when the year changes
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
    comparison(avg, &max1, &min1, 0, 6);        // first year
    comparison(avg, &max2, &min2, 6, 12);       // second year

    if (avg[max1] >= avg[max2]) {
        printf("Lake %s had the highest ice concentration.\n", names[max1]);
    }
    else {
        printf("Lake %s had the highest ice concentration.\n", names[max2-6]);
    }

    if (avg[min1] <= avg[min2]) {
        printf("Lake %s had the lowest ice concentration.\n", names[min1]);
    }
    else {
        printf("Lake %s had the lowest ice concentration.\n", names[min2]);
    }

    // printf("Lake %s had the highest ice concentration in 2023.\n", names[max1]);
    // printf("Lake %s had the highest ice concentration in 2024.\n", names[max2 - 6]);

    printf("\n\n");


    // Question 3
    printf("Question 3\n");
    for (int c = 0; c < 6; c++) {
        comparison(real[c], &maxLake, &dummy, 0, num_elements); // find the max value of lake and location
        double m = real[c][maxLake];        // max value of that lake
        allLakesMax[c] = m;     // store in separate "max" array
        printf("Highest ice concentration at Lake %s: %.2f%% at ", names[c], m);
    
        for(int i = 0, check = 0; i < num_elements; i++) {      // finds any duplicate dates and prints them
            if (real[c][i] == m) {
                if (check != 0) {
                    printf(", ");
                }
                printf("day %d, %d", day1[i], year1[i]);
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
    comparison(allLakesMax, &maxLake, &dummy, 0, 6);       // find the largest "largest value" from each lake
    absMax = allLakesMax[maxLake];      // store ABSOLUTE maximum value

    printf("The highest ice concentration percentage was found at Lake %s with a %.2f%% on ", names[maxLake], absMax);
    for(int i = 0, check = 0; i < num_elements; i++) {      // finds any duplicate dates and prints them
        if (real[maxLake][i] == absMax) {
            if (check != 0) {
                printf(", ");
            }
            printf("day %d, %d", day1[i], year1[i]);
            check = 1;
        }
    }
    printf("\n\n");

    // Question 5
    for (int i = 0; i < num_elements; i++) {
        fprintf(sup, "%d %lf\n", i, super[i]);
        fprintf(mich, "%d %lf\n", i, michig[i]);
        fprintf(huron, "%d %lf\n", i, hur[i]);
        fprintf(erie, "%d %lf\n", i, eri[i]);
        fprintf(on, "%d %lf\n", i, ontar[i]);
        fprintf(cl, "%d %lf\n", i, stclr[i]);
        fprintf(combine, "%d %lf %lf %lf %lf %lf %lf \n", i, super[i], michig[i], hur[i], eri[i], ontar[i], stclr[i]);
    }
    printf("Question 5 Complete\n\n");
    printf("Question 6 Complete\n\n");
    // Question 6
    printf("Question 7\n");
    //Turning from summation to average for 6
    for (int i = 0; i <= 6; i++){
        avg21[i] /= count21;
        avg22[i] /= count22;
        avg221[i] /= count221;
        avg23[i] /= count23;
        avg231[i] /= count231;
        avg24[i] /= count24;
        
    }
    printf("\n\n");

    //Printing the table (q7)


    printf("                        Data set 1                      Data set 2                      Data set 3\n");
    printf("                  2021          2022              2022          2023              2023          2024\n");

    for (int i = 0; i < 6; i++){
        printf("%10s: ", names[i]);
        printf("%10lf %13lf %17lf  %12lf %17lf  %12lf \n", avg21[i], avg22[i], avg221[i], avg23[i], avg[i], avg[i+6]);
    }
    printf("%s: ", names[6]);
    printf("%10lf %13lf %17lf  %12lf %17lf  %12lf \n", avg21[6], avg22[6], avg221[6], avg23[6], avg[12], avg[13]);

    fclose(data);
    fclose(data1);
    fclose(data2);
    data = fopen("g2023_2024_ice.dat.txt", "r");
    data1 = fopen("g2021_2022_ice.dat.txt", "r");
    data2 = fopen("g2022_2023_ice.dat.txt", "r");
    count = 0;
    for(int i = 0; i<=7; i++){
        fgets(row, 100, data);
        fgets(row, 100, data1);
        fgets(row, 100, data2);
        
    }

    //Printing data to files similar to q5, but with all 3 data sets
    while (!feof(data1) || !feof(data2) || !feof(data)){
        count++;
        fprintf(sup8, "%d ", count);
        fprintf(mich8, "%d ", count);
        fprintf(huron8, "%d ", count);
        fprintf(erie8, "%d ", count);
        fprintf(on8, "%d ", count);
        fprintf(cl8, "%d ", count);
        fgets(row, 100, data1);
        sscanf(row, "%d %lf %lf %lf %lf %lf %lf %lf %lf", &year, &day, &savg, &mavg, &havg, &eavg, &oavg, &clavg, &total);
        fprintf(sup8, "%lf ", savg);
        fprintf(mich8, "%lf ", mavg);
        fprintf(huron8, "%lf ", havg);
        fprintf(erie8, "%lf ", eavg);
        fprintf(on8, "%lf ", oavg);
        fprintf(cl8, "%lf ", clavg);
        fgets(row, 100, data2);
        sscanf(row, "%d %lf %lf %lf %lf %lf %lf %lf %lf", &year, &day, &savg, &mavg, &havg, &eavg, &oavg, &clavg, &total);
        fprintf(sup8, "%lf ", savg);
        fprintf(mich8, "%lf ", mavg);
        fprintf(huron8, "%lf ", havg);
        fprintf(erie8, "%lf ", eavg);
        fprintf(on8, "%lf ", oavg);
        fprintf(cl8, "%lf ", clavg);
        fgets(row, 100, data);
        sscanf(row, "%d %lf %lf %lf %lf %lf %lf %lf %lf", &year, &day, &savg, &mavg, &havg, &eavg, &oavg, &clavg, &total);
        fprintf(sup8, "%lf\n", savg);
        fprintf(mich8, "%lf\n", mavg);
        fprintf(huron8, "%lf\n", havg);
        fprintf(erie8, "%lf\n", eavg);
        fprintf(on8, "%lf\n", oavg);
        fprintf(cl8, "%lf\n", clavg);
    }
    printf("Question 8 complete\n\n");

    fclose(data);
    fclose(data1);
    fclose(data2);
    return 0;
}