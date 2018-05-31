SUBDIRS = tests

AM_CPPFLAGS = -I. -I$(top_srcdir)

noinst_LTLIBRARIES = liboutput.la

liboutput_la_SOURCES = \
	isyl-output.h		\
	ioutput.h		\
	ioutput.cxx		\
	sylout-thai.h		\
	sylout-thai.cxx		\
	sylout-roman.h		\
	sylout-roman.cxx	\
	sylout-phonetic.h	\
	sylout-phonetic.cxx	\
	sylout-raw.h		\
	sylout-raw.cxx		\
	output-delim.h	\
	output-delim.inl	\
	output-delim.cxx	\
	output-roman.h	\
	output-roman.inl	\
	output-roman.cxx	\
	output-json.h	\
	output-json.inl	\
	output-json.cxx	\
	output-gjson.h		\
	output-gjson.inl	\
	output-gjson.cxx	\
	$(NULL)

liboutput_la_LIBADD = \
	$(top_builddir)/sylstring/libsylstring.la	\
	$(top_builddir)/lattice/liblattice.la		\
	$(NULL)

