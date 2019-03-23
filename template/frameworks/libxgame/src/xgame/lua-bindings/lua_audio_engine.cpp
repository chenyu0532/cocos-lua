//
// generated by olua
//
#include "xgame/lua-bindings/lua_cocos2d_ui.h"
#include "xgame/lua-bindings/lua_conv.h"
#include "xgame/lua-bindings/lua_conv_manual.h"
#include "xgame/xlua.h"
#include "xgame/xruntime.h"
#include "olua/olua.hpp"
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"



static int _cocos2d_experimental_AudioProfile_get_name(lua_State *L)
{
    lua_settop(L, 1);

    cocos2d::experimental::AudioProfile *self = nullptr;

    olua_to_cppobj(L, 1, (void **)&self, "cc.AudioProfile");

    // <function var>
    std::string ret = (std::string)self->name;
    int num_ret = olua_push_std_string(L, ret);

    return num_ret;
}

static int _cocos2d_experimental_AudioProfile_set_name(lua_State *L)
{
    lua_settop(L, 2);

    cocos2d::experimental::AudioProfile *self = nullptr;
    std::string arg1;       /** name */

    olua_to_cppobj(L, 1, (void **)&self, "cc.AudioProfile");
    olua_check_std_string(L, 2, &arg1);

    // <function var>
    self->name = arg1;

    return 0;
}

static int _cocos2d_experimental_AudioProfile_get_maxInstances(lua_State *L)
{
    lua_settop(L, 1);

    cocos2d::experimental::AudioProfile *self = nullptr;

    olua_to_cppobj(L, 1, (void **)&self, "cc.AudioProfile");

    // <function var>
    unsigned int ret = (unsigned int)self->maxInstances;
    int num_ret = olua_push_uint(L, (lua_Unsigned)ret);

    return num_ret;
}

static int _cocos2d_experimental_AudioProfile_set_maxInstances(lua_State *L)
{
    lua_settop(L, 2);

    cocos2d::experimental::AudioProfile *self = nullptr;
    lua_Unsigned arg1 = 0;   /** maxInstances */

    olua_to_cppobj(L, 1, (void **)&self, "cc.AudioProfile");
    olua_check_uint(L, 2, &arg1);

    // <function var>
    self->maxInstances = (unsigned int)arg1;

    return 0;
}

static int _cocos2d_experimental_AudioProfile_get_minDelay(lua_State *L)
{
    lua_settop(L, 1);

    cocos2d::experimental::AudioProfile *self = nullptr;

    olua_to_cppobj(L, 1, (void **)&self, "cc.AudioProfile");

    // <function var>
    double ret = (double)self->minDelay;
    int num_ret = olua_push_number(L, (lua_Number)ret);

    return num_ret;
}

static int _cocos2d_experimental_AudioProfile_set_minDelay(lua_State *L)
{
    lua_settop(L, 2);

    cocos2d::experimental::AudioProfile *self = nullptr;
    lua_Number arg1 = 0;   /** minDelay */

    olua_to_cppobj(L, 1, (void **)&self, "cc.AudioProfile");
    olua_check_number(L, 2, &arg1);

    // <function var>
    self->minDelay = (double)arg1;

    return 0;
}

static int luaopen_cocos2d_experimental_AudioProfile(lua_State *L)
{
    oluacls_class(L, "cc.AudioProfile", nullptr);
    oluacls_property(L, "name", _cocos2d_experimental_AudioProfile_get_name, _cocos2d_experimental_AudioProfile_set_name);
    oluacls_property(L, "maxInstances", _cocos2d_experimental_AudioProfile_get_maxInstances, _cocos2d_experimental_AudioProfile_set_maxInstances);
    oluacls_property(L, "minDelay", _cocos2d_experimental_AudioProfile_get_minDelay, _cocos2d_experimental_AudioProfile_set_minDelay);

    olua_registerluatype<cocos2d::experimental::AudioProfile>(L, "cc.AudioProfile");
    oluacls_createclassproxy(L);

    return 1;
}

static int luaopen_cocos2d_experimental_AudioEngine_AudioState(lua_State *L)
{
    oluacls_class(L, "cc.AudioState", nullptr);
    oluacls_const_integer(L, "ERROR", (lua_Integer)cocos2d::experimental::AudioEngine::AudioState::ERROR);
    oluacls_const_integer(L, "INITIALIZING", (lua_Integer)cocos2d::experimental::AudioEngine::AudioState::INITIALIZING);
    oluacls_const_integer(L, "PLAYING", (lua_Integer)cocos2d::experimental::AudioEngine::AudioState::PLAYING);
    oluacls_const_integer(L, "PAUSED", (lua_Integer)cocos2d::experimental::AudioEngine::AudioState::PAUSED);

    olua_registerluatype<cocos2d::experimental::AudioEngine::AudioState>(L, "cc.AudioState");
    oluacls_createclassproxy(L);

    return 1;
}

static int _cocos2d_experimental_AudioEngine_lazyInit(lua_State *L)
{
    lua_settop(L, 0);

    // static bool lazyInit()
    bool ret = (bool)cocos2d::experimental::AudioEngine::lazyInit();
    int num_ret = olua_push_bool(L, ret);

    return num_ret;
}

static int _cocos2d_experimental_AudioEngine_end(lua_State *L)
{
    lua_settop(L, 0);

    // static void end()
    cocos2d::experimental::AudioEngine::end();

    return 0;
}

static int _cocos2d_experimental_AudioEngine_getDefaultProfile(lua_State *L)
{
    lua_settop(L, 0);

    // static AudioProfile* getDefaultProfile()
    cocos2d::experimental::AudioProfile *ret = (cocos2d::experimental::AudioProfile *)cocos2d::experimental::AudioEngine::getDefaultProfile();
    int num_ret = olua_push_cppobj<cocos2d::experimental::AudioProfile>(L, ret, "cc.AudioProfile");

    return num_ret;
}

static int _cocos2d_experimental_AudioEngine_play2d(lua_State *L)
{
    lua_settop(L, 4);

    std::string arg1;       /** filePath */
    bool arg2 = false;   /** loop */
    lua_Number arg3 = 0;   /** volume */
    cocos2d::experimental::AudioProfile *arg4 = nullptr;   /** profile */

    olua_check_std_string(L, 1, &arg1);
    olua_opt_bool(L, 2, &arg2, (bool)false);
    olua_opt_number(L, 3, &arg3, (lua_Number)1.0f);
    olua_opt_cppobj(L, 4, (void **)&arg4, "cc.AudioProfile", nullptr);

    // static int play2d(const std::string& filePath, bool loop = false, float volume = 1.0f, const AudioProfile *profile = nullptr)
    int ret = (int)cocos2d::experimental::AudioEngine::play2d(arg1, arg2, (float)arg3, arg4);
    int num_ret = olua_push_int(L, (lua_Integer)ret);

    return num_ret;
}

static int _cocos2d_experimental_AudioEngine_setLoop(lua_State *L)
{
    lua_settop(L, 2);

    lua_Integer arg1 = 0;   /** audioID */
    bool arg2 = false;   /** loop */

    olua_check_int(L, 1, &arg1);
    olua_check_bool(L, 2, &arg2);

    // static void setLoop(int audioID, bool loop)
    cocos2d::experimental::AudioEngine::setLoop((int)arg1, arg2);

    return 0;
}

static int _cocos2d_experimental_AudioEngine_isLoop(lua_State *L)
{
    lua_settop(L, 1);

    lua_Integer arg1 = 0;   /** audioID */

    olua_check_int(L, 1, &arg1);

    // static bool isLoop(int audioID)
    bool ret = (bool)cocos2d::experimental::AudioEngine::isLoop((int)arg1);
    int num_ret = olua_push_bool(L, ret);

    return num_ret;
}

static int _cocos2d_experimental_AudioEngine_setVolume(lua_State *L)
{
    lua_settop(L, 2);

    lua_Integer arg1 = 0;   /** audioID */
    lua_Number arg2 = 0;   /** volume */

    olua_check_int(L, 1, &arg1);
    olua_check_number(L, 2, &arg2);

    // static void setVolume(int audioID, float volume)
    cocos2d::experimental::AudioEngine::setVolume((int)arg1, (float)arg2);

    return 0;
}

static int _cocos2d_experimental_AudioEngine_getVolume(lua_State *L)
{
    lua_settop(L, 1);

    lua_Integer arg1 = 0;   /** audioID */

    olua_check_int(L, 1, &arg1);

    // static float getVolume(int audioID)
    float ret = (float)cocos2d::experimental::AudioEngine::getVolume((int)arg1);
    int num_ret = olua_push_number(L, (lua_Number)ret);

    return num_ret;
}

static int _cocos2d_experimental_AudioEngine_pause(lua_State *L)
{
    lua_settop(L, 1);

    lua_Integer arg1 = 0;   /** audioID */

    olua_check_int(L, 1, &arg1);

    // static void pause(int audioID)
    cocos2d::experimental::AudioEngine::pause((int)arg1);

    return 0;
}

static int _cocos2d_experimental_AudioEngine_pauseAll(lua_State *L)
{
    lua_settop(L, 0);

    // static void pauseAll()
    cocos2d::experimental::AudioEngine::pauseAll();

    return 0;
}

static int _cocos2d_experimental_AudioEngine_resume(lua_State *L)
{
    lua_settop(L, 1);

    lua_Integer arg1 = 0;   /** audioID */

    olua_check_int(L, 1, &arg1);

    // static void resume(int audioID)
    cocos2d::experimental::AudioEngine::resume((int)arg1);

    return 0;
}

static int _cocos2d_experimental_AudioEngine_resumeAll(lua_State *L)
{
    lua_settop(L, 0);

    // static void resumeAll()
    cocos2d::experimental::AudioEngine::resumeAll();

    return 0;
}

static int _cocos2d_experimental_AudioEngine_stop(lua_State *L)
{
    lua_settop(L, 1);

    lua_Integer arg1 = 0;   /** audioID */

    olua_check_int(L, 1, &arg1);

    // static void stop(int audioID)
    cocos2d::experimental::AudioEngine::stop((int)arg1);

    return 0;
}

static int _cocos2d_experimental_AudioEngine_stopAll(lua_State *L)
{
    lua_settop(L, 0);

    // static void stopAll()
    cocos2d::experimental::AudioEngine::stopAll();

    return 0;
}

static int _cocos2d_experimental_AudioEngine_setCurrentTime(lua_State *L)
{
    lua_settop(L, 2);

    lua_Integer arg1 = 0;   /** audioID */
    lua_Number arg2 = 0;   /** sec */

    olua_check_int(L, 1, &arg1);
    olua_check_number(L, 2, &arg2);

    // static bool setCurrentTime(int audioID, float sec)
    bool ret = (bool)cocos2d::experimental::AudioEngine::setCurrentTime((int)arg1, (float)arg2);
    int num_ret = olua_push_bool(L, ret);

    return num_ret;
}

static int _cocos2d_experimental_AudioEngine_getCurrentTime(lua_State *L)
{
    lua_settop(L, 1);

    lua_Integer arg1 = 0;   /** audioID */

    olua_check_int(L, 1, &arg1);

    // static float getCurrentTime(int audioID)
    float ret = (float)cocos2d::experimental::AudioEngine::getCurrentTime((int)arg1);
    int num_ret = olua_push_number(L, (lua_Number)ret);

    return num_ret;
}

static int _cocos2d_experimental_AudioEngine_getDuration(lua_State *L)
{
    lua_settop(L, 1);

    lua_Integer arg1 = 0;   /** audioID */

    olua_check_int(L, 1, &arg1);

    // static float getDuration(int audioID)
    float ret = (float)cocos2d::experimental::AudioEngine::getDuration((int)arg1);
    int num_ret = olua_push_number(L, (lua_Number)ret);

    return num_ret;
}

static int _cocos2d_experimental_AudioEngine_getState(lua_State *L)
{
    lua_settop(L, 1);

    lua_Integer arg1 = 0;   /** audioID */

    olua_check_int(L, 1, &arg1);

    // static AudioState getState(int audioID)
    cocos2d::experimental::AudioEngine::AudioState ret = (cocos2d::experimental::AudioEngine::AudioState)cocos2d::experimental::AudioEngine::getState((int)arg1);
    int num_ret = olua_push_uint(L, (lua_Unsigned)ret);

    return num_ret;
}

static int _cocos2d_experimental_AudioEngine_getMaxAudioInstance(lua_State *L)
{
    lua_settop(L, 0);

    // static int getMaxAudioInstance()
    int ret = (int)cocos2d::experimental::AudioEngine::getMaxAudioInstance();
    int num_ret = olua_push_int(L, (lua_Integer)ret);

    return num_ret;
}

static int _cocos2d_experimental_AudioEngine_setMaxAudioInstance(lua_State *L)
{
    lua_settop(L, 1);

    lua_Integer arg1 = 0;   /** maxInstances */

    olua_check_int(L, 1, &arg1);

    // static bool setMaxAudioInstance(int maxInstances)
    bool ret = (bool)cocos2d::experimental::AudioEngine::setMaxAudioInstance((int)arg1);
    int num_ret = olua_push_bool(L, ret);

    return num_ret;
}

static int _cocos2d_experimental_AudioEngine_uncache(lua_State *L)
{
    lua_settop(L, 1);

    std::string arg1;       /** filePath */

    olua_check_std_string(L, 1, &arg1);

    // static void uncache(const std::string& filePath)
    cocos2d::experimental::AudioEngine::uncache(arg1);

    return 0;
}

static int _cocos2d_experimental_AudioEngine_uncacheAll(lua_State *L)
{
    lua_settop(L, 0);

    // static void uncacheAll()
    cocos2d::experimental::AudioEngine::uncacheAll();

    return 0;
}

static int _cocos2d_experimental_AudioEngine_getProfile1(lua_State *L)
{
    lua_settop(L, 1);

    lua_Integer arg1 = 0;   /** audioID */

    olua_check_int(L, 1, &arg1);

    // static AudioProfile* getProfile(int audioID)
    cocos2d::experimental::AudioProfile *ret = (cocos2d::experimental::AudioProfile *)cocos2d::experimental::AudioEngine::getProfile((int)arg1);
    int num_ret = olua_push_cppobj<cocos2d::experimental::AudioProfile>(L, ret, "cc.AudioProfile");

    return num_ret;
}

static int _cocos2d_experimental_AudioEngine_getProfile2(lua_State *L)
{
    lua_settop(L, 1);

    std::string arg1;       /** profileName */

    olua_check_std_string(L, 1, &arg1);

    // static AudioProfile* getProfile(const std::string &profileName)
    cocos2d::experimental::AudioProfile *ret = (cocos2d::experimental::AudioProfile *)cocos2d::experimental::AudioEngine::getProfile(arg1);
    int num_ret = olua_push_cppobj<cocos2d::experimental::AudioProfile>(L, ret, "cc.AudioProfile");

    return num_ret;
}

static int _cocos2d_experimental_AudioEngine_getProfile(lua_State *L)
{
    int num_args = lua_gettop(L);

    if (num_args == 1) {
        if (olua_is_int(L, 1)) {
            return _cocos2d_experimental_AudioEngine_getProfile1(L);
        }

        // if (olua_is_std_string(L, 1)) {
            return _cocos2d_experimental_AudioEngine_getProfile2(L);
        // }
    }

    luaL_error(L, "method 'cocos2d::experimental::AudioEngine::getProfile' not support '%d' arguments", num_args);

    return 0;
}

static int _cocos2d_experimental_AudioEngine_getPlayingAudioCount(lua_State *L)
{
    lua_settop(L, 0);

    // static int getPlayingAudioCount()
    int ret = (int)cocos2d::experimental::AudioEngine::getPlayingAudioCount();
    int num_ret = olua_push_int(L, (lua_Integer)ret);

    return num_ret;
}

static int _cocos2d_experimental_AudioEngine_setEnabled(lua_State *L)
{
    lua_settop(L, 1);

    bool arg1 = false;   /** isEnabled */

    olua_check_bool(L, 1, &arg1);

    // static void setEnabled(bool isEnabled)
    cocos2d::experimental::AudioEngine::setEnabled(arg1);

    return 0;
}

static int _cocos2d_experimental_AudioEngine_isEnabled(lua_State *L)
{
    lua_settop(L, 0);

    // static bool isEnabled()
    bool ret = (bool)cocos2d::experimental::AudioEngine::isEnabled();
    int num_ret = olua_push_bool(L, ret);

    return num_ret;
}

static int _cocos2d_experimental_AudioEngine_setFinishCallback(lua_State *L)
{
    lua_settop(L, 3);

    cocos2d::experimental::AudioEngine *self = nullptr;
    lua_Integer arg1 = 0;   /** audioID */
    std::function<void(int, const std::string &)> arg2 = nullptr;   /** callback */

    olua_to_cppobj(L, 1, (void **)&self, "cc.AudioEngine");
    olua_check_int(L, 2, &arg1);

    if (olua_is_std_function(L, 3)) {
        void *callback_store_obj = (void *)self;
        std::string tag = olua_makecallbacktag("FinishCallback");
        std::string func = olua_setcallback(L, callback_store_obj, tag.c_str(), 3, OLUA_CALLBACK_TAG_REPLACE);
        arg2 = [callback_store_obj, func, tag](int arg1, const std::string &arg2) {
            lua_State *L = olua_mainthread();
            int top = lua_gettop(L);

            olua_push_int(L, (lua_Integer)arg1);
            olua_push_std_string(L, arg2);
            olua_callback(L, callback_store_obj, func.c_str(), 2);

            lua_settop(L, top);
        };
    } else {
        void *callback_store_obj = (void *)self;
        std::string tag = olua_makecallbacktag("FinishCallback");
        olua_removecallback(L, callback_store_obj, tag.c_str(), OLUA_CALLBACK_TAG_ENDWITH);
        arg2 = nullptr;
    }

    // void setFinishCallback(int audioID, @nullable const std::function<void(int,const std::string&)>& callback)
    self->setFinishCallback((int)arg1, arg2);

    return 0;
}

static int _cocos2d_experimental_AudioEngine_preload(lua_State *L)
{
    lua_settop(L, 3);

    cocos2d::experimental::AudioEngine *self = nullptr;
    std::string arg1;       /** filePath */
    std::function<void(bool)> arg2 = nullptr;   /** callback */

    olua_to_cppobj(L, 1, (void **)&self, "cc.AudioEngine");
    olua_check_std_string(L, 2, &arg1);

    if (olua_is_std_function(L, 3)) {
        void *callback_store_obj = (void *)self;
        std::string tag = olua_makecallbacktag("preload");
        std::string func = olua_setcallback(L, callback_store_obj, tag.c_str(), 3, OLUA_CALLBACK_TAG_REPLACE);
        arg2 = [callback_store_obj, func, tag](bool arg1) {
            lua_State *L = olua_mainthread();
            int top = lua_gettop(L);

            olua_push_bool(L, arg1);
            olua_callback(L, callback_store_obj, func.c_str(), 1);

            lua_settop(L, top);
        };
    } else {
        void *callback_store_obj = (void *)self;
        std::string tag = olua_makecallbacktag("preload");
        olua_removecallback(L, callback_store_obj, tag.c_str(), OLUA_CALLBACK_TAG_ENDWITH);
        arg2 = nullptr;
    }

    // void preload(const std::string& filePath, @nullable std::function<void(bool isSuccess)> callback)
    self->preload(arg1, arg2);

    return 0;
}

static int luaopen_cocos2d_experimental_AudioEngine(lua_State *L)
{
    oluacls_class(L, "cc.AudioEngine", nullptr);
    oluacls_setfunc(L, "lazyInit", _cocos2d_experimental_AudioEngine_lazyInit);
    oluacls_setfunc(L, "end", _cocos2d_experimental_AudioEngine_end);
    oluacls_setfunc(L, "getDefaultProfile", _cocos2d_experimental_AudioEngine_getDefaultProfile);
    oluacls_setfunc(L, "play2d", _cocos2d_experimental_AudioEngine_play2d);
    oluacls_setfunc(L, "setLoop", _cocos2d_experimental_AudioEngine_setLoop);
    oluacls_setfunc(L, "isLoop", _cocos2d_experimental_AudioEngine_isLoop);
    oluacls_setfunc(L, "setVolume", _cocos2d_experimental_AudioEngine_setVolume);
    oluacls_setfunc(L, "getVolume", _cocos2d_experimental_AudioEngine_getVolume);
    oluacls_setfunc(L, "pause", _cocos2d_experimental_AudioEngine_pause);
    oluacls_setfunc(L, "pauseAll", _cocos2d_experimental_AudioEngine_pauseAll);
    oluacls_setfunc(L, "resume", _cocos2d_experimental_AudioEngine_resume);
    oluacls_setfunc(L, "resumeAll", _cocos2d_experimental_AudioEngine_resumeAll);
    oluacls_setfunc(L, "stop", _cocos2d_experimental_AudioEngine_stop);
    oluacls_setfunc(L, "stopAll", _cocos2d_experimental_AudioEngine_stopAll);
    oluacls_setfunc(L, "setCurrentTime", _cocos2d_experimental_AudioEngine_setCurrentTime);
    oluacls_setfunc(L, "getCurrentTime", _cocos2d_experimental_AudioEngine_getCurrentTime);
    oluacls_setfunc(L, "getDuration", _cocos2d_experimental_AudioEngine_getDuration);
    oluacls_setfunc(L, "getState", _cocos2d_experimental_AudioEngine_getState);
    oluacls_setfunc(L, "getMaxAudioInstance", _cocos2d_experimental_AudioEngine_getMaxAudioInstance);
    oluacls_setfunc(L, "setMaxAudioInstance", _cocos2d_experimental_AudioEngine_setMaxAudioInstance);
    oluacls_setfunc(L, "uncache", _cocos2d_experimental_AudioEngine_uncache);
    oluacls_setfunc(L, "uncacheAll", _cocos2d_experimental_AudioEngine_uncacheAll);
    oluacls_setfunc(L, "getProfile", _cocos2d_experimental_AudioEngine_getProfile);
    oluacls_setfunc(L, "getPlayingAudioCount", _cocos2d_experimental_AudioEngine_getPlayingAudioCount);
    oluacls_setfunc(L, "setEnabled", _cocos2d_experimental_AudioEngine_setEnabled);
    oluacls_setfunc(L, "isEnabled", _cocos2d_experimental_AudioEngine_isEnabled);
    oluacls_setfunc(L, "setFinishCallback", _cocos2d_experimental_AudioEngine_setFinishCallback);
    oluacls_setfunc(L, "preload", _cocos2d_experimental_AudioEngine_preload);

    olua_registerluatype<cocos2d::experimental::AudioEngine>(L, "cc.AudioEngine");
    oluacls_createclassproxy(L);

    return 1;
}

int luaopen_audio_engine(lua_State *L)
{
    olua_require(L, "cc.AudioProfile", luaopen_cocos2d_experimental_AudioProfile);
    olua_require(L, "cc.AudioState", luaopen_cocos2d_experimental_AudioEngine_AudioState);
    olua_require(L, "cc.AudioEngine", luaopen_cocos2d_experimental_AudioEngine);
    return 0;
}
