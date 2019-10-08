[参考资料](https://coral.ise.lehigh.edu/jild13/2016/07/11/hello/): gsl 通常的使用方法是先安装，生成 include 文件夹 (含有所有头文件) 和 lib 文件夹 (.so 文件以及 .a 文件). 先下载最新版安装包, 目前是 `gsl-2.5.tar.gz`, 解压命令 `tar -xvzf gsl-2.5.tar.gz`, 得到 gsl-2.5 文件夹, `cd gsl-2.5`, 然后 `./configure --prefix=安装目录` 其中安装目录只能是绝对目录. 然后 `sudo make`, 安装好以后 `sudo make check` 检查, 然后 `sudo make install` 即可. 只有最后一步会在安装目录中生成文件.

如果 `make check` 出了问题， 可以根据提示具体看一看 log 文件， 之前出错时因为 sh 文件权限问题， 用 `sudo chmod +x *` 即可

```c
// example.c
#include <stdio.h>
#include <gsl/gsl_sf_bessel.h>

int main (void) {
    double x = 15.0;
    double y = gsl_sf_bessel_J0 (x);
    printf ("J0(%g) = %.18e\n", x, y);
    return 0;
}
```
要编译, 用
```
gcc -Wall -I 安装目录/include/ -c example.c
```
要 link, 用
```
gcc test.o -Wl,-rpath,安装目录/lib -L 安装目录/lib -lgsl -lgslcblas -lm
```
其中 gsl 包含所有 gsl 的函数, gslcblas 提供了一个 cblas, 但也可以用其他更优化的如 ATLAS 提供的, m 是编译器的 math library.

## 以下试图使用 apt 直接安装 gsl
* 使用 `sudo apt-get install libgsl` 再按两次 tab 即可显示所有相关包
* 安装完后用 `locate libgsl.so` 或者 `locate libgsl` 就能找到所有 `so` 文件（貌似找不到 `a` 文件）， 只好放弃

## 源码再利用
gsl 完全是 c 语言写的, 所以 cuda 应该也是以用的, 但是不能用编译好的 a 和 so, 而是要重新由源码编译. 即使不用 cuda, 直接使用源码也可以让代码更 portable.

用 understand 分析了一下 `bessel` 和 `3j` symbol 两个函数, 发现如果不修改代码, 要找到编译某个函数需要的所有文件真的很难, 至少有几十个文件. 其中有一个比较特殊的文件是 `config.h`, 应该是要运行安装包的 config 以后才会生成的.

我觉得可以把所有的头文件和 c 文件都放在一个文件夹里面, 然后做一个类似 SCID_TDSE 的 makefile, 自动分析出 dependency. 不过 c 和 fortran 不同， 要做到自动还是很有难度的. 不知道 understand 有没有这个功能. 如果不行, 干脆就所有 c 文件都编译? 又或许安装包里的 makefile 已经有 dependency list 了.

然后又发现 gsl 安装的就是所谓的 two-step process: configure followed by make.

![](gsl源码笔记1.png)

用 git 对比了一下安装过程的源码, 发现安装过程并不会改变任何源码(.c 和 .h 文件), 只会根据系统生成 "config.h", 其实也可以直接手动修改该文件, 主要是一些宏的定义和取消, 注释非常易懂. 所以理论上, 只要把所有源码文件都放到一起编译就可以了.
