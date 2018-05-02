SUBDIRS = tests

AM_CPPFLAGS = -I. -I$(top_srcdir)

noinst_LTLIBRARIES = libsylstring.la

libsylstring_la_SOURCES = \
	sylcomp.cxx	\
	sylcomp.h	\
	sylcomp.inl	\
	syl.h		\
	syl.inl		\
	sylstring.cxx	\
	sylstring.h	\
	sylstring.inl	\
	sylout-thai.h		\
	sylout-thai.cxx		\
	sylout-roman.h		\
	sylout-roman.cxx	\
	sylout-phonetic.h	\
	sylout-phonetic.cxx	\
	$(NULL)

libsylstring_la_LIBADD = \
	$(top_builddir)/thortho/libthortho.la	\
	$(NULL)

