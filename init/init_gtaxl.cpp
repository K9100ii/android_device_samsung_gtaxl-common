/*
   Copyright (c) 2016, The Linux Foundation. All rights reserved.
   Copyright (c) 2017-2020, The LineageOS Project. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include <android-base/logging.h>
#include <android-base/strings.h>
#include <android-base/properties.h>

using android::base::GetProperty;

// copied from build/tools/releasetools/ota_from_target_files.py
// but with "." at the end and empty entry
std::vector<std::string> ro_product_props_default_source_order = {
    "",
    "product.",
    "odm.",
    "odm_dlkm.",
    "vendor.",
    "vendor_dlkm.",
    "system.",
    "system_ext.",
};

void property_override(char const prop[], char const value[], bool add)
{
    auto pi = (prop_info *) __system_property_find(prop);

    if (pi != nullptr) {
        __system_property_update(pi, value, strlen(value));
    } else if (add) {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

void set_ro_product_prop(char const prop[], char const value[])
{
    for (const auto &source : ro_product_props_default_source_order) {
        auto prop_name = "ro.product." + source + prop;
        property_override(prop_name.c_str(), value, false);
    }
}

void set_ro_build_prop(char const prop[], char const value[])
{
    for (const auto &source : ro_product_props_default_source_order) {
        auto prop_name = "ro." + source + "build." + prop;
        property_override(prop_name.c_str(), value, false);
    }
};

void vendor_load_properties()
{
    std::string bootloader = GetProperty("ro.bootloader", "");

    if (bootloader.find("P585N0") == 0) {
        /* SM-P585N0 */
        property_override("ro.build.description", "gtanotexlltekx-user 8.1.0 M1AJQ P585N0KOS1CTH7 release-keys", false);
        set_ro_product_prop("model", "SM-P585N0");
        set_ro_product_prop("device", "gtanotexlltekx");
        set_ro_product_prop("name", "gtanotexlltekx");
    } else if (bootloader.find("P585M") == 0) {
        /* SM-P585M */
        property_override("ro.build.description", "gtanotexllteub-user 8.1.0 M1AJQ P585MUBU2CUF2 release-keys", false);
        set_ro_product_prop("model", "SM-P585M");
        set_ro_product_prop("device", "gtanotexllte");
        set_ro_product_prop("name", "gtanotexllteub");
    } else if (bootloader.find("P585Y") == 0) {
        /* SM-P585Y */
        property_override("ro.build.description", "gtanotexlltedx-user 8.1.0 M1AJQ P585YDXS2CTJ1 release-keys", false);
        set_ro_product_prop("model", "SM-P585Y");
        set_ro_product_prop("device", "gtanotexllte");
        set_ro_product_prop("name", "gtanotexlltedx");
    } else if (bootloader.find("P588C") == 0) {
        /* SM-P588C */
        property_override("ro.build.description", "gtanotexlltezc-user 8.1.0 M1AJQ P588CZCS3CTJ1 release-keys", false);
        set_ro_product_prop("model", "SM-P588C");
        set_ro_product_prop("device", "gtanotexlltechn");
        set_ro_product_prop("name", "gtanotexlltezc");
    } else if (bootloader.find("P585") == 0) {
        /* SM-P585 */
        property_override("ro.build.description", "gtanotexlltejx-user 8.1.0 M1AJQ P585JXS3CTL1 release-keys", false);
        set_ro_product_prop("model", "SM-P585");
        set_ro_product_prop("device", "gtanotexllte");
        set_ro_product_prop("name", "gtanotexlltejx");
    } else if (bootloader.find("P583") == 0) {
        /* SM-P583 */
        property_override("ro.build.description", "gtanotexlwifizc-user 8.1.0 M1AJQ P583ZCS3CTJ1 release-keys", false);
        set_ro_product_prop("model", "SM-P583");
        set_ro_product_prop("device", "gtanotexlwifichn");
        set_ro_product_prop("name", "gtanotexlwifizc");
    } else if (bootloader.find("P580") == 0) {
        /* SM-P580 */
        property_override("ro.build.description", "gtanotexlwifizs-user 8.1.0 M1AJQ P580ZSS1CTI1 release-keys", false);
        set_ro_product_prop("model", "SM-P580");
        set_ro_product_prop("device", "gtanotexlwifikx");
        set_ro_product_prop("name", "gtanotexlwifizs");
    } else if (bootloader.find("T585N0") == 0) {
        /* SM-T585N0 */
        property_override("ro.build.description", "gtaxlltekx-user 8.1.0 M1AJQ T585N0KOS1CTJ1 release-keys", false);
        set_ro_product_prop("model", "SM-T585N0");
        set_ro_product_prop("device", "gtaxlltekx");
        set_ro_product_prop("name", "gtaxlltekx");
    } else if (bootloader.find("T585C") == 0) {
        /* SM-T585C */
        property_override("ro.build.description", "gtaxlltezc-user 8.1.0 M1AJQ T585CZCU6CTF1 release-keys", false);
        set_ro_product_prop("model", "SM-T585C");
        set_ro_product_prop("device", "gtaxlltechn");
        set_ro_product_prop("name", "gtaxlltezc");
    } else if (bootloader.find("T587") == 0) {
        /* SM-T585 */
        property_override("ro.build.description", "gtaxlltejv-user 8.1.0 M1AJQ T587JVS6CTC1 release-keys", false);
        set_ro_product_prop("model", "SM-T587");
        set_ro_product_prop("device", "gtaxllte");
        set_ro_product_prop("name", "gtaxlltejv");
    } else if (bootloader.find("T585") == 0) {
        /* SM-T585 */
        property_override("ro.build.description", "gtaxlltexx-user 8.1.0 M1AJQ T585XXS7CUI5 release-keys", false);
        set_ro_product_prop("model", "SM-T585");
        set_ro_product_prop("device", "gtaxllte");
        set_ro_product_prop("name", "gtaxlltexx");
    } else if (bootloader.find("T580") == 0) {
        /* SM-T580 */
        property_override("ro.build.description", "gtaxlwifixx-user 8.1.0 M1AJQ T580XXS5CTK1 release-keys", false);
        set_ro_product_prop("model", "SM-T580");
        set_ro_product_prop("device", "gtaxlwifi");
        set_ro_product_prop("name", "gtaxlwifixx");
    }

    LOG(INFO) << "Found bootloader id " << bootloader <<  ", setting build properties" << std::endl;
}
