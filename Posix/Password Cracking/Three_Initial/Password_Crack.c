#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>

/******************************************************************************
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2 uppercase
  letters and a 2 digit integer. Your personalised data set is included in the
  code. 

  Compile with:
    cc -o Three_Initial Three_Initial.c -lcrypt

  If you want to analyse the results then use the redirection operator to send
  output to a file that you can view using an editor or the less utility:

    ./Three_Initial > Three_Initial.txt

  Dr Kevan Buckley, University of Wolverhampton, 2018
******************************************************************************/
int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$tTx2BjjTu.5ft2cPoIdrgLW7fuhzpBOxUKegi1rbAwLkGA72ihKbI9iVaHqSmz8sCwj1VeRXWaDvoSW1TO7A/1",
  "$6$KB$QH0ziqv8rHkcKmDliYMG936vks5xS0ti9/mW0cAqW40viPFxGb3xsUGj.XzWYtPMNERZhOYW2DixwPB03CzqB1",
  "$6$KB$2JgeE8PySv0vB4GN5kNzhMxpi3q.i3LfaJCbzkDWxWrup1JKfv28gDPZJrwZ3qyP9/mvDXlO9TwLBSl/XDmcA/",
  "$6$KB$7rANMlqw35aWxrgzUBoG1b5qMBEzrmpc1fvHdg7TIYJdOJaidsgGJAaXE5BkHrbHCzLOibvIf7MWRW6xuU7Fb0"
};

/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

/**
 This function can crack the kind of password explained above. All combinations
 that are tried are displayed and when the password is found, #, is put at the 
 start of the line. Note that one of the most time consuming operations that 
 it performs is the output of intermediate results, so performance experiments 
 for this kind of program should not include this. i.e. comment out the printfs.
*/

void Passwordcrack(char *salt_and_encrypted){
  int x, y, z, a;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='A'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
	for(z='A'; z<='Z'; z++){
      	for(a=0; a<=99; a++){
		sprintf(plain, "%c%c%c%02d", x, y, z,a); 
		enc = (char *) crypt(plain, salt);
		count++;
		if(strcmp(salt_and_encrypted, enc) == 0){
		  printf("#%-8d%s %s\n", count, plain, enc);
		} /*else {
		  printf(" %-8d%s %s\n", count, plain, enc);
		}*/
      }
	}
    }
  }
  printf("%d solutions explored\n", count);
}

//Calculating time

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
int main(int argc, char *argv[])
{
  	int i;
	struct timespec start, finish;   
  	long long int time_elapsed;

  	clock_gettime(CLOCK_MONOTONIC, &start);

  	for(i=0;i<n_passwords;i<i++) 
	{
    		Passwordcrack(encrypted_passwords[i]);
  	}
	clock_gettime(CLOCK_MONOTONIC, &finish);
	  time_difference(&start, &finish, &time_elapsed);
	  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
		                                 (time_elapsed/1.0e9)); 
  return 0;
}
