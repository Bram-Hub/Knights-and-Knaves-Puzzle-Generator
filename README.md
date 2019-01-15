# Knights and Knaves Puzzle Generator
## Authors
2016:
William Goubeaux

## About
This project contains a number of files they are all explained here:

generator.cpp - This is the c++ program I made to find solutions to knights and knaves puzzles.
                I used a > in the terminal in order to write the output to a file.

site_creator.cpp - This is a program that takes the output from the generator and turns it into HTML files.

result(2/3/4).txt - These are the output from the generator. It is easiest to explain what they are with an example.
                    
                    0 - a 0
                    1 - d 0 1
                    2 - a 1
                    0 = 0
                    1 = 0
                    2 = 0

                    This is a solution generated for 3 people.
                    The first 3 lines tell you what each person is saying.
                    The numbers stand for a specific person ( 0 = person 1, 1 = person 2, 2 = person 3 ).
                    The stuff to the right of the (-) is a specific saying.
                    The number to the left of the (-) is who is going to say that.
                    The letters represent what connective the person is saying.
                    For example, if person 1 is A and person 2 is B:
                      a 0 means A
                      b 0 mean ~A
                      c 0 1 means A ^ B
                      d 0 1 means A ^ ~B
                      e 0 1 means ~A ^ B
                      f 0 1 means ~A ^ ~B
                      g 0 1 means A v B
                      h 0 1 means A v ~B
                      i 0 1 means ~A v B
                      j 0 1 means ~A v ~B
                      k 0 1 means A <-> B
                      l 0 1 means ~(A <-> B)

                    The last three lines are the solution to the puzzle.
                    The number before the (=) is the person.
                    The number after is what the person is ( 0 = knave, 1 = knight ).

Puzzles/knightsandknaves*.html - These are the html files were generated.
                         There are 74 solutions using 2 people, so I turned all of these into HTML files.
                         There are 15,540 solutions using 3 people. I turned about 1,000 of these into HTML files.
                         There are 6,562,536 solutions using 4 people. I turned 1,000 of these into HTML files as well.

kak.png - This is just a picture that the HTML files use to look a bit nicer.
          It needs to be in the same folder as the HTML files if you want it to show up on the webpage.

names.txt - This is just a large file of names that I used for generating the puzzles.
            I am leaving it here in the case that someone else wants to revisit the generator code.

**************************************************************************************************************************

[I also gave a google slides presentation](https://drive.google.com/open?id=1JpjG7aZkNDzyFqVGynBEtV80mo65b3yTQ0K6MjiuU8I).
