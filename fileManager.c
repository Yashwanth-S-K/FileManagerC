#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
    #include <direct.h>     // For _mkdir on Windows
    #include <windows.h>    // For listing directories and files on Windows
    #define mkdir(folder_name, mode) _mkdir(folder_name)  // Ignore mode on Windows
    #define chdir _chdir     // For changing directories on Windows
#else
    #include <sys/stat.h>   // For mkdir on Unix/Linux
    #include <sys/types.h>
    #include <dirent.h>     // For listing directories and files on Unix/Linux
    #include <unistd.h>     // For changing directories on Unix/Linux
#endif

// Function to create a folder
void create_folder(const char *folder_name) {
    if (mkdir(folder_name, 0777) == 0) {  // Mode 0777 is for Unix-like systems, ignored on Windows
        printf("Folder '%s' created successfully.\n", folder_name);
    } else {
        perror("Error creating folder");
    }
}

// Function to create a file
void create_file(const char *file_name) {
    FILE *file = fopen(file_name, "w");
    if (file) {
        printf("File '%s' created successfully.\n", file_name);
        fclose(file);
    } else {
        perror("Error creating file");
    }
}

// Function to edit (append to) a file
void edit_file(const char *file_name) {
    FILE *file = fopen(file_name, "a");
    if (!file) {
        perror("Error opening file for editing");
        return;
    }

    printf("Enter text to append to the file (end with Ctrl+D or Ctrl+Z on Windows):\n");
    char ch;
    while ((ch = getchar()) != EOF) {
        fputc(ch, file);
    }

    printf("File '%s' edited successfully.\n", file_name);
    fclose(file);
}

// Function to delete a file or folder
void delete_file(const char *file_name) {
    if (remove(file_name) == 0) {
        printf("File or folder '%s' deleted successfully.\n", file_name);
    } else {
        perror("Error deleting file/folder");
    }
}

// Function to list all files and folders in the current directory
void list_directory_contents() {
    printf("\n--- Contents of current directory ---\n");

#ifdef _WIN32
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile("*", &findFileData); // Find first file/folder in the directory

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("No contents found.\n");
        return;
    } else {
        do {
            printf("%s\n", findFileData.cFileName);
        } while (FindNextFile(hFind, &findFileData) != 0);

        FindClose(hFind);
    }
#else
    DIR *d;
    struct dirent *dir;
    d = opendir("."); // Open the current directory
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    } else {
        perror("Unable to open directory");
    }
#endif
}

// Function to change directory (enter subdirectory)
void enter_directory(const char *folder_name) {
    if (chdir(folder_name) == 0) {
        printf("Entered directory '%s'.\n", folder_name);
    } else {
        perror("Error entering directory");
    }
}

// Function to navigate back to the parent directory
void go_back() {
    if (chdir("..") == 0) {
        printf("Moved back to the parent directory.\n");
    } else {
        perror("Error moving back to the parent directory");
    }
}

int main() {
    int choice;
    char name[100];

    while (1) {
        // List the contents before each user interaction
        list_directory_contents();

        // Menu options for the file manager
        printf("\nFile Manager Menu:\n");
        printf("1. Create Folder\n");
        printf("2. Create File\n");
        printf("3. Edit File\n");
        printf("4. Delete File/Folder\n");
        printf("5. Enter Directory\n");
        printf("6. Go Back to Parent Directory\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // To consume the newline character after entering choice

        switch (choice) {
            case 1: // Create folder
                printf("Enter folder name: ");
                fgets(name, sizeof(name), stdin);
                name[strlen(name) - 1] = '\0';  // Remove newline character
                create_folder(name);
                break;
            case 2: // Create file
                printf("Enter file name: ");
                fgets(name, sizeof(name), stdin);
                name[strlen(name) - 1] = '\0';  // Remove newline character
                create_file(name);
                break;
            case 3: // Edit file
                printf("Enter file name to edit: ");
                fgets(name, sizeof(name), stdin);
                name[strlen(name) - 1] = '\0';  // Remove newline character
                edit_file(name);
                break;
            case 4: // Delete file/folder
                printf("Enter file or folder name to delete: ");
                fgets(name, sizeof(name), stdin);
                name[strlen(name) - 1] = '\0';  // Remove newline character
                delete_file(name);
                break;
            case 5: // Enter directory
                printf("Enter directory name to enter: ");
                fgets(name, sizeof(name), stdin);
                name[strlen(name) - 1] = '\0';  // Remove newline character
                enter_directory(name);
                break;
            case 6: // Go back to parent directory
                go_back();
                break;
            case 7: // Exit
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
