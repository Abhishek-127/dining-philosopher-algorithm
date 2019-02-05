Name:   Abhishek Jhoree
ID:     09986820
Assignment 3
Operating Systems CIS*3110
March 26th 2018

- What the program does?
---- qustion 1-----
As instructed, the program implements the dining philosopher algorithm for the first
question.

---- question 2 ----
The second program runs a simulator which takes processes of different sizes, 
load them into memory according to a certian amount of rules and swap out the processes 
to create a bigger hole.We were asked to make some assumptions of this program which can 
be found on the Assignment description.

---- How to Run the code -----
- first, compile the code
1. do make
This will create an executable called 'run' in the bin folder

- to run part 1(dining philosopher)
do ./bin/run arg1 arg2
an example is ./bin/run 3 2

- to run  part2
do ./bin/run filename.txt

Assumptions:
Part 1:
-Must enter in 3 arguments. They must be integers. 
-You must enter 2 numbers followed by spaces. If you add extra an error message will 
be displayed saying that there is not enough or too many arguements.

part 2
The filename must exist and placed in proper directory (depending on how you run the code)




