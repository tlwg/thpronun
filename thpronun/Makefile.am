SUBDIRS = tests

bin_PROGRAMS = \
	thpronun	\
	$(NULL)

AM_CPPFLAGS = -I$(top_srcdir)
DEFS = -DEXCEPT_DICT_DIR=\"$(pkgdatadir)\" -DVERSION=\"$(VERSION)\"

thpronun_SOURCES = \
	thpronun.cxx	\
	$(NULL)
thpronun_LDADD = \
	$(top_builddir)/parser/libparser.la	\
	$(top_builddir)/output/liboutput.la	\
	$(NULL)

