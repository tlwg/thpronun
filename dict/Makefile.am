SUBDIRS = tests

AM_CPPFLAGS = -I. -I$(top_srcdir) $(LIBDATRIE_CFLAGS)

noinst_LTLIBRARIES = libdict.la

libdict_la_SOURCES = \
	dict.h		\
	dict.inl	\
	dict.cxx	\
	$(NULL)

libdict_la_LIBADD = \
	$(LIBDATRIE_LIBS)	\
	$(NULL)

bin_PROGRAMS = gen-lookup-dict

gen_lookup_dict_SOURCES =	\
	gen-lookup-dict.c	\
	$(NULL)

gen_lookup_dict_LDADD = \
	$(LIBDATRIE_LIBS)	\
	$(NULL)
