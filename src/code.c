#include<stdlib.h>
#include<stdio.h>

#include "code.h"
#include "paragraph.h"
#include "globals.h"
#include "text.h"
#include "codelist.h"

Code* code_from_offsets(long start_offset, long end_offset) {
    Code *code = malloc(sizeof(Code));
    code->value = malloc(end_offset - start_offset + 1);
    code->next = NULL;
    code->first_paragraph = NULL;
    int i = 0;
    int ch;
    fseek(file, start_offset, SEEK_SET);
    while ((ch = fgetc(file)) != ']') {
        code->value[i] = (char)ch;
        i++;
    }
    printf("New code value : %s\n", code->value);
    return code;
}

void code_free(Code* code) {
    if (code->next) {
        code_free(code->next);
    }
    Paragraph *paragraph = code->first_paragraph;
    Paragraph *last_paragraph;
    while (paragraph) {
        last_paragraph = paragraph;
        paragraph = paragraph->next;
        free(last_paragraph);
    }
    free(code->value);
    free(code);
}

void code_copy_paragraph_and_push(Code *code, Paragraph *paragraph) {
    Paragraph *new_paragraph = malloc(sizeof(Paragraph));
    new_paragraph->start = paragraph->start;
    new_paragraph->next = code->first_paragraph;
    code->first_paragraph = new_paragraph;
}

void code_get_paragraphs(Code *code, Text *text) {
    Paragraph *paragraph = text->first_paragraph;
    while (paragraph) {
        printf("code_get_paragraphs paragraph : %p\n", paragraph);
        CodeList *codes_in_paragraph = paragraph_get_codes(paragraph);
        if (codes_in_paragraph->first_code) {
            printf("We have a code in paragraph\n");
        }
        if (codelist_is_in(codes_in_paragraph, code)) {
            printf("code_get_paragraphs add paragraph\n");
            code_copy_paragraph_and_push(code, paragraph);
        };
        paragraph = paragraph->next;
    }
}

