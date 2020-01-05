#include <stdio.h>
#include <math.h>
#include <math.h>
#include <time.h>

/******************************************************************************
 * This program takes an initial estimate of m and c and finds the associated 
 * rms error. It is then as a base to generate and evaluate 8 new estimates, 
 * which are steps in different directions in m-c space. The best estimate is 
 * then used as the base for another iteration of "generate and evaluate". This 
 * continues until none of the new estimates are better than the base. This is
 * a gradient search for a minimum in mc-space.
 * 
 * To compile:
 *   cc -o lin80 80.c -lm
 * 
 * To run:
 *   ./lin80
 * 
 * Dr Kevan Buckley, University of Wolverhampton, 2018
 *****************************************************************************/

typedef struct point_t {
  double x;
  double y;
} point_t;

int n_data = 1000;
point_t data[];

double residual_error(double x, double y, double m, double c) {
  double e = (m * x) + c - y;
  return e * e;
}

double rms_error(double m, double c) {
  int i;
  double mean;
  double error_sum = 0;
  
  for(i=0; i<n_data; i++) {
    error_sum += residual_error(data[i].x, data[i].y, m, c);  
  }
  
  mean = error_sum / n_data;
  
  return sqrt(mean);
}
int time_difference(struct timespec *start, struct timespec *finish, long long int *difference)
 {
	  long long int ds =  finish->tv_sec - start->tv_sec; 
	  long long int dn =  finish->tv_nsec - start->tv_nsec; 

	  if(dn < 0 ) {
	    ds--;
	    dn += 1000000000; 
  } 
	  *difference = ds * 1000000000 + dn;
	  return !(*difference > 0);
}

int main() {
  int i;
  double bm = 1.3;
  double bc = 10;
  double be;
  double dm[8];
  double dc[8];
  double e[8];
  double step = 0.01;
  double best_error = 999999999;
  int best_error_i;
  int minimum_found = 0;
  
  double om[] = {0,1,1, 1, 0,-1,-1,-1};
  double oc[] = {1,1,0,-1,-1,-1, 0, 1};

  be = rms_error(bm, bc);

  while(!minimum_found) {
    for(i=0;i<8;i++) {
      dm[i] = bm + (om[i] * step);
      dc[i] = bc + (oc[i] * step);    
    }
      
    for(i=0;i<8;i++) {
      e[i] = rms_error(dm[i], dc[i]);
      if(e[i] < best_error) {
        best_error = e[i];
        best_error_i = i;
      }
    }

    printf("best m,c is %lf,%lf with error %lf in direction %d\n", 
      dm[best_error_i], dc[best_error_i], best_error, best_error_i);
    if(best_error < be) {
      be = best_error;
      bm = dm[best_error_i];
      bc = dc[best_error_i];
    } else {
      minimum_found = 1;
    }
  }
  printf("minimum m,c is %lf,%lf with error %lf\n", bm, bc, be);
	struct timespec start, finish;   
  	long long int time_elapsed;

  	clock_gettime(CLOCK_MONOTONIC, &start);
	clock_gettime(CLOCK_MONOTONIC, &finish);
	  time_difference(&start, &finish, &time_elapsed);
	  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
		                                 (time_elapsed/1.0e9)); 
	

  return 0;
}

point_t data[] = {
  {67.34,113.70},{65.64,107.33},{77.21,120.83},{69.46,98.53},
  {82.66,122.81},{79.93,110.25},{78.72,119.00},{71.73,106.55},
  {79.88,114.48},{85.62,137.14},{71.45,109.96},{72.83,99.46},
  { 0.99,29.26},{41.64,88.04},{18.43,34.17},{24.64,70.43},
  {49.23,62.57},{17.18,33.32},{84.17,125.71},{19.16,37.59},
  {65.75,94.69},{61.89,100.96},{ 7.63,25.76},{32.14,75.14},
  {81.85,132.03},{62.62,99.49},{60.93,120.92},{38.71,66.57},
  {44.26,83.96},{42.01,77.08},{55.64,87.09},{45.27,77.45},
  { 9.59,27.71},{99.70,141.63},{77.48,120.65},{66.43,102.85},
  {79.04,134.08},{74.00,114.55},{30.98,57.81},{58.33,83.90},
  {34.38,56.83},{ 1.19,17.17},{ 6.97,34.57},{35.24,55.81},
  {30.30,88.92},{53.17,75.40},{42.71,63.72},{26.61,61.59},
  {67.95,117.09},{37.62,74.16},{36.21,67.80},{ 4.51,34.16},
  {45.87,84.07},{25.21,46.04},{64.21,93.56},{65.06,93.89},
  {30.48,64.90},{59.71,120.09},{37.16,80.84},{17.85,42.87},
  {69.09,107.85},{13.35,55.72},{92.53,140.18},{59.93,93.65},
  {10.66,44.69},{60.76,83.69},{ 6.90,25.23},{24.37,52.24},
  {66.02,98.22},{71.45,105.31},{39.64,65.89},{ 1.67,44.18},
  {52.06,79.66},{ 5.83, 5.63},{21.68,44.37},{82.06,134.78},
  {20.98,46.32},{94.81,106.13},{23.19,56.99},{89.42,150.81},
  {86.69,107.89},{ 7.53,46.05},{22.20,51.09},{58.69,83.56},
  {25.24,71.88},{56.56,101.92},{77.00,137.81},{23.36,31.65},
  {40.02,48.64},{23.04,32.97},{50.21,72.95},{88.09,137.94},
  {41.99,77.03},{47.55,90.55},{28.70,79.00},{ 7.01,41.29},
  {59.05,79.52},{72.94,108.69},{76.35,136.24},{18.50,30.83},
  {17.65,53.08},{27.57,58.30},{31.17,63.25},{ 3.00,22.16},
  {21.59,50.88},{36.35,54.90},{97.99,129.01},{53.11,86.90},
  { 6.15,38.09},{19.92,46.53},{72.60,99.95},{ 2.82,15.30},
  {14.38,58.68},{89.13,111.72},{73.88,108.91},{40.61,81.11},
  {60.52,87.35},{21.28,55.84},{36.89,72.37},{72.83,129.51},
  {62.15,110.24},{65.84,102.33},{ 3.59,33.20},{78.11,121.23},
  {79.29,110.04},{ 0.13,17.69},{28.18,51.85},{94.84,153.27},
  {85.73,118.16},{41.64,50.94},{85.42,124.76},{79.55,111.57},
  {76.25,131.75},{14.04,35.88},{76.12,125.38},{23.46,40.44},
  {93.52,131.54},{56.07,92.32},{17.61,62.10},{90.60,123.23},
  {96.11,151.08},{85.55,130.36},{11.98,20.15},{11.24,40.19},
  {11.68,38.91},{34.57,79.75},{89.99,105.98},{94.33,147.77},
  {56.14,96.07},{44.58,82.10},{69.71,128.47},{99.50,145.75},
  {45.20,75.93},{63.72,93.83},{ 5.07,32.86},{97.44,124.34},
  {91.51,154.66},{ 0.28,22.35},{66.69,94.12},{80.72,107.31},
  {63.21,105.80},{93.23,127.61},{ 0.93,29.76},{32.10,64.73},
  {53.13,87.32},{ 4.92,31.81},{83.93,102.15},{99.90,156.21},
  {32.77,50.50},{13.12,38.10},{19.25,57.25},{63.27,72.60},
  {50.18,92.36},{ 3.99,24.79},{18.10,35.38},{30.15,69.54},
  {62.29,98.85},{24.76,67.64},{24.85,64.25},{ 5.67,31.17},
  {56.04,92.60},{87.97,131.55},{11.84,30.71},{90.64,126.68},
  {34.09,55.57},{ 8.42, 7.34},{41.89,77.80},{27.70,48.74},
  {16.52,49.82},{66.40,95.89},{38.80,61.87},{29.50,39.37},
  {37.98,65.04},{45.80,79.95},{ 9.42,29.01},{98.34,135.98},
  {90.21,142.61},{86.08,133.69},{21.97,46.87},{36.60,65.46},
  {10.25,40.89},{67.24,109.69},{60.25,100.91},{13.57,20.30},
  {78.84,116.30},{ 2.81,11.60},{91.18,125.62},{94.99,140.08},
  {68.13,100.95},{80.90,126.83},{59.56,92.96},{27.95,62.37},
  {78.45,113.47},{88.97,119.96},{18.62,37.35},{77.64,133.58},
  {46.23,68.88},{44.42,73.34},{56.11,94.63},{59.72,97.99},
  {25.97,70.14},{97.66,118.61},{95.29,153.68},{39.14,82.20},
  {12.22,30.14},{38.87,65.58},{35.09,74.04},{45.98,84.97},
  {33.38,61.14},{48.51,79.80},{52.60,89.19},{12.75,21.85},
  {83.98,112.89},{90.47,136.95},{85.64,124.85},{10.56,30.50},
  {68.76,108.95},{70.89,116.29},{72.25,109.02},{96.91,143.34},
  {15.99,45.55},{92.84,121.32},{96.68,126.49},{27.09,79.73},
  {86.96,119.46},{64.29,99.51},{47.36,80.45},{ 6.79,30.58},
  {49.93,83.78},{36.10,78.50},{34.13,68.19},{47.16,86.70},
  {69.09,104.55},{37.07,83.93},{ 9.54,22.37},{86.48,141.92},
  {43.44,78.14},{52.96,77.11},{ 6.39,27.23},{53.63,77.69},
  { 3.54,28.30},{34.50,51.47},{81.48,127.58},{79.28,127.79},
  {48.67,91.02},{77.50,108.81},{ 6.90,32.70},{86.95,116.14},
  {26.05,50.56},{66.70,97.02},{13.60,51.66},{22.12,62.89},
  {94.92,132.01},{88.24,130.97},{35.81,79.29},{70.92,113.75},
  {85.37,119.86},{36.51,56.43},{12.54,54.17},{ 7.46,13.50},
  {39.02,68.12},{64.14,90.79},{ 4.78,22.45},{84.60,139.87},
  {66.41,114.43},{13.85,50.71},{17.31,37.41},{65.31,109.93},
  {73.68,116.82},{50.17,77.19},{18.98,45.91},{54.23,81.06},
  {57.20,88.44},{59.00,98.90},{96.09,138.92},{69.51,94.27},
  {95.13,123.40},{76.05,100.87},{58.39,92.40},{32.51,52.97},
  {83.24,107.82},{71.00,107.09},{78.24,100.69},{84.45,123.03},
  { 9.13,45.13},{79.96,125.13},{96.84,143.73},{14.14,31.39},
  {60.79,98.53},{ 7.17,36.14},{62.77,98.94},{20.82,39.88},
  {18.18,44.74},{27.48,46.52},{52.76,87.91},{75.91,107.97},
  {47.22,63.04},{73.98,111.08},{80.42,127.46},{26.77,50.71},
  {92.27,127.31},{62.72,105.10},{25.18,49.57},{34.18,68.51},
  {31.47,51.66},{ 3.73,46.05},{19.66,53.65},{73.06,106.12},
  {76.38,107.84},{72.90,99.43},{85.91,133.50},{48.35,77.42},
  {16.16,53.66},{58.53,97.94},{38.15,82.85},{86.08,137.09},
  {92.39,127.70},{47.97,74.37},{97.35,142.08},{59.84,84.91},
  {16.21,37.57},{75.99,106.34},{74.71,109.90},{79.99,124.20},
  {50.24,103.34},{58.72,108.99},{98.91,136.66},{ 0.13,30.29},
  {43.30,83.70},{60.16,104.14},{ 6.19,32.49},{63.43,104.83},
  {49.12,103.74},{96.09,143.01},{34.27,58.84},{47.70,75.47},
  {65.57,100.37},{74.95,88.29},{50.06,84.33},{58.60,90.73},
  {99.95,131.92},{34.62,55.33},{93.14,145.11},{ 1.05,23.00},
  {80.94,131.46},{47.96,86.45},{70.90,109.70},{71.20,124.83},
  {61.77,107.90},{49.79,81.97},{88.55,157.36},{72.53,103.38},
  {53.81,86.77},{18.16,58.37},{42.20,74.42},{89.22,113.59},
  { 0.19, 5.76},{20.32,29.51},{71.13,89.39},{85.44,110.13},
  {96.43,129.90},{77.80,126.32},{15.54,31.71},{50.58,69.64},
  {26.16,62.02},{61.44,87.50},{62.23,120.84},{41.77,71.83},
  {13.10,37.48},{95.80,131.12},{24.10,51.95},{ 8.28,17.64},
  { 5.78,21.14},{ 5.34,32.93},{84.68,119.50},{ 8.68,30.59},
  {77.82,131.67},{92.12,142.85},{92.84,119.94},{74.83,106.79},
  {76.61,136.85},{ 9.15,22.06},{13.03,54.85},{74.24,106.22},
  {71.52,126.98},{78.96,125.49},{75.97,126.49},{61.70,84.30},
  {25.78,38.49},{82.62,123.08},{54.57,93.57},{ 6.61,42.04},
  {70.45,120.18},{65.22,99.43},{14.85,39.59},{19.14,51.44},
  {51.62,94.44},{98.37,133.24},{91.05,137.44},{72.88,108.56},
  {18.62,51.05},{ 3.70,28.27},{42.59,78.93},{97.60,133.66},
  {92.86,125.38},{17.23,72.35},{25.07,73.86},{ 4.34,24.54},
  {93.81,144.53},{11.98,44.04},{ 5.08,38.52},{40.68,77.28},
  {42.19,72.92},{42.38,72.60},{31.50,53.95},{ 6.54,52.37},
  {86.11,141.04},{26.94,60.74},{23.55,38.80},{13.55,57.35},
  {75.96,96.91},{37.50,50.50},{51.48,79.59},{13.84,50.15},
  {54.95,100.00},{67.42,106.62},{ 8.37,19.61},{26.73,48.75},
  {55.98,78.92},{69.91,108.60},{45.51,71.92},{76.95,115.40},
  {95.63,118.72},{91.91,119.44},{10.73,26.34},{60.31,97.45},
  {38.15,69.23},{61.48,96.76},{ 8.59,42.58},{60.67,84.67},
  {36.81,64.30},{65.07,97.64},{85.25,112.26},{ 9.14,27.96},
  {10.96,36.54},{28.50,48.47},{41.14,70.80},{70.21,117.30},
  {91.35,139.21},{81.38,135.21},{35.41,45.53},{93.48,138.37},
  {45.90,83.62},{78.93,104.86},{36.97,73.26},{29.36,48.11},
  {14.25,47.84},{18.64,49.49},{33.88,66.87},{58.51,102.41},
  {64.27,122.68},{26.45,56.83},{64.85,89.55},{14.80,51.50},
  {36.22,55.14},{35.63,68.61},{ 6.77,51.69},{79.61,141.43},
  {69.68,100.36},{98.17,156.56},{71.82,126.45},{90.98,131.44},
  { 9.03,23.22},{38.40,72.77},{28.21,56.06},{66.73,92.18},
  {54.88,96.43},{20.66,58.06},{94.63,139.30},{14.05,42.22},
  {55.51,99.70},{94.81,120.75},{ 6.92,38.04},{73.48,97.92},
  {19.03,43.05},{71.57,107.15},{69.11,113.46},{ 4.93,24.84},
  {79.49,127.45},{31.57,45.68},{30.45,68.18},{50.45,87.83},
  {60.49,89.77},{ 3.59,26.63},{18.80,49.52},{10.26,21.96},
  {74.40,104.05},{49.93,81.57},{79.73,127.07},{68.00,99.73},
  {72.78,114.06},{97.71,140.35},{83.02,151.98},{87.11,127.24},
  {11.73,12.48},{30.98,58.70},{41.77,69.96},{ 8.50,34.37},
  {80.05,116.82},{70.06,103.36},{25.19,48.06},{ 3.18,18.90},
  {63.23,107.62},{85.17,111.28},{94.02,122.82},{72.49,120.39},
  {76.34,115.37},{94.60,144.87},{67.42,111.35},{11.85,39.82},
  {64.94,81.62},{ 5.40,38.38},{90.90,114.71},{20.32,53.67},
  {10.17,19.25},{72.28,123.07},{76.33,112.17},{ 6.24,31.05},
  {24.97,55.80},{64.47,112.37},{48.95,74.46},{72.02,109.36},
  { 0.29,32.00},{21.11,59.74},{18.99,42.91},{ 7.30,38.59},
  {24.73,41.97},{16.84,40.34},{40.13,56.84},{65.48,90.11},
  {24.77,55.76},{97.51,154.16},{25.20,59.14},{30.18,49.57},
  {10.00,19.22},{ 4.04,38.03},{19.90,37.99},{21.29,32.99},
  {49.99,79.17},{93.49,133.44},{31.88,60.85},{27.38,28.01},
  {61.56,93.25},{26.00,41.72},{29.39,61.75},{32.64,55.22},
  {88.16,116.11},{16.79,51.40},{97.74,125.80},{27.43,53.58},
  {24.64,48.19},{30.52,66.59},{98.14,140.10},{93.59,139.03},
  {69.88,108.85},{ 5.75,15.47},{98.84,104.29},{39.86,83.68},
  {54.13,72.52},{95.95,140.98},{90.24,125.62},{ 6.41,40.04},
  {54.70,89.42},{30.06,71.47},{73.37,99.31},{96.33,134.78},
  {43.08,76.06},{62.67,91.02},{69.71,121.86},{34.71,72.22},
  {12.89,43.63},{52.65,82.07},{94.48,140.35},{ 0.46,35.85},
  {51.37,80.94},{17.00,59.85},{70.53,108.02},{85.86,124.89},
  {84.17,115.65},{90.24,136.09},{49.50,101.23},{83.64,132.49},
  {35.41,70.80},{75.56,122.82},{56.82,82.77},{95.03,135.92},
  {98.92,135.12},{90.86,126.56},{71.51,100.07},{73.64,113.68},
  {11.54,34.19},{98.58,131.08},{11.27,25.62},{66.29,100.32},
  {11.97,54.36},{67.79,92.60},{29.86,45.83},{31.04,57.26},
  {49.64,68.56},{76.33,119.95},{80.35,119.48},{62.73,116.67},
  {77.80,119.12},{37.01,50.55},{29.06,51.25},{49.58,63.32},
  {61.54,107.83},{52.67,82.12},{61.64,89.95},{ 7.90,26.30},
  {33.71,55.76},{53.07,105.38},{83.84,104.08},{86.87,124.47},
  {19.69,49.51},{96.45,132.62},{42.04,72.70},{51.86,85.66},
  {84.85,111.61},{31.26,61.70},{ 0.60,28.93},{90.68,143.17},
  {10.13,47.20},{48.38,82.48},{83.10,117.64},{24.56,65.32},
  { 0.16,23.81},{57.64,97.76},{76.52,122.84},{21.94,60.85},
  {13.51,39.59},{96.77,154.21},{86.02,125.76},{20.03,61.87},
  { 9.01,17.91},{92.49,129.96},{38.59,70.76},{75.91,112.95},
  {88.04,120.79},{75.84,121.94},{17.70,42.10},{ 8.76,25.78},
  {60.53,102.64},{ 3.14,20.83},{61.25,75.10},{72.68,124.13},
  {76.15,104.86},{56.39,101.21},{77.90,112.47},{ 6.09,33.55},
  {42.86,97.50},{60.95,86.58},{ 3.31,32.22},{82.78,109.12},
  { 0.07,11.61},{86.66,141.73},{50.42,96.48},{47.70,90.41},
  {89.26,135.34},{61.56,102.49},{38.10,63.27},{85.58,106.39},
  {56.01,98.26},{16.60,43.65},{79.22,116.05},{67.80,123.44},
  {17.48,59.04},{75.32,115.28},{57.36,83.02},{37.84,58.59},
  {64.01,105.86},{24.23,40.61},{ 7.75,26.68},{87.44,135.22},
  {95.74,129.67},{ 6.76,16.07},{64.79,106.16},{99.46,135.54},
  {84.58,125.76},{84.06,114.72},{10.28,47.54},{42.13,68.28},
  {44.37,87.68},{26.79,48.09},{44.92,84.74},{52.78,94.07},
  { 4.99,31.61},{90.10,131.74},{13.19,38.03},{32.37,64.58},
  {23.81,68.78},{99.34,137.77},{60.86,106.77},{34.28,75.89},
  {88.29,126.42},{70.57,91.24},{61.75,97.04},{58.92,100.51},
  { 0.98,31.08},{18.66,28.53},{42.35,66.57},{29.19,39.96},
  {63.07,115.47},{79.25,120.20},{81.18,136.37},{37.52,72.97},
  {55.97,91.89},{31.24,51.04},{57.36,78.88},{33.74,62.91},
  {95.09,128.79},{32.07,54.62},{32.39,71.86},{72.62,129.41},
  {90.37,127.01},{23.33,46.97},{57.34,76.17},{17.91,41.86},
  {51.46,103.63},{45.57,80.42},{22.84,43.01},{73.31,111.63},
  {19.24,50.03},{68.26,109.62},{32.70,61.95},{45.03,84.59},
  {48.51,76.24},{52.19,86.37},{62.04,102.23},{42.47,83.31},
  {76.42,98.61},{32.53,63.17},{49.78,93.90},{24.74,43.22},
  {37.14,50.11},{93.91,128.57},{70.29,102.69},{44.70,70.37},
  { 1.75,24.62},{39.07,54.29},{10.47,36.65},{66.14,100.52},
  {41.95,78.68},{65.90,99.38},{93.08,149.95},{85.14,132.75},
  {46.38,74.95},{76.75,109.43},{10.53,26.52},{ 9.44,43.19},
  {45.30,80.50},{ 4.15,15.32},{25.95,48.89},{73.51,110.33},
  { 3.23,14.36},{ 5.48,18.28},{54.15,88.11},{42.72,66.38},
  {94.75,140.06},{46.98,68.62},{44.09,64.82},{10.41,49.91},
  {44.13,95.00},{92.31,134.19},{59.86,94.19},{23.65,39.75},
  { 1.89,29.28},{59.76,95.32},{31.81,66.66},{56.24,87.64},
  {61.89,88.86},{ 9.81,38.71},{91.22,115.85},{48.51,82.10},
  {80.03,130.44},{61.99,112.53},{17.62,30.35},{ 9.53,25.46},
  {11.63,39.18},{18.23,43.32},{80.40,135.19},{16.63,47.24},
  {45.68,88.28},{20.29,32.32},{38.87,74.29},{41.20,71.95},
  {20.54,65.57},{78.98,101.52},{62.46,106.58},{91.52,118.50},
  {48.87,109.98},{62.70,98.89},{24.34,51.55},{79.04,125.09},
  {55.40,79.91},{41.32,67.92},{44.28,83.11},{70.73,126.69},
  {25.32,35.98},{32.70,56.44},{50.43,85.98},{34.48,67.52},
  {37.72,72.87},{19.21,64.74},{15.05,26.62},{69.88,115.44},
  {80.72,133.31},{48.50,77.25},{ 8.12,15.20},{63.67,100.22},
  { 4.07,26.00},{54.05,76.88},{92.85,138.62},{79.06,113.07},
  {77.77,116.61},{ 7.39,22.58},{55.31,65.65},{19.34,37.96},
  {64.59,92.76},{68.71,102.89},{12.91,41.95},{50.02,67.97},
  {50.22,59.74},{69.76,115.01},{77.66,122.09},{ 1.00,32.59},
  {33.23,62.46},{90.08,126.41},{ 8.62,45.57},{77.50,113.10},
  {81.85,129.04},{33.90,66.03},{14.00,18.61},{ 3.66,13.92},
  {32.33,51.21},{76.59,120.04},{32.66,56.47},{38.33,56.24},
  {80.96,133.73},{81.64,121.36},{58.72,92.46},{40.93,68.43},
  {53.66,94.13},{54.16,102.01},{64.30,89.10},{45.89,77.19},
  {85.43,126.37},{13.04,36.05},{71.34,104.49},{96.82,127.41},
  {75.17,96.38},{27.60,48.81},{85.03,142.47},{23.13,53.45},
  {53.18,81.87},{55.21,107.00},{19.15,53.67},{82.66,116.31},
  {16.11,46.71},{71.00,112.74},{97.38,138.83},{98.50,149.62},
  { 1.49,23.41},{54.99,99.72},{25.45,52.38},{50.71,81.57},
  {89.44,116.90},{47.80,80.66},{49.34,76.23},{78.97,130.45},
  {52.15,74.93},{10.02,37.30},{ 4.54,19.81},{37.28,66.17},
  {17.25,50.92},{56.36,74.46},{68.18,103.21},{66.36,112.69},
  {31.13,67.26},{ 0.03,20.19},{11.67,43.95},{84.36,137.33},
  {56.27,83.27},{74.40,125.67},{72.63,125.23},{ 2.31,35.72},
  {35.96,78.27},{86.74,133.83},{79.18,117.13},{40.45,57.84},
  {30.96,55.10},{55.39,78.49},{ 9.89,34.02},{23.87,44.22},
  { 6.79,39.16},{15.57,26.00},{98.48,144.68},{51.00,86.53},
  {89.40,117.01},{66.98,107.62},{15.97,25.82},{56.23,92.48},
  {18.88,31.00},{56.72,98.64},{78.92,114.63},{85.64,126.69},
  {64.40,96.98},{85.99,146.61},{ 5.17, 6.90},{97.92,149.29},
  { 0.07,26.60},{71.48,93.16},{ 2.11,28.51},{55.52,82.79},
  { 8.77,54.27},{ 0.58, 3.25},{39.34,77.55},{95.06,139.12},
  {60.68,88.65},{39.39,78.82},{57.83,83.39},{72.14,120.75},
  {40.65,71.37},{ 6.07,31.20},{85.27,131.37},{96.75,140.76},
  {36.49,65.08},{ 1.87,17.13},{33.04,81.93},{21.67,50.03},
  {42.43,57.86},{65.56,101.12},{73.42,108.60},{ 7.16,42.83},
  {63.57,107.08},{23.82,62.40},{ 0.75,28.26},{60.59,94.40},
  {92.98,137.74},{17.61,28.21},{29.25,57.52},{87.47,119.40},
  {96.38,144.61},{13.28,39.57},{22.24,48.22},{70.60,123.10},
  {86.99,112.36},{11.12,29.35},{70.63,92.78},{55.21,103.61},
  {82.36,119.56},{44.26,66.55},{85.85,114.83},{60.43,101.17},
  {31.88,50.02},{22.06,53.85},{39.30,56.76},{28.56,58.99},
  {71.77,119.59},{89.11,129.27},{42.16,104.21},{38.20,73.32},
  {22.15,51.01},{64.38,112.16},{59.82,122.34},{16.53,33.83},
  {64.26,83.98},{62.65,93.34},{49.31,85.00},{ 9.17,32.73}
};
