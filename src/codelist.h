#ifndef CODELIST_H
#define CODELIST_H

typedef struct Code Code;
typedef struct Text Text;

typedef struct CodeList {
    Code *first_code;
} CodeList;


CodeList* codelist_new();
Code* codelist_pop(CodeList *codelist);
void codelist_dump(CodeList *codelist);
void codelist_push(CodeList *codelist, Code *code);
CodeList* codelist_reverse(CodeList *codelist);
void codelist_fprintf(CodeList *codelist, char* output_file);
int codelist_is_in(CodeList *codelist, Code *code);
void codelist_append_unique(CodeList *codelist, Code *code);
CodeList* codelist_merge_and_free(CodeList* chief_codelist, CodeList* slave_codelist);
void codelist_get_paragraphs(CodeList *codelist, Text *text);
void codelist_free(CodeList *codelist);

#endif
