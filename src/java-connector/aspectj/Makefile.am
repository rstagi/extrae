include $(top_srcdir)/PATHS

EXTRAEJ_ASPECTS_DIR=$(DESTDIR)$(libdir)/extraejaspects

install-data-local: 
	$(MKDIR_P) $(EXTRAEJ_ASPECTS_DIR)
	cp -r src/extrae/aspects/* $(EXTRAEJ_ASPECTS_DIR)

uninstall-local:
	rm -r $(EXTRAEJ_ASPECTS_DIR)

