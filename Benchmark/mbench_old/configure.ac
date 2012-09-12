AC_INIT([mbench], [0.2])
LT_INIT
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CC
AC_PROG_LEX
AC_PROG_YACC
AC_PROG_LIBTOOL
AM_PROG_AS

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
	Makefile
	src/Makefile
	src/lib/Makefile
	src/compiler/Makefile
	src/compiler/mbench_bc], [chmod +x src/compiler/mbench_bc])

AC_CHECK_FUNCS([strdup alloca malloc realloc gethostname getpagesize])
AC_CHECK_FUNCS([gettimeofday mkdir strstr])
AC_C_INLINE
AC_CHECK_HEADERS([malloc.h stdint.h stdlib.h string.h stddef.h libintl.h])
AC_CHECK_HEADERS([sys/ioctl.h])

AC_TYPE_UINT64_T
AC_TYPE_SIZE_T
AC_FUNC_ALLOCA
AC_FUNC_MALLOC
AC_FUNC_REALLOC

AC_OUTPUT
