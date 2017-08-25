all:
	cd nv/maple/C; $(MAKE)

test:
	cd nv/maple/C; $(MAKE) test

clean:
	cd nv/maple/C; $(MAKE) clean

veryclean:
	cd nv/maple/C; $(MAKE) veryclean

tar:veryclean
	cd ..;tar cvfz /tmp/call_FGb.linux.x64.tar.gz call_FGb

.PHONY:tar
