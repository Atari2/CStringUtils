/**
 * @brief @file stringutils.h
 * @author Alessio Rosiello
 * @date 30/10/2020
 * @brief Various utility functions for c-strings
 */

#ifndef UTILS_STRINGUTILS_H
#define UTILS_STRINGUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>

/**
 * @brief All the errors defined in this library
 */
typedef enum StringUtilsErrors {
    NullPtrError = 0,
    EmptySeparator = 1,
    InvalidSubstringIndex = 2,
    SignalHandlerError = 3
} StringUtilsErrors;


/**
 * @brief The types of tracing available in this library
 * <br> NoTrace is completely silent execution
 * <br> Warn warns on errors (if custom error handler is present, it kills the program otherwise)
 */
typedef enum StringUtilsTraceLvl {
    NoTrace = 0,
    Warn = 1
} StringUtilsTraceLvl;

/**
 * This is the internal structure that holds all references to any string that gets allocated within this library.
 * By default it starts out with max_size of 1000, you can override this by calling user_init() at the start of the program.
 * It will auto expand as needed, doubling its size every time to avoid O(n) spent allocating when limit is reached.
 * @param strings: the list of refs to all the allocated strings
 * @param contains: the current number of refs contained
 * @param max_size: the current max_size that the struct will hold
 * @see user_init()
 */
typedef struct alloced_strings {
    char** strings;
    unsigned long long contains;
    unsigned long long max_size;
} alloced_strings;

/**
 * This is the internal structure that holds all references to any list of strings that gets allocated within this library
 * Be aware that any of the refs of each string in each list is held within alloced_strings.
 * So if you manually free anything from here, you don't have to free each string ref because those will get cleaned up by free_all_stringutil_structuress().
 * By default it starts out with max_size of 500, you can override this by calling user_init() at the start of the program
 * It will auto expand as needed, doubling its size every time to avoid O(n) spent allocating when limit is reached.
 * @param vectors: the list of refs to all the allocated lists of strings
 * @param contains: the current number of refs contained
 * @param max_size: the current max_size that the struct will hold
 * @see free_all_stringutils_structures()
 * @see user_init()
 */
typedef struct alloced_vects {
    char*** vectors;
    unsigned long long contains;
    unsigned long long max_size;
} alloced_vects;

// string utility functions
/**
 * @brief Returns a copy of original string with all whitespace characters removed from both ends of given string.
 * <br> Whitespace includes: space, carriage return, newline and tabs
 * <br> trim("  my beatiful string   ") -> "my beatiful string"
 * @param original (string to be trimmed)
 * @return trimmed (new trimmed string)
 */
char* trim(char* string);

/**
 * @brief Returns a copy of original string with specified character removed from both ends of given string.
 * <br> trimchar("xxxmy beatiful stringxxx", 'x') -> "my beatiful string"
 * @param original (string to be trimmed)
 * @param c (character to remove)
 * @return trimmed (new trimmed string)
 */
char* trimchar(char* string, char c);

/**
 * @brief Returns a copy of original string with specified characters removed from both ends of given string.
 * <br> trimnchar("xyzmy beatiful stringzyy", "xyz") -> "my beatiful string"
 * @param original (string to be trimmed)
 * @param params (string contaning all the characters to be removed)
 * @return trimmed (new trimmed string)
 */
char* trimnchar(char* string, char* params);

/**
 * @brief Returns a copy of original string with the specified string removed from both ends of given string.
 * <br> trimstr("hellohellomy beatiful stringhello", "hello") -> "my beatiful string"
 * @param original (string to be trimmed)
 * @param needle (string to trim from original)
 * @return trimmed (new trimmed string)
 */
char* trimstr(char* string, char* needle);

/**
 * @brief Returns a copy of original string with all whitespace characters removed from the end of given string.
 * <br> Whitespace includes: space, carriage return, newline and tabs
 * <br> trimend("  my beatiful string   ") -> "   my beatiful string"
 * @param original (string to be trimmed)
 * @return trimmed (new trimmed string)
 */
char* trimend(char* string);

/**
 * @brief Returns a copy of original string with specified character removed from the end of given string.
 * <br> trimendchar("xxxmy beatiful stringxxx", 'x') -> "xxxmy beatiful string"
 * @param original (string to be trimmed)
 * @param c (character to remove)
 * @return trimmed (new trimmed string)
 */
char* trimendchar(char* string, char c);

/**
 * @brief Returns a copy of original string with specified characters removed from the end of given string.
 * <br> trimendnchar("xyzmy beatiful stringzyy", "xyz") -> "xyzmy beatiful string"
 * @param original (string to be trimmed)
 * @param params (string contaning all the characters to be removed)
 * @return trimmed (new trimmed string)
 */
char* trimendnchar(char* string, char* params);

/**
 * @brief Returns a copy of original string with the specified string removed from the end of given string.
 * <br> trimendstr("hellohellomy beatiful stringhello", "hello") -> "hellohellomy beatiful string"
 * @param original (string to be trimmed)
 * @param needle (string to trim from original)
 * @return trimmed (new trimmed string)
 */
char* trimendstr(char* string, char* needle);

/**
 * @brief Returns a copy of original string with all whitespace characters removed from the start of given string.
 * <br> Whitespace includes: space, carriage return, newline and tabs
 * <br> trimstart("  my beatiful string   ") -> "my beatiful string   "
 * @param original (string to be trimmed)
 * @return trimmed (new trimmed string)
 */
char* trimstart(char* string);

/**
 * @brief Returns a copy of original string with specified character removed from the start of given string.
 * <br> trimstartchar("xxxmy beatiful stringxxx", 'x') -> "my beatiful stringxxx"
 * @param original (string to be trimmed)
 * @param c (character to remove)
 * @return trimmed (new trimmed string)
 */
char* trimstartchar(char* string, char c);

/**
 * @brief Returns a copy of original string with specified characters removed from the start of given string.
 * <br> trimstartnchar("xyzmy beatiful stringzyy", "xyz") -> "my beatiful stringzyy"
 * @param original (string to be trimmed)
 * @param params (string contaning all the characters to be removed)
 * @return trimmed (new trimmed string)
 */
char* trimstartnchar(char* string, char* params);

/**
 * @brief Returns a copy of original string with the specified string removed from the start of given string.
 * <br> trimstartstr("hellohellomy beatiful stringhello", "hello") -> "my beatiful stringhello"
 * @param original (string to be trimmed)
 * @param needle (string to trim from original)
 * @return trimmed (new trimmed string)
 */
char* trimstartstr(char* string, char* needle);

/**
 * @brief Returns a copy of the first n characters of original string
 * <br> strncopy("hello world!", 4) -> "hello"
 * @param orig (string to copy)
 * @param n (number of characters to copy)
 * @return string
 */
char* strncopy(char* orig, long long n);

/**
 * @brief Returns a copy of given string
 * <br> strcopy("hello world!") -> "hello world!"
 * @param orig (string to copy)
 * @return string
 */
char* strcopy(char* orig);

/**
 * @brief Returns number of times the needle is found in given string
 * <br> count("hello how are you, hello", "hello") -> 2
 * @param haystack (string to search in)
 * @param needle (string to be found)
 * @return n of times needle is found in haystack
 */
int count(char* haystack, char* needle);

/**
 * @brief Returns number of times the given character is found in given string
 * <br> countc("hello how are you, hello", "h") -> 3
 * @param haystack (string to search in)
 * @param c (character to be found)
 * @return n of times character is found in haystack
 */
int countc(char* haystack, char c);

/**
 * @brief Returns number of times any of the given list of characters is found in given string
 * <br> countnc("hello how are you, hello", "he") -> 6
 * @param haystack (string to search in)
 * @param params (characters to be found)
 * @return n of times any one of the characters is found in haystack
 */
int countnc(char* haystack, char* params);

/**
 * @brief Returns a list of strings, generated by splitting the original string at any whitespace character
 * <br> Stores in (*size) the length of the list
 * <br> Whitespace includes: space, newline, carriage return, tab
 * <br> split("this is a string") -> ["this", "is", "a", "string"]
 * @param string (string to be split)
 * @param size (gets set by the function, returns length of list)
 * @return list of strings
 */
char** split(char* string, int* size);

/**
 * @brief Returns a list of strings, generated by splitting the original string at specified character
 * <br> Stores in (*size) the length of the list
 * <br> splitc("this,is,a,string", ",") -> ["this", "is", "a", "string"]
 * @param string (string to be split)
 * @param c (character to split at)
 * @param size (gets set by the function, returns length of list)
 * @return list of strings
 */
char** splitc(char* string, char c, int* size);

/**
 * @brief Returns a list of strings, generated by splitting the original string at any of the specified characters
 * <br> Stores in (*size) the length of the list
 * <br> splitnc("this,is*a?string", ",*?") -> ["this", "is", "a", "string"]
 * @param string (string to be split)
 * @param params (characters to split at)
 * @param size (gets set by the function, returns length of list)
 * @return list of strings
 */
char** splitnc(char* string, char* params, int* size);

/**
 * @brief Returns a list of strings, generated by splitting the original string at another string
 * <br> Stores in (*size) the length of the list
 * <br> splitstr("this[sep]is[sep]a[sep]string", "[sep]") -> ["this", "is", "a", "string"]
 * @param string (string to be split)
 * @param needle (string to split at)
 * @param size (gets set by the function, returns length of list)
 * @return list of strings
 */
char** splitstr(char* string, char* needle, int* size);

/**
 * @brief Checks if given string ends with another string
 * <br> endswith("this ends with another", "another") -> 1
 * @param haystack (string to check)
 * @param needle (string that haystack has to end with)
 * @return 1 if true, 0 if false
 */
int endswith(char* haystack, char* needle);

/**
 * @brief Checks if given string ends with specified character
 * <br> endswithc("this ends with a", 'a') -> 1
 * @param haystack (string to check)
 * @param needle (character that haystack has to end with)
 * @return 1 if true, 0 if false
 */
int endswithc(char* haystack, char needle);

/**
 * @brief Checks if given string starts with specified string
 * <br> startswith("this starts with", "this") -> 1
 * @param haystack (string to check)
 * @param needle (string that haystack has to start with)
 * @return 1 if true, 0 if false
 */
int startswith(char* haystack, char* needle);

/**
 * @brief Checks if given string starts with specified character
 * <br> startswithc("this starts with", 't') -> 1
 * @param haystack (string to check)
 * @param needle (character that haystack has to start with)
 * @return 1 if true, 0 if false
 */
int startswithc(char* haystack, char needle);

/**
 * @brief Checks if given string contains specified string
 * <br> contains("this string contains pebble, it does!", "pebble") -> 1
 * @param haystack (string to check)
 * @param needle (string to find)
 * @return 1 if true, 0 if false
 */
int contains(char* haystack, char* needle);

/**
 * @brief Checks if given string contains specified character
 * <br> containsc("this string contains p, it does!", 'p') -> 1
 * @param haystack (string to check)
 * @param needle (character to find)
 * @return 1 if true, 0 if false
 */
int containsc(char* haystack, char needle);

/**
 * @brief Checks if given string contains specified string, if so, returns first index of occurrence
 * <br> find("this string contains pebble, it does! (pebble again)", "pebble") -> 21
 * @param haystack (string to check)
 * @param needle (string to find)
 * @return first index of occurrence, else -1
 */
int find(char* haystack, char* needle);

/**
 * @brief Checks if given string contains specified character, if so, returns first index of occurrence
 * <br> findc("this string contains p, it does! (p again)", 'p') -> 21
 * @param haystack (string to check)
 * @param needle (character to find)
 * @return first index of occurrence, else -1
 */
int findc(char* haystack, char needle);

/**
 * @brief Checks if given string contains specified character, if so, returns last index of occurrence
 * <br> rfind("this string contains pebble, it does! (pebble again)", "pebble") -> 39
 * @param haystack (string to check)
 * @param needle (string to find)
 * @return last index of occurrence, else -1
 */
int rfind(char* haystack, char* needle);

/**
 * @brief Checks if given string contains specified character, if so, returns last index of occurrence
 * <br> rfindc("this string contains p, it does! (p again)", 'p') -> 34
 * @param haystack (string to check)
 * @param needle (character to find)
 * @return last index of occurrence, else -1
 */
int rfindc(char* haystack, char needle);

/**
 * @brief Concatenates 2 strings together into a new string.
 * <br> sum("hello", "world") -> "helloworld"
 * @param first
 * @param second
 * @return both strings concatenated
 */
char* sum(char* first, char* second);

/**
 * @brief Returns a new string with all instances of a character in given string removed
 * <br> sub("hello", 'l') -> "heo"
 * @param haystack (original string)
 * @param needle (character to remove)
 * @return string without specified character
 */
char* sub(char* haystack, char needle);

/**
 * @brief Returns new string with original string concatenated with specified character
 * <br> append("hello world", '!') -> "hello world!"
 * @param first
 * @param second (character to add)
 * @return string with appended character
 */
char* append(char* first, char second);

/**
 * @brief Returns a new string with all characters to be uppercase
 * <br> toupperstr("make me big") -> "MAKE ME BIG"
 * @param string (to be capitalized)
 * @return string with all uppercase characters
 */
char* toupperstr(char* string);

/**
 * @brief Returns a new string with all characters to be lowercase
 * <br> tolowerstr("MAKE ME SMALL") -> "make me small"
 * @param string (to be lowercased)
 * @return string with all lowercase characters
 */
char* tolowerstr(char* string);

/**
 * @brief Returns a "zipped" string, basically removes all adjacent repeated whitespace to 1 occurrence
 * <br> Whitespace includes: space, newline, carriage return, tab
 * zip_string("    hello     world") -> " hello world"
 * @param string
 * @return zipped string
 */
char* zip_string(char* string);

/**
 * @brief Replaces all occurrences of specified needle with specified rep in given original string, returns a new string, doesn't modify in-place.
 * <br> replace("hello,world,!", ",", "test") -> "hellotestworldtest!"
 * @param orig (string to search into)
 * @param needle (string to find)
 * @param rep (string to replace with)
 * @return string with all needles replaced with rep
 */
char* replace(char* orig, char* needle, char* rep);

/**
 * @brief Replaces all occurrences of specified needle with specified rep in given original string, returns a new string, doesn't modify in-place.
 * <br> replacec("hello*world*!", '*', ' ') -> "hello world !"
 * @param orig (string to search into)
 * @param needle (character to find)
 * @param rep (character to replace with)
 * @return string with all needles replaced with rep
 */
char* replacec(char* orig, char needle, char rep);

/**
 * @brief Returns a new string which is a substring of original, equivalent to [start:end] in Python.
 * If end is -1, it'll be equivalent to  [start:].
 * If start is -1, it'll be equivalent to [:end].
 * If both are -1, it'll return a copy of the original string.
 * <br> substr("hello world", 0, 4) -> "hello"
 * <br> substr("hello world", 4, -1) -> "o world"
 * @param orig (the string to grab the substring from)
 * @param start (starting index, -1 to be from start always)
 * @param end (ending index, -1 to go to end always)
 * @return substring of given range
 */
char* substr(char* orig, int start, int end);

// allocation utility functions
/**
 * @brief Allocates a generic void** pointer of size*count bytes. Size and count are given by the user.
 * <br>void** ptr = safe_alloc_generic(10, 2)
 * @warning <b>THIS DOES NOT GET FREED by free_all_stringutils_structures(), it's up to the caller to free this memory</b>
 * @param size
 * @param count
 * @return an allocated void** pointer of given size and count
 * @see free_all_stringutils_structures()
 */
void** safe_alloc_generic(size_t size, size_t count);

/**
 * @brief Allocates a generic char* pointer of given size (size DOESN'T NEED to account for string terminator)
 * <br> This DOES get freed by free_all_stringutils_structures(), so you don't need to manually free this memory if you call it
 * <br> char* str = alloc_safe_str(strlen("this is a test"))
 * @see free_all_stringutils_structures()
 * @param size
 * @return allocated char* pointer
 */
char* alloc_safe_str(size_t size);

// library functions
/**
 * @brief This functions frees each and every string/every list of strings allocated by any function of this header.
 * <br> This is to facilitate memory management, since you just need to call this function at the end of whatever you want.
 * <br> Please do note that if this was compiled with GCC this function will be called automatically at program exit if possible.
 * <br> So make sure to know what you're doing if you call this manually!
 */
void free_all_stringutils_structures();

/**
 * @brief Exposes internal list of all currently allocated strings. Use with caution, as this has no guarantees.
 * <br> If you free any string from this, make sure to also modify the .contains parameter.
 * @return pointer to internal struct of strings
 */
alloced_strings* expose_internal_strings();

/**
 * @brief Exposes internal list of all currently allocated lists of strings. Use with caution, as this has no guarantees.
 * <br> If you free any list from this, make sure to also modify the .contains parameter.
 * Also, also make sure to free the strings of said list from the internal strings first.
 * @return pointer to internal struct of list of strings
 */
alloced_vects* expose_internal_vectors();

/**
 * @brief This is a function that (if needed) <b>has</b> to be called at the start of the program execution (or before any function of this library gets called).
 * The purpose of this function is to override the default starting sizes of the structs that hold the refs.
 * <br> user_init(200, 10) -> will set size of alloced_strings to 200 and of alloced_vects to 10
 * @see alloced_strings
 * @see alloced_vects
 * @param max_strings (the new starting size for the string struct, default is 1000)
 * @param max_vectors (the new starting size for the vects struct, default is 500)
 */
void user_init(long long max_strings, long long max_vectors);

/**
 * @brief This function's only purpose is to receive another function to handle any exceptions thrown by this library.
 * <br> Defined exceptions can be found in StringUtilsErrors
 * <br> func's prototype should be a void return with a single int argument
 * <br> In POSIX systems, exceptions triggered by this library will be SIGUSR1, on Windows however, it'll trigger SIGTERM, so be aware.
 * <br> If the trace level is on Warn, it'll also print some information, otherwise it'll be silent and just raise.
 * <br> The trace level can be set with set_trace_lvl_stringutils()
 * @param func (the function to call)
 * @see StringUtilsErrors
 * @see StringUtilsTraceLvl
 * @see set_trace_lvl_stringutils()
 */
void override_signal_exception_stringutils(void (*func)(int));

/**
 * @brief This function must be called in order to modify the trace level of the library.
 * <br> By default it's set to NoTrace
 * @param trace_lvl (trace level to set, valid values are only NoTrace or Warn)
 * @see StringUtilsTraceLvl
 */
void set_trace_lvl_stringutils(StringUtilsTraceLvl trace_lvl);

/**
 * @brief This function translates a StringUtilsErrors code into the appropriate message.
 * @param err (StringUtilsErrors values)
 * @return string (message)
 * @see StringUtilsErrors
 */
char* errcodetostr_stringutils(StringUtilsErrors err);
#endif //UTILS_STRINGUTILS_H
