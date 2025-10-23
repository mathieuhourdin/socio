#ifndef CODE_H
#define CODE_H

typedef struct Paragraph Paragraph;

typedef struct Text Text;

typedef struct Code {
    char* value;
    struct Code* next;
    Paragraph* first_paragraph;
} Code;

Code* code_from_offsets(long start_offset, long end_offset);

void code_free(Code* code);

void code_copy_paragraph_and_push(Code *code, Paragraph *paragraph);

void code_get_paragraphs(Code *code, Text *text);
#endif
