# Philosophers

## Goal of the project

The goal is to gain proficiency in **concurrent programming** concepts to implement a solution to the dining philosophers problem, ensuring that **philosophers can eat without deadlocks** or starvation. Through this project, I have learned how to effectively utilize **threads**, **mutexes**, and other synchronization mechanisms to manage shared resources.

### Deadlock

Situation that occurs in concurrent computing when two or more processes or threads become **permanently blocked**, each waiting for the other to release a resource or take a specific action, resulting in a halt in the system's progress. 

### The problem

The dining philosophers problem is a classic scenario where a group of philosophers is seated around a table, each with their own bowl of spaghetti and a set of chopsticks. These philosophers alternate between periods of **thinking**, **eating**, and **sleeping**.

However, there is a constraint that poses a challenge: there are a limited number of chopsticks available, and each philosopher requires two chopsticks to eat. The catch is that they can only use the chopsticks that are adjacent to them on the table.

This constraint creates a potential issue. If every philosopher tries to grab the chopstick on their left simultaneously, a deadlock can occur, where no philosopher can proceed with their meal.

![Untitled](Philosophers%20cd21fb92b41d4ad0bb4e1a7f64981417/Untitled.png)

To overcome this problem, a synchronization strategy or protocol needs to be devised. This strategy should ensure that each philosopher can acquire the necessary chopsticks without causing conflicts or resource contention among themselves. The aim is to find a solution that allows all philosophers to eat without encountering a deadlock situation.

### Applications

The project's applications include learning **multithreading**, **critical section management**, and **deadlock prevention**, all of which are crucial in concurrent programming and managing shared resources efficiently.

## What is a thread?

A thread is a lightweight process that can run concurrently with other threads. It executes a sequence of instructions independently, allowing for multiple tasks to be performed simultaneously. Threads share memory with other threads and the main program, but have their own stack and registers. This enables them to execute code independently, but requires proper synchronization for shared resources.

![Untitled](Philosophers%20cd21fb92b41d4ad0bb4e1a7f64981417/Untitled%201.png)

Threads are often used to improve the performance and responsiveness of programs, as they can allow multiple tasks to be executed concurrently. For example, a web server might use threads to handle multiple requests from different clients at the same time.

### Example

To expedite cooking dinner, instead of doing tasks sequentially, you can use multiple threads to run concurrently. For example, one thread can chop vegetables, another can boil pasta, and so on. This approach enables quicker and more efficient completion of the dinner preparations.

## Operations with threads? (library: pthread.h)

1. **`pthread_create(&tid, attr, function, arg)`**: Creates a new thread in the program.
    - **`tid`**: Pointer to the task identifier.
    - **`attr`**: Task attributes (e.g., priority).
    - **`function`**: The function to be executed by the new thread.
    - **`arg`**: Pointer to the parameters passed to the function.
2. **`pthread_exit(void *value_ptr)`**: The calling thread finishes and saves the results in the **`value_ptr`** pointer.
3. **`pthread_join(pthread_t thread, void *value_ptr)`**: The calling thread waits until the specified thread has finished, and the result returned by the thread is placed in **`(*value_ptr)`**.

Additional command:

1. **`pthread_detach()`**: Detaches a thread from the calling thread. It automatically releases the thread's resources when it completes, without requiring the calling thread to wait using **`pthread_join()`**. Once detached, the thread cannot be re-attached, and its resources cannot be reclaimed by the calling thread.

**Explanation**

The input parameters for the new task are passed through the last argument of `pthread_create`, and the new task receives its parameter in the unique argument of its function. 

The output parameters returned by the new task are placed in the parameter of `pthread_exit`, being received by the creating task through the last argument of `pthread_join` (by reference).

## What is a data race?

A data race is a type of concurrency bug that can occur in computer programs that have multiple threads or processes running concurrently and accessing shared data. **It happens when two or more threads access the same shared data concurrently without proper synchronization**, and at least one of them performs a write operation.

In a data race, the **final value** of the shared data **becomes unpredictable** because it depends on the order in which the threads access it. This can lead to unexpected behavior, including crashes, incorrect results, and security vulnerabilities.

**Example:**

```c
//Data races
int mails = 0;
void* routine()
{
	for (int i = 0; i < 1000000; i++)
		mails++;
	//read mails 
	//increment 
	//write mails
}

int main(int ac, char **av)
{
	srand(time(NULL));
	pthread_t t1, t2;
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return 2;
	if (pthread_join(t1, NULL) != 0)
		return 3;
	if (pthread_join(t2, NULL) != 0)
		return 4;
	printf("Numbers of mails: %d\n", mails);
	return 0;
}
Output: "Numbers of mails: 998925".

Thread1        Thread2        Action
-------------------------------------
29 (1º)         -              READ
   -           29 (2º)         READ
29 (3º)         -              INCREMENT
30 (4º)         -              WRITE
30 (5º)         -              READ
30 (6º)         -              INCREMENT
31 (7º)         -              WRITE
   -           29 (8º)         INCREMENT
   -           30 (9º)         WRITE
Deste modo, fomos de 31 para 30, perdendo assim um dos incrementos.
```

Other example, consider two threads that access a shared variable x. Thread A reads the value of x and increments it by 1, while thread B reads the value of x and multiplies it by 2. If thread A and thread B run concurrently without proper synchronization, the final value of x will depend on the order in which the threads access it. If thread A reads x first and then thread B reads x, the final value of x will be (x + 1) * 2. But if thread B reads x first and then thread A reads x, the final value of x will be (x * 2) + 1.

## Conditional variables

**Conditional variable:** A synchronization object that allows threads to wait until a certain condition is true before proceeding with their execution. This is done by allowing threads to block (i.e. sleep) until a signal is received from another thread indicating that the condition has been met.

In the POSIX threads library, **`pthread_wait()`**, **`pthread_broadcast()`**, and **`pthread_signal()`** are functions used for inter-thread synchronization and communication through conditional variables.

- **`pthread_wait()`**: Blocks the current thread until a signal is received on the specified conditional variable. It requires a mutex to be locked before calling, and the mutex is automatically reacquired when the thread wakes up after receiving the signal.
- **`pthread_broadcast()`**: Wakes up all threads waiting on the specified conditional variable. It allows multiple threads to continue their execution simultaneously.
- **`pthread_signal()`**: Wakes up one thread waiting on the specified conditional variable. It selectively resumes the execution of one waiting thread.

In summary, conditional variables facilitate synchronization and coordination among threads in a multi-threaded program. These functions provided by the POSIX threads library offer a way for threads to wait for signals, wake up waiting threads, or wake up a single waiting thread, respectively.

### Care to be taken

![Untitled](Philosophers%20cd21fb92b41d4ad0bb4e1a7f64981417/Untitled%202.png)

When a task calls `wait()` on a condition variable, it enters the waiting queue atomically and releases the latch. If the condition changes and a `signal` or `broadcast` is issued, at least one task in the waiting queue will be unblocked.

However, the unblocked task doesn't immediately run; it becomes executable but must re-acquire the latch for `wait()` to return. During this time, the condition value may change back, causing issues.

To address this, recheck the condition after `wait()` returns using a `**while (condition)` loop**, not a simple `if (condition)` check. This ensures the task rechecks the condition repeatedly until it is valid, preventing race condition problems.

Additionally, be aware of spurious wakeups, where `wait()` returns without an actual `signal` or `broadcast`. Use the `while (condition)` loop to handle such cases.

In conclusion, when using condition variables, recheck the condition after `wait()`, use a `while (condition)` loop, and consider potential spurious wakeups for proper synchronization and to avoid race conditions in multi-threaded environments.

## Golden Rule or Amdahl's Law

Amdahl's Law, also known as the "Golden Rule," evaluates the performance of parallel systems by estimating the speedup gained from using multiple processors compared to a single one.

It states that the **speedup is limited** by the portion of the task that cannot be parallelized. 

The larger this sequential fraction, the smaller the speedup achieved with more processors. The illusion of an infinitely large number of processors can be misleading, as the speeds of each virtual processor may differ and be unpredictable, ultimately impacting the overall system performance and limiting the speedup achieved.

# What is a mutex?

### Simpler Definition

A **mutex** is a programming construct that prevents multiple threads or processes from simultaneously accessing a shared resource, by allowing only one thread or process to access it at a time.

### Definition

A mutex (short for "mutual exclusion") is a programming construct used to prevent multiple threads or processes from simultaneously accessing a shared resource, such as a variable, file, or device. It is a synchronization primitive that ensures that only one thread or process can access the shared resource at a time, thereby preventing conflicts and data corruption.

A mutex typically works by providing a lock that can be acquired by a thread or process when it needs to access the shared resource. If the lock is already held by another thread or process, the requesting thread or process will block until the lock is released. Once the lock is acquired, the thread or process can access the shared resource safely, knowing that no other thread or process can access it concurrently. When the thread or process is finished accessing the shared resource, it releases the lock so that another thread or process can acquire it.

Mutexes are commonly used in **multi-threaded** or **multi-process programming environments**, where multiple threads or processes need to access shared resources. They are often used in conjunction with other synchronization primitives, such as semaphores or condition variables, to implement complex synchronization protocols.

### Example

```c
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock; // declare a mutex variable

void *thread_function(void *arg) {
    pthread_mutex_lock(&lock); // acquire the lock
    printf("Thread is executing\n");
    pthread_mutex_unlock(&lock); // release the lock
    return NULL;
}

int main() {
    pthread_t thread_id;
    pthread_mutex_init(&lock, NULL) // initialize the mutex
    pthread_create(&thread_id, NULL, thread_function, NULL) // create a thread
    pthread_mutex_lock(&lock); // acquire the lock
    printf("Main thread is executing\n");
    pthread_mutex_unlock(&lock); // release the lock
    pthread_join(thread_id, NULL); // wait for the thread to finish
    pthread_mutex_destroy(&lock); // destroy the mutex
    return 0;
}
```

### Commands for mutex’s:

1. **`pthread_mutex_init`**: This function is used to initialize a mutex variable, which is a synchronization primitive used to prevent simultaneous access to shared resources by multiple threads. The function takes a pointer to a mutex variable and a pointer to a mutex attribute object as arguments, and returns 0 on success.
2. **`pthread_mutex_destroy`**: This function is used to destroy a mutex variable that was initialized using **`pthread_mutex_init()`**. The function takes a pointer to the mutex variable as an argument, and returns 0 on success.
3. **`pthread_mutex_lock`**: This function is used to lock a mutex variable, which blocks other threads from accessing the shared resource protected by the mutex. If the mutex is already locked by another thread, the calling thread will be blocked until the mutex becomes available. The function takes a pointer to the mutex variable as an argument, and returns 0 on success.
4. **`pthread_mutex_unlock`**: This function is used to unlock a mutex variable, allowing other threads to access the shared resource protected by the mutex. The function takes a pointer to the mutex variable as an argument, and returns 0 on success. It is important to note that the calling thread must own the mutex before calling this function, otherwise the behavior is undefined.

### Difference between thin and global mutex?

A **global mutex** is a mutex that can be accessed by threads across the entire program, while a **thread-specific** (or "thin") mutex is a mutex that is only accessible by the thread that owns it.

The main difference between global and thin mutexes is their scope. Global mutexes are useful when multiple threads need to access a shared resource, as they **ensure that only one thread can access the resource at a time**. However, global mutexes can also be a source of contention, as all threads must compete for access to the same mutex.

Thin mutexes, on the other hand, are useful when a thread needs to protect a resource that is not shared with other threads. By using a thin mutex, **the thread can ensure that no other thread will modify or access the resource** **while it is being used**.

Another important difference is the cost of acquiring and releasing the mutex. A thin mutex typically has a lower overhead compared to a global mutex, as it only needs to be managed by the owning thread. Global mutexes, on the other hand, may require more resources to manage, as they need to be accessed and updated by multiple threads.

*Global mutexes are better suited for protecting shared resources, while thin mutexes are better suited for protecting thread-specific resources.*

## The philosophers solution

**Naive Implementation**

```c
`filosofo(int id) {
  while (TRUE) {
    pensar();
    <adquirir os garfos>
    comer();
    <libertar os garfos>
  }
}`
```

The problem with this implementation is that it can cause the program to halt indefinitely. For example, if each philosopher locks the fork to their right, none of them will be able to execute the second lock on the fork to their left, causing the program to be **stuck infinitely**.

### Why i cant solve the philophosers problem by letting one eat at a time?

1. **Efficiency:** If only one philosopher is allowed to eat at a time, the overall efficiency of the system will be reduced. This is because the philosopher will need to wait for all the other philosophers to finish eating before they can eat again.
2. **Resource utilization:** Allowing only one philosopher to eat at a time can result in poor utilization of resources. For example, if there are five philosophers and only one can eat at a time, four seats at the table will be unused, resulting in a waste of resources.
3. **Deadlock:** In some cases, allowing only one philosopher to eat at a time can lead to a deadlock situation, where each philosopher is holding onto one fork and waiting for the other fork to become available. This can result in a situation where no philosopher can eat, even though there are resources available.
4. **Starvation:** If a philosopher is constantly being skipped over in the rotation, they may never get a chance to eat. This can result in starvation, which is an undesirable outcome.

## What are the uspleep() and gettimeofday() functions?

- **`usleep()`** is a function in C that **suspends the execution of the calling thread for a specified number of microseconds.** It takes an unsigned integer argument that represents the number of microseconds to sleep. This function can be useful in synchronizing threads or adding delay between operations.
- **`gettimeofday()`** is a function in C that **retrieves the current time in microseconds** and timezone information. It is often used for measuring time intervals or for timestamping events. The function takes two arguments: a pointer to a struct timeval that will hold the time information, and a pointer to a struct timezone that will hold timezone information.

**Example:**

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
    struct timeval start, end;
    unsigned long long elapsed_time;

    gettimeofday(&start, NULL); // Get the current time
    printf("Sleeping for 1 second...\n");
    usleep(1000000); // Sleep for 1 second
    gettimeofday(&end, NULL); // Get the current time again
    
		// Calculate the elapsed time in microseconds
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    // Print the elapsed time
    printf("Elapsed time: %llu microseconds\n", elapsed_time);

    return 0;
}
```

### What is time_t ?

**`time_t`** is a **data type** used in the C and C++ programming languages to represent time values. It is defined in the header file **`<time.h>`** and represents the **number of seconds elapsed since the Unix epoch**, which is midnight on January 1, 1970, Coordinated Universal Time (UTC).

The **`time_t`** data type is used in various functions in the C and C++ standard libraries, such as **`time()`**, **`difftime()`**, and **`ctime()`**, which deal with time values and date/time manipulation. **`time_t`** values are typically stored as signed integers, although the actual implementation may vary between systems.

It is worth noting that **`time_t`** is not suitable for representing dates and times with high precision or accuracy, as it only represents whole seconds. For higher precision, alternative representations such as **`struct tm`** or **`std::chrono::time_point`** can be used.

### What is __uint64_t?

**`__uint64_t`** is a typedef for an unsigned 64-bit integer in C. It's defined in the **`<stdint.h>`** header file and is typically used when you need to declare an unsigned integer that's guaranteed to be 64 bits wide, regardless of the underlying hardware or compiler.

**`__uint64_t`** is used instead of **`unsigned long long`** or **`unsigned long`** to ensure portability of the code. **`unsigned long long`** is often used to represent a 64-bit integer, but it may not be exactly 64 bits wide on all systems, depending on the underlying hardware or compiler. In contrast, **`__uint64_t`** is always exactly 64 bits wide.

### Why create my_usleep() function?

The **`usleep()`** function sleeps for a specified number of microseconds, but it's not precise, and the actual sleep time may be longer or shorter than the specified time. This is because the implementation of **`usleep()`** **may vary across different systems**, and it may be affected by other factors such as system load and scheduling.

The custom **`ft_usleep()`** function uses **`gettimeofday()`** to measure the exact time before and after the sleep, and it waits until the exact number of milliseconds has passed before returning. This makes it more precise than the **`usleep()`** function and ensures that the program sleeps for exactly the desired amount of time.

Therefore, if you need precise timing in your program, it's better to use a custom **`ft_usleep()`** function or similar implementation that relies on the **`gettimeofday()`** function. However, if precision is not critical, you can use the standard **`usleep()`** function provided by the system.

## Flags to check data races

**`valgrind --tool=helgrind`**

**`cc -fsanitize=thread`**
