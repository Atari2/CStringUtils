## CStringUtils

A simple library for string manipulation in C.

* Documentation can be found at this webpage http://www.atarismwc.com/stringutils/
* A navigable PDF can also be downloaded from : http://www.atarismwc.com/cstringutilsdoc.pdf

Example usage:
```c
#include "stringutils.h"

void custom_handler(int err) {
    printf("Basically this just ignore thrown exceptions\n");
    return;
}

int main() {
    set_trace_lvl(Warn);                            // We set the trace level
    override_signal_exception(custom_handler);      // Let's add a custom error handler, why not
    user_init(10, 5);                               // Let's also reduce the memory footprint (not required)
    char* orig  = "testneedletest";
    char* c = trimstr(orig, "test");                // Trim, sum and append
    c = sum(c, orig);
    c = append(c, 'k');
    printf("%s\n%s\n%d\n%d\n", orig, c, rfind(orig, "test"), find(c, "needle"));
    char* a = "\t\t\t\t                               hello world";     
    char* b = trim(a);                              // Some more trim and split.
    int n = 0;
    char** d = splitstr("hello world", " ", &n);
    printf("%s\n", b);
    for (int i = 0; i < n; i++) {
        printf("%s\n", d[i]);
    }
    return 0;                                       // We gracefully exit without worrying about memory leaks.
}
```
Valgrind output of this little program:
```
valgrind --leak-check=full --show-leak-kinds=all ./a.out
==44== Memcheck, a memory error detector
==44== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==44== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==44== Command: ./a.out
==44==
testneedletest
needletestneedletestk
10
0
hello world
hello
world
==44==
==44== HEAP SUMMARY:
==44==     in use at exit: 0 bytes in 0 blocks
==44==   total heap usage: 14 allocs, 14 frees, 1,390 bytes allocated
==44==
==44== All heap blocks were freed -- no leaks are possible
==44==
==44== For lists of detected and suppressed errors, rerun with: -s
==44== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
Compilation with GCC is highly recommended.