#if 0
cc main.c -nostdinc -nostdlib -fno-stack-protector -fno-asynchronous-unwind-tables killgnu/libkillgnu.a -o c_stripcomments
exit
#endif

#include "killgnu/killgnu.h"

int main(int ArgsCount, const char ** Args) {
  if (ArgsCount < 2) {
    killGnuPrint("c_stripcomments error: pass the path to a file as the second argument.\n");
    goto exit;
  }

  int fd = killGnuOpen(Args[1], 02, 0400 | 0200);
  if (fd < 0) {
    killGnuPrint("c_stripcomments error: fd < 0\n");
    goto exit;
  }

  KillGnuFileStatus fileStatus = {};
  killGnuFstat(fd, &fileStatus);

  int isComment = 0;
  for (long i = 0; i < fileStatus.st_size; i += 1) {
    char c = 0;
    killGnuPread(fd, &c, 1, i);

    if (c == 0) {
      break;
    }

    if (c == ' ' && isComment == 0) {
      killGnuPrint(" ");
      continue;
    }

    if (c == '\n' && isComment == 1) {
      isComment = 0;
    }

    if (c == '/') {
      char peek = 0;
      killGnuPread(fd, &peek, 1, i + 1);
      if (peek == '/') {
        isComment = 1;
      }
    }

    if (isComment == 0) {
      char s[2];
      s[0] = c;
      s[1] = 0;
      killGnuPrint(s);
    }
  }

  killGnuClose(fd);

exit:;
}
