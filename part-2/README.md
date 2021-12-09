# Debugging

So far, you could debug your programs by looking really hard at the program and thinking your way out of the problem. (Or you ask your instructor for help and magically the problem was identified and resolved.)

Imagine the sorts of problems that you may encounter in the future. Are these problems that you can ask someone for help and they'll readily know how to help you make progress towards your goal?

This is an unlikely scenario. What is more likely is that you'll need to experiment and observe your program in order to understand how the program's behavior is as expected or is completely unexpected. Differentiating the behavior of your program means first understanding what is the correct behavior, otherwise distinguishing between the expected and unexpected is impossible.

The programmer has at their disposal a very powerful tool. It is the [debugger](https://en.wikipedia.org/wiki/Debugger). With a debugger, a programmer can monitor and control how a program executes. While the programming is running, the programmer can pause the program, look at the values stored in the variables, and verify that the program is behaving as expected.

Since we're using [`clang++`](https://en.wikipedia.org/wiki/Clang), we'll use the [`lldb`](https://en.wikipedia.org/wiki/LLDB_(debugger)). Both of these tools are part of the [LLVM](https://en.wikipedia.org/wiki/LLVM) project. (If we were using `g++` we would use the `gdb` debugger.)

Before starting, familiarize yourself with `lldb` by reading the short [LLDB Tutorial](https://lldb.llvm.org/use/tutorial.html).

Let's start with a program we can easily understand. Imagine you have the following program saved in a file named hello.cc. (A copy of this program is provided at the root of the repository.)


```c++
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
  int x = 42;
  cout << "Hello World\n";
  int y = x + 10;
  cout << "X is " << x << "\n";
  cout << "Y is " << y << "\n";
  return 0;
}
```

Using the command `clang++ -g -std=c++14 hello.cc -o hello` we can compile the program.

To run the program, we could use the command `./hello`. The output will look like the following:

```
$ clang++ -g -std=c++14 hello.cc -o hello
$ ./hello
Hello World
X is 42
Y is 52
```

If we'd like to use the debugger, we'd use the `lldb` command to load our program and then run our program. The output may look a little like the following.

```
$ lldb hello
(lldb) target create "hello"
Current executable set to '/tmp/hello' (x86_64).
(lldb) run
Process 22762 launched: '/tmp/hello' (x86_64)
Hello World
X is 42
Y is 52
Process 22762 exited with status = 0 (0x00000000) 
(lldb) quit
$ 
```

Setting a breakpoint is an important skill to develop. A breakpoint is a place in our program where the debugger will pause our program while it is executing. This allows us to look at the values stored in variables and monitor how our program has executed.

Remember we had a program named `hello.cc` and the contents of the file looks like the listing below. Line numbers have been added to help illustrate how breakpoints work.

```c++
   1  #include <iostream>
   2  
   3  using namespace std;
   4  
   5  int main(int argc, char const *argv[]) {
   6    int x = 42;
   7    cout << "Hello World\n";
   8    int y = x + 10;
   9    cout << "X is " << x << "\n";
  10    cout << "Y is " << y << "\n";
  11    return 0;
  12  }
```

After loading our program into `lldb`, we can set a breakpoint at any given line by specifying the filename and line number. In cases where there is only 1 C++ source file, like in this case, then you can omit the filename.

```
$ lldb hello
(lldb) target create "hello"
Current executable set to '/tmp/hello' (x86_64).
(lldb) breakpoint set --file hello.cc --line 9
Breakpoint 1: where = hello`main + 54 at hello.cc:9:11, address = 0x00000000004011f6
(lldb) run
Process 22820 launched: '/tmp/hello' (x86_64)
Hello World
Process 22820 stopped
* thread #1, name = 'hello', stop reason = breakpoint 1.1
    frame #0: 0x00000000004011f6 hello`main(argc=1, argv=0x00007fffffffe538) at hello.cc:9:11
   6   	  int x = 42;
   7   	  cout << "Hello World\n";
   8   	  int y = x + 10;
-> 9   	  cout << "X is " << x << "\n";
   10  	  cout << "Y is " << y << "\n";
   11  	  return 0;
   12  	}
(lldb) print x
(int) $0 = 42
(lldb) print y
(int) $1 = 4198608
(lldb) next
Process 22820 stopped
* thread #1, name = 'hello', stop reason = step over
    frame #0: 0x00000000004011ff hello`main(argc=1, argv=0x00007fffffffe538) at hello.cc:10:8
   7   	  cout << "Hello World\n";
   8   	  int y = x + 10;
   9   	  cout << "X is " << x << "\n";
-> 10  	  cout << "Y is " << y << "\n";
   11  	  return 0;
   12  	}
(lldb) print y
(int) $2 = 52
(lldb) continue
Process 22820 resuming
X is 42
Y is 52
Process 22820 exited with status = 0 (0x00000000) 
(lldb) quit
```

In the above lldb session, following steps occur:

1. lldb is started and it loads the program hello
1. A breakpoint is set at line 9 in the file hello.cc
1. The program is run within lldb; it stops at the breakpoint
1. The value of x is printed
1. The value of y is printed and it isn't what was expected
1. lldb is instructed to continue to the `next` line and wait
1. The value of y is printed again and it matches what we expect
1. lldb is told to `continue` and the program is unpaused; it continues executing until it reaches the end
1. To exit lldb, the `quit` command is used

Try using lldb on your older programs to see what you can do with lldb. Try to find out how to do the following actions:

* Set a breakpoint in different files
* Set a breakpoint whenever a specific function is called
* Set a watchpoint which will pause the program anytime a specific variable's value changes
* Print out a backtrace which will show all the functions that have been called and in what order

In this exercise, the program you have been given has some bugs. Using your whits, your compiler, and your debugger, find and squash the bugs in the program. Turn the error filled program into a beautiful and correct program.


## Requirements

The program takes three arguments to generate a series of random numbers. The first two arguments are the minimum and maximum values for the range of randome numbers and the third is how many random numbers to generate.

The random numbers are stored in a C++ vector. The values are printed to the terminal and the average, median and mode are calculated and printed.

Correct any errors and address any compiler warnings.

To compile your program, you use the `make` command. A Makefile is provided for this exercise.

The Makefile has the following targets:

* all: builds the project
* clean: removes object and dependency files
* spotless: removes everything the clean target removes and all binaries
* format: outputs a [`diff`](https://en.wikipedia.org/wiki/Diff) showing where your formatting differes from the [Google C++ style guide](https://google.github.io/styleguide/cppguide.html)
* lint: output of the [linter](https://en.wikipedia.org/wiki/Lint_(software)) to give you tips on how to improve your code
* header: check to make sure your files have the appropriate header
* test: run tests to help you verify your program is meeting the assignment's requirements. This does not grade your assignment.
* unittest: run unit tests to verify parts of your program performs according to the instructor supplied unit tests.

## Inline Documentation
The project is thoroughly documented inline using the [Doxygen](https://en.wikipedia.org/wiki/Doxygen) format. The documentation establishes a framework for you to follow so that you can implement all the details of the program. To generate HTML formatted documents to view on your computer use the make target `doc`.

The inline documentation is saved in `doc/html`. To view the documentation, use the command `gio open doc/html/index.html` which will open the index file in your web browser.

Another benefit of documenting your code is that when you use an editor like Visual Studio Code, it can show you the documentation when you point your mouse's cursor at a function name.

## Don't Forget

Please remember that:

- You need to put a header in every file.
- You need to follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
- Remove the `TODO` comments.

## Testing Your Code

Computers only ever do exactly what they are told, exactly the way they are told it, and never anything else. Testing is an important process to writing a program. You need to test for the program to behave correctly and test that the program behaves incorrectly in a predictable way.

As programmers we have to remember that there are a lot of ways that we can write the wrong program and only one to a few ways to write the correct program. We have to be aware of [cognitive biases](https://en.wikipedia.org/wiki/List_of_cognitive_biases) that we may exercise that lead us to believe we have correctly completed our program. That belief may be incorrect and our software may have errors. [Errors in software](https://www.wired.com/2005/11/historys-worst-software-bugs/) may lead to loss of [life](https://www.nytimes.com/2019/03/14/business/boeing-737-software-update.html), [property](https://en.wikipedia.org/wiki/Mariner_1), [reputation](https://en.wikipedia.org/wiki/Pentium_FDIV_bug), or [all of the above](https://en.wikipedia.org/wiki/2009%E2%80%9311_Toyota_vehicle_recalls).

### Test strategy

Start simple, and work your way up. Good tests are specific, cover a broad range of fundamentally different possibilities, can identify issues quickly, easily, and directly, without need for much set up, and can almost be diagnosed by inspection if the code fails to execute the test correctly.

## Example Output

Please ensure your program's output is identical to the example below.

```
$ make
set -e; clang++ -MM -g -O3 -Wno-return-type -pipe -std=c++14 -D LINUX -D AMD64 utility.cc \
| sed 's/\(utility\)\.o[ :]*/\1.o utility.d : /g' > utility.d; \
[ -s utility.d ] || rm -f utility.d
set -e; clang++ -MM -g -O3 -Wno-return-type -pipe -std=c++14 -D LINUX -D AMD64 rng.cc \
| sed 's/\(rng\)\.o[ :]*/\1.o rng.d : /g' > rng.d; \
[ -s rng.d ] || rm -f rng.d
set -e; clang++ -MM -g -O3 -Wno-return-type -pipe -std=c++14 -D LINUX -D AMD64 analyze.cc \
| sed 's/\(analyze\)\.o[ :]*/\1.o analyze.d : /g' > analyze.d; \
[ -s analyze.d ] || rm -f analyze.d
clang++ -g -O3 -Wno-return-type -pipe -std=c++14 -D LINUX -D AMD64 -c analyze.cc
clang++ -g -O3 -Wno-return-type -pipe -std=c++14 -D LINUX -D AMD64 -c rng.cc
clang++ -g -O3 -Wno-return-type -pipe -std=c++14 -D LINUX -D AMD64 -c utility.cc
clang++ -g -O3 -Wno-return-type -pipe -std=c++14 -o analyze analyze.o rng.o utility.o 
$ ./analyze 1 5 10
analyze: malloc.c:2379: sysmalloc: Assertion `(old_top == initial_top (av) && old_size == 0) || ((unsigned long) (old_size) >= MINSIZE && prev_inuse (old_top) && ((unsigned long) old_end & (pagesize - 1)) == 0)' failed.
Aborted (core dumped)
$ lldb ./analyze
(lldb) target create "./analyze"
Current executable set to '/tmp/cpsc-120-solution-lab-13/part-2/analyze' (x86_64).
(lldb) run 1 5 10
Process 17323 launched: '/tmp/cpsc-120-solution-lab-13/part-2/analyze' (x86_64)
analyze: malloc.c:2379: sysmalloc: Assertion `(old_top == initial_top (av) && old_size == 0) || ((unsigned long) (old_size) >= MINSIZE && prev_inuse (old_top) && ((unsigned long) old_end & (pagesize - 1)) == 0)' failed.
Process 17323 stopped
* thread #1, name = 'analyze', stop reason = signal SIGABRT
    frame #0: 0x00007ffff7abd18b libc.so.6`raise + 203
libc.so.6`raise:
->  0x7ffff7abd18b <+203>: movq   0x108(%rsp), %rax
    0x7ffff7abd193 <+211>: xorq   %fs:0x28, %rax
    0x7ffff7abd19c <+220>: jne    0x7ffff7abd1c4            ; <+260>
    0x7ffff7abd19e <+222>: movl   %r8d, %eax
(lldb) 
```

