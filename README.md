## Extracts SMART data from disk  

This outputs a dump of SMART data, given a diskname at argument.  

Dependency: This sits on top of the libatasmart library.  

## How to Use  

`libtool --mode=link gcc -g -0 -o test test.c libatasmart.la`  
`sudo ./test /dev/sda`  


