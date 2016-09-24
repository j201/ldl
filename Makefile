BUNDLE = ldl.lv2
SOURCES = $(wildcard *.c)
CFLAGS += -shared -fPIC -std=c99 -I$(LV2_SOURCE_PATH)

.PHONY: clean install check-env

$(BUNDLE) : ldl.so manifest.ttl ldl.ttl
	mkdir -p $(BUNDLE)
	cp ldl.so manifest.ttl ldl.ttl $(BUNDLE)

# TODO: standard way to load source path?
ldl.so : $(SOURCES) check-env
	gcc $(CFLAGS) -o ldl.so $(SOURCES)

clean :
	rm -r $(BUNDLE)
	rm ldl.so

install :
	mkdir -p ~/.lv2
	cp -r ldl.lv2 ~/.lv2

check-env:
ifndef LV2_SOURCE_PATH
	$(error LV2_SOURCE_PATH is undefined)
endif
