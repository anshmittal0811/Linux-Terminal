# Linux Terminal

A custom interactive Linux terminal implementation developed in C, utilizing various system calls to provide core terminal functionality.

## 🚀 Features

This terminal supports the following built-in commands:

- **`cd`** - Change directory
- **`mkdir`** - Create directories
- **`rm`** - Remove files and directories
- **`cat`** - Display file contents
- **`history`** - Show command history
- **`echo`** - Display text
- **`exit`** - Exit the terminal
- **`pwd`** - Print working directory

## 🛠️ Technical Implementation

The terminal is built using fundamental Linux system calls:

- **`fork()`** - Create child processes for command execution
- **`getcwd()`** - Get current working directory
- **`wait()`** - Wait for child processes to complete
- **`exec()`** family - Execute commands
- **`chdir()`** - Change directory operations

## 📋 Prerequisites

- Linux operating system
- GCC compiler
- Make utility (optional)

## 🔧 Installation & Usage

### Clone the Repository
```bash
git clone https://github.com/anshmittal0811/Linux-Terminal.git
cd Linux-Terminal
```

### Compile the Program
```bash
gcc -o terminal main.c
```

### Run the Terminal
```bash
./terminal
```

## 💻 Usage Examples

```bash
# Navigate directories
$ pwd
/home/user

$ cd Documents
$ pwd
/home/user/Documents

# Create and manage files/directories
$ mkdir test_folder
$ echo "Hello World" > test.txt
$ cat test.txt
Hello World

# View command history
$ history
1. pwd
2. cd Documents
3. mkdir test_folder
4. echo "Hello World" > test.txt
5. cat test.txt

# Exit the terminal
$ exit
```

## 🏗️ Architecture

The terminal follows a simple architecture:

1. **Command Parser** - Parses user input and identifies commands
2. **Process Management** - Uses `fork()` to create child processes
3. **Built-in Commands** - Implements core commands directly
4. **External Commands** - Executes system programs via `exec()`
5. **History Management** - Maintains command history

## 📝 Supported Command Details

| Command | Description | Example |
|---------|-------------|---------|
| `pwd` | Print current working directory | `pwd` |
| `cd <path>` | Change directory | `cd /home/user` |
| `mkdir <name>` | Create directory | `mkdir newfolder` |
| `rm <file>` | Remove file | `rm file.txt` |
| `cat <file>` | Display file contents | `cat readme.txt` |
| `echo <text>` | Display text | `echo "Hello World"` |
| `history` | Show command history | `history` |
| `exit` | Exit terminal | `exit` |

## 🔍 Implementation Details

### Process Flow
1. Display prompt
2. Read user input
3. Parse command and arguments
4. Check if command is built-in
5. If built-in: execute directly
6. If external: fork() → exec() → wait()
7. Update history
8. Repeat

### Memory Management
- Dynamic memory allocation for command storage
- Proper cleanup of child processes
- History buffer management

## 👨‍💻 Author

**Ansh Mittal** - [anshmittal0811](https://github.com/anshmittal0811)

## 📚 Learning Outcomes

This project demonstrates:
- Understanding of Linux system calls
- Process management in Unix-like systems
- Command-line interface development
- C programming best practices
- Memory management in C

## 🐛 Known Issues

- Limited error handling for edge cases
- Basic command parsing (may not handle complex arguments)
- No support for pipes or redirection

## 🔮 Future Enhancements

- [ ] Add support for command pipes (`|`)
- [ ] Implement input/output redirection (`>`, `<`)
- [ ] Add tab completion
- [ ] Implement job control (background processes)
- [ ] Add more built-in commands (`ls`, `grep`, etc.)
- [ ] Improve error handling and user feedback

---

*This project was created as a learning exercise to understand Linux system programming and terminal implementation.*
