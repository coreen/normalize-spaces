Generate executable via
```
gcc -Wall -g -std=c11 -o tabReplace tabReplace.c fileProcessing.c replacement.c
gcc -Wall -g -std=c11 -o spaceReplace spaceReplace.c fileProcessing.c replacement.c
```

Run with
```
./tabReplace
./spaceReplace
```


Test file execution with `server.py`

Sample Test Output
```
$ ./spaceReplace
please enter the number of spaces a TAB character should equal: 
	3
do you want trailing spaces after TAB conversion to be dropped? [Y/N]: 
	N
leaving spaces in conversion requested
what type of input will be provided? [F(ile)/S(tdin)]: 
	F
please enter the input file to process: 
	server.py
how should output be formatted? [I(nline)/E(xternal File)]: 
	E
please enter the output file to process: 
	test.py
```

See test.py for the example output