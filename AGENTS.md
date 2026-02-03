# AGENTS.md

## Build Commands

This project uses a Makefile-based build system.

### Core Commands
- `make` or `make all` - Build all libraries (static and shared)
- `make clean` - Remove all build artifacts
- `make -j$(nproc)` - Parallel build using all available cores

### Build Outputs
- Static library: `.build/libcgeneric.a`
- Shared library: `.build/libcgeneric.so`
- Individual module libraries: `.build/lib{module}.a` and `.build/lib{module}.so`

### Testing
This project currently has no formal test suite. To test manually:
1. Include the relevant headers from `include/cgeneric/`
2. Link against the built libraries from `.build/`
3. Create test programs and compile with `-I./include -L./build -lcgeneric`

## Code Style Guidelines

### General Standards
- Language: C11 (GNU11 standard)
- Compiler: GCC with strict warnings (`-Wall -Wextra -Werror`)
- Build directory: `.build/` (all artifacts go here)

### Import Organization
Headers are organized in this order:
1. Project headers (relative to `include/cgeneric/`) - e.g., `#include "cgeneric/array.h"`
2. Standard library headers - e.g., `#include <stddef.h>`, `#include <stdint.h>`
3. System headers - e.g., `#include <stdlib.h>`, `#include <string.h>`

### Naming Conventions

#### Public API (Macros)
- Use `UPPER_SNAKE_CASE` with module prefix
- Examples: `ARRAY_CONSTRUCT`, `STACK_PUSH`, `QUEUE_POP`, `HASH_TABLE_PUT`

#### Internal Functions
- Prefix with underscore: `_function_name`
- Use `snake_case`: `_array_construct`, `_stack_push`, `_queue_init`

#### Structs
- Use `lowercase_snake_case` for struct names: `struct array`, `struct stack`
- Forward declare with `typedef` in headers

#### Variables
- Use `lowercase_snake_case` for all variables
- Descriptive names: `size_per_element`, `required_size`, `element_data`

### Types and Sizes
- Use fixed-width types from `stdint.h` for binary compatibility:
  - `uint8_t` for element sizes
  - `uint16_t` for capacities and indices  
  - `uint32_t` for hash keys
- Use `size_t` for memory allocations and array calculations
- Use `bool` from `stdbool.h` for boolean returns

### Memory Management Patterns

#### Flexible Array Members
- All containers use flexible array members at end of structs
- Allocation: `malloc(sizeof(struct) + capacity * element_size)`
- Memory layout: metadata first, then element storage

#### Construction Pattern
Two-phase initialization:
1. `_construct()` - allocates memory and calls init
2. `_init()` - initializes pre-allocated memory (for stack/static allocation)

#### Destruction Pattern
- Functions accept double pointers: `_array_destroy(&array_ptr)`
- Functions set pointer to NULL after free
- Always check for NULL before free

### Error Handling
- Use `assert()` for programming errors and contract violations
- Return `bool` for operations that can fail (e.g., push operations)
- No exceptions - return codes and assertions only
- Use NULL for allocation failures

### Macro Design
- Use `typeof()` GCC extension for type safety in macros
- Wrap macro bodies in `({...})` statement expressions
- Use stringification `#` to capture type names for runtime checking
- Example: `#define STACK_PUSH(stack, type, value) ({typeof(value) tmp = (value); _stack_push(stack, &tmp, #type);})`

### Documentation
- Use C-style `/** */` comments for function documentation
- Brief inline comments for complex logic
- Document undefined behavior (e.g., array bounds checking)

### Code Organization
- Headers in `include/cgeneric/` with include guards
- Implementation files in `source/`
- Include guard pattern: `__C_GENERIC_MODULE_H__`
- Keep implementation details in `.c` files

### Performance Considerations
- Use `memcpy()` for element copying
- Minimize memory allocations
- Prefer stack allocation when possible
- Use zero-initialization with `memset()`

### Type Safety
- Use type name strings for runtime type checking (stack/queue)
- Compile-time type checking via macro wrappers
- Element size validation in public functions

## Development Notes

### Adding New Container Types
1. Follow existing patterns in array/stack/queue/hashtable
2. Use flexible array member for element storage
3. Provide both construct/init and destroy patterns
4. Create type-safe macro wrappers
5. Update Makefile (automatic via wildcards)

### Memory Layout
All containers follow this layout:
```c
struct container {
    // metadata fields
    uint8_t size_per_element;
    uint16_t capacity;
    // other fields...
    char elements[]; // flexible array member
};
```

This enables single allocation for both metadata and elements, improving cache locality and reducing allocation overhead.