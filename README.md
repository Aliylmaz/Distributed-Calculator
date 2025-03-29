

### 📌 README.md

```markdown
# 🧮 Multi-Process Calculator with Pipes in C

This project is a **terminal-based calculator** written in **C** using **UNIX system calls** like `fork()`, `pipe()`, and `execlp()`.

The calculator supports:
- Addition
- Subtraction
- Multiplication
- Division

Each operation is handled by a **dedicated subprocess**, and results are saved in a `results.txt` file automatically by the subprocesses (not the main process).

---

## 🚀 How It Works

1. **Main Program (`calculator.c`)**
   - Displays a menu and gets two numbers from the user.
   - Sends the numbers to the corresponding subprocess through a pipe.
   - Receives the result back via the same pipe and prints it on the terminal.

2. **Subprocesses (`addition.c`, `subtraction.c`, etc.)**
   - Read the numbers from the pipe.
   - Perform the operation.
   - Send the result back to the parent through the pipe.
   - **Also save the result to `results.txt`** using file system calls.

3. **No `dup`, `dup2`, or `STDIN_FILENO` are used**, in accordance with system programming constraints.

---

## 📁 File Structure

```
.
├── calculator.c
├── addition.c
├── subtraction.c
├── multiplication.c
├── division.c
├── results.txt     # Automatically generated
├── Makefile        # (Optional) You can add a makefile to compile all
└── README.md
```

---

## 🛠️ Compilation

You can compile the files individually using `gcc`:

```bash
gcc -o calculator calculator.c
gcc -o addition addition.c
gcc -o subtraction subtraction.c
gcc -o multiplication multiplication.c
gcc -o division division.c
```

---

## ▶️ Running

```bash
./calculator
```

---

## 🧾 Example Output

```
========================================
          Welcome to Calculator         
========================================
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Exit
========================================
Enter your choice: 1
Enter two numbers (e.g., 10 5): 12 7

========================================
             ***** RESULT *****         
Addition Result: 12 + 7 = 19
========================================
```

The same result is also saved to `results.txt` automatically.

---

## 🔒 Constraints Met

- ✔ No use of `dup`, `dup2`, or `STDIN_FILENO`
- ✔ Each subprocess performs its own calculation
- ✔ Saver logic is implemented **inside subprocesses**
- ✔ Results are passed via pipes
- ✔ Modular and clean architecture

---

## 👨‍💻 Author

https://github.com/Aliylmaz

---

## 📜 License

This project is open source and free to use under the MIT License.
```

