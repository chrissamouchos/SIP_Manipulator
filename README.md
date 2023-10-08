# SIP_Manipulator

During a technical interview for Telecommunications Engineer/Developer I was asked to create a parser that scraps data from incoming SIP messages and stores them in a local SQLITE database.

## Description

The Session Initiation Protocol (SIP) is a signaling protocol used for initiating, maintaining, and terminating communication sessions that include voice, video and messaging applications. SIP is used in Internet telephony, in private IP telephone systems, as well as mobile phone calling over LTE (VoLTE). The messages are either SIP Requests or SIP Responses. The implement a handshake type of procedure in order to establish communication between the caller, the base station and the calling.
For a network operator it is really important to implement a parser in low-level code (C in our case) for the SIP Messages that will be executed in the base station and will send the info to Radio Controller.



## Algorithm

The program opens a txt file that contains the message. With "getline" the code reads the file line by line until EOF and then based on the ":" it stores in a 2D string array the data after the delimeter. As the length of the string is unknown from before I use "strdup" in order to automatically allocate the proper memory size. After that the program creates/opens a local DB (using SQLite3) and inserts the data array into the one existing table. A select has been implemented in order to showcase the functionality of the program

## Execution

Just hit`make run`. There have been implemented a variety of other options like:

- valgrind, that showcases the correct memory management
- gprof, for code profiling
- and of course `make clean` that deletes all .out .o .txt files and the .db as well