#ifndef TEXT_H
#define TEXT_H

typedef struct Paragraph Paragraph;
typedef struct CodeList CodeList;

typedef struct Text {
    Paragraph* first_paragraph;
} Text;

Text* text_build();
CodeList* text_get_codes(Text *text);
void text_dump(Text* text);
void text_print_codes(Text* text);
void text_free(Text* text);

#endif
