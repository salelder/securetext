#include "stdio.h"
#include "time.h"
const int KEYSIZE = 256; // number of unsigned chars in key
const int DOUBLE = 512; // number of unsigned chars in squared key

void zero(const int NUMBITS, unsigned char a[]) {int k;for(k=0;k<NUMBITS;++k)a[k]=0;}

void add(const int NUMBITS, unsigned char a[], unsigned char b[], unsigned char result[]) {
  unsigned int fullsum;
  unsigned char carry = 0;
  int k;

  for (k = 0; k < NUMBITS; ++k) {
    fullsum = a[k] + b[k] + carry;
    result[k] = fullsum;
    if (result[k] < fullsum) {carry=1;} else {carry=0;}
  }
}
void shiftbigger(const int NUMBITS, unsigned char a[], int n) {
  int k = NUMBITS-1;
  while (k >= 0) {
    if (k-n >= 0) { a[k] = a[k-n]; }
    else { a[k]=0; }
    --k;
  }
}
void shiftsmaller(const int NUMBITS, unsigned char a[], int n) {
  int k = 0;
  while (k < NUMBITS) {
    if (k+n < NUMBITS) {a[k] = a[k+n];}
    else { a[k]=0; }
    ++k;
  }
}

// large number by a single digit
void multiply_digit(const int NUMBITS, unsigned char a[], unsigned char d, unsigned char result[]) {
  unsigned int fullprod;
  unsigned char carry = 0;
  int k;
  for (k=0;k<NUMBITS;++k) {
    fullprod = (a[k] * d) + carry;
    result[k] = fullprod;
    carry = (fullprod - result[k]) / 256;
  }
}
void multiply(const int NUMBITS, unsigned char a[], unsigned char b[], unsigned char result[]) {
  unsigned char temp[NUMBITS];
  int k;

  zero(NUMBITS, result);
  for (k=0;k<NUMBITS;++k) {
    multiply_digit(NUMBITS, a, b[k], temp);
    shiftbigger(NUMBITS, temp, k);
    add(NUMBITS, temp, result, result);
  }
}

void disp(const int NUMBITS, unsigned char a[]) {int k;for(k=NUMBITS-1;k>=0;--k) {printf("%x",a[k]);}printf("\n");}

void benchmark(const int NUMBITS, int N) {
  unsigned char a[NUMBITS];
  unsigned char b[NUMBITS];
  unsigned char c[NUMBITS];
  int k;
  clock_t start, finish;
  start = clock();
  for (k=0; k < N; ++k) {
    multiply(NUMBITS, a, b, c);
  }
  finish = clock();
  printf("Multiplies per second: %f\n", (double)(N*CLOCKS_PER_SEC)/(finish-start));
}

void main() {
  benchmark(256, 1000);
  unsigned char a[KEYSIZE]; zero(KEYSIZE, a); a[0] = 2; a[1] = 12;
  unsigned char b[KEYSIZE]; zero(KEYSIZE, b); b[0] = 40; b[1] = 3;
  unsigned char c[KEYSIZE]; multiply(KEYSIZE, a, b, c);
  disp(KEYSIZE, c);
}