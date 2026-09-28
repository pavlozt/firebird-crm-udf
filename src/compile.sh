#http://www.firebirdsql.org/en/writing-udfs-for-interbase/#writing_udfs_for_linux_unix_platforms
gcc -c -O -fpic  ibu.c
ld -G ibu.o -lm -lc -lib_util -o ibu.so
echo compiled. then copy it :
echo  cp ibu.so  /usr/lib/firebird/2.5/UDF
