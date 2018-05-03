SUBDIRS = tests

AM_CPPFLAGS = -I. -I$(top_srcdir)

noinst_LTLIBRARIES = libsylstring.la

libsylstring_la_SOURCES = \
	sylcomp.cxx	\
	sylcomp.h	\
	sylcomp.inl	\
	syl.h		\
	syl.inl		\
	sylstring.h	\
	sylstring.inl	\
	sylout-thai.h		\
	sylout-thai.cxx		\
	sylout-roman.h		\
	sylout-roman.cxx	\
	sylout-phonetic.h	\
	sylout-phonetic.cxx	\
	sylstrout-delim.h	\
	sylstrout-delim.inl	\
	sylstrout-delim.cxx	\
	sylstrout-roman.h	\
	sylstrout-roman.inl	\
	sylstrout-roman.cxx	\
	sylstrout-json.h	\
	sylstrout-json.inl	\
	sylstrout-json.cxx	\
	$(NULL)

libsylstring_la_LIBADD = \
	$(top_builddir)/thortho/libthortho.la	\
	$(NULL)

