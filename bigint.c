#include "stdio.h"
const int KEYSIZE = 256; // number of unsigned chars in key

void zero(unsigned char a[KEYSIZE]) {int k;for(k=0;k<KEYSIZE;++k)a[k]=0;}

void add(unsigned char a[KEYSIZE], unsigned char b[KEYSIZE], unsigned char result[KEYSIZE]) {
  unsigned int fullsum;
  unsigned char sum;
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
  }
}
void shiftsmaller(unsigned char a[KEYSIZE], int n) {
  
}

void multiply(unsigned char a[KEYSIZE], unsigned char b[KEYSIZE], unsigned char result[KEYSIZE]) {

}

void main() {
  unsigned char a[KEYSIZE]; zero(a); a[0] = 243;
  unsigned char b[KEYSIZE]; zero(b); b[0] = 123;
  unsigned char c[KEYSIZE]; add(a, b, c);


  printf("c[0]=%u, c[1]=%u, c[2]=%u", c[0], c[1], c[2]);
}