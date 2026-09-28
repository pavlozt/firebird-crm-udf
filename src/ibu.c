
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ibase.h>
#include "example.h"
#include <ib_util.h>


/*
 * Installation how to :
 apt-get install firebird2.5-dev
 gcc -fPIC -c ibu.c -o ibu.o
 gcc -shared -oibu.so ibu.o
 put to /usr/lib/firebird/2.5/UDF
 /etc/init.d/firebird2.5-super restart


#http://www.firebirdsql.org/en/writing-udfs-for-interbase/#writing_udfs_for_linux_unix_platforms
gcc -c -O -fpic  ibu.c
ld -G ibu.o -lm -lc -lib_util -o ibu.so
echo compiled. then copy it :
echo  cp ibu.so  /usr/lib/firebird/2.5/UDF

*/

int EXPORT version();
double EXPORT mrand();
double EXPORT mult3(double *, double *, double *);
char* EXPORT substr(const char *, int *, int *);
char* EXPORT getphone(char *);
char* EXPORT upcase(const char *);
char* EXPORT upcase2(char* s);

int EXPORT version()
{
 return 2;
}

double EXPORT mrand()
{
return ((float) rand() / (float) RAND_MAX);
}

double EXPORT mult3(double *a, double *b, double *c)
{
return *a * *b * *c;
}


char* EXPORT substr(const char *s, int *m, int *n)
{
	if (!s) {
		return 0;
	}

	char* buf;
	long length = strlen(s);
	if (!length ||
		*m > *n ||
		*m < 1  ||
		*n < 1  ||
		*m > length)
	{
		buf = (char*)ib_util_malloc(1);
		buf[0] = '\0';
	}
	else
	{
		/* we want from the mth char to the
		   nth char inclusive, so add one to
		   the length. */
		/* CVC: We need to compensate for n if it's longer than s's length */
		if (*n > length) {
			length -= *m - 1;
		}
		else {
			length = *n - *m + 1;
		}
		buf = (char*)ib_util_malloc (length + 1);
		memcpy(buf, s + *m - 1, length);
		buf[length] = '\0';
	}
	return buf;
}

char* EXPORT getphone(char *s)
{
  if (!s)
    return 0;
     
  char* i = s;
  char* j = i;
  while (*j != '\0')
  {
    if (*j >= '0' && *j <= '9') {
      *i = *j;
      i++;
    }
    j++;
  }
  const long length = i - s;
  char* buf = (char *) ib_util_malloc(length + 1);
  memcpy(buf, s, length);
  buf[length] = '\0';
  return buf;
}

char* EXPORT upcase(const char *s)
{
  if (!s)
    return 0;
	
  char* buf = (char *) ib_util_malloc(strlen(s) + 1);
  char* p = buf;
  while (*s)
  {
    if (*s >= 'à' && *s <= 'ÿ') {
      *p++ = *s++ - 'à' + 'À';
    }
    else 
    if (*s >= 'a' && *s <= 'z') {
      *p++ = *s++ - 'a' + 'A';
    }
    else
    if (*s == '¸') {
      *p++ = *s++ - '¸' + '¨';
    }
    else
      *p++ = *s++;
  }
  *p = '\0';
  return buf;
}

char* EXPORT upcase2(char* s)
{
  if (!s)
    return s;
	
  char *p = s;
  while (*s)
  {
    if (*s >= 'à' && *s <= 'ÿ') {
      *s++ = *s - 'à' + 'À';
    }
    else 
    if (*s >= 'a' && *s <= 'z') {
      *s++ = *s - 'a' + 'A';
    }
    else
    if (*s == '¸') {
      *s++ = *s - '¸' + '¨';
    }
    else
      *s++;
  }
  return p;
}
