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

#include "SamsungAccelSensor.h"

#include <hardware/sensors.h>
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

SamsungAccelSensor::SamsungAccelSensor(int32_t sensorHandle,
                                       ISensorsEventCallback* callback)
    : AccelSensor(sensorHandle, callback), SamsungSensor("accelerometer_sensor", 1) {
    mSensorInfo.name = SamsungSensor::getName() + " Accelerometer";
    mSensorInfo.vendor = SamsungSensor::getVendor();
    mSensorInfo.maxRange = 4.f * GRAVITY_EARTH;
    mSensorInfo.resolution = 0.0011971008f;
    mSensorInfo.power = 0.13f;
    mSensorInfo.minDelay = 10000;
    mSensorInfo.maxDelay = 200000;
}

void SamsungAccelSensor::flush() {
    std::string sysfs_flush_path = "/sys/devices/virtual/sensors/sensor_dev/flush";
    std::ofstream sysfs_flush(sysfs_flush_path);

    if (sysfs_flush.is_open()) {
        sysfs_flush << 0;
        sysfs_flush.close();
    } else {
        ALOGE("Failed to open %s", sysfs_flush_path.c_str());
    }
}

void SamsungAccelSensor::activate(bool enable) {
    AccelSensor::activate(SamsungSensor::enable(enable));

    if (enable) {
        setPollDelay(66667000);
        flush();
    } else {
        setPollDelay(200000000);
    }
}

std::vector<Event> SamsungAccelSensor::readEvents() {
    std::vector<Event> events;
    Event event;
    event.sensorHandle = mSensorInfo.sensorHandle;
    event.sensorType = mSensorInfo.type;
    event.timestamp = ::android::elapsedRealtimeNano();

    std::ifstream in(getRawDataPath());

    if (in.is_open()) {
        std::string tmp;
        int32_t x, y, z;

        getline(in, tmp);
        sscanf(tmp.c_str(), "%i,%i,%i", &x, &y, &z);

        event.u.vec3.x = x / CONVERT_ACCEL;
        event.u.vec3.y = y / CONVERT_ACCEL;
        event.u.vec3.z = z / CONVERT_ACCEL;
    } else {
        ALOGE("Failed to read %s", getRawDataPath().c_str());
    }

    event.u.vec3.status = SensorStatus::ACCURACY_HIGH;
    events.push_back(event);

    return events;
}

}  // namespace implementation
}  // namespace V2_X
}  // namespace sensors
}  // namespace hardware
}  // namespace android
