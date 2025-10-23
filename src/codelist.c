#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "codelist.h"
#include "paragraph.h"
#include "code.h"
#include "text.h"

CodeList* codelist_new() {
    CodeList *codelist = malloc(sizeof(CodeList));
    codelist->first_code = NULL;
    return codelist;
}

Code* codelist_pop(CodeList *codelist) {
    if (codelist->first_code == NULL) return NULL;
    Code *code = codelist->first_code;
    codelist->first_code = code->next;
    code->next = NULL;
    return code;
}

void codelist_dump(CodeList *codelist) {
    printf("Codelist : %p\n", codelist);
    Code *code = codelist->first_code;
    while (code) {
        printf("Code %p : %s\n", code, code->value);
        Paragraph *paragraph = code->first_paragraph;
        while (paragraph) {
            paragraph_print(paragraph);
            paragraph = paragraph->next;
        }
        printf("\n\n\n");
        code = code->next;
    }
}


void codelist_push(CodeList *codelist, Code *code) {
    code->next = codelist->first_code;
    codelist->first_code = code;
}

CodeList* codelist_reverse(CodeList *codelist) {
    CodeList *codelist_out = codelist_new();
    while (codelist->first_code) {
        codelist_push(codelist_out, codelist_pop(codelist));
    }
    return codelist_out;
}

void codelist_fprintf(CodeList *codelist, char* output_file) {
    FILE *f = fopen(output_file, "wb");
    CodeList *codelist_reversed = codelist_reverse(codelist);
    Code *code = codelist_reversed->first_code;
    while (code) {
        fprintf(f, "Code : %s\n", code->value);
        Paragraph *paragraph = code->first_paragraph;
        while (paragraph) {
            paragraph_fprintf(paragraph, f);
            paragraph = paragraph->next;
        }
        fputs("\n\n\n", f);
        code = code->next;
    }
    fclose(f);

}

int codelist_is_in(CodeList *codelist, Code *code) {
    Code *test_code = codelist->first_code;
    while (test_code) {
        if (strcmp(test_code->value, code->value) == 0) {
            return 1;
        }
        test_code = test_code->next;
    }
    return 0;
}

void codelist_append_unique(CodeList *codelist, Code *code) {
    if (codelist_is_in(codelist, code) == 0) {
        codelist_push(codelist, code);
    } else {
        free(code);
    }
}

CodeList* codelist_merge_and_free(CodeList* chief_codelist, CodeList* slave_codelist) {
    Code *code;
    while (slave_codelist->first_code) {
        code = codelist_pop(slave_codelist);
        codelist_append_unique(chief_codelist, code);
    }
    free(slave_codelist);
    return chief_codelist;

}

void codelist_get_paragraphs(CodeList *codelist, Text *text) {
    printf("codelist_get_paragraphs"); Code *code = codelist->first_code;
    while (code) {
        printf("codelist get paragraphs for code : %s\n", code->value);
        code_get_paragraphs(code, text);
        code = code->next;
    }
}
void codelist_free(CodeList *codelist) {
    Code *code = codelist->first_code;
    Code *code_to_free;
    while (code) {
        code_to_free = code;
        code = code->next;
        code_free(code_to_free);
    }
}

