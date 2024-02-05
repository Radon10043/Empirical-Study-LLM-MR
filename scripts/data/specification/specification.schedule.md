> ### Program Name: `schedule`
>
> ### Description
> The `schedule` program simulates a simple process scheduler in an operating system. It manages processes with different priorities, handling operations such as process creation, blocking and unblocking of processes, priority upgrades, time quantum expiration, and process termination. The program operates based on commands read from the standard input, simulating a basic scheduler's behavior in response to system events.
>
> ### Functionality
> - **Process Management**: Supports adding new processes with specified priorities, finishing (terminating) processes, and flushing (terminating) all processes based on priority.
> - **Priority Handling**: Allows upgrading the priority of a process and manages processes in different priority queues.
> - **Quantum Handling**: Simulates the expiration of a quantum (time slice) for the currently running process, placing it back in the priority queue.
> - **Blocking/Unblocking**: Simulates blocking a process (e.g., for I/O) and unblocking a process, moving it back into the appropriate priority queue.
>
> ### Components
> - **Process (Ele)**: Structure representing a process with fields for priority, value (process ID), and pointers to next and previous processes in a queue.
> - **List**: Structure representing a doubly linked list used to manage queues of processes.
> - **Priority Queues**: An array of lists (`prio_queue`), where each list holds processes of a specific priority.
> - **Block Queue**: A list holding processes that are currently blocked.
>
> ### Key Functions
> - `main`: Reads commands from standard input and executes scheduler operations accordingly.
> - `new_ele`, `new_list`, `append_ele`, `del_ele`, `find_nth`, `free_ele`: Manage dynamic creation, modification, and deletion of elements (processes) and lists (queues).
> - `schedule`: Chooses the next process to run based on priority.
> - `finish_process`, `finish_all_processes`: Handles the termination of the current process or all processes, respectively.
> - `upgrade_process_prio`, `block_process`, `unblock_process`, `quantum_expire`, `add_process`, `init_prio_queue`, `initialize`: Implement the scheduler's logic for various operations.
>
> ### Input Specification
> The program expects an initial configuration through command-line arguments specifying the number of processes at each priority level (from highest to lowest). Commands to manage processes are read from standard input, formatted as follows:
> - `1 prio`: Add a new process with priority `prio`.
> - `2 prio ratio`: Upgrade the priority of a process from `prio` using `ratio` to select the process.
> - `3`: Block the current process.
> - `4 ratio`: Unblock a process using `ratio` to select from the block queue.
> - `5`: Simulate quantum expiration for the current process.
> - `6`: Finish the current process.
> - `7`: Flush (finish) all processes according to priority.
>
> ### Output Specification
> The program outputs the value (ID) of processes as they terminate, printing each value followed by a space.
>
> ### Execution
> Run the program with initial priorities as arguments, and provide commands through standard input, e.g.:
> ```sh
> echo "1 2\n6\n7" | ./schedule 1 2 3
> ```
> This command sequence adds a new process with priority 2, finishes the current process, and then flushes the remaining processes.