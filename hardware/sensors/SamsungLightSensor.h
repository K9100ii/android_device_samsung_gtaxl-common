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

#ifndef SAMSUNG_LIGHT_SENSOR_H
#define SAMSUNG_LIGHT_SENSOR_H

#include "SamsungSensor.h"

namespace android {
namespace hardware {
namespace sensors {
namespace V2_X {
namespace implementation {

class SamsungLightSensor : public LightSensor, public SamsungSensor {
    public:
        SamsungLightSensor(int32_t sensorHandle, ISensorsEventCallback* callback);
        void activate(bool enable);
        virtual std::vector<Event> readEvents() override;
};

}  // namespace implementation
}  // namespace V2_X
}  // namespace sensors
}  // namespace hardware
}  // namespace android

#endif // SAMSUNG_LIGHT_SENSOR_H
