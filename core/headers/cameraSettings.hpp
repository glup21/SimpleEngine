#ifndef CAMERA_SETTINGS_H
#define CAMERA_SETTINGS_H

struct CameraSettings
{

    float fov = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    float lookSensitivity = 150.0f;
    float movingSpeed = 0.2f;

};

#endif