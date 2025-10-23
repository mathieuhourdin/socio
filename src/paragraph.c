#include<stdlib.h>
#include<stdio.h>
#include "globals.h"

#include "paragraph.h"
#include "globals.h"
#include "codelist.h"
#include "code.h"

Paragraph* paragraph_from_start(long start) {
    Paragraph *paragraph = malloc(sizeof(Paragraph));
    paragraph->start = start;
    paragraph->next = NULL;
    return paragraph;
}

void paragraph_print(Paragraph *paragraph) {
    printf("Paragraph : %p\n", paragraph);
    fseek(file, paragraph->start - 1, SEEK_SET);
    int ch;
    while ((ch = fgetc(file)) != EOF && ch != '\n' && ch != '[') {
        printf("%c", (char)ch);
    }
    printf("\n\n");
}

void paragraph_fprintf(Paragraph *paragraph, FILE *f) {
    // Se placer au début du paragraphe dans le fichier source
    fseek(file, paragraph->start - 1, SEEK_SET);

    int ch;
    // Lire chaque octet et l’écrire dans le nouveau fichier
    while ((ch = fgetc(file)) != EOF && ch != '\n' && ch != '[') {
        fputc(ch, f);
    }

    // Ajouter une double nouvelle ligne à la fin du paragraphe
    fputs("\n\n", f);
}

CodeList* paragraph_get_codes(Paragraph* paragraph) {
    printf("paragraph_get_codes\n");
    fseek(file, paragraph->start, SEEK_SET);
    int ch = fgetc(file);
    CodeList *codelist = codelist_new();
    printf("Ch : %d\n", ch);
    while (ch != EOF && ch != '\n') {
        printf("%c", ch);
        if ((char)ch == '[') {
            printf("start of code\n");
            long code_start = ftell(file);
            int code_length = 0;
            while ((char)(ch = fgetc(file)) != ']') {
                code_length++;
            }
            long code_end = ftell(file);
            Code *code = code_from_offsets(code_start, code_end);
            //codelist_dump(codelist);
            codelist_append_unique(codelist, code);
            printf("paragraph_get_codes after append\n");
            fseek(file, code_end, SEEK_SET);
        }
        ch = fgetc(file);
    }
    return codelist;
}

void paragraph_print_codes(Paragraph* paragraph) {
    CodeList *codes = paragraph_get_codes(paragraph);
    Code *code = codes->first_code;
    while (code) {
        printf("Code : %s\n", code->value);
        Code *keep_code = code;
        code = code->next;
        code_free(keep_code);
    }
}

long paragraph_get_next_line_start(Paragraph* paragraph) {
    fseek(file, paragraph->start, SEEK_SET);
    int ch;
    while ((ch = fgetc(file)) != EOF && (ch != '\n')) {
        printf("%c", ch);
    }
    printf("\n");
    if (ch == EOF) {
        return (long)NULL;
    }
    ch = fgetc(file);
    if (ch == '\r') {
        fgetc(file);
        return ftell(file);
    }
    return ftell(file);
}

void paragraph_free(Paragraph *paragraph) {
    free(paragraph);
}
