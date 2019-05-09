# Shen-C

Shen-C is a C port of the [Shen](http://shenlanguage.org/) programming language.  

Shen is a portable functional programming language developed by [Mark Tarver](http://marktarver.com/) that offers
* Pattern matching
* Lambda calculus consistency
* Macros for defining domain specific languages
* Optional lazy evaluation
* Optional static type checking based on [Sequent calculus](https://en.wikipedia.org/wiki/Sequent_calculus)
* An integrated fully functional Prolog
* An inbuilt compiler-compiler, Shen-YACC

Shen-C is implemented as an interpreter, mainly tested on Linux (Ubuntu 18.04) using Clang.

The [iOS version of Shen-C](https://chatolab.wordpress.com/2017/07/10/shen-programming-language-for-ios/) is available on the App Store, which is a full featured Shen REPL with a customized keyboard for both iPhone and iPad.

Other ports of Shen by the Shen-C author includes
* [Shen-JVM](https://github.com/otabat/shen-jvm)
* [Shen for Android](https://chatolab.wordpress.com/2017/12/26/shen-programming-language-for-android/), which is a full featured Shen REPL with a customized keyboard for Android on Google Play

## Installation for Linux
1. Install [Clang](http://releases.llvm.org/download.html)

2. Install [Boehm GC](http://www.hboehm.info/gc/)

3. Change directory to the project root

4. Compile Shen-C
```
make
```
A binary file named `shen-c` will be created under the `project_root/bin` directory.

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


## Learn Shen
* [Official website of Shen](http://shenlanguage.org/)
* [The Shen OS Kernel Manual](http://shenlanguage.org/learn-shen/index.html)
* [The Official Shen Standard](http://www.shenlanguage.org/learn-shen/shendoc.htm)
* [Shen Community Wiki](https://github.com/Shen-Language/wiki/wiki)
* [The Book of Shen: third edition](https://www.amazon.co.uk/Book-Shen-Third-Mark-Tarver/dp/1784562130)


## License

#### Shen
Copyright (c) 2010-2015, Mark Tarver  
Shen is released under the [BSD License](https://github.com/otabat/shen-c/tree/master/src/shen/license.txt).  

#### Shen-C
Copyright (c) 2017, Tatsuya Tsuda  
Shen-C is released under the [MIT License](http://www.opensource.org/licenses/MIT).
