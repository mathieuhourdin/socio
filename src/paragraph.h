#ifndef PARAGRAPH_H
#define PARAGRAPH_H

#include<stdio.h>

typedef struct CodeList CodeList;

typedef struct Paragraph {
    long start;
    struct Paragraph* next;
} Paragraph;

Paragraph* paragraph_from_start(long start);

void paragraph_print(Paragraph *paragraph);

void paragraph_fprintf(Paragraph *paragraph, FILE *f);

CodeList* paragraph_get_codes(Paragraph* paragraph);

void paragraph_print_codes(Paragraph* paragraph);

long paragraph_get_next_line_start(Paragraph* paragraph);

void paragraph_free(Paragraph *paragraph);

#endif
