build:
	gcc jinit.c -o jinit

clean:
	rm -f jinit 

there:
	make del
	mkdir te
	gcc jinit.c -o te/jinit

del:
	rm -dfr te/

