# Directory Bookmark

A utility tool to bookmark directories (only works for Ubuntu) and open those directories in the file explorer.

## Installation

```
git clone https://github.com/Xorrad/directory-bookmark.git
cd directory-bookmark
make
sudo mv ./bin/dbm /usr/bin/dbm
```

Or in one command:
```
git clone https://github.com/Xorrad/directory-bookmark.git && cd directory-bookmark && make && sudo mv ./bin/dbm /usr/bin/dbm
```

## Usage

```
Usage: dbm [OPTION]... BOOKMARK...
       dbm <TEXT>

Open a directory in the file explorer using a bookmark.
Note that only Ubuntu (with nautilus) is supported as of now.

Create and delete bookmarks pointing to directory.

  -a, --add   add a new bookmark
  -d, --delete   delete a bookmark, if it exists
  -l, --list   list all saved bookmarks
  -h, --help   display this help and exit
```

## License

This project is licensed under the MIT License - see the [LICENSE](https://raw.githubusercontent.com/Xorrad/directory-bookmark/master/LICENSE) file for details.