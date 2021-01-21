</$objtype/mkfile

BIN=$home/bin/$objtype

TARG=chat-fmt

OFILES=chat-fmt.$O

BIN=$home/bin/$objtype

UPDATE=\
	mkfile\
	chat\
	chat-fmt.c

</sys/src/cmd/mkmany

install:V:
	for (i in $TARG)
		mk $MKFLAGS $i.install
	cp chat $home/bin/rc/chat


