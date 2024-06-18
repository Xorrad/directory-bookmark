# Directory Bookmark

A utility tool to bookmark directories (only works for linux) and open those directories in the file explorer.

## Installation

```
git clone https://github.com/Xorrad/directory-bookmark.git && cd directory-bookmark
```
```
make
```
```
sudo mv ./bin/dbm /usr/bin/
```

## Usage

```
Usage: dbm [OPTION]... BOOKMARK...
Open, create and delete directory bookmarks.

  -a, --add   add a new bookmark
  -d, --delete   delete a new bookmark, if it exists
  -l, --list   list all saved bookmarks
  -h, --help   display this help and exit
```

## License

This project is licensed under the MIT License - see the [LICENSE](https://raw.githubusercontent.com/Xorrad/directory-bookmark/master/LICENSE) file for details.