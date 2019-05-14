require "core.olua-cls"

local M = {}

M.NAME = "xgame"
M.HEADER_PATH = "frameworks/libxgame/src/lua-bindings/lua_xgame.h"
M.SOURCE_PATH = "frameworks/libxgame/src/lua-bindings/lua_xgame.cpp"

M.INCLUDES = [[
#include "lua-bindings/lua_xgame.h"
#include "lua-bindings/lua_conv.h"
#include "lua-bindings/lua_conv_manual.h"
#include "xgame/xfilesystem.h"
#include "xgame/xlua.h"
#include "xgame/xpreferences.h"
#include "xgame/xdownloader.h"
#include "xgame/xruntime.h"
#include "xgame/xtimer.h"
#include "olua/olua.hpp"
]]

M.CLASSES = {
    include("conf/xgame/kernel/kernel.runtime.lua"),
    include("conf/xgame/kernel/kernel.filesystem.lua"),
    include("conf/xgame/kernel/kernel.preferences.lua"),
    include("conf/xgame/kernel/kernel.timer.lua"),
    include("conf/xgame/kernel/kernel.window.lua"),
    include("conf/xgame/kernel/kernel.downloader.lua"),
}

return M