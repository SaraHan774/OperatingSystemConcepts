# operating-system-concepts
Operating System Concepts - programming projects. (2020/03 ~ )

### Chapter 3 Programming Project : mini Unix Shell
* Making a little shell program that will accept command line inputs. 
* for example, `ls -al` will be stored in `char * args`. Parent process will `fork()` to make a child process. Child process will `execvp()` to execute the given command arguments. 
