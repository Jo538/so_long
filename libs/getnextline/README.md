# Get Next Line

*A 42 School project by jchartie*

## 📋 Overview

The **get_next_line** project is a function that reads and returns a line from a file descriptor, one line at a time. This project teaches efficient buffer management, static variables, and file I/O operations in C.

### Function Prototype

```c
char *get_next_line(int fd);
```

### Return Values

- **Read line**: Returns the line that was read, including the terminating `\n` character (except when EOF is reached and the line doesn't end with `\n`)
- **NULL**: Returned when there is nothing left to read or an error occurred

## 🎯 Key Features

- Reads from file descriptors and standard input
- Configurable buffer size via compilation flag
- Uses static variables to maintain state between function calls
- Memory-efficient: reads only as needed, not the entire file at once

## 📁 Project Structure

```
.
├── get_next_line.c         # Core implementation
├── get_next_line_utils.c   # Helper functions
├── get_next_line.h         # Header file with prototypes
└── README.md               # This file
```

### File Descriptions

- **get_next_line.c**: Contains the main `get_next_line()` function that orchestrates reading, buffering, and returning lines
- **get_next_line_utils.c**: Contains utility functions such as `ft_strlen()`, `ft_strchr()`, `ft_strjoin()`, etc.
- **get_next_line.h**: Header file with function prototypes and necessary library includes

## 🔧 Compilation

The project must compile successfully both with and without the `-D BUFFER_SIZE` flag to define the buffer size for `read()`.

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl_test
```

## 💻 Usage

### Basic Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Reading from Standard Input

```c
#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
    char *line;

    while (get_next_line(0) != NULL)  // 0 = stdin
    {
        printf("You entered: %s", line);
        free(line);
    }
    return (0);
}
```

## ⚙️ Implementation Details

The function uses a **static variable** to preserve data between successive calls, allowing it to:
- Store unprocessed characters from previous reads
- Handle lines that span multiple buffer reads

### Algorithm Overview

1. **Error checking**: Validates file descriptor and buffer size
2. **Reading**: Reads from the file descriptor in chunks of `BUFFER_SIZE` bytes
3. **Line extraction**: Searches for `\n` character to identify line boundaries
4. **Buffer management**: Stores remaining data for the next function call
5. **Return**: Returns the extracted line or NULL if EOF/error

## 🚫 Constraints & Requirements

### Requirements
- Must work with files and standard input
- Must handle varying `BUFFER_SIZE` values (including 1, 9999, 10000000)
- Undefined behavior if the file changes between calls
- Undefined behavior when reading binary files (bonus handling optional)
- Memory leaks are not tolerated

## 🧪 Testing

Test the function with:
- Different buffer sizes (1, 42, 9999, 10000000)
- Various file types (empty files, files without `\n`, large files)
- Standard input
- Multiple file descriptors
- Edge cases (very long lines, single character files)

## 📚 Resources

- [42 Subject PDF](https://cdn.intra.42.fr/pdf/pdf/188916/en.subject.pdf)
- [File Descriptors in C](https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/)
- [Using read() in C](https://www.educative.io/answers/read-data-from-a-file-using-read-in-c)

## 🤖 AI Assistance

AI tools were used to:
- Understand advanced concepts around stdin, stdout, and stderr data streams
- Develop comprehensive testing strategies
- Debug edge cases and optimize buffer management
- Help write the README.md 
