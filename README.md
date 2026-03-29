# Depression Analysts

## Project Overview
Depression Analysts is an interactive C++ and SFML application that lets a user review student lifestyle data, guess whether a featured student has depression, and sort the dataset with **Merge Sort** or **Quick Sort** using selectable table columns such as GPA, Sleep, Study Hours, Social Media, Physical Activity, Stress, and Age.

The program:
- loads student records from a CSV file
- displays one featured student on the left side of the window
- lets the user answer **Yes** or **No** to whether that student has depression
- shows the remaining students in a scrollable table
- allows sorting the table with **Merge Sort** or **Quick Sort**
- reports the runtime of the chosen sorting algorithm

## Repository Structure

```text
headers/
├── student.h
├── Sorters.h
└── scrolling.h

src/
├── main.cpp
├── student.cpp
├── Sorters.cpp
└── scrolling.cpp
```

### File Roles
- `main.cpp` loads the dataset, creates the SFML window, handles user interaction, and runs the main game logic.
- `student.h` / `student.cpp` define the `student` data structure and constructor.
- `Sorters.h` / `Sorters.cpp` contain the sorting enum and the Merge Sort / Quick Sort implementations.
- `scrolling.h` / `scrolling.cpp` implement the scrollable table UI and column-based sort selection.

## Requirements
Before running this project, make sure you have:
- **C++17 or later**
- **SFML 3**
- A compiler such as `g++`, MSVC, or a CLion-supported toolchain
- The dataset file `student_lifestyle_100k.csv`
- The font file `sans.ttf`

## Required File Paths
The current code uses these relative paths:
- CSV file: `../../../../src/student_lifestyle_100k.csv`
- Font file: `../../../../Resources/Google_Sans/sans.ttf`

If your folder structure is different, update those paths in `main.cpp`.

## How to Run

### Option 1: Build with an IDE
Open the project in an IDE such as **Visual Studio** or **CLion**, then:
1. Add all source files to the project:
   - `main.cpp`
   - `student.cpp`
   - `Sorters.cpp`
   - `scrolling.cpp`
2. Add the `headers` folder to your include directories.
3. Link SFML correctly.
4. Make sure the CSV and font paths are valid relative to the executable.
5. Build and run.

### Option 2: Build from the command line with g++
You may need to adjust include and library paths depending on where SFML is installed on your machine.

```bash
g++ -std=c++17 src/main.cpp src/student.cpp src/Sorters.cpp src/scrolling.cpp -Iheaders -o DepressionAnalysts -lsfml-graphics -lsfml-window -lsfml-system
```

Then run:

```bash
./DepressionAnalysts
```

On Windows, run:

```bash
DepressionAnalysts.exe
```

## How to Use the Program
1. Launch the application.
2. A featured student appears on the left side of the window.
3. Click **Yes** or **No** to guess whether the student has depression.
4. Your correct and wrong counts are tracked on screen.
5. The table on the right shows the remaining students.
6. Scroll with the mouse wheel while the cursor is over the table.
7. Click a sortable table header to choose a sorting criterion.
8. Click **Merge Sort** or **Quick Sort** to sort the table using the selected criterion.
9. The program displays the time taken for the selected sorting algorithm.

## Sorting Features
The project supports sorting by:
- GPA
- Age
- Sleep Duration
- Study Hours
- Social Media Hours
- Physical Activity
- Stress Level

The project includes:
- **Merge Sort**
- **Quick Sort**

## Troubleshooting
### CSV file will not load
Check that:
- `student_lifestyle_100k.csv` exists
- the relative path in `main.cpp` matches your machine
- the program is being run from the expected working directory

### Font will not load
Check that:
- `sans.ttf` exists in the expected relative location
- the font path in `main.cpp` is correct

### Window opens but table does not sort
Make sure you clicked a sortable table header first, then clicked either **Merge Sort** or **Quick Sort**.

### SFML linker errors
This usually means:
- SFML is not installed correctly
- include paths are wrong
- library paths are wrong
- the wrong SFML version is being linked

## Authors
Derek Rosales and David Mendoza

