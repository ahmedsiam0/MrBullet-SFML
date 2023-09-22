AC_INIT([mr-bullet], [1.0], [none])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_PROG_AR
LT_INIT
AC_PROG_CXX
AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
AC_CONFIG_MACRO_DIRS([m4])

PKG_CHECK_MODULES(SFML, [sfml-graphics, sfml-window, sfml-system, sfml-audio, sfml-network], CPPFLAGS="$CPPFLAGS $SFML_CFLAGS"; LIBS="$LIBS $SFML_LIBS")

AC_OUTPUT
