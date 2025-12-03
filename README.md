# Arbitrary Precision Calculator (APC)

The **Arbitrary Precision Calculator (APC)** is a C-based project that performs arithmetic on integers of *unlimited size*. It bypasses standard data-type limits by storing numbers using a **doubly linked list** structure.

## 🚀 Features

* Supports **very large integers**
* Operations: **Addition**, **Subtraction**, **Multiplication**, **Division**
* **Doubly linked list** implementation for efficient digit handling
* Input numbers are provided via **command-line arguments**
* Modular code with separate `.c` files for each operation

## 📂 Project Structure

```
├── main.c
├── apc.h
├── dll.c
├── addition.c
├── subtraction.c
├── multiplication.c
├── division.c
└── README.md
```

## 🛠️ How It Works

* Each digit of the large number is stored as a node in a **DLL**
* Operations mimic manual arithmetic but at unlimited precision
* Output is displayed without any loss of accuracy

## ▶️ Usage

Compile:

```bash
gcc *c 
```

Run with two large numbers and an operator:

```bash
./a.out <num1> <operator> <num2>
```

### Example:

```bash
./a.out 987654321987654321 + 123456789123456789
```

## 📌 Applications

* Cryptography
* High-precision mathematical computing
* Competitive programming
* Educational tool for linked-list arithmetic

## 🤝 Contributions

Feel free to open issues or submit pull requests to improve functionality or add new features.

---
