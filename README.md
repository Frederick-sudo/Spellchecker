Project Description:
An application developed through C that uses hash tables to efficiently store and retrieve dictionary words for a quick spell checking of text files. Developed as part of Harvard University's CS50x course.

Features:
Load words from dictionary into a hash table for a fast lookup.
Checks word-for-word the text files and compares them to the dictionary
Mispelled words are reported
Using 'malloc' and 'free' manages memory manually and dynamically
Valgrind detects possible memory leaks

Technologies Used:
  C Programming Language
  Custom implementation of hash tables
  File handling
  Manual Memory Management through 'malloc' and 'free'
  Debugging with Valgrind

Project Files:
dictionary.c - Responsible for the implementation of dictionary loading, checking, and unloading.
dictionary.h - Header file that defines functions and data structures.
speller.c - The main program that is responsible for handling input files and calling dictionary functions
Makefile - Simplifies compilation of files
dictionaries/ - Sample dictionaires used for testing

How to run:
  Compile the program 
    make speller
    
  Run spell checker of a text file
    ./speller [dictionary] textfile.txt    ex:./speller dictionaries/large textfiles/sample.txt

  Use Valgrind to check for memory leaks 
    valgrind ./speller dictionaries/large textfiles/sample.txt

Project Background:
Built as a core project in **CS50x: Computer Science Course** from Harvard University, this app simulates real-world stock trading platforms, demonstrating full-stack web development skills.
    
