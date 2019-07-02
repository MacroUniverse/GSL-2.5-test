* try to use gsl only from source
* "include" and "source" folders should be in the search path
* "include" folder is the "include" folder in gsl installation path
* "source" folder has other source files needed from gsl source
* don't change any of the source files (.c .h) except "configure.h"
* since there are source files with the same names, use subfolders in "source" folder
* some `.c` files are not to be compiled but only to be included, e.g. "legendre_source.c". I suspect these files all have "_source" in file names.
* macro is very useful in c language when defining slightly different functions with different function names, see "legendre_source.c" for example.
