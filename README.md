# The Idea

A Fullstack app for dealing with Data Structures and Algorithms, the main purpose of this is educational, so I tried to tackle different patterns and best practices in C++, did not give as much attention to the UI since I focused on learning C++.

# Technologies

## Backend (C++)

- CrowCpp For HTTP API
- Catch2 For Unit Testing
- CPR as an HTTP Client for Integration Testing
- sqlite_orm for Database ORM (SQLite)
- CMake + CPM as Build and Package Managers

## Frontend

- Astro Frontend Framework
- TailwindCSS for CSS
- Axios as an HTTP API Client Library

## Database

- Relational DB SQL (SQLite)

# How to Setup (Running the app locally)

0. Make sure you have installed C++17 (v23 Recommended) or above and NodeJS v20+
1. Build the Server (From Root, in the Terminal)

```
mkdir build
cd build
cmake ..
cmake --build .
```

2. (In Another Terminal [For Better Speed]) Install Frontend Dependencies (From Root, in the Terminal)

```
cd frontend
npm install
```

3. Run the server (From Root, in the Terminal)
   ./build/bin/DSA-CPP (If you are windows add .exe in the end, like DSA-CPP.exe)

4. Run the Frontend (From Root, in the Terminal)

```
cd frontend
npm run dev
```

# Implementations
## Data Structures
- Double-Circular LinkedList
- Queue
- Heap
- Tree
- Stack 


## Naming Conventions

#### PascalCase
- Class
- Namespace
- Struct
- Enum
- Public Methods of a Class or Struct

#### camelCase
- Private Methods of a Class or Struct
- Non-Constant Variables
- Generally All Methods (except a Member of a Class or Struct)

#### snake_case
- CAPITALIZED_SNAKE_CASE for Constants
- small_snake_case for JSON Keys

#### kebab-case
- URL endpoints

#### Pre-fixes
- m_* for Private Members of a Class or Struct (Variables)
- g_* for Global Variables
- s_* for Global Static Variables

## Codebase Statistics
| Language      | files | blank | comment | code |
|---------------|-------|-------|---------|------|
| C/C++ Header  | 18    | 188   | 50      | 758  |
| C++           | 16    | 185   | 129     | 653  |
| JSON          | 4     | 0     | 0       | 36   |
| Astro         | 2     | 2     | 0       | 17   |
| SVG           | 1     | 0     | 0       | 9    |
| JavaScript    | 1     | 2     | 2       | 7    |
| CSS           | 1     | 0     | 0       | 1    |
| **SUM:**      | 43    | 377   | 181     | 1481 |

## Some Confusing Concepts that I learned (in C++) for me :)
- constexpr:
Declares that a value or function can be calculated at compile time. Every constexpr is also const, but not every const is constexpr.
- inline:
Allows a function or variable to be defined in a header file without multiple-definition errors.
Use in defining constants/functions in headers, and want them usable in multiple .cpp files.
Use inline for global constants/functions in headers.
- static:
What it does:
Inside a function → value persists between calls

In global/file scope → value stays private to the file

In class → value is shared across all objects
Use for file-level constants, or shared class values.
- extern:
Says “this variable exists in another file.” You don’t create it here, just refer to it.
Use to share a global variable between .cpp files.
Examples:
in a file.cpp:
```
extern int sharedCount;
```
in another file.cpp:
```
int sharedCount = 0;  // real definition
```
- define:
Replaces code before compilation. Like find-and-replace.
Rarely needed now — prefer const, constexpr, inline.
Not type-safe, and can cause weird bugs.
Examples:
```
  #define PI 3.14
  #define SQUARE(x) ((x)*(x))
```
- typedef:
Creates an alias for a complex type. 
Examples: 
```
typedef unsigned int uint;
```
- using:
Modern, cleaner version of typedef.
Examples:
```
using uint = unsigned int;
```
| Goal                           | Use                              |
| ------------------------------ | -------------------------------- |
| Constant value in a file only  | `static const` or `constexpr`    |
| Global constant (in header)    | `inline constexpr`               |
| Global variable, one file only | `static`                         |
| Global variable, shared        | `extern` in `.h`, real in `.cpp` |
| Reusable constant for template | `constexpr`                      |

| Keyword           | What it Does                  | Use When                      |
| ----------------- | ----------------------------- | ----------------------------- |
| `uint32_t`        | Unsigned 32-bit integer       | You want a specific size      |
| `uint_fast32_t`   | Fastest type ≥ 32-bit         | You want performance          |
| `uint_least16_t`  | Smallest type ≥ 16-bit        | You want minimal memory usage |
| `size_t`          | Unsigned size of object/array | For array indexing or lengths |
| `intmax_t`        | Biggest signed type available | For largest possible values   |
| `typedef`/`using` | Create readable type aliases  | Clean up code                 |

| Type        | Use Case                          |
| ----------- | --------------------------------- |
| `size_t`    | Used for sizes, like array length |
| `ptrdiff_t` | Result of subtracting pointers    |
| `intmax_t`  | Biggest possible signed integer   |
| `uintmax_t` | Biggest possible unsigned integer |

