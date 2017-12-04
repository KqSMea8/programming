#include <string.h>
#include <stdio.h>

void *Memmove(void *dest, const void *src, size_t n) {
  char *p = (char *)dest;
  const char *q = (const char *)src;
  int i;

  if (dest == NULL || src == NULL) {
    return NULL;
  }

  if (dest < src) { // from head 
    for (i = 0; i < n; i++) {
      *p++ = *q++;
      //p++;
      //q++;
    }
  } else if (dest > src) { //from rear 
    for (i = n-1; i >= 0; i--) {
      *(p+i) = *(q+i);
    }
  }

  return dest;
}

int main() {
  int a[] = {1,2,3};
  int i;

  Memmove(a+1, a,sizeof(int) *2);
  for (i = 0; i < 3; i++)
    printf("%d\n", a[i]);
  return 0;
}
