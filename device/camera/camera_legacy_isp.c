#include "camera.h"

#include "device/buffer.h"
#include "device/buffer_list.h"
#include "device/device.h"
#include "device/links.h"
#include "opts/log.h"
#include "opts/fourcc.h"
#include "device/buffer_list.h"
#include "http/http.h"

static const char *isp_names[2] = {
  "ISP",
  "ISP-LOW"
};

int camera_configure_legacy_isp(camera_t *camera, buffer_list_t *src_capture, float div, int res)
{
  camera->legacy_isp[res] = device_v4l2_open(isp_names[res], "/dev/video12");

  buffer_list_t *isp_output = device_open_buffer_list_output(
    camera->legacy_isp[res], src_capture);
  buffer_list_t *isp_capture = device_open_buffer_list_capture(
    camera->legacy_isp[res], isp_output, div, V4L2_PIX_FMT_YUYV, true);

  camera_capture_add_output(camera, src_capture, isp_output);

  if (camera_configure_output(camera, isp_capture, res) < 0) {
    return -1;
  }

  return 0;
}
