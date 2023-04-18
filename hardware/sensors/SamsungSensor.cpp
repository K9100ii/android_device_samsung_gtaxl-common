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

#include "SamsungSensor.h"

#include <log/log.h>

#include <fstream>

namespace android {
namespace hardware {
namespace sensors {
namespace V2_X {
namespace implementation {

std::string kSensorsBasePath1("/sys/class/sensor_event/symlink/");
std::string kSensorsBasePath2("/sys/devices/virtual/sensors/");

SamsungSensor::SamsungSensor(std::string name, uint64_t id) : mName(name), mId(id) {};

bool SamsungSensor::enable(bool enable) {
    std::string sysfs_enable_path = kSensorsBasePath1 + mName + "/enable";
    uint64_t enabled_sensors;
    std::fstream sysfs_enable(sysfs_enable_path, std::ios::in | std::ios::out);

    if (sysfs_enable.good()) {
        sysfs_enable >> enabled_sensors;

        if ((enabled_sensors & mId) != enable) {
            sysfs_enable << (enable ? enabled_sensors + mId : enabled_sensors - mId);
            sysfs_enable.seekg(0);

            sysfs_enable = std::fstream(sysfs_enable_path);
            sysfs_enable >> enabled_sensors;
        }

        return enabled_sensors & mId;
    } else {
        ALOGE("Failed to change state of %s", mName.c_str());
    }

    return false;
}

std::string SamsungSensor::getName() {
    std::string name;
    std::ifstream in(kSensorsBasePath2 + mName + "/name");

    getline(in, name);

    return name;
}

std::string SamsungSensor::getVendor() {
    std::string vendor;
    std::ifstream in(kSensorsBasePath2 + mName + "/vendor");

    getline(in, vendor);

    return vendor;
}

std::string SamsungSensor::getRawDataPath() {
    return kSensorsBasePath2 + mName + "/raw_data";
}

void SamsungSensor::setPollDelay(int value) {
    std::string sysfs_poll_delay_path = kSensorsBasePath1 + mName + "/poll_delay";
    std::ofstream sysfs_poll_delay(sysfs_poll_delay_path);

    if (sysfs_poll_delay.is_open()) {
        sysfs_poll_delay << value << std::endl;
        sysfs_poll_delay.close();
    } else {
        ALOGE("Failed to open %s", sysfs_poll_delay_path.c_str());
    }
}

}  // namespace implementation
}  // namespace V2_X
}  // namespace sensors
}  // namespace hardware
}  // namespace android
