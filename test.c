#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <atasmart.h>

int main(int argc, char *argv[]) {
  const char *device = NULL;
  SkDisk *disk;
  int result;

  if (!device) {
    if (optind != argc-1) {
      fprintf(stderr, "Please input a disk name.\n");
      return 1;
    }
    device = argv[optind];
  }

  if ( (result = sk_disk_open(device, &disk)) < 0 ) {
    fprintf(stderr, "Fail to open disk %s: %s\n", device, strerror(errno));
    return 1;
  }

  if ( (result = sk_disk_dump(disk)) < 0 ) {
    fprintf(stderr, "Could not dump disk data: %s\n", strerror(errno));
    goto done;
  }

  done:
    if (disk)
      sk_disk_free(disk);

  return 0;
}
