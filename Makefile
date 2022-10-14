OBJCPY = objcopy

screensaver: main.c
	$(CC) -o screensaver main.c -g -l X11 $(CFLAGS)
	$(OBJCPY) --only-keep-debug screensaver screensaver.dbg
	chmod -x screensaver.dbg
	$(OBJCPY) --strip-unneeded screensaver

clean:
	$(RM) screensaver*

.PHONY: clean

