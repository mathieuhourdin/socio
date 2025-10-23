# SOCIO

This file is a trackrecord of the conception of the projetc (made for educational purpose mainly)

### ideation

I want to perform a base transformation of a sociology document.
The document is presented in a descriptive way. Then it is coded with analytical codes.
Each code is a [code] at the end of the paragraph, on the same line.

I want to transform the document in another text document where the content of the enquiry is presented organized by codes.

### assumptions ###
codes are at the end of lines
[] are only used for codes and a closing ] follows an opening [.

### draft exploration of the problem ###

loop through the document, identify codes, have a list of codes, loop again with the codes and record the address.
I dont need to copy the paragraphs, i can only record a pointer to its head.
I surely have to identify the codes first.
And i need a data structure to store the identified codes.
the codes are at the end of each line, so i can jump to the end of the line and look for the codes
I must remove codes from lines at the end but it is the very last point, just before to write in the file.

I may store the pointers to the head of the line but would i be able to get only the line ?

So here i need : 

A list of codes;
loop through the document to identify codes and field the list of codes.

then for each code of the list, loop through the text lines to see if the code is present.
If so, add an element to the code list.

then loop through the code list, add the code to the new file, and then loop through the list associated with the code to print text (using the pointers)

### Concepts i need ###

A struct Text that holds every paragraphs. IT has ownership over the paragraphs.
A struct CodeList for code lists. Code lists are stacks (last in first out);
A struct for codes
A struct Text for the list of paragraphs
A struct for paragraphs
 - has a pointer to the start of a line

A linked list for codes.
A linked list for each codes with paragraphs in it.
A method to know if a given code is present in a line.
A method to find every codes possible in the file.

### Final spec ###

Socio is a sociology enquiry documents manipulating tool.
It transforms a sociology descriptive documents marked with codes into a documents organized by codes.

It transforms a list of paragraph (the text) into a list of codes, which each have a list of related paragraphs.

Codes have ownership on their related paragraphs.
CodeList have ownership on their codes.
Text has ownership on its paragraphs.

