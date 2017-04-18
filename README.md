# Shen-C

Shen-C is a C port of the [Shen](http://shenlanguage.org/) programming language.  

Shen-C is implemented in C99 currently as an interpreter, mainly tested on macOS using Clang. It should also work using GCC.


## Installation for macOS

1. Install [Boehm GC](https://www.hboehm.info/gc/)
```
  brew install libgc
```

2. Change directory to the project root

3. Compile Shen-C
```
make
```  
A binary file named `shen-c` will be created under the `project_root/bin` directory.  


## Installation for other platforms
Install [Boehm GC](https://www.hboehm.info/gc/), and change the [Makefile](https://github.com/otabat/shen-c/tree/master/Makefile) to match the platform.


## Usage

1. Run Shen-C REPL
```
make repl
```
or if rlwrap is installed
```
rlwrap make repl
```

2. Quit Shen-C REPL
```
(quit)
```
or
```
(exit)
```


## License

#### Shen
Copyright (c) 2010-2015, Mark Tarver  
Shen is released under the [BSD License](https://github.com/otabat/shen-c/tree/master/src/shen/license.txt).  

#### Shen-C
Copyright (c) 2017, Tatsuya Tsuda  
Shen-C is released under the [MIT License](http://www.opensource.org/licenses/MIT).
