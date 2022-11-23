# C Data Structures

This started off as just a challenge I made for myself: trying to re-
create one of the first data structures I learned to create: Linked
Lists, in C. After feeling comfortable with writing Linked Lists, I
decided to code the rest of the data structures I learned in Algorithm-
ic design II at University of South Carolina. This is what this Github
Repo has become now. 

## REQUIREMENTS

If you plan on using the Makefiles provided in each subfolder, then
there are 2 dependencies. Otherwise you can choose a compiler fully at 
your own discretion if you plan on using a compiler and memcheck
resource leak checking program of your choice.
#### GCC: Gnu Compiler Collection. Used to compile C code.

My personal compiler of choice. (Until I'm made aware of a
benefit to learning how to use CLANG versus sticking to the compiler
I learned C with). This is the compiler that the Makefile I wrote uses
to compile the C code.

#### Valgrind: A CLI Program That Utilizes Memcheck For Memory Analysis

The resource_leak_check target in my Makefile uses valgrind in order to
check for unaccounted-for memory leaks in the code.

## The Data Structure Subfolders

### Linked List

Still missing some key functions associated with Linked Lists. Has the
basics, though. Can add, remove, search for occurrence, and print.

### Binary Tree

This one has all base functionalities, but I would definitely like to,
and <i>will</i> improve it further. One of my plans within the next
few updates is add balancing via the AVL and Red-Black approaches.

### Running Demos

A Makefile is included in each of the data structures' subfolders.
The default Makefile target will compile and run the demo source file, 
<data structure folder>/src/main.c. The only other targets of note are
clean if you wanna clean the binaries created after compilation, and
resource_leak_check, which runs the program valgrind for checking for 
checking that all memory blocks reserved by malloc have been cleared
from the heap. 
