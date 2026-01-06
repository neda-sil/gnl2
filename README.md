*This project has been created as part of 42 curriculum by neda-sil.*

**get_next_line(int fd);**

# DESCRIPTION:

The get_next_line project aims to read from a file descriptor and return one line at a time.
For each calls of the function, one line (ending by ‘\n’ or ‘\0’) will be returned, as long as the file descriptor is not finished.

# INSTRUCTIONS:

Using « open("[file_name]") », you will have an int to put in the « fd » location on prototype. You can then store get_next_line’s return in a char \*.
To use the project, you have to compile « get_next_line.c » and « get_next_line_utils.c » (and keep the « get_next_line.h » file in the same location).
Including the « get_next_line.h » file in you main project is necessary for it to work.

Note : you can compile it using -D BUFFER_SIZE n to set the BUFFER_SIZE size.

# RESSOURCES:

What is a file descriptor and how to manipulate it using open and read:
https://www.codequoi.com/manipuler-un-fichier-a-laide-de-son-descripteur-en-c/

static variables :
https://www.codequoi.com/variables-locales-globales-statiques-en-c/

# ADDITIONAL:

After many tries, i decided to use simple strings for the project.
Using a tamporary variable that I would malloc and free repetitively looked like the easiest way to make it work.
