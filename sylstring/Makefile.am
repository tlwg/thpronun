SUBDIRS = tests

AM_CPPFLAGS = -I. -I$(top_srcdir)

noinst_LTLIBRARIES = libsylstring.la

libsylstring_la_SOURCES = \
	sylcomp.cxx	\
	sylcomp.h	\
	sylcomp.inl	\
	sylstring.cxx	\
	sylstring.h	\
	sylstring.inl	\
	$(NULL)

libsylstring_la_LIBADD = \
	$(top_builddir)/thortho/libthortho.la	\
	$(NULL)

