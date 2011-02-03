#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "hidapi.h"
#include <microhttpd.h>
#include <unistd.h>

#define MAX_STR 255



static int handle_request(
    void *cls,
    struct MHD_Connection *connection,
    const char *url,
    const char *method,
    const char *version,
    const char *upload_data,
    size_t *upload_data_size,
    void **con_cls) {

  int res, i, ret;
  unsigned char buf[256];
  hid_device *handle;

  // Open the device using the VID, PID,
  // and optionally the Serial number.
  ////handle = hid_open(0x4d8, 0x3f, L"12345");
  handle = hid_open(0x6096, 0x0158, NULL);
  if (!handle) {
    printf("unable to open device\n");
    return 1;
  }

  struct MHD_Response *response;
  if (strcmp(method,"GET")) return MHD_NO;

  /*
  memset(buf, 0x00, 32);
  buf[0] = 0x00;
  hid_write(handle, buf, 17);
  if (res < 0)
    printf("Unable to write() (2)\n");
  */

  memset(buf, 0x00, sizeof(buf));
  res = hid_read(handle, buf, 32);
  hid_close(handle);

  /*
  printf("read: " );
  for (i = 0; i < res; i++)
    printf("%02hhx ", buf[i]);
  printf("\n");
  */

  int v = buf[4] + (256 * buf[5]);

  // Check to see if the value is negative
  if(0x05 == buf[1])
    v = -v;

  char value[128];
  memset(value, 0x00, 32);

  if(!strcmp(url,"/jsonp"))
    snprintf(value, 128, "var coffeeWeight = %d;\n", v);
  else
    snprintf(value, 32, "%d\n", v);

  response = MHD_create_response_from_data(strlen(value), value,
					   MHD_NO, MHD_YES);
  MHD_add_response_header (response, "Content-Type", "text/plain");
  ret = MHD_queue_response(connection, 200, response);
  MHD_destroy_response(response);
  return ret;
}

int main(int argc, char* argv[])
{

  struct MHD_Daemon *daemon = MHD_start_daemon(
        MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
        &handle_request, NULL,
        MHD_OPTION_THREAD_POOL_SIZE, 2,
        MHD_OPTION_END
    );
  if (!daemon) {
    fprintf(stderr, "Cannot start daemon\n");
    return 1;
  }
    for (;;) sleep(0xffffffff);
    MHD_stop_daemon (daemon);


  return 0;
}
