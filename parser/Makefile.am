SUBDIRS = tests

AM_CPPFLAGS = -I. -I$(top_srcdir) $(LIBTHAI_CFLAGS)

lib_LTLIBRARIES = libparser.la

libparser_la_SOURCES = \
	parser.h	\
	parser.cxx	\
	$(NULL)

libparser_la_LIBADD = \
	$(top_builddir)/sylstring/libsylstring.la	\
	$(LIBTHAI_LIBS)	\
	$(NULL)

