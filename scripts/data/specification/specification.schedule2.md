> ### Program Name: `schedule2`
>
> ### Description
> The `schedule2` program simulates a process scheduler for an operating system. It manages a set of processes with varying priorities, handling operations like adding new processes, blocking and unblocking processes, expiring quantum for the current process, upgrading process priorities, finishing the current process, and flushing all processes.
>
> ### Key Components
> - **`schedule2.c`**: The main source file that implements the scheduler logic.
> - **`schedule2.h`**: The header file that defines constants, structures, and function prototypes used by the scheduler.
>
> ### Data Structures
> - **Process**: Defined in `schedule2.h`, this structure represents a process with a process ID (`pid`), priority, and a pointer to the next process in a queue.
> - **Queue**: An array of queues (`prio_queue`) where each queue corresponds to a different priority level. There is also a special queue for blocked processes.
>
> ### Constants
> - `MAXPRIO`: The maximum priority level.
> - `BLOCKPRIO`: The priority level used for the blocked queue.
> - Commands for scheduling operations (e.g., `NEW_JOB`, `BLOCK`, `UNBLOCK`, `QUANTUM_EXPIRE`, `FINISH`, `FLUSH`).
>
> ### Scheduler Operations
> - **New Job**: Adds a new process with a specified priority.
> - **Upgrade Priority**: Increases the priority of a process based on a given ratio within its current queue.
> - **Block**: Moves the current process to the blocked queue.
> - **Unblock**: Moves a process from the blocked queue back to its appropriate priority queue based on a given ratio.
> - **Quantum Expire**: Simulates the expiration of a quantum (time slice) by placing the current process at the end of its priority queue.
> - **Finish**: Terminates the current process and selects the next process to run.
> - **Flush**: Terminates all processes in all queues.
>
> ### Functions
> - **`main`**: Initializes the scheduler, processes command-line arguments to populate the queues with processes, reads commands from standard input, and executes them.
> - **Queue Manipulation Functions**: Includes functions to add a process to a queue, remove a process from a queue, and manipulate the current process (`enqueue`, `new_job`, `block`, `unblock`, `quantum_expire`, `finish`, `flush`).
> - **Utility Functions**: Functions to get the current process, reschedule processes, and manage the scheduler's state (`get_current`, `reschedule`, `get_command`).
>
> ### Execution
> To run the program, execute the compiled binary and provide the initial number of processes for each priority level via command-line arguments:
> ```sh
> ./schedule2 3 2 1
> ```
> The program then reads scheduler commands from standard input.
>
> ### Input Format
> Commands are read from `stdin` and can include operations like adding a new job, blocking the current process, unblocking a process, etc. Each command is specified by an integer code followed by necessary arguments, such as priority or ratio.
>
> ### Output
> The program prints the PID of processes as they are finished. For the `FLUSH` command, it prints the PIDs of all remaining processes in order of their termination.
>
> ### Note
> The specification is based on the provided source code snippet and common functionalities expected from a process scheduler simulation. The actual behavior might vary depending on the complete implementation details and additional functionalities not covered in the snippet.