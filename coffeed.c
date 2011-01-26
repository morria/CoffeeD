#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "hidapi.h"

#include <unistd.h>

#define MAX_STR 255

int main(int argc, char* argv[])
{
  int res;
  unsigned char buf[256];
  hid_device *handle;
  int i;

  // Set up the command buffer.
  memset(buf,0x00,sizeof(buf));

  // Open the device using the VID, PID,
  // and optionally the Serial number.
  ////handle = hid_open(0x4d8, 0x3f, L"12345");
  handle = hid_open(0x6096, 0x0158, NULL);
  if (!handle) {
    printf("unable to open device\n");
    return 1;
  }

  // Read the weight
  res = hid_read(handle, buf, 32);

  for (i = 0; i < res; i++)
    printf("%02hhx ", buf[i]);
  printf("\n");
  // printf("%d\n", buf[4]);

  return 0;
}
