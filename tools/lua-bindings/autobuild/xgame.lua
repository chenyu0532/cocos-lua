require "autobuild.xgame-types"

local olua = require "olua"
local typeconv = olua.typeconv
local typecls = olua.typecls
local cls = nil
local M = {}

olua.nowarning(typeconv, typecls, cls)

M.NAME = "xgame"
M.HEADER_PATH = "../../frameworks/libxgame/src/lua-bindings/lua_xgame.h"
M.SOURCE_PATH = "../../frameworks/libxgame/src/lua-bindings/lua_xgame.cpp"
M.INCLUDES = [[
#include "lua-bindings/lua_xgame.h"
#include "lua-bindings/lua_conv.h"
#include "lua-bindings/lua_conv_manual.h"
#include "xgame/xfilesystem.h"
#include "xgame/xlua.h"
#include "xgame/xpreferences.h"
#include "xgame/xdownloader.h"
#include "xgame/xruntime.h"
#include "xgame/xrootscene.h"
#include "xgame/xtimer.h"
#include "olua/olua.hpp"
]]
M.CHUNK = [[
]]

M.CLASSES = {}

cls = typecls(M.CLASSES)
cls.CPPCLS = "xgame::SceneNoCamera"
cls.SUPERCLS = "cocos2d::Scene"
cls.funcs [[
    static SceneNoCamera *create()
    static SceneNoCamera *createWithSize(const cocos2d::Size& size)
    static SceneNoCamera *createWithPhysics()
]]

cls = typecls(M.CLASSES)
cls.CPPCLS = "xgame::runtime"
cls.funcs [[
    static void clearStorage()
    static bool launch(const std::string &scriptPath)
    static bool restart()
    static bool isRestarting()
    static bool isDebug()
    static float getTime()
    static void gc()
    static const std::string getPackageName()
    static const std::string getVersion()
    static const std::string getVersionBuild()
    static const std::string getChannel()
    static const std::string getOS()
    static const std::string getDeviceInfo()
    static const std::string getLanguage()
    static void setAudioSessionCatalog(const std::string &catalog)
    static const std::string getAudioSessionCatalog()
    static bool canOpenURL(const std::string &uri)
    static void setLogPath(const std::string &path)
    static const std::string getLogPath()
    static void setAntialias(bool enabled, unsigned int numSamples)
    static bool isAntialias()
    static unsigned int getNumSamples()
    static bool support(const std::string &api)
    static void printSupport()
    static void disableReport()
]]
cls.func('testCrash', [[{
    xgame::runtime::log("test native crash!!!!");
    char *prt = NULL;
    *prt = 0;
    return 0;
}]])
cls.func('setDispatcher', [[{
    int handler = olua_reffunc(L, 1);
    xgame::runtime::setDispatcher([handler](const std::string &event, const std::string &args) {
        lua_State *L = olua_mainthread();
        int top = lua_gettop(L);
        olua_geterrorfunc(L);
        olua_getref(L, handler);
        if (lua_isfunction(L, -1)) {
            lua_pushstring(L, event.c_str());
            lua_pushstring(L, args.c_str());
            lua_pcall(L, 2, 0, top + 1);
        }
        lua_settop(L, top);
    });
    return 0;
}]])
cls.func('openURL', [[{
    lua_settop(L, 2);
    int callback = LUA_REFNIL;
    if (lua_isfunction(L, 2)) {
        callback = olua_reffunc(L, 2);
    }
    xgame::runtime::openURL(olua_checkstring(L, 1), [callback](bool success) {
        if (callback != LUA_REFNIL) {
            lua_State *L = olua_mainthread();
            int top = lua_gettop(L);
            olua_geterrorfunc(L);
            olua_getref(L, callback);
            if (lua_isfunction(L, -1)) {
                lua_pushboolean(L, success);
                lua_pcall(L, 1, 0, top + 1);
                olua_unref(L, callback);
            }
            lua_settop(L, top);
        }
    });
    return 0;
}]])
cls.props [[
    restarting
    debug
    time
    packageName
    version
    versionBuild
    channel
    os
    deviceInfo
    language
    audioSessionCatalog
    logPath
    antialias
    numSamples
]]

cls = typecls(M.CLASSES)
cls.CPPCLS = "xgame::filesystem"
cls.funcs [[
    static const std::string getWritablePath()
    static const std::string getCacheDirectory()
    static const std::string getDocumentDirectory()
    static const std::string getTmpDirectory()
    static const std::string getSDCardDirectory()
    static const std::string shortPath(const std::string &path, size_t limit = 60)
    static const std::string fullPath(const std::string &path)
    static bool createDirectory(const std::string &path, bool isFilePath = false)
    static bool remove(const std::string &path)
    static bool exist(const std::string &path)
    static bool isFile(const std::string &path)
    static bool isDirectory(const std::string &path)
    static bool rename(const std::string &oldPath, const std::string &newPath)
    static bool copy(const std::string &srcPath, const std::string &destPath)
    static cocos2d::Data read(const std::string &path)
    static bool unzip(const std::string &path, const std::string &dest)
]]
cls.func('write', [[{
    size_t len;
    lua_settop(L, 2);
    std::string path = olua_tostring(L, 1);
    const char *data = olua_checklstring(L, 2, &len);
    bool ret = (bool)xgame::filesystem::write(path, data, len);
    olua_push_bool(L, ret);
    return 1;
}
]])
cls.props [[
    writablePath
    cacheDirectory
    documentDirectory
    tmpDirectory
    sdCardDirectory
]]

cls = typecls(M.CLASSES)
cls.CPPCLS = "xgame::preferences"
cls.funcs [[
    static bool getBoolean(const char *key, bool defaultValue = false)
    static void setBoolean(const char *key, bool value)
    static float getFloat(const char *key, float defaultValue = 0)
    static void setFloat(const char *key, float value)
    static double getDouble(const char *key, double defaultValue = 0)
    static void setDouble(const char *key, double value)
    static int getInteger(const char *key, int defaultValue = 0)
    static void setInteger(const char *key, int value)
    static std::string getString(const char *key, const char *defaultValue = "")
    static void setString(const char *key, const char *value)
    static void deleteKey(const char *key)
    static void flush()
]]

cls = typecls(M.CLASSES)
cls.CPPCLS = "xgame::timer"
cls.funcs [[
    static std::string createTag()
]]
cls.func('killDelay', [[{
    lua_settop(L, 1);
    const char *tag = olua_checkstring(L, 1);
    void *cb_store = olua_getstoreobj(L, "kernel.timer");
    olua_removecallback(L, cb_store, tag, OLUA_CALLBACK_TAG_ENDWITH);
    xgame::timer::killDelay(tag);
    return 0;
}]])
cls.func('delayWithTag', [[{
    lua_settop(L, 3);
    size_t len;
    float time = (float)olua_checknumber(L, 1);
    const char *tag = luaL_checklstring(L, 2, &len);
    if (len <= 0) {
        luaL_error(L, "tag should not be empty!");
    }
    
    void *cb_store = olua_getstoreobj(L, "kernel.timer");
    std::string func = olua_setcallback(L, cb_store, tag, 3, OLUA_CALLBACK_TAG_REPLACE);
    xgame::timer::delayWithTag(time, tag, [cb_store, func]() {
        lua_State *L = olua_mainthread();
        int top = lua_gettop(L);
        olua_callback(L, cb_store, func.c_str(), 0);
        olua_removecallback(L, cb_store, func.c_str(), OLUA_CALLBACK_TAG_EQUAL);
        lua_settop(L, top);
    });
    return 0;
}]])
cls.func('delay', [[{
    lua_settop(L, 2);
    float time = (float)olua_checknumber(L, 1);
    unsigned int callback = olua_reffunc(L, 2);
    xgame::timer::delay(time, [callback]() {
        lua_State *L = olua_mainthread();
        int top = lua_gettop(L);
        olua_geterrorfunc(L);
        olua_getref(L, callback);
        if (lua_isfunction(L, -1)) {
            lua_pcall(L, 0, 0, top + 1);
            olua_unref(L, callback);
        }
        lua_settop(L, top);
    });
    return 0;
}]])
cls.func('schedule', [[{
    lua_settop(L, 2);
    float interval = (float)olua_checknumber(L, 1);
    unsigned int callback = olua_reffunc(L, 2);
    unsigned int id = xgame::timer::schedule(interval, [callback](float dt) {
        lua_State *L = olua_mainthread();
        int top = lua_gettop(L);
        olua_geterrorfunc(L);
        olua_getref(L, callback);
        if (lua_isfunction(L, -1)) {
            lua_pushnumber(L, dt);
            lua_pcall(L, 1, 0, top + 1);
        }
        lua_settop(L, top);
    });
    lua_pushinteger(L, ((uint64_t)callback << 32) | (uint64_t)id);
    return 1;
}]])
cls.func('unschedule', [[{
    lua_settop(L, 1);
    uint64_t value = olua_checkinteger(L, 1);
    unsigned int callback = value >> 32;
    unsigned int id = value & 0xFFFFFFFF;
    olua_unref(L, callback);
    xgame::timer::unschedule(id);
    return 0;
}]])

cls = typecls(M.CLASSES)
cls.CPPCLS = "xgame::window"
cls.REG_LUATYPE = false
cls.funcs [[
]]
cls.func('getVisibleBounds', [[{
    auto rect = cocos2d::Director::getInstance()->getOpenGLView()->getVisibleRect();
    lua_pushinteger(L, rect.getMinX());
    lua_pushinteger(L, rect.getMaxX());
    lua_pushinteger(L, rect.getMaxY());
    lua_pushinteger(L, rect.getMinY());
    return 4;
}
]])
cls.func('getFrameSize', [[{
    auto size = cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize();
    lua_pushnumber(L, size.width);
    lua_pushnumber(L, size.height);
    return 2;
}
]])
cls.func('getDesignSize', [[{
    auto size = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    lua_pushnumber(L, size.width);
    lua_pushnumber(L, size.height);
    return 2;
}]])
cls.func('setDesignSize', [[{
    lua_settop(L, 3);
    cocos2d::Director::getInstance()->getOpenGLView()->setDesignResolutionSize(
        (float)olua_checknumber(L, 1), (float)olua_checknumber(L, 2),
        (ResolutionPolicy)olua_checkinteger(L, 3));
    return 0;
}]])
cls.func('convertToCameraSpace', [[{
    cocos2d::Rect rect;
    cocos2d::Vec3 out;
    auto director = cocos2d::Director::getInstance();
    auto pt = cocos2d::Vec2(olua_checknumber(L, 1), olua_checknumber(L, 2));
    auto runningScene = director->getRunningScene();
    auto w2l = runningScene->getWorldToNodeTransform();
    rect.size = director->getOpenGLView()->getDesignResolutionSize();
    cocos2d::isScreenPointInRect(pt, runningScene->getDefaultCamera(), w2l, rect, &out);
    lua_pushnumber(L, out.x);
    lua_pushnumber(L, out.y);
    return 2;
}]])

cls = typecls(M.CLASSES)
cls.CPPCLS = "xgame::downloader"
cls.funcs [[
]]
cls.func('load', [[{
    lua_settop(L, 3);
    xgame::downloader::FileTask task;
    task.url = olua_checkstring(L, 1);
    task.path = olua_checkstring(L, 2);
    task.md5 = olua_optstring(L, 3, "");
    xgame::downloader::load(task);
    return 0;
}]])
cls.func('setDispatcher', [[{
    static const char *STATES[] = {"ioerror", "loaded", "pending", "invalid"};
    
    lua_settop(L, 1);
    void *store_obj = olua_getstoreobj(L, "kernel.downloader");
    std::string func = olua_setcallback(L, store_obj, "dispatcher", 1, OLUA_CALLBACK_TAG_REPLACE);
    xgame::downloader::setDispatcher([store_obj, func](const xgame::downloader::FileTask &task) {
        lua_State *L = olua_mainthread();
        int top = lua_gettop(L);
        lua_pushstring(L, task.url.c_str());
        lua_pushstring(L, task.path.c_str());
        lua_pushstring(L, STATES[task.state]);
        olua_callback(L, store_obj, func.c_str(), 3);
        lua_settop(L, top);
    });
    return 0;
}]])

return M