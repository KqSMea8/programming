#include <iostream>

using namespace std;

int func_simple(int array[], int n) {
  int min = array[0];
  for (int i = 1; i < n; i++) {
    if (min > array[i]) {
      return i;
    }
  }
  return 0;
}

int func(int array[], int n) {
  int *p = array;
  int *q = p + (n-1);
  int *middle = NULL;

  while (q != p) {
    middle = p + (q - p) / 2;
    if (*middle <= *q) {
      q = middle;
    } else {
      p = middle + 1;
    }
  }
  return p - array;
    
}

int main() {
  int test[] = {5,1,2, 3, 4};
  int index = func(test, sizeof(test) / sizeof(test[0]));
  cout << test[index] << endl;
  return 0;
}
