#include "lua_bindings.h"
#include "lua_crypto.h"
#include "lua_javabridge.h"
#include "lua_xgame.h"
#include "lua_cocos2d.h"
#include "lua_cocos2d_ui.h"
#include "lua_spine.h"
#include "lua_fairygui.h"
#include "lua_xml_http_request.h"
#include "lua_photo.h"
#include "lua_recorder.h"
#include "xgame/xruntime.h"
#include "xgame/xlua.h"
#include "cjson/lua_cjson.h"
#include "md5/md5.h"
#include "pbc/pbc.h"
#include "lame/lua_lame.h"
#include "qrencode/lua_qrcode.h"
#include "bugly/lua_bugly.h"

int luaopen_bindings(lua_State *L)
{
    xlua_call(L, luaopen_cocos2d);
    xlua_call(L, luaopen_cocos2d_ui);
    xlua_call(L, luaopen_spine);
    xlua_call(L, luaopen_fairygui);
    xlua_call(L, luaopen_xgame);
    xlua_call(L, luaopen_xml_http_request);
    
    olua_require(L, "kernel.protobuf.c", luaopen_protobuf_c);
    olua_require(L, "kernel.md5" , luaopen_md5);
    olua_require(L, "kernel.base64", luaopen_base64);
    olua_require(L, "kernel.xxtea", luaopen_xxtea);
    olua_require(L, "kernel.openssl", luaopen_openssl);
    olua_require(L, "kernel.cjson", luaopen_cjson);
    olua_require(L, "kernel.cjson.safe", luaopen_cjson_safe);
    olua_require(L, "kernel.qrcode", luaopen_qrcode);
    olua_require(L, "kernel.qrcode.QRSprite", luaopen_qrsprite);
    olua_require(L, "kernel.lame", luaopen_lame);
    olua_require(L, "kernel.photo", luaopen_photo);
    olua_require(L, "kernel.recorder", luaopen_recorder);
    olua_require(L, "kernel.bugly", luaopen_bugly);
    olua_preload(L, "kernel.luaj", luaopen_javabridge);

    return 0;
}
