//
// Created by Bryan Tester on 10/06/2020.
//

#ifndef PIPETCAM_RASPIFASTCAMCLASS_H
#define PIPETCAM_RASPIFASTCAMCLASS_H

#include "interface/mmal/mmal.h"
#include "interface/mmal/mmal_logging.h"
#include "interface/mmal/mmal_buffer.h"
#include "interface/mmal/util/mmal_util.h"
#include "interface/mmal/util/mmal_util_params.h"
#include "interface/mmal/util/mmal_default_components.h"
#include "interface/mmal/util/mmal_connection.h"

class RaspiFastCamClass {
public:
    RaspiFastCamClass(RASPISTILL_STATE state);
    ~RaspiFastCamClass();
    virtual void image_callback(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer, void *userData);
    int run();
private:
    RASPISTILL_STATE state;

};

#endif //PIPETCAM_RASPIFASTCAMCLASS_H
