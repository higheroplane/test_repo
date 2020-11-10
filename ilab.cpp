
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <cstring>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>

const int canary = 17;

const int N = 100;

int id (int x, int y)
{
    return 10*x + y;
}

void assert_my_canaries (void * array, int num, int size)
{
    int c1 = *(((int*) array) - 1);
    int c2 = *((int*) ((char*)array + N * size));

    assert (c1 == canary && c2 == canary);
}

int plus_one (int a)
{
    return a + 2;
}

void f_plus_one (void* in, void* out)
{
    *((int*) out) = *((int*) in) + 2;
}

int map (void * array, int num, int size, void (*f) (void *, void*))
{
    assert (array);
    assert (f);
    assert (array != f);

    void * new_elem = calloc (1, size);

    assert (new_elem);

    for (int i = 0; i < num; i ++)
    {
        void * current_elem = (char*) array + i * size;
        f (current_elem, new_elem);
        if (!memcpy (current_elem, new_elem, size)) return 1;
    }

    free (new_elem);

    return 0;
}

// char -> wchar_t
// wprint wscanf fwscanf iswalpha ctype.h
 // f( . , . ) -> f (a, . )
 // f: a -> a
 // [a] -> [f(a)]

 //

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

void print_code (const char letter)
{
    wprintf (L"Binary code for [%c] is ["BYTE_TO_BINARY_PATTERN"]\n", letter, BYTE_TO_BINARY(letter));
}

void print_code (const wchar_t letter)
{
    wprintf (L"Binary code код [%lc] is ["BYTE_TO_BINARY_PATTERN""BYTE_TO_BINARY_PATTERN""BYTE_TO_BINARY_PATTERN""BYTE_TO_BINARY_PATTERN"] \n",
     letter, BYTE_TO_BINARY(letter>>24), BYTE_TO_BINARY(letter>>16), BYTE_TO_BINARY(letter>>8), BYTE_TO_BINARY(letter));
}

bool is_letter (char c)
{
    return c >= 'A' && c <= 'z'; // so bad
}

int main ()
{
    //sudo update-locale LANG=en_US.UTF-8 LANGUAGE=en.UTF

    setlocale(LC_ALL, "");

    FILE* text = fopen ("utf.txt", "rb");

    wchar_t letter = L'ы';

    print_code (letter);

    char cp_letter = 0;

    wprintf (L"%d\n", fscanf (text, "%c", &cp_letter));
    
    print_code (cp_letter);

    fclose (text);

    //print_code (letter);

    return 0;
}

// 01111111
// 110

// (hello, world) -> 111110helloworld


