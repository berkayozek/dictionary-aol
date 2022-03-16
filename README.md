# Authors
- Berkay ÖZEK
- Berke ÖCAL

# Design overview:
In this project we designed a dictionary program based on tries data structure and finds terms how many times appears in the files. We have used sequential reading, block reading and reading files with thread.

# Task1:
Firstly, we created an R-Trie, and the nodes has 256 children. This amount of child increases the memory usage,
therefore, we decided to implement Ternary Search Tree. Ternary Search Tree has 3 child which are left, equal, and right.
If the current word character is smaller than node character, it goes left node. If it is bigger than node character, it goes right node.
If the current word character is equal then node character, it goes the equal node.

# Task 2:
In the Task2, we designed program that reads 10 different files line by line and it adds the terms of the query into TST.
Firstly, we have two inner loops for each File iteration. First loop is for the reading line
from file and second one is for the parsing the queries into terms, and we add terms into trie.
After that we print all terms and their count.

# Task 3:
In the third Task we implemented a program that reads block of queries from 10 different files.
Firstly, we found the file size for each 10 different files. Then, we read input corresponding file
with fread function. After this step we parsed input string with respect to new line and spaces
characters respectively to get the terms of queries. Firstly, we wrote a check mechanism to prevent
undesired line and word splits. If a query doesn't contain new line character, then
its needs to go back with fseek. If query contains new line character, it parses the query into
terms and it adds each term into trie.

# Task 4:
In this Task, we used Thread for reading queries from 10 different file.
When the one threads wants to insert into trie, thread locks the lock variable and
when the insert operation is finished it unlocks the lock variable.
Therefore, all threads works perfectly because only one threads enter the critical section
at the given time. After that we print the trie in terms of terms and counts of term.

# Task 5:
In the task we used Thread for reading queries from 10 different files, but we added terms into
10 different tries. In each Thread it reads queries from files line by line, and we used
strtok_r for splitting the terms because, strtok is not thread safe and it did not work properly.
We didn't use mutex because there is no critical section and we adds terms into 10 different tries.
After all threads finish, we merge the first thread with threads which is between 2 to 10.
At then we print all terms and counts of term into output file.

# Task 6:
In this task we read all queries from the files and adding them into one trie sequentially.
First, we find the how much byte we need for file by using fseek. First, we go to end of the file
by fseek and we read the whole file into string. After that we have two different inner loops,
first one is for the splitting line, and second one is for the splitting the terms. We used
strtok_r for splitting because two strtok can spoil each other. We added each terms in to one
trie. After that, we printed terms and count of terms into output file.

# Complete Specification:

- We wrote wrapper function for each Thread. If there is a critical section, we used mutex.

- In the multiple splitting operations, we used strtok_r because more than one strtok may spoil each other. Also, using strtok with multiple threads spoils parsed data. Therefore, we used strtok_r for each wrapper function for calling thread.

- In the block reading we used some techniques to read each queries correctly from the file. If we have block that has no \n at the end of the string therefore we should go back to \n characters from the file to read whole query. Thus, we avoid getting half of the terms.

- The files have unique characters between 0-255 therefore we cannot store this number of children with R-Trie. So, we implemented better solution which is Ternary Search Tree. In this way, we reduce the memory usage and at the end we can handle to read 10 files into trie with 1.1 GB memory usage.

- In task3, when we are reading by 2048 block, we cannot get the last query from the file because there is no 2048 block at the end of the file. We changed the fread buffer size to reaming character for reading the last block.

# Known Bugs and Problems
- Line Size cannot be lower than 1024, because some queries are longer 512 bytes.

# How to Compile
`$ make`

# How to Run
For each task you should give specific name

#### For example running Task2:
`$ ./Task2`

### For runing all Task:
`$ ./Task2 ; ./Task3 ; ./Task4 ; ./Task5 ; ./Task6`
