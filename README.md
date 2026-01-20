# Automated Logical Reasoning System

## 📌 Project Overview

This project is an **Automated Logical Reasoning System** developed as part of my **Discrete Mathematics course** in the **first semester**.
It uses basic programming concepts in **C++** to evaluate logical expressions and perform reasoning tasks automatically.

The system works on propositional logic expressions written using variables and logical operators.

---

## ✨ Features

* Generate **Truth Tables** for logical expressions
* Check **Logical Equivalence** between two expressions
* **Save** results to a file
* **View / Load** previously saved results

---

## 🧠 Supported Logic

* Variables: `A` to `Z`
* Operators:

  * `!`  → NOT
  * `&`  → AND
  * `|`  → OR
  * `>`  → Implication
  * `=`  → Equivalence
* Parentheses `( )` are supported
* Maximum of **5 variables** per expression

---

## ⚙️ How It Works

1. The input logical expression is first **validated**.
2. It is converted from **infix notation to postfix notation** using stacks.
3. The postfix expression is evaluated for all possible combinations of variables.
4. Based on this, truth tables are generated or equivalence is checked.

---

## 📂 Menu Options

1. Generate Truth Table
2. Check Logical Equivalence
3. View / Load Saved Results
4. Exit

---

## 🛠 Technologies Used

* **C++**
* Stack-based expression evaluation
* File handling (`fstream`)
* Console-based user interface

---

## 🚀 Learning Outcome

This project helped me strengthen my understanding of:

* Discrete logic and truth tables
* Stack operations
* Expression parsing
* Problem-solving and logical thinking
* File handling in C++

It was one of the **most challenging and rewarding projects of my first semester**.

---

## 📌 How to Run

1. Compile the code using a C++ compiler:

   ```
   g++ main.cpp -o logic_system
   ```
2. Run the program:

   ```
   ./logic_system
   ```

---

## 📄 Notes

* Input expressions must follow the supported syntax.
* Invalid expressions are automatically rejected.
* Results can be saved and viewed later using text files.

---

## 🙌 Author

**Muhammad Bin Ijaz**
Software Engineering Student

---

⭐ If you found this project helpful or interesting, feel free to star the repository!
