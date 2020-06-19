//
// Created by Bryan Tester on 10/06/2020.
//

#ifndef PIPETCAM_RASPIFASTCAMCLASS_H
#define PIPETCAM_RASPIFASTCAMCLASS_H

#include <zmq.h>
#include <cstdint>

#include "interface/mmal/mmal.h"
#include "interface/mmal/mmal_logging.h"
#include "interface/mmal/mmal_buffer.h"
#include "interface/mmal/util/mmal_util.h"
#include "interface/mmal/util/mmal_util_params.h"
#include "interface/mmal/util/mmal_default_components.h"
#include "interface/mmal/util/mmal_connection.h"

/** Structure containing all state information for the current run
 */
typedef struct
{
    int width;                          /// Requested width of image
    int height;                         /// requested height of image
    int quality;                        /// JPEG quality setting (1-100)
    char *filename;                     /// filename of output file
    char *socket_addr;                  /// Address for ZMQ socket
    int socket_type;                    /// type of ZMQ socket
    int verbose;                        /// !0 if want detailed run information
    uint32_t exposure;                  /// exposure period (us)
    MMAL_FOURCC_T encoding;             /// Encoding to use for the output file.

    MMAL_COMPONENT_T *camera_component;    /// Pointer to the camera component
    MMAL_COMPONENT_T *encoder_component;   /// Pointer to the encoder component
    MMAL_CONNECTION_T *preview_connection; /// Pointer to the connection from camera to preview
    MMAL_CONNECTION_T *encoder_connection; /// Pointer to the connection from camera to encoder

    MMAL_POOL_T *encoder_pool; /// Pointer to the pool of buffers used by encoder output port

} RASPISTILL_STATE;

const char* header_str = "{\"htype\": [\"chunk-1.0\"], \"shape\": [%d, %d, %d], \"type\": \"%s\", \"frame\": %d}";

class RaspiFastCamClass {
public:
    RaspiFastCamClass(RASPISTILL_STATE state);
    ~RaspiFastCamClass();
    virtual void image_callback(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer, void *userData, uint64_t uid);
    int run();

    uint64_t frameCounter;

private:
    RASPISTILL_STATE state;
};

#endif //PIPETCAM_RASPIFASTCAMCLASS_H
