# Mini Shell in C (Linux)

## 📌 Overview
This project implements a simple Linux shell that executes user commands using low-level system calls. It demonstrates process creation, command parsing, and execution similar to Unix shells.

## 🚀 Features
- Execute external commands (ls, pwd, etc.)
- Built-in commands (cd, exit)
- Command parsing with arguments
- Process creation using fork()
- Command execution using execvp()
- Parent-child synchronization using wait()

## 🛠️ Technologies Used
- C Programming
- Linux System Calls (fork, execvp, wait)
- Process Management
- String Parsing

## ⚙️ How It Works
- Reads user input
- Parses command and arguments
- Creates child process using fork()
- Executes command using execvp()
- Parent waits for execution to complete

## 🧪 Usage

### Compile
