include $(top_srcdir)/PATHS

EXTRA_DIST=es

JNI_INCLUDE_DIR=include

all: javatrace.jar

javatrace.jar: es/bsc/cepbatools/extrae/Wrapper.java
	$(JAVAC) $(BASE_DIR)/src/java-connector/jni/es/bsc/cepbatools/extrae/Wrapper.java $(BASE_DIR)/src/java-connector/jni/es/bsc/cepbatools/extrae/JavaProbes.java -d .
	$(JAVAH) -d $(JNI_INCLUDE_DIR) -jni es.bsc.cepbatools.extrae.Wrapper es.bsc.cepbatools.extrae.JavaProbes
	$(JAR) cvf javatrace.jar es/bsc/cepbatools/extrae/Wrapper.class es/bsc/cepbatools/extrae/JavaProbes.class

clean-local:
	rm -fr javatrace.jar es/bsc/cepbatools/extrae/Wrapper.class es/bsc/cepbatools/extrae/JavaProbes.class $(JNI_INCLUDE_DIR)

install-data-local: javatrace.jar
	$(MKDIR_P) $(DESTDIR)$(libdir)
	cp javatrace.jar $(DESTDIR)$(libdir)

uninstall-local:
	rm $(DESTDIR)$(libdir)/javatrace.jar
