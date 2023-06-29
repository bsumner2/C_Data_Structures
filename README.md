# C Data Structures

This started off as just a challenge I made for myself: trying to re-
create one of the first data structures I learned to create: Linked
Lists, in C. After feeling comfortable with writing Linked Lists, I
decided to code the rest of the data structures I learned in Algorithm-
ic design II at University of South Carolina. This is what this Github
Repo has become now. 

# Jun 29th 2023 Update

This repo has now become a place for my actually (semi-)serious data structures.
Data structures that can take generics and that I would be willing to use in an
actual project if need be.

## Data Structures So Far

### Hashmap

Basic 7919-index table open hashmap that takes cstring keys and generic values 
via void* value param and size_t size param for malloc to know how much space to 
reserve for the data, and copies the data in void* value via memmove.

### AVL Tree

Basic AVL-style restructuring binary search tree. Handles allocation of generics
in the same way that the hashmap does. Only difference here being that it also
takes callback function parameters for comparing the data parameterized with the
data already in the tree. 

## Memory Safety

Deallocation of data in nodes is simply free(node->data), so make sure any composition
(i.e.: dynamic metadata within the data youre adding to these data structures)
is dealt with appropriately. I suggest any pointers within structs you wish to add to
any of these data structures point to static memory, that way when free(node->data) is called,
we don't lose the only tether to the dynamic data we would otherwise have had.
If you think it would be wise of me to add a deallocator function callback as a parameter
for any data-removal or whole-structure-freeing functions, then please feel free to PM me,
and I can take it into consideration. For the time being, I left it out because I feel like
the amount of parameters it has at its current state is already a lot and, at least in my head,
seems like a slipperly slope toward overpolluting the call stack.
