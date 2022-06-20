atomic:=TestAndSet
#atomic:=CompareAndExchange
#atomic:=ExchangeAndAdd
#atomic:=LoadLinkedAndStoreConditional

block:=Spin
#block:=Yield
#block:=Wait

defines:=-D$(atomic) -D$(block)

objs:=$(atomic).o
vpath %.c Lock/$(shell echo $(MAKE_HOST) | sed 's/[-_].*//')

ccflags:=-pthread
ldflags:=-pthread

include ../../GNUmakefile
