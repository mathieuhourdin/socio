#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<locale.h>

#include"code.h"
#include "paragraph.h"
#include "globals.h"
#include "codelist.h"
#include "text.h"


FILE *file = NULL;

int main() {

    setlocale(LC_ALL, "en_US.UTF-8");
    file = fopen("socio.txt", "r");
    if (!file) {
        perror("fopen");
        return 1;
    }

    printf("File : %p\n", file);

    Text *text = text_build();
    text_dump(text);
    //text_print_codes(text);
    CodeList *codelist = text_get_codes(text);
    codelist_get_paragraphs(codelist, text);
    codelist_dump(codelist);
    codelist_fprintf(codelist, "output.txt");
    fclose(file);
    text_free(text);
    codelist_free(codelist);
    return 0;
}
