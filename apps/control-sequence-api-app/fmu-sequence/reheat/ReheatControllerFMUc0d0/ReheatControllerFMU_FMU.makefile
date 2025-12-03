# FIXME: before you push into master...
RUNTIMEDIR=/usr/bin/../include/omc/c/
#COPY_RUNTIMEFILES=$(FMI_ME_OBJS:%= && (OMCFILE=% && cp $(RUNTIMEDIR)/$$OMCFILE.c $$OMCFILE.c))

fmu:
	rm -f 417.fmutmp/sources/ReheatControllerFMU_init.xml
	cp -a "/usr/bin/../share/omc/runtime/c/fmi/buildproject/"* 417.fmutmp/sources
	cp -a ReheatControllerFMU_FMU.libs 417.fmutmp/sources/
