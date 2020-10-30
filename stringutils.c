#include "stringutils.h"

typedef enum Errors {
    NullPtrError = 0,
    EmptySeparator = 1
} Errors;

#define MAX_STRINGS 1000
#define MAX_VECT 500
#define str char*
#define vstr char**
#define uint unsigned int
#define ulint unsigned long int
#define ll long long
#define p(name) (*name)
#define tp(type, name) type *name

alloced_strings structs = { NULL, 0, MAX_STRINGS};
alloced_vects vstructs = { NULL, 0, MAX_VECT};

str trim(str string) {
    return trimnchar(string, "\t\r\n ");
}
str trimchar(str string, char c) {
    return trimendchar(trimstartchar(string, c), c);
}
str trimnchar(str string, str params) {
    return trimendnchar(trimstartnchar(string, params), params);
}
str trimstr(str string, str needle) {
    return trimendstr(trimstartstr(string, needle), needle);
}
str trimend(str string) {
    return trimendnchar(string, "\t\r\n ");
}
str trimendchar(str string, char c) {
    str ptr = strcopy(string);
    uint n = strlen(string) - 1;
    while (ptr[n] == c && n > 0) {
        ptr[n] = '\0';
        n--;
    }
    return ptr;
}
str trimendnchar(str string, str params) {
    str ptr = strcopy(string);
    uint n = strlen(ptr) - 1;
    for (uint i = n; i > 0; i--) {
        int found = 0;
        for (int j = 0; j < strlen(params); j++) {
            if (ptr[i] == params[j]) {
                ptr = trimendchar(ptr, params[j]);
                found = 1;
                i = strlen(ptr);
            }
        }
        if (!found)
            break;
    }
    return ptr;
}
str trimendstr(str string, str needle) {
    str ptr = strcopy(string);
    uint n = strlen(needle);
    uint end = strlen(ptr);
    if (n > end)
        return ptr;
    while (strncmp(ptr+end-n, needle, n) == 0) {
        ptr[end-n] = '\0';
        end = strlen(ptr);
    }
    return ptr;
}
str trimstart(str string) {
    return trimstartnchar(string, "\t\r\n ");
}
str trimstartchar(str string, char c) {
    str ptr = strcopy(string);
    while ((*ptr) == c)
        ptr++;
    return ptr;
}
str trimstartnchar(str string, str params) {
    str ptr = strcopy(string);
    for (uint i = 0; i < strlen(ptr); i++) {
        int found = 0;
        for (int j = 0; j < strlen(params); j++) {
            if (ptr[i] == params[j]) {
                ptr = trimstartchar(ptr, params[j]);
                found = 1;
                j = 0;
            }
        }
        if (!found)
            break;
    }
    return ptr;
}
str trimstartstr(str string, str needle) {
    str ptr = strcopy(string);
    uint n = strlen(needle);
    if (n > strlen(string))
        return ptr;
    while(strncmp(ptr, needle, n) == 0)
        ptr += n;
    return ptr;
}
str strncopy(str orig, ll n) {
    if (orig == NULL) {
        printf("NULL pointer was trying to be copied\n");
        exit(NullPtrError);
    }
    if (structs.contains == 0) {
        structs.strings = malloc(sizeof(vstr)*structs.max_size);
    } else if (structs.max_size == structs.contains) {
        structs.max_size *= 2;
        structs.strings = realloc(structs.strings, sizeof(vstr)*structs.max_size);
    }

    str ptr = malloc(n + 1);
    structs.strings[structs.contains] = ptr;
    structs.contains++;
    strncpy(ptr, orig, n+1);
    return ptr;
}
str strcopy(str orig) {
    if (orig == NULL) {
        printf("NULL pointer was trying to be copied\n");
        exit(NullPtrError);
    }
    return strncopy(orig, strlen(orig));
}

int endswith(str haystack, str needle) {
    if (haystack == NULL || needle == NULL)
        return 0;
    uint a = strlen(haystack);
    uint b = strlen(needle);
    if (b > a) return 0;
    return 0 == strncmp(haystack+a-b, needle, b);
}
int endswithc(str haystack, char needle) {
    if (haystack == NULL)
        return 0;
    uint a = strlen(haystack);
    return haystack[a-1] == needle;
}
int startswith(str haystack, str needle) {
    if (haystack == NULL || needle == NULL)
        return 0;
    uint a = strlen(haystack);
    uint b = strlen(needle);
    if (b > a) return 0;
    return 0 == strncmp(haystack, needle, b);
}
int startswithc(str haystack, char needle) {
    if (haystack == NULL)
        return 0;
    return haystack[0] == needle;
}
int find(str haystack, str needle) {
    if (strlen(needle) > strlen(haystack))
        return -1;
    if (strlen(needle) == strlen(haystack) && strcmp(haystack, needle) == 0)
        return 0;
    uint n = strlen(needle);
    for (int i = 0; i < strlen(haystack) - n; i++) {
        if (strncmp(haystack+i, needle, n) == 0)
            return i;
    }
    return -1;
}

int rfind(str haystack, str needle) {
    uint n = strlen(needle);
    uint a = strlen(haystack);
    if (n > a)
        return -1;
    if (n == a && strcmp(needle, haystack) == 0)
        return 0;
    for (int i = a-n; i > n; i--) {
        if (strncmp(haystack+i, needle, n) == 0)
            return i;
    }
    return -1;
}

int findc(str haystack, char needle) {
    for (int i = 0; i < strlen(haystack); i++)
        if (haystack[i] == needle)
            return i;
    return -1;
}

int findnc(str haystack, str params) {
    for (int i = 0; i < strlen(haystack); i++)
        for (int j = 0; j < strlen(params); j++)
            if (haystack[i] == params[j])
                return i;
    return -1;
}

int rfindc(str haystack, char needle) {
    for (int i = strlen(haystack) - 1; i >= 0; i--)
        if (haystack[i] == needle)
            return i;
    return -1;
}
int rfindnc(str haystack, str params) {
    for (int i = strlen(haystack) - 1; i >= 0; i--)
        for (int j = 0; j < strlen(params); j++)
            if (haystack[i] == params[j])
                return i;
    return -1;
}
int contains(str haystack, str needle) {
    return find(haystack, needle) != -1;
}
int containsc(str haystack, char needle) {
    return findc(haystack, needle) != -1;
}
str sum(str first, str second) {
    if (first == NULL || second == NULL) {
        printf("NULL pointer was trying to be added\n");
        exit(NullPtrError);
    }
    str ptr = malloc(strlen(first) + strlen(second) + 1);
    strncpy(ptr, first, strlen(first)+1);
    strcat(ptr, second);
    return ptr;
}

str sub(str haystack, char needle) {
    str ptr = strcopy(haystack);
    int i = 0;
    uint n = strlen(ptr);
    while (ptr[i] != '\0') {
        if (ptr[i] == needle) {
            memmove(ptr+i, ptr+i+1, n-i);
        } else { i++; }
    }
    return ptr;
}

str append(str first, char second) {
    if (first == NULL) {
        printf("NULL pointer was trying to be added\n");
        exit(NullPtrError);
    }
    str ptr = malloc(strlen(first)+2);
    strncpy(ptr, first, strlen(first)+1);
    uint n = strlen(ptr);
    ptr[n] = second;
    ptr[n+1] = '\0';
    return ptr;
}
int count(str haystack, str needle) {
    int n = 0;
    uint a = strlen(haystack);
    uint b = strlen(needle);
    if (b > a || (b == a && strcmp(haystack, needle) != 0))
        return 0;
    if (b == a && strcmp(haystack, needle) == 0)
        return 1;
    for (int i = 0; i <= a-b; i++) {
        if (strncmp(haystack+i, needle, b) == 0)
            n++;
    }
    return n;
}
int countnc(str haystack, str params) {
    int n = 0;
    for (int i = 0; i < strlen(params); i++)
        n += countc(haystack, params[i]);
    return n;
}
int countc(str haystack, char c) {
     int n = 0;
     for (int i = 0; i < strlen(haystack); i++)
         if (haystack[i] == c)
             n++;
     return n;
}
int countstr(str haystack , str needle) {
    int n = 0;
    uint a = strlen(haystack);
    uint b = strlen(needle);
    if (b > a)
        return 0;
    if (a == b)
        return strcmp(haystack, needle) == 0;
    for (int i = 0; i <= a-b; i++) {
        if (strncmp(haystack+i, needle, b) == 0)
            n++;
    }
    return n;
}

vstr alloc_vect(int size) {
    vstr ret = malloc(size);
    if (vstructs.contains == 0) {
        vstructs.vectors = malloc(sizeof(vstr*)*vstructs.max_size);
    } else if (vstructs.max_size == vstructs.contains) {
        vstructs.max_size *= 2;
        vstructs.vectors = realloc(vstructs.vectors, sizeof(vstr*)*vstructs.max_size);
    }
    vstructs.vectors[vstructs.contains] = ret;
    vstructs.contains++;
    return ret;
}

vstr split(str string, tp(int, size)) {
    int n = 0;
    vstr vect = splitnc(string, "\t\n\r ", size);
    for (int i = 0; i < p(size); i++) {
        if (strlen(vect[i]) != 0)
            n++;
    }
    vstr retv = alloc_vect(sizeof(str)*n);
    for (int i = 0, j = 0; i < p(size); i++) {
        if (strlen(vect[i]) != 0)
            retv[j++] = strcopy(vect[i]);
    }
    p(size) = n;
    return retv;
}
vstr splitc(str string, char c, tp(int, size)) {
    p(size) = countc(string, c)+1;
    if (p(size) == 0)
        return NULL;
    vstr vect = alloc_vect(sizeof(str)*(p(size)));
    int a = findc(string, c);
    vect[0] = strncopy(string, a);
    vect[0][a] = '\0';
    int b = a + findc(string+a+1, c);
    int i = 1;
    while (a != -1 && b != -1 && i < p(size)) {
        vect[i] = strncopy(string+a+1, b-a);
        vect[i][b-a] = '\0';
        i++;
        a = b+1;
        b = a + findc(string+a+1, c);
        if ((a-1) >= b) {
            vect[i] = strncopy(string + a + 1, strlen(string) - a);
            break;
        }
    }
    return vect;
}
vstr splitnc(str string, str params, tp(int, size)) {
    if (strlen(params) == 0) {
        printf("Split attempt with empty separator\n");
        exit(EmptySeparator);
    }
    int n = countnc(string, params) + 1;
    if (n == 0)
        return NULL;
    vstr vect = alloc_vect(sizeof(str)*n);
    int a = findnc(string, params);
    if (a == -1) {
        p(size) = n;
        vect[0] = strcopy(string);
        return vect;
    }
    vect[0] = strncopy(string, a);
    vect[0][a] = '\0';
    int b = a + findnc(string+a+1, params);
    int i = 1;
    while (a != -1 && b != -1 && i < n) {
        vect[i] = strncopy(string+a+1, b-a);
        vect[i][b-a] = '\0';
        i++;
        a = b+1;
        b = a + findnc(string+a+1, params);
        if ((a-1) >= b) {
            vect[i] = strncopy(string + a + 1, strlen(string) - a);
            break;
        }
    }
    p(size) = n;
    return vect;
}
vstr splitstr(str string, str needle, tp(int, size)) {
    if (strlen(needle) == 0) {
        printf("Split attempt with empty separator\n");
        exit(EmptySeparator);
    }
    int n = countstr(string, needle)+1;
    int l = strlen(needle);
    if (n == 1) {
        vstr vect = alloc_vect(sizeof(str)*n);
        vect[0] = calloc(1, 1);
        p(size) = n;
        return vect;
    }
    vstr vect = alloc_vect(sizeof(str)*n);
    int a = find(string, needle);
    vect[0] = strncopy(string, a);
    vect[0][a] = '\0';
    int b = a + find(string+a+l, needle);
    if (b == -1 && n == 2) {
        vect[1] = alloc_safe_str(1);
        vect[1][0] = '\0';
        p(size) = n;
        return vect;
    }
    int i = 1;
    while (a != -1 && b != -1 && i < n) {
        vect[i] = strncopy(string+a+l, b-a);
        vect[i][b-a] = '\0';
        i++;
        a = b+l;
        b = a + find(string+a+l, needle);
        if ((a-1) >= b) {
            vect[i] = strncopy(string + a + l, strlen(string) - a - l);
            break;
        }
    }
    p(size) = n;
    return vect;
}
str toupperstr(str string) {
    str ptr = strcopy(string);
    for (int i = 0; i < strlen(string); i++) {
        ptr[i] = toupper(ptr[i]);
    }
    return ptr;
}
str tolowerstr(str string) {
    str ptr = strcopy(string);
    for (int i = 0; i < strlen(string); i++) {
        ptr[i] = tolower(ptr[i]);
    }
    return ptr;
}
str zip_string(str string) {
    str ptr = strcopy(string);
    uint n = strlen(string);
    int i = 0;
    int prev = 0;
    while (ptr[i] != '\0') {
        if (prev)  { i++; prev = 0; continue; }
        if (ptr[i] != ' ' && ptr[i] != '\t' && ptr[i] != '\n' && ptr[i] != '\r') {
            prev = 1; i++;
        } else {
            memmove(ptr+i, ptr+i+1, n-i);
            n = strlen(ptr);
        }
    }
    return ptr;
}

str replace(str orig, str needle, str rep) {
    int n = count(orig, needle);
    int a = strlen(orig);
    int b = strlen(needle);
    int c = strlen(rep);
    ll len = a - n*b + n*c;
    str ptr = alloc_safe_str(len);
    int i, j = 0, k = 0;
    while (n > 0) {
        i = find(orig+j, needle) + j;
        strncpy(ptr+k, orig+j, i-j);
        ptr[k+i-j] = '\0';
        strcat(ptr+k+i-j, rep);
        k += (i-j) + c;
        j = i + b;
        n--;
    }
    strcat(ptr+k, orig+j);
    return ptr;
}

str replacec(str orig, char needle, char rep) {
    str ptr = strcopy(orig);
    for (int i = 0; i < strlen(ptr); i++) {
        if (ptr[i] == needle)
            ptr[i] = rep;
    }
    return ptr;
}

void** safe_alloc_generic(size_t size, size_t count) {
    void** ptr = calloc(size, count);
    if (ptr == NULL) {
        printf("Memory %lu bytes couldn't be alloc'd\n", (ulint)(size*count));
        exit(NullPtrError);
    }
    return ptr;
}

str alloc_safe_str(size_t size) {
    str ptr = malloc(size+1);
    if (ptr == NULL) {
        printf("Memory %lu bytes couldn't be alloc'd\n", (ulint)(size));
        exit(NullPtrError);
    }
    if (structs.contains == 0) {
        structs.strings = malloc(sizeof(vstr)*structs.max_size);
    } else if (structs.max_size == structs.contains) {
        structs.max_size *= 2;
        structs.strings = realloc(structs.strings, sizeof(vstr)*structs.max_size);
    }
    structs.strings[structs.contains] = ptr;
    structs.contains++;
    ptr[0] = '\0';
    return ptr;
}

alloced_strings* expose_internal_strings() {
    return &structs;
}

alloced_vects* expose_internal_vectors() {
    return &vstructs;
}

void free_all_structures() {
    for (ll i = 0; i < structs.contains; i++) {
        free(structs.strings[i]);
    }
    for (ll i = 0; i < vstructs.contains; i++) {
        free(vstructs.vectors[i]);
    }
    free(structs.strings);
    free(vstructs.vectors);
}

void user_init(ll max_strings, ll max_vect) {
    structs.max_size = max_strings;
    vstructs.max_size = max_vect;
}
#undef str 
#undef uint
#undef ulint
#undef vstr
#undef p
#undef tp
#undef ll
#undef MAX_STRINGS
#undef MAX_VECT