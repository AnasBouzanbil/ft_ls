# ft_ls

A custom implementation of the classic UNIX `ls` command, written in C. This project is a popular programming exercise (often part of the 42 School curriculum) designed to teach about the UNIX filesystem, system calls, and manipulating data structures in C.

##  Features

`ft_ls` supports the following standard `ls` flags:

- `-l`: Use a long listing format, displaying file permissions, number of links, owner, group, size, and timestamp.
- `-a`: Do not ignore entries starting with `.` (hidden files).
- `-r`: Reverse the order of the sort.
- `-t`: Sort by modification time, newest first.
- `-R`: List subdirectories recursively.

It also supports parsing multiple directories and files passed as arguments.

## 🛠️ Getting Started

### Prerequisites

- `gcc` compiler
- `make` utility

### Installation

1. Clone the repository:
   ```bash
   git clone <your-repo-url>
   cd ft_ls
   ```

2. Compile the project using `make`:
   ```bash
   make
   ```
   This will generate the `ft_ls` executable.

### Usage

Run the compiled executable with or without flags and directory paths:

```bash
# Basic usage
./ft_ls

# With flags
./ft_ls -la

# Specific directories
./ft_ls -lR /path/to/directory
```

### Makefile Rules

The included `Makefile` provides the following commands:
- `make`: Compiles the project.
- `make clean`: Removes the object files (if any).
- `make fclean`: Removes the executable.
- `make re`: Recompiles the entire project from scratch.

## 📁 Project Structure

- `main.c`: Entry point and core logic.
- `parse.c`: Parses the command-line arguments and flags.
- `manipulation.c` & `Helper.c`: Handles directory traversal, file data extraction, and utility functions.
- `print.c`: Handles the formatting and display of the output.
- `ft_ls.h` / `ft_ls_struct.h`: Header files defining the data structures and function prototypes.

## About

This project is built to understand how the operating system interacts with files and directories through standard library functions like `opendir`, `readdir`, `lstat`, and more.
