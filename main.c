#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>

#define equals(x, y)  (strcmp(x, y) == 0)

#define VERSION   "v1.0"

int main(int argc, char **argv)
{
  const char *display_str = NULL;
  bool activate = false,
       reset = false;

  // Arg-parsing
  for(int i = 1; i < argc; i++)
  {
    if(equals(argv[i], "-h"))
    {
      puts(
            "Options:\n\n"
            "\t-v\tPrint version and exit\n\n"
            "\t-d\tOpen given display\n\n"
            "\t-a\tActivate screensaver\n\n"
            "\t-r\tReset/Disable Screensaver\n\n"
            "sudo200 and contributors 2022"
          );
      return EXIT_FAILURE;
    }
    else if(equals(argv[i], "-v"))
    {
      puts(VERSION);
      return EXIT_FAILURE;
    }
    else if(equals(argv[i], "-d"))
      display_str = argv[++i];
    else if(equals(argv[i], "-a"))
      activate = true;
    else if(equals(argv[i], "-r"))
      reset = true;
  }

  if(activate && reset)
  {
    fputs("-a and -r are mutually exclusive", stderr);
    return EXIT_FAILURE;
  }


  Display *display = XOpenDisplay(display_str);
  if(display == NULL)
  {
    fputs("Cannot open display\n", stderr);
    return EXIT_FAILURE;
  }

  if(activate)
    XForceScreenSaver(display, ScreenSaverActive);
  if(reset)
    XForceScreenSaver(display, ScreenSaverReset);
  
  XCloseDisplay(display);
  return EXIT_SUCCESS;
}

