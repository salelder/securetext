#include "stdio.h"
#include "time.h"
const int KEYSIZE = 256; // number of unsigned chars in key

void zero(unsigned char a[KEYSIZE]) {int k;for(k=0;k<KEYSIZE;++k)a[k]=0;}

void add(unsigned char a[KEYSIZE], unsigned char b[KEYSIZE], unsigned char result[KEYSIZE]) {
  unsigned int fullsum;
  unsigned char carry = 0;
  int k;

  for (k = 0; k < KEYSIZE; ++k) {
    fullsum = a[k] + b[k] + carry;
    result[k] = fullsum;
    if (result[k] < fullsum) {carry=1;} else {carry=0;}
  }
}
void shiftbigger(unsigned char a[KEYSIZE], int n) {
  int k = KEYSIZE-1;
  while (k >= 0) {
    if (k-n >= 0) { a[k] = a[k-n]; }
    else { a[k]=0; }
    --k;
  }
}
void shiftsmaller(unsigned char a[KEYSIZE], int n) {
  int k = 0;
  while (k < KEYSIZE) {
    if (k+n < KEYSIZE) {a[k] = a[k+n];}
    else { a[k]=0; }
    ++k;
  }
}

// large number by a single digit
void multiply_digit(unsigned char a[KEYSIZE], unsigned char d, unsigned char result[KEYSIZE]) {
  unsigned int fullprod;
  unsigned char carry = 0;
  int k;
  for (k=0;k<KEYSIZE;++k) {
    fullprod = (a[k] * d) + carry;
    result[k] = fullprod;
    carry = (fullprod - result[k]) / 256;
  }
}
void multiply(unsigned char a[KEYSIZE], unsigned char b[KEYSIZE], unsigned char result[KEYSIZE]) {
  unsigned char temp[KEYSIZE];
  int k;

  zero(result);
  for (k=0;k<KEYSIZE;++k) {
    multiply_digit(a, b[k], temp);
    shiftbigger(temp, k);
    add(temp, result, result);
  }
}

void benchmark(int N) {
  unsigned char a[KEYSIZE];
  unsigned char b[KEYSIZE];
  unsigned char c[KEYSIZE];
  int k;
  clock_t start, finish;
  start = clock();
  for (k=0; k < N; ++k) {
    multiply(a, b, c);
  }
  finish = clock();
  printf("Multiplies per second: %f", (double)(N*CLOCKS_PER_SEC)/(finish-start));
}

void main() {
  benchmark(1000);
}