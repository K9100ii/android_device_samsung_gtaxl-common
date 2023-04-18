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

#include "SamsungLightSensor.h"

#include <log/log.h>
#include <utils/SystemClock.h>

#include <fstream>
#include <stdio.h>

namespace android {
namespace hardware {
namespace sensors {
namespace V2_X {
namespace implementation {

using ::android::hardware::sensors::V2_1::Event;
using V1_0::SensorStatus;

SamsungLightSensor::SamsungLightSensor(int32_t sensorHandle,
                                       ISensorsEventCallback* callback)
    : LightSensor(sensorHandle, callback), SamsungSensor("light_sensor", 1) {
    mSensorInfo.name = SamsungSensor::getName() + " Light";
    mSensorInfo.vendor = SamsungSensor::getVendor();
    mSensorInfo.maxRange = 60000.0f;
    mSensorInfo.resolution = 1.0f;
    mSensorInfo.power = 0.75f;
    mSensorInfo.minDelay = 10000;
    mSensorInfo.maxDelay = 200000;
}

void SamsungLightSensor::activate(bool enable) {
    LightSensor::activate(SamsungSensor::enable(enable));
}

std::vector<Event> SamsungLightSensor::readEvents() {
    std::vector<Event> events;
    Event event;
    event.sensorHandle = mSensorInfo.sensorHandle;
    event.sensorType = mSensorInfo.type;
    event.timestamp = ::android::elapsedRealtimeNano();

    std::ifstream in(getRawDataPath());

    if (in.is_open()) {
        std::string tmp;
        int32_t w;

        getline(in, tmp);
        sscanf(tmp.c_str(), "%*i,%*i,%*i,%i", &w);

        event.u.vec3.x = w;
    } else {
        ALOGE("Failed to read %s", getRawDataPath().c_str());
    }

    event.u.vec3.status = SensorStatus::ACCURACY_HIGH;

    if (event.u.vec3 != mPreviousEvent.u.vec3 || !mPreviousEventSet) {
        events.push_back(event);
        mPreviousEvent = event;
        mPreviousEventSet = true;
    }

    return events;
}

}  // namespace implementation
}  // namespace V2_X
}  // namespace sensors
}  // namespace hardware
}  // namespace android
