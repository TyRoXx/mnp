rm atoi 2>/dev/null
clang atoi.c -oatoi -O3 -Wall -pedantic && time ./atoi
