CXXFLAGS=-Wall
CC=$(CXX)

PROGRAMS=albumlister
OBJECTS=album.o track.o

ALLOBJECTS=$(OBJECTS) $(patsubst %,%.o,$(PROGRAMS))

default: $(PROGRAMS)

%.d: %.cc
	$(SHELL) -ec '$(CXX) -MM $(CXXFLAGS) $< | \
	perl -pe '"'"'s|($*\.o)[ :]*|\1 $@: |g'"'"' > $@'

albumlister: $(OBJECTS)

clean:
	-rm -f $(ALLOBJECTS) $(ALLOBJECTS:%.o=%.d) $(PROGRAMS)

include $(ALLOBJECTS:%.o=%.d)
