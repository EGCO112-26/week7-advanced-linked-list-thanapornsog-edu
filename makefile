compile: ll_example.c ll.c
	 @gcc ll_example.c ll.c -o mylist

run: mylist
	 @./mylist

clean:
	 rm mylist