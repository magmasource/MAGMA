#!/bin/sh

if [ -x "$(command -v easyMelts)" ] && [ "$(command -v easyMelts.command)" == "$0" ]; then
    # Special case, double-clicked file in Path ($PWD contains home space, window 1 is easyMelts.command location)
    # Adapted from https://alvinalexander.com/ and https://stackoverflow.com/questions/23923017/
    if [ "$PWD" == "$HOME" ]; then

	osascript -e 'on run(argv)' \
		  -e 'tell application "Finder"' \
		  -e 'set myWin to window 1' \
		  -e 'set thePath to (quoted form of POSIX path of (target of myWin as alias))' \
		  -e 'end tell' \
		  -e 'if (thePath as String) = (quoted form of POSIX path of item 1 of argv as String) then' \
		  -e 'tell application "Terminal"' \
		  -e 'activate' \
		  -e 'do script "cd " & thePath & "; mkdir -p tables; easyMelts"' \
		  -e 'end tell' \
		  -e 'else' \
		  -e 'tell application "Terminal"' \
		  -e 'activate' \
		  -e 'do script "easyMelts"' \
		  -e 'end tell' \
		  -e 'end if' \
		  -e 'end' \
		  -- "$(dirname $0)/"
    else
	mkdir -p tables;
	easyMelts;
    fi
else
   cd $(dirname $0);
   mkdir -p tables;
   ./easyMelts;
fi

