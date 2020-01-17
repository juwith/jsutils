Doxygen
Class
Library
Binary that use library
create pkg-config
use other project pkg-config

How to use  
step 1.  
```
$ ./autogen.sh  
```
step 2.  
```
$ ./configure  
```
 You can use option if necessary.  
step 3. 
```
 $ make  
 $ make install  
```

How to create Doxygen
step 1. make configure file for doxygen
```
$ doxygen -g
```
step 2. modify created 'Doxygen' file
```
$ vi Doxygen
```
step 3. create doc
```
$ doxygen
```