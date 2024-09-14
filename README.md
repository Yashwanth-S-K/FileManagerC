# FileManagerC

# File Manager in C

This project is a simple file manager system written in C that allows users to create folders, create and edit files, delete files or folders, and navigate through directories using the terminal.

## Features

- **Create Folder**: Create a new folder in the current directory.
- **Create File**: Create a new file in the current directory.
- **Edit File**: Append text to an existing file.
- **Delete File/Folder**: Delete a specified file or folder.
- **List Directory Contents**: Automatically list all files and folders in the current directory before every operation.
- **Enter Directory**: Navigate into a subdirectory to view its contents.
- **Go Back**: Move back to the parent directory from a subdirectory.
  
## Prerequisites

To compile and run this program, you need:

- **C Compiler** (GCC recommended)
- **Git** (to clone the repository and manage source code)

## How to Compile

### On Linux/Unix-based systems:
Compile the C program using GCC:

bash

gcc fileManager.c -o fileManager

Run the program:

bash

    ./fileManager

On Windows:

    Download and install MinGW or Cygwin to get a GCC-compatible environment.
    Clone the repository and navigate to the project folder:

    bash

git clone https://github.com/Yashwanth-S-K/FileManagerC.git
cd FileManagerC

Compile the program:

bash

  gcc fileManager.c -o fileManager.exe

Run the program:

bash

  fileManager.exe



License

This project is open-source and available under the MIT License. See the LICENSE file for more details.
