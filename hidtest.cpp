#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "hidapi.h"

#include <unistd.h>

int main(int argc, char* argv[])
{
	int res;
	unsigned char buf[256];
	#define MAX_STR 255
	wchar_t wstr[MAX_STR];
	hid_device *handle;
	int i;

	struct hid_device_info *devs, *cur_dev;

	// Set up the command buffer.
	memset(buf,0x00,sizeof(buf));
	buf[0] = 0x01;
	buf[1] = 0x81;

	// Open the device using the VID, PID,
	// and optionally the Serial number.
	////handle = hid_open(0x4d8, 0x3f, L"12345");
	handle = hid_open(0x6096, 0x0158, NULL);
	if (!handle) {
		printf("unable to open device\n");
 		return 1;
	}

	// Request state (cmd 0x81). The first byte is the report number (0x1).
	buf[0] = 0x00;
	buf[1] = 0x00;
	hid_write(handle, buf, 17);
	if (res < 0)
	  printf("Unable to write() (2)\n");

	// Read requested state. hid_read() has been set to be
	res = hid_read(handle, buf, 32);

	// printf("Data read: %d\n", res);
	// Print out the returned buffer.
	for (i = 0; i < res; i++)
	printf("%02hhx ", buf[i]);
	printf("\n");
	// printf("%d\n", buf[4]);

	return 0;
}
