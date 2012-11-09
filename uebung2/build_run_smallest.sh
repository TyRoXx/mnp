rm sm 2>/dev/null
clang smallest.c -osm -O3 -Wall -pedantic && time ./sm
