/****************************************************************************
*                                                                           *
*   DBM : a utility tool to bookmark directories (in linux).                *
*                                                                           *
*   Made by Xorrad <monsieurs.aymeric@gmail.com>                            *
*   This code is licensed under MIT license (see LICENSE for details)       *
*                                                                           *
****************************************************************************/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <filesystem>

using Arguments = std::vector<std::string>;

// Global variables.
const std::string FILE_PATH = std::string(getenv("HOME")) + "/.bookmarks";
std::map<std::string, std::string> BOOKMARKS;

// Utility functions
Arguments ParseArgs(int argc, char* argv[]);

// Bookmarks functions.
std::string GetCurrentDirectory();
void LoadBookmarks();
void SaveBookmarks();
void OpenBookmark(std::string name);

// Commands functions.
void DisplayHelp();

int main(int argc, char* argv[]) {
    Arguments args = ParseArgs(argc, argv);

    if(args.size() == 0) {
        printf("dbm: missing operand\n");
        printf("Try 'dbm --help' for more information.\n");
        return 0;
    }

    LoadBookmarks();
        
    if(args[0] == "-h" || args[0] == "--help") {
        DisplayHelp();
        return 0;
    }
    
    if(args[0] == "-a" || args[0] == "--add") {
        if(args.size() < 2) {
            printf("dbm: missing operand after '%s'\n", args[0].c_str());
            printf("Try 'dbm --help' for more information.\n");        
            return 0;
        }
        // Replace or add bookmark to list
        // then save to the file.
        std::string path = GetCurrentDirectory();
        BOOKMARKS[args[1]] = path;
        SaveBookmarks();
        printf("dbm: bookmark '%s' saved successfully\n", args[1].c_str());
        return 0;
    }
    
    if(args[0] == "-d" || args[0] == "--delete") {
        if(args.size() < 2) {
            printf("dbm: missing operand after '%s'\n", args[0].c_str());
            printf("Try 'dbm --help' for more information.\n");        
            return 0;
        }
        std::string name = args[1];
        if(BOOKMARKS.count(name) == 0) {
            printf("dbm: cannot remove '%s' : No such bookmark\n", name.c_str());
            return 0;
        }
        BOOKMARKS.erase(name);
        SaveBookmarks();
        printf("dbm: bookmark '%s' deleted successfully\n", name.c_str());
        return 0;
    }
    
    if(args[0] == "-l" || args[0] == "--list") {
        for(auto [name, path] : BOOKMARKS) {
            printf("%s\t%s\n", name.c_str(), path.c_str());
        }
        return 0;
    }


    if(args[0][0] == '-') {
        printf("dbm: invalid option '%s'\n", args[0].c_str());
        printf("Try 'dbm --help' for more information.\n");
        return 0;
    }

    std::string name = args[0];
    
    if(BOOKMARKS.count(name) == 0) {
        printf("dbm: cannot open '%s' : No such bookmark\n", name.c_str());
        return 0;
    }
    OpenBookmark(name);

    return 0;
}

Arguments ParseArgs(int argc, char* argv[]) {
    Arguments args;
    // Skip executable path by starting at 1.
    for(int i = 1; i < argc; i++) {
        args.push_back(argv[i]);
    }
    return args;
}

std::string GetCurrentDirectory() {
    char buffer[FILENAME_MAX];
    getcwd(buffer, FILENAME_MAX);
    return std::string(buffer);
}

void LoadBookmarks() {
    std::ifstream file(FILE_PATH);
    if(!file) {
        return;
    }
    std::string bookmark;
    std::string path;
    while(file >> bookmark >> path) {
        BOOKMARKS[bookmark] = path;
    }
    file.close();
}

void SaveBookmarks() {
    // Could be improved to avoid rewritting the entire file each time.
    std::ofstream file(FILE_PATH);
    if(!file) {
        printf("dbm: error: failed to save bookmarks file\n");
        exit(1);
    }
    for(auto [name, path] : BOOKMARKS) {
        file << name << " \"" << path << "\"" << std::endl;
    }
    file.close();
}

void OpenBookmark(std::string name) {
    // Open the file explorer at the bookmark's directory.
    std::string path = BOOKMARKS[name];
    std::string command = "nautilus -w " + path + " &";
    system(command.c_str());
}

void DisplayHelp() {
    printf("Usage: dbm [OPTION]... BOOKMARK...\n");
    printf("Open, create and delete directory bookmarks.\n\n");
    printf("  -a, --add   add a new bookmark\n");
    printf("  -d, --delete   delete a new bookmark, if it exists\n");
    printf("  -l, --list   list all saved bookmarks\n");
    printf("  -h, --help   display this help and exit\n\n");
    printf("Official repository: <https://github.com/Xorrad/directory-bookmark/>\n");
}