* try to use gsl only from source

# File Directory
* "include" folder is the same as the one in the installation directory
* "source" folder has all other sources needed for compilation

* only "config.h" is system dependent and is generated while installation. The current "config.h" is generated in ksu linux., but also works for Visual Studio.
* Makefile is based on the dependency graph of the Understand app.
