# CS351 Project B - Mini Query Engine

## Overview

This project implements a simple in-memory query engine in C++.

The query engine can load CSV files into memory and execute basic SQL-like SELECT queries. The goal of this project is to demonstrate fundamental concepts of data loading, parsing, query processing, and software testing using modern development tools such as CMake and GitHub Actions.

---

## Features

- Load CSV files into memory using the `LOAD` command
- Query all columns using `SELECT *`
- Query specific columns using `SELECT column1, column2`
- Display query results in a tabular format
- Handle invalid table names
- Handle invalid column names
- Automated build and test using GitHub Actions

---

## Getting Started

### Prerequisites

The following software is required:

- C++17 compatible compiler
  - GCC
  - Clang
  - MSVC
- CMake 3.10 or newer
- Git (optional)

Verify installation:

```bash
g++ --version
cmake --version
```

### Building

Clone the repository:

```bash
git clone <repository-url>
cd 11402_CS351_ProjectB
```

Configure the project:

```bash
cmake -B build
```

Build the executable:

```bash
cmake --build build
```

---

### Usage

Run the program:

#### Windows

```powershell
.\build\Debug\QueryEngine.exe
```

#### Linux / macOS

```bash
./build/QueryEngine
```

Example commands:

```text
LOAD input

SELECT * FROM input

SELECT name, age FROM input

HELP

EXIT
```

---

## Implementation Details

### Data Storage

The system stores tables in memory using an `unordered_map`:

```cpp
unordered_map<string, Table> database;
```

Each table contains:

- Column names
- Row data

```cpp
struct Table {
    vector<string> columns;
    vector<vector<string>> rows;
};
```

### CSV Loading

The `LOAD` command:

1. Opens the specified CSV file
2. Reads the header row as column names
3. Reads the remaining rows as data records
4. Stores the table in memory

### Query Processing

The `SELECT` command supports:

```text
SELECT * FROM table_name

SELECT column1, column2 FROM table_name
```

The parser:

1. Identifies the `FROM` keyword
2. Extracts requested columns
3. Finds corresponding column indices
4. Displays matching data

### Error Handling

The system reports errors for:

- Missing files
- Invalid table names
- Invalid column names
- Incorrect query syntax

---

## Testing

### Manual Test Cases

#### Test Case 1: Load CSV File

Input:

```text
LOAD input
```

Expected Result:

```text
Success: Successfully loaded table 'input'
```

---

#### Test Case 2: Query All Columns

Input:

```text
SELECT * FROM input
```

Expected Result:

All columns and rows are displayed.

---

#### Test Case 3: Query Specific Columns

Input:

```text
SELECT name, age FROM input
```

Expected Result:

Only the selected columns are displayed.

---

#### Test Case 4: Invalid Column

Input:

```text
SELECT address FROM input
```

Expected Result:

```text
Error: Column 'address' not found.
```

---

#### Test Case 5: Invalid Table

Input:

```text
SELECT name FROM student
```

Expected Result:

```text
Error: Table 'student' does not exist.
```

---

### Automated Testing

Automated testing is implemented using GitHub Actions.

Workflow file:

```text
.github/workflows/build.yml
```

The workflow automatically:

1. Configures the project with CMake
2. Builds the executable
3. Runs predefined test commands from:

```text
tests/test_input.txt
```

GitHub Actions verifies that the project can be successfully built and executed on every push and pull request.

---