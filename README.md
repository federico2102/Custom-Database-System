# C++ Database Management Framework

## Project Overview
This project is an implementation of a basic database management system (DBMS) designed to handle core database functionalities such as adding tables, inserting records, searching with criteria, and ensuring data integrity through key checks and type validation. The project focuses on developing an efficient, modular system in C++ that handles memory management and complex data structures.

## Technologies Used
- **Programming Language**: C++
- **Standard Libraries**: `<vector>`, `<string>`, `<algorithm>`
- **Custom Header Files**: `BaseDatos.h`, `Tabla.h`, `Registro.h`

## Key Functionalities
### 1. **Table and Record Management**
- **Table Creation and Deletion**: Implementation of functions to create and delete tables, ensuring proper memory management.
- **Record Insertion**: Validation checks to ensure records can be added only if they adhere to the table’s schema and unique constraints.
- **Search Functionality**: Ability to search records based on complex criteria, filtering results dynamically.

### 2. **Data Integrity and Type Validation**
- **Field Type Matching**: Verifies that data types in records match the table schema to prevent type conflicts.
- **Key Uniqueness**: Ensures that no duplicate keys are present when adding new records.
- **Set Operations**: Utilizes helper functions to validate field sets and enforce integrity constraints.

### 3. **Memory Management**
- **Dynamic Allocation**: Proper use of `new` and `delete` to manage dynamic memory for tables and records.
- **Destructor Implementation**: Custom destructors to prevent memory leaks when tables and records are removed.

### 4. **Algorithmic Problem-Solving**
- **Efficient Searching and Filtering**: Implements searching algorithms to apply criteria and filter records efficiently.
- **Comparison Operators**: Custom operators (`==`, `!=`) for database equality checks, ensuring data consistency.
- **Use of STL**: Leveraged the Standard Template Library (STL) for data manipulation and iteration.

## Skills Demonstrated
### 1. **Memory Management in C++**
- Implemented constructors and destructors to handle dynamic memory allocation and prevent leaks.
- Ensured proper deletion of nested data structures and pointers.

### 2. **Modular Code Design**
- Designed a modular structure with classes and functions that promote readability and maintainability.
- Split functionality across multiple headers and source files to adhere to clean coding practices.

### 3. **Complex Data Structures**
- Used vectors and tuples to manage tables and records.
- Implemented logic for set comparisons and type validations.

### 4. **Algorithmic Thinking**
- Applied efficient search algorithms for filtering data according to user-defined criteria.
- Managed key uniqueness and data validation using algorithmic checks and helper functions.

## Getting Started
To begin, download the code from this repository. This can be done either directly using Git or by downloading the project as a zip file. The recommended method is using Git as explained below:

```bash
git clone https://git.exactas.uba.ar/mmiguel/aed2-2c2017-tp1.git
```

### Running the Project in CLion (Optional)
1. In CLion, go to **File -> Import Project** and select "Open Project."
2. Once the project loads, select "correrTests" from the top right corner.
3. Click the **Play** button to run the tests.

### Running Tests from the Command Line
```bash
mkdir build && cd build
cmake ..
make
./correrTests
```
To recompile, simply run `make` again.

If the compilation fails, delete the `build` directory and repeat the above steps.

---
