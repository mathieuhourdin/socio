#include <stdlib.h>

#include "text.h"
#include "paragraph.h"
#include "codelist.h"

Text* text_build() {
    Text *text = malloc(sizeof(Text));
    Paragraph *paragraph = paragraph_from_start(0);
    text->first_paragraph = paragraph;
    long next_paragraph_start = paragraph_get_next_line_start(paragraph);
    Paragraph *old_paragraph = paragraph;
    while (next_paragraph_start) {
        Paragraph *new_paragraph = paragraph_from_start(next_paragraph_start);
        old_paragraph->next = new_paragraph;
        old_paragraph = new_paragraph;
        next_paragraph_start = paragraph_get_next_line_start(old_paragraph);
    }
    return text;
}

CodeList* text_get_codes(Text *text) {
    Paragraph *paragraph = text->first_paragraph;
    CodeList *codelist = codelist_new();
    while (paragraph) {
        CodeList *found_codes = paragraph_get_codes(paragraph);
        printf("master_codelist : %p, slave_codelist : %p\n", codelist, found_codes);
        codelist = codelist_merge_and_free(codelist, found_codes);
        paragraph = paragraph->next;
    }
    return codelist;
}

void text_dump(Text* text) {
    Paragraph *paragraph = text->first_paragraph;
    while (paragraph) {
        printf("Paragraph positions : %ld\n", paragraph->start);
        paragraph = paragraph->next;
    }
}

void text_print_codes(Text* text) {
    printf("Start print codes\n");
    Paragraph *paragraph = text->first_paragraph;
    while (paragraph) {
        printf("New paragraph with start : %ld\n", paragraph->start); 
        paragraph_print_codes(paragraph);
        paragraph = paragraph->next;
    }
}

void text_free(Text* text) {
    Paragraph *paragraph = text->first_paragraph;
    Paragraph *paragraph_to_free;
    while (paragraph) {
        paragraph_to_free = paragraph;
        paragraph = paragraph->next;
        free(paragraph_to_free);
    }
}
        


