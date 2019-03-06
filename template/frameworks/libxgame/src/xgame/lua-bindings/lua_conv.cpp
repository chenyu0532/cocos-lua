//
// generated by tolua
//
#include "xgame/lua-bindings/lua_conv.h"
#include "xgame/xlua.h"
#include "tolua/tolua.hpp"

int luacv_push_cocos2d_experimental_Viewport(lua_State *L, const cocos2d::experimental::Viewport &value)
{
    lua_createtable(L, 0, 4);
    tolua_rawsetfieldnumber(L, -1, "left", value._left);
    tolua_rawsetfieldnumber(L, -1, "bottom", value._bottom);
    tolua_rawsetfieldnumber(L, -1, "width", value._width);
    tolua_rawsetfieldnumber(L, -1, "height", value._height);
    return 1;
}

void luacv_check_cocos2d_experimental_Viewport(lua_State *L, int idx, cocos2d::experimental::Viewport *value)
{
    if (!value) {
        luaL_error(L, "value is NULL");
    }
    luaL_checktype(L, idx, LUA_TTABLE);
    value->_left = (float)tolua_checkfieldnumber(L, idx, "left");
    value->_bottom = (float)tolua_checkfieldnumber(L, idx, "bottom");
    value->_width = (float)tolua_checkfieldnumber(L, idx, "width");
    value->_height = (float)tolua_checkfieldnumber(L, idx, "height");
}

void luacv_pack_cocos2d_experimental_Viewport(lua_State *L, int idx, cocos2d::experimental::Viewport *value)
{
    if (!value) {
        luaL_error(L, "value is NULL");
    }
    value->_left = (float)luaL_checknumber(L, idx + 0);
    value->_bottom = (float)luaL_checknumber(L, idx + 1);
    value->_width = (float)luaL_checknumber(L, idx + 2);
    value->_height = (float)luaL_checknumber(L, idx + 3);
}

int luacv_unpack_cocos2d_experimental_Viewport(lua_State *L, const cocos2d::experimental::Viewport &value)
{
    lua_pushnumber(L, value._left);
    lua_pushnumber(L, value._bottom);
    lua_pushnumber(L, value._width);
    lua_pushnumber(L, value._height);
    return 4;
}

bool luacv_is_cocos2d_experimental_Viewport(lua_State *L, int idx)
{
    return lua_istable(L, idx);
}

int luacv_push_cocos2d_Vec2(lua_State *L, const cocos2d::Vec2 &value)
{
    lua_createtable(L, 0, 2);
    tolua_rawsetfieldnumber(L, -1, "x", value.x);
    tolua_rawsetfieldnumber(L, -1, "y", value.y);
    return 1;
}

void luacv_check_cocos2d_Vec2(lua_State *L, int idx, cocos2d::Vec2 *value)
{
    if (!value) {
        luaL_error(L, "value is NULL");
    }
    luaL_checktype(L, idx, LUA_TTABLE);
    value->x = (float)tolua_checkfieldnumber(L, idx, "x");
    value->y = (float)tolua_checkfieldnumber(L, idx, "y");
}

void luacv_pack_cocos2d_Vec2(lua_State *L, int idx, cocos2d::Vec2 *value)
{
    if (!value) {
        luaL_error(L, "value is NULL");
    }
    value->x = (float)luaL_checknumber(L, idx + 0);
    value->y = (float)luaL_checknumber(L, idx + 1);
}

int luacv_unpack_cocos2d_Vec2(lua_State *L, const cocos2d::Vec2 &value)
{
    lua_pushnumber(L, value.x);
    lua_pushnumber(L, value.y);
    return 2;
}

bool luacv_is_cocos2d_Vec2(lua_State *L, int idx)
{
    return lua_istable(L, idx);
}

int luacv_push_cocos2d_Vec3(lua_State *L, const cocos2d::Vec3 &value)
{
    lua_createtable(L, 0, 3);
    tolua_rawsetfieldnumber(L, -1, "x", value.x);
    tolua_rawsetfieldnumber(L, -1, "y", value.y);
    tolua_rawsetfieldnumber(L, -1, "z", value.z);
    return 1;
}

void luacv_check_cocos2d_Vec3(lua_State *L, int idx, cocos2d::Vec3 *value)
{
    if (!value) {
        luaL_error(L, "value is NULL");
    }
    luaL_checktype(L, idx, LUA_TTABLE);
    value->x = (float)tolua_checkfieldnumber(L, idx, "x");
    value->y = (float)tolua_checkfieldnumber(L, idx, "y");
    value->z = (float)tolua_checkfieldnumber(L, idx, "z");
}

void luacv_pack_cocos2d_Vec3(lua_State *L, int idx, cocos2d::Vec3 *value)
{
    if (!value) {
        luaL_error(L, "value is NULL");
    }
    value->x = (float)luaL_checknumber(L, idx + 0);
    value->y = (float)luaL_checknumber(L, idx + 1);
    value->z = (float)luaL_checknumber(L, idx + 2);
}

int luacv_unpack_cocos2d_Vec3(lua_State *L, const cocos2d::Vec3 &value)
{
    lua_pushnumber(L, value.x);
    lua_pushnumber(L, value.y);
    lua_pushnumber(L, value.z);
    return 3;
}

bool luacv_is_cocos2d_Vec3(lua_State *L, int idx)
{
    return lua_istable(L, idx);
}