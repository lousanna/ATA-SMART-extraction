#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <atasmart.h>

static void parse_attributes(SkDisk *d, const SkSmartAttributeParsedData *a, void* userdata) {
  char name[32];
  char pretty[32];
  char threshold[32], thresholdWorst[32], thresholdCurr[32];

  snprintf(threshold, sizeof(threshold), "%3u", a->threshold);
  threshold[sizeof(threshold)-1] = 0;
  snprintf(thresholdWorst, sizeof(thresholdWorst), "%3u", a->worst_value);
  thresholdWorst[sizeof(thresholdWorst)-1] = 0;
  snprintf(thresholdCurr, sizeof(thresholdCurr), "%3u", a->current_value);
  thresholdCurr[sizeof(thresholdCurr)-1] = 0;

  printf("%3u\n", a->id);
  printf("%-27s\n", a->name);
  printf("%-3s\n", thresholdCurr);
  printf("%-3s\n", thresholdCurr);
  printf("%-3s\n", thresholdWorst);
  printf("%lu\n", a->pretty_value);
  printf("%d\n", a->online);
  printf("%-7s\n", a->good_now_valid ? a->good_now ? "Y" : "N" : "N/A");
  printf("%-7s\n", a->good_in_the_past_valid ? a->good_in_the_past ? "Y" : "N" : "N/A");
}

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

  if ( (result = sk_disk_smart_parse_attributes(disk, (SkSmartAttributeParseCallback) parse_attributes, NULL)) < 0) {
    fprintf(stderr, "Fail to parse SMART: %s\n", strerror(errno));
  }

  printf("\nFull dump below:\n");
  if ( (result = sk_disk_dump(disk)) < 0 ) {
    fprintf(stderr, "Could not dump disk data: %s\n", strerror(errno));
    goto done;
  }

  done:
    if (disk)
      sk_disk_free(disk);

  return 0;
}
