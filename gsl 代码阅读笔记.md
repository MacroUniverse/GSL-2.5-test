* GSL 是一个纯 C library， 但再 C++ 中可以调用， 因为如果 `__cplusplus` 宏有定义， 头文件会自动在声明中加入 `extern "c"`
* 用 Understand 快速决定 dependency



* Understand 里面每个文件右键的 Graphical Views-> Cluster Call 可以看到这个文件中调用的函数的定义在哪些其他文件中。 大部分应该是定义在 `.c` 文件中， inline function 有可能定义在头文件中。 可惜不能多级展开
* 一些 `.c` 文件其实是用于被 include 的而不是用于单独编译
* 不同文件夹中会有同名文件， 搜索的时候要注意不要选错

* 如果需要在程序中使用一个函数， 就先在 eneity filter 中找到这个函数， 查看所在的 `.c` 文件， 然后再用 cluster call 一层层地看 dependency 就好。 把所有依赖的 `.c` 文件先添加到 VS 的工程中（或 Makefile 中）， 就可以试着编译了。 编译有可能出错， 因为有些 `.c` 文件是被 include 而不能单独编译。 但这些文件的特征很明显， 例如上来就定义函数， 没有任何 include。 把这些函数排除掉以后应该就可以编译成功了。


## Dependency Tree
* 如果把这个 tree 放在 Makefile 中， 编译的时候只会编译需要的 `.c` 文件， 不需要的不会编译
* 为了方便， 头文件以及用于 include 的 `c` 文件不会出现在树种。 如果不去改 gsl 源码， 省略他们其实没什么问题。
* 注意其中有 circular dependency， make 的时候可能会给出警告。 但这种 circular dependency 的确存在， 所以去掉反而不妥。
* 我们把 tree 的每一行进行排序， 越往上的 `o` 文件的定义必须出现在所有使用的上方（circular denpendency 除外）

stream.o: stream.c
error.o: error.c stream.o
log.o: log.c  error.o
pow_int.o: pow_int.c error.o
trig.o: trig.c log.o error.o
math.o: math.c
fdiv.o: fdiv.c
infnan.o: infnan.c fdiv.o
coerce.o: coerce.c
elementary.o: elementary.c coerce.o error.o
exp.o: exp.c error.o gamma.o
zeta.o: zeta.c exp.o error.o gamma.o elementary.o
psi.o: psi.c math.o exp.o error.o infnan.o gamma.o zeta.o
gamma.o: gamma.c  log.o exp.o error.o psi.o trig.o
poch.o: poch.c log.o exp.o error.o gamma.o pow_int.o psi.o
bessel_temme.o: bessel_temme.c 
bessel_amp_phase.o: bessel_amp_phase.c
bessel.o: bessel.c exp.o error.o poch.o bessel_amp_phase.o gamma.o elementary.o bessel_temme.o
bessel_J1.o: bessel_J1.c  error.o bessel.o
airy.o: airy.c err.o trig.o
airy_der.o: airy_der.c exp.o error.o
airy.o: airy.c cheb_evalZ_mode.o error.o trig.o
bessel_olver.o: bessel_olver.c  airy_der.o airy.o error.o
bessel_J0.o: bessel_J0.c  error.o bessel.o
bessel_Jn.o: bessel_Jn.c bessel_J1.o error.o bessel.o bessel_olver.o bessel_J0.o
legendre_poly.o: legendre_poly.c log.o error.o poch.o bessel_Jn.o bessel_J0.o
laguerre.o: laguerre.c error.o exp.o gamma.o
coulomb_bound.o: coulomb_bound.c error.o exp.o laguerre.o gamma.o pow_int.o
