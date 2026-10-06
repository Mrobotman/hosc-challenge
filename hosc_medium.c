// hosc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ALLOCS 16

void *chunks[MAX_ALLOCS] = {0};
size_t sizes[MAX_ALLOCS] = {0};

void menu() {
    printf("1) malloc\n2) free\n3) edit\n4) show\n5) quit\n> ");
}

int read_int() {
    char buf[16];
    read(0, buf, 15);
    return atoi(buf);
}

void do_malloc() {
    printf("idx: "); int idx = read_int();
    printf("size: "); size_t size = read_int();
    if (idx < 0 || idx >= MAX_ALLOCS || size == 0 || size > 0x400) return;
    chunks[idx] = malloc(size);
    sizes[idx] = size;
    printf("allocated at idx %d\n", idx);
}

void do_free() {
    printf("idx: "); int idx = read_int();
    if (idx < 0 || idx >= MAX_ALLOCS) return;
    free(chunks[idx]);
    
}

void do_edit() {
    printf("idx: "); int idx = read_int();
    if (idx < 0 || idx >= MAX_ALLOCS || !chunks[idx]) return;
    printf("data: ");
    read(0, chunks[idx], sizes[idx]); // meun ngen binde  même après free -> UAF write
}

void do_show() {
    printf("idx: "); int idx = read_int();
    if (idx < 0 || idx >= MAX_ALLOCS || !chunks[idx]) return;
    printf("data: ");
    puts(chunks[idx]); 
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    int choice;
    while (1) {
        menu();
        choice = read_int();
        switch (choice) {
            case 1: do_malloc(); break;
            case 2: do_free(); break;
            case 3: do_edit(); break;
            case 4: do_show(); break;
            case 5: exit(0);
            default: printf("invalid\n");
        }
    }
    return 0;
}
