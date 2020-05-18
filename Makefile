TARGETS=cidr gethostbyname ipconvert ipgen iplist2cidr iprand
PREFIX:=/usr/local

.PHONY: clean all

all: $(TARGETS)

clean:
	rm $(TARGETS)

install: all
	install $(TARGETS) $(PREFIX)/bin/
