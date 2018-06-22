pkgdata_DATA = \
	except.dic	\
	$(NULL)

EXCEPT_SRC = \
	ex-elong.tsv	\
	ex-karan.tsv	\
	ex-montho-d.tsv	\
	ex-misc.tsv	\
	ex-multi-end.tsv	\
	ex-tone.tsv	\
	ex-tr-so.tsv	\
	$(NULL)

EXTRA_DIST = \
	$(EXCEPT_SRC)	\
	$(NULL)

CLEANFILES = \
	except.tsv	\
	except.dic	\
	$(NULL)

except.tsv: $(EXCEPT_SRC)
	cat $^ | LC_ALL=C sort -u > $@

except.dic: except.tsv
	$(top_builddir)/dict/gen-lookup-dict $< $@
