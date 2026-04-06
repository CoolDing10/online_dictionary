cc:=gcc


union_test:union_test.c
	-$(cc) -o $@ $^
	-./$@
	-rm ./$@