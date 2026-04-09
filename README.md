# Project B - CSV Mini Database & Query Engine
## Overview

A lightweight CSV parsing and query engine that handles complex data formats including quoted fields and special characters. This project demonstrates fundamental database concepts through a practical implementation.

## Features

- **Robust CSV Parser**: Handles quoted fields, escaped characters, and various delimiters
- **Query Engine**: Basic SQL-like operations for data retrieval and filtering
- **Lightweight Design**: Minimal dependencies with optional library support
- **Error Handling**: Graceful handling of malformed CSV data

## Getting Started

### Prerequisites

- C++17 or later
- Optional: vcpkg or Conan for dependency management

### Building

```bash
mkdir build
cd build
cmake ..
make
```

### Usage

```cpp
#include "csv_parser.h"

CSVParser parser("data.csv");
auto results = parser.query("SELECT * WHERE id > 10");
```

## Implementation Details

The parser handles:
- Quoted field values with commas
- Escaped quotes within fields
- Custom delimiters
- Empty fields and trailing whitespace

## Testing

Run the test suite:

```bash
./test_csv_engine
```