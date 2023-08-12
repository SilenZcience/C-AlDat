
// we are using prinf & scanf, therefor stdio.h must be included
#include <stdio.h>

// we return an error code [0,1,2] within the method, therefor return type must be 'int'
int main(void) {
  int n=0;
  printf("Bitte Anzahl eingeben: ");
  // scanf needs an address as a parameter, not an integer
  if(scanf("%d", &n) == 0){
    printf("Fehler!\n");
    return 1;
  }
  printf("\n");
 
  int input[n];
  for(int i=0; i < n; ++i) {
    printf("Zahl %d: ", i+1);
    if(scanf("%d", &input[i]) == 0) {
      printf("Fehler!\n");
      return 2;
    }
    printf("\n");
  }

  // when declaring a variable we need to define a data type, in this case 'int', because input[0] is 'int'
  int m_sum = input[0];
  for(int i=0; i < n; ++i) {
    int sum = 0;
    // a loop is using ';', not ',' to split start, end and step
    for(int j=0; i+j < n; ++j) {
      sum += input[i+j];
    }
    if(sum > m_sum) {
      m_sum = sum;
    }
  }

  printf("Ergebnis: %d\n", m_sum);

  return 0;
}
