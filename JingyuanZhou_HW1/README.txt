Jingyuan Zhou
Assignment 1

Problem 1
In this problem, since we know the input is a single integer, I manually counted the number of bits it should be shifted and hardcoded it. For each byte, I "squeezed" out the other bytes and shifted it to the right place. There must be better ways to do it.

Problem 2
I am only able to determine bit by bit. There should be a way to extract sign, exponent and mantissa directly.

Problem 3
If we can assume that the input is in the exact format that we want it to be, my program works.

Problem 4
I only format the values within the array to one decimal place number before printing it out.The values that are actually saved in the array have more decimal places.

Problem 5
I only format the values within the array to one decimal place number before printing it out.The values that are actually saved in the array have more decimal places.

Problem 6
My program gives a segmentation fault, but I'm not sure how to fix it. 

Problem 7
I got 5 warning when running this program. Four of them are "variable length arrays are a C99 feature [-Wvla-extension]". Since I only know to declare a static array this way, I do not know how to fix this. The other warning I get is "ISO C90 forbids mixing declarations and code". In order to comply to the format given by the professor, I decide not to move the two lines "M = 1000;" and "N = 1000;".

Problem 8
The output is exactly the same as requested if I input directly by pasting the content of a text file; however, if I use "< test.txt", it will first show the content in the file and then show the shorted list.

Problem 9
It works under the assumption that the input is a valid file name and can be read. Another thing is that I declared and initialized "char text[MAX_LINES][MAX_CHAR_PER_LINE];" outside of the main function so that it can be accessed. This may not be the best way to do this.

Problem 10
It works fine, but I initialized the ine wordnum outside of main function for convenience. 