// Vita3K emulator project
// Copyright (C) 2023 Vita3K team
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include <module/load_module.h>

#include <config/state.h>
#include <emuenv/state.h>
#include <kernel/load_self.h>
#include <kernel/state.h>

bool is_lle_module(SceSysmoduleModuleId module_id, EmuEnvState &emuenv) {
    const auto paths = sysmodule_paths[module_id];

    // Do we know the module and its dependencies' paths?
    const bool have_paths = !paths.empty();

    // Current modules works for loading
    const auto auto_lle_modules = {
        SCE_SYSMODULE_SAS,
        SCE_SYSMODULE_PGF,
        SCE_SYSMODULE_SYSTEM_GESTURE,
        SCE_SYSMODULE_XML,
        SCE_SYSMODULE_MP4,
        SCE_SYSMODULE_ATRAC,
        SCE_SYSMODULE_AVPLAYER,
        SCE_SYSMODULE_JSON,
        SCE_SYSMODULE_HTTP,
        SCE_SYSMODULE_SSL,
        SCE_SYSMODULE_HTTPS,
    };

    if (have_paths) {
        if (emuenv.cfg.current_config.modules_mode != ModulesMode::MANUAL) {
            if (std::find(auto_lle_modules.begin(), auto_lle_modules.end(), module_id) != auto_lle_modules.end())
                return true;
        }

        if (emuenv.cfg.current_config.modules_mode != ModulesMode::AUTOMATIC) {
            for (auto path : paths) {
                if (std::find(emuenv.cfg.current_config.lle_modules.begin(), emuenv.cfg.current_config.lle_modules.end(), path) != emuenv.cfg.current_config.lle_modules.end())
                    return true;
            }
        }
    }

    return false;
}

bool is_module_loaded(KernelState &kernel, SceSysmoduleModuleId module_id) {
    return std::find(kernel.loaded_sysmodules.begin(), kernel.loaded_sysmodules.end(), module_id) != kernel.loaded_sysmodules.end();
}
