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

Shen-C is implemented as an interpreter, mainly tested on macOS (Apple Silicon) using Clang.

Besides macOS (Apple Silicon), Ubuntu 20.04 LTS (x86_64/AArch64) is a minor supported OS.

The [iOS version of Shen-C](https://chatolab.wordpress.com/2017/07/10/shen-programming-language-for-ios/) is available on the App Store, which is a full featured Shen REPL with a customized keyboard for both iPhone and iPad.

Other ports of Shen by the Shen-C author includes
* [Shen-JVM](https://github.com/otabat/shen-jvm)
* [Shen for Android](https://chatolab.wordpress.com/2017/12/26/shen-programming-language-for-android/), which is a full featured Shen REPL with a customized keyboard for Android on Google Play


## Installation
1. Download a release build from [releases](https://github.com/otabat/shen-c/releases)
2. Unarchive a release build
```
tar xvf shen-c-{VERSION}-{OS}-{ARCH}.tar.gz
```


## Usage
1. Run Shen-C REPL from a release build

Run the shell script under the build directory.
```
cd shen-c-{VERSION}-{OS}-{ARCH}
./shen-c
```

2. Quit Shen-C REPL

Pass an exit status
```
(exit 1)
```


## Build from source
1. Install the required softwares

For macOS install [Boehm GC](http://www.hboehm.info/gc/) by [Homebrew](https://brew.sh/) or from [sources](http://www.hboehm.info/gc/gc_source/)
```
  brew install libgc
```

For Linux (Ubuntu)

Install `make`
```
sudo apt install make
```

Install [Clang](http://releases.llvm.org/download.html)
```
sudo apt install clang
```

Install [Boehm GC](http://www.hboehm.info/gc/)
```
sudo apt install libgc-dev
```

2. Change directory to the project root

3. Build Shen-C

To build a non-release build
```
make
```
A binary file named `shen-c` will be created under the `bin` directory.

To build a release build
```
make release
```
A release build will be created under the `release` directory.


## Run non-release build

There are several ways to run a non-release build.

* Run the shell script under the project root.
```
./shen-c
```

* Run Shen-C REPL by using the make command
```
make repl
```
or if rlwrap is installed
```
make rrepl
```

* Run Shen-C REPL from a compiled binary

Set the `SHEN_C_HOME` environment variable to the project root for a Unix shell
```
export SHEN_C_HOME=/path/to/shen-c
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


## Learn Shen
* [Official website of Shen](http://shenlanguage.org/)
* [The Shen OS Kernel Manual](http://shenlanguage.org/learn-shen/index.html)
* [The Official Shen Standard](http://www.shenlanguage.org/learn-shen/shendoc.htm)
* [Shen Community Wiki](https://github.com/Shen-Language/wiki/wiki)
* [The Book of Shen: third edition](https://www.amazon.co.uk/Book-Shen-Third-Mark-Tarver/dp/1784562130)


## License

#### Shen
Copyright (c) 2010-2022, Mark Tarver  
Shen is released under the [BSD License](https://github.com/otabat/shen-c/tree/master/shen/LICENSE.txt).  

#### Shen-C
Copyright (c) 2022, Tatsuya Tsuda
Shen-C is released under the [MIT License](http://www.opensource.org/licenses/MIT).
