/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SAMSUNG_SENSOR_H
#define SAMSUNG_SENSOR_H

#include "Sensor.h"

#include <hardware/sensors.h>

#define MAX_ACCEL_1G  8192
#define CONVERT_ACCEL (MAX_ACCEL_1G / GRAVITY_EARTH)

namespace android {
namespace hardware {
namespace sensors {
namespace V2_X {
namespace implementation {

class SamsungSensor {
    public:
        SamsungSensor(std::string name, uint64_t id);
        bool enable(bool enable);
        std::string getName();
        std::string getVendor();
        std::string getRawDataPath();
        void setPollDelay(int value);

    private:
        std::string mName;
        uint64_t mId;
};

}  // namespace implementation
}  // namespace V2_X
}  // namespace sensors
}  // namespace hardware
}  // namespace android

#endif // SAMSUNG_SENSOR_H
