# Makefile from: http://scottmcpeak.com/autodepend/autodepend.html

CFLAGS = -std=c99 -Wpedantic -Wall -Wshadow -Wextra

PROJECT = test_naive
OBJS := ../../fifo.o test_naive.o

# Link
$(PROJECT): $(OBJS)
	gcc $(OBJS) -o $(PROJECT)

# Pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

# Rompile and generate dependency info;
# more complicated dependency computation, so all prereqs listed
# will also become command-less, prereq-less targets
#   sed:    strip the target (everything before colon)
#   sed:    remove any continuation backslashes
#   fmt -1: list words one per line
#   sed:    strip leading spaces
#   sed:    add trailing colons
%.o: %.c
	gcc -c $(CFLAGS) $*.c -o $*.o
	gcc -MM $(CFLAGS) $*.c > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

# Remove compilation products
clean:
	rm -f $(PROJECT) *.o *.d ../../*.o ../../*.d
