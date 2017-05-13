# Shen-C

Shen-C is a C port of the [Shen](http://shenlanguage.org/) programming language.  

Shen-C is implemented in C99 currently as an interpreter, mainly tested on macOS using Clang. Should also work with GCC.


## Installation for macOS

1. Install [Boehm GC](http://www.hboehm.info/gc/) by [Homebrew](https://brew.sh/) or from [sources](http://www.hboehm.info/gc/gc_source/)
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
Install [Boehm GC](http://www.hboehm.info/gc/), and change the [Makefile](https://github.com/otabat/shen-c/tree/master/Makefile) to match the platform.


## Usage

1. Run Shen-C REPL by using make command
```
make repl
```
or if rlwrap is installed
```
make rrepl
```

2. Run Shen-C REPL directly  
Set the `SHEN_C_HOME` environment variable to the Shen-C project root  
If you are using bash for a Unix shell  
```
export SHEN_C_HOME=/home/user/shen-c
```
and then
```
alias shen-c='$SHEN_C_HOME/bin/shen-c'
```
or if rlwrap is installed
```
alias shen-c='rlwrap $SHEN_C_HOME/bin/shen-c'
```
and finally
```
shen-c
```

3. Quit Shen-C REPL
```
(quit)
```
or with an exit status
```
(exit 1)
```


## License

#### Shen
Copyright (c) 2010-2015, Mark Tarver  
Shen is released under the [BSD License](https://github.com/otabat/shen-c/tree/master/src/shen/license.txt).  

#### Shen-C
Copyright (c) 2017, Tatsuya Tsuda  
Shen-C is released under the [MIT License](http://www.opensource.org/licenses/MIT).
