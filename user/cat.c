#include <inc/lib.h>

char buf[4096];

void
cat(int f, char *s) {
  long n;
  int r;

  while ((n = read(f, buf, (long)sizeof(buf))) > 0)
  {
    cprintf("cat read: %d\n",(int)n);
    /* for (int i=0;i<n;i++)
      cputchar(buf[i]);
    cprintf("\n"); */
    if ((r = write(1, buf, n)) != n)
      panic("write error copying %s: %i", s, r);
    cprintf("cat write %d\n",r);
  }
  if (n < 0)
    panic("error reading %s: %i", s, (int)n);
}

void
umain(int argc, char **argv) {
  int f, i;

  binaryname = "cat";
  if (argc == 1)
    cat(0, "<stdin>");
  else
    for (i = 1; i < argc; i++) {
      f = open(argv[i], O_RDONLY);
      if (f < 0)
        printf("can't open %s: %i\n", argv[i], f);
      else {
        cat(f, argv[i]);
        close(f);
      }
    }
}
