When you program with POSIX Threads API, there is one thing about pthread_exit() that you may ignore for mistake. 

In subroutines that complete normally, there is nothing special you have to do unless you want to pass a return code back using pthread_exit(). 

The completion won't affect the other threads which were created by the main thread of this subroutine. However, in main(), when the code has been executed to the end, there could leave a choice for you. If you want to kill all the threads that main() created before, you can dispense with calling any functions. 

But if you want to keep the process and all the other threads except for the main thread alive after the exit of main(), then you can call pthread_exit() to realize it. 
And any files opened inside the main thread will remain open after its termination.

