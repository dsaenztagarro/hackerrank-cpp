[![Build Status](https://travis-ci.org/dsaenztagarro/hackerrank-cpp.svg?branch=master)](https://travis-ci.org/dsaenztagarro/hackerrank-cpp)

# hackerrank-cpp

Run command: `./bin/compile < test/fixtures/test1.txt`

To show the script to be executed

`make --just-print`

Documentation
-------------

Verify `check` test framework for c is installed locally with: 

```shell
pkg-config --cflags --libs check`
```

[Makefile tricks](http://locklessinc.com/articles/makefile_tricks/)

Book log
--------

- Package check has a bug in Ubuntu platform. Enough to try another unit test framework :(

[Check unit test framework BUG - Ubuntu](https://git.libssh.org/projects/libssh.git/diff/?h=v0-3&id=3ce7d7a28c057bbe72f55d221657fd0d6d54f246&context=2&ignorews=1)
[Ubuntu check package](https://bugs.launchpad.net/ubuntu/+source/check/+bug/125781)

```
+  # check_pic is a workaround for ubuntu's check bug which does not compile
+  # check as a shared library with -fPIC.
+  # see https://bugs.launchpad.net/ubuntu/+source/check/+bug/125781
   find_library(CHECK_LIBRARY
     NAMES
-      check
+      check_pic check
     PATHS
       ${_CHECK_LIBDIR}
```

[Unit test frameworks](https://en.wikipedia.org/wiki/List_of_unit_testing_frameworks#C)


Todo
----

- [ ] Implement queue as linked list
