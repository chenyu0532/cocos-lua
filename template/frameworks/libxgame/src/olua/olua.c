#include "olua/olua.h"

#define CLS_CLSIDX  (lua_upvalueindex(1))
#define CLS_ISAIDX  (lua_upvalueindex(2))
#define CLS_FUNCIDX (lua_upvalueindex(3))
#define CLS_GETIDX  (lua_upvalueindex(4))
#define CLS_SETIDX  (lua_upvalueindex(5))
#define CLS_ISA     ".isa"
#define CLS_FUNC    ".func"
#define CLS_GET     ".get"
#define CLS_SET     ".set"

#define VOIDCLS     "void *"
#define OBJ_REF_TABLE ((void *)olua_pushobj)
#define TRACEBACK (_traceback ? _traceback : dummy_traceback)
#define MAX(a, b)   ((a) > (b) ? (a) : (b))
#define MIN(a, b)   ((a) < (b) ? (a) : (b))

static lua_CFunction _traceback = NULL;

static inline bool strequal(const char *str1, const char *str2)
{
    return strcmp(str1, str2) == 0;
}

static inline bool strendwith(const char *src, const char *suffix)
{
    const char *pos = strstr(src, suffix);
    return !pos ? false : (src + strlen(src) == pos + strlen(suffix));
}

static int dummy_traceback(lua_State *L)
{
    return 0;
}

LUALIB_API lua_Integer olua_checkinteger(lua_State *L, int idx)
{
    luaL_checktype(L, idx, LUA_TNUMBER);
    return luaL_checkinteger(L, idx);
}

LUALIB_API lua_Number olua_checknumber(lua_State *L, int idx)
{
    luaL_checktype(L, idx, LUA_TNUMBER);
    return luaL_checknumber(L, idx);
}

LUALIB_API const char *olua_checkstring(lua_State *L, int idx)
{
    luaL_checktype(L, idx, LUA_TSTRING);
    return luaL_checkstring(L, idx);
}

LUALIB_API bool olua_checkboolean(lua_State *L, int idx)
{
    if (!(olua_isnoneornil(L, idx) || olua_isboolean(L, idx))) {
        luaL_checktype(L, idx, LUA_TBOOLEAN);
    }
    return lua_toboolean(L, idx);
}

LUALIB_API int olua_rawgetfield(lua_State *L, int idx, const char *field)
{
    idx = lua_absindex(L, idx);
    lua_pushstring(L, field);
    return lua_rawget(L, idx);
}

LUALIB_API void olua_rawsetfield(lua_State *L, int idx, const char *field)
{
    idx = lua_absindex(L, idx);
    lua_pushstring(L, field);
    lua_insert(L, -2);
    lua_rawset(L, idx);
}

LUALIB_API void olua_seterrfunc(lua_CFunction errfunc)
{
    _traceback = errfunc;
}

LUALIB_API const char *olua_typename(lua_State *L, int idx)
{
    const char *tn = NULL;
    if (lua_getmetatable(L, idx)) {
        if (olua_rawgetfield(L, -1, "classname") == LUA_TSTRING) {
            tn = lua_tostring(L, -1);
        }
        lua_pop(L, 2); // pop mt and value
    }
    return tn ? tn : lua_typename(L, lua_type(L, idx));
}

LUALIB_API const char *olua_tostring(lua_State *L, int idx)
{
    if (olua_isuserdata(L, idx)) {
        intptr_t p = (intptr_t)olua_touserdata(L, idx, void *);
        intptr_t p2 = (intptr_t)lua_topointer(L, idx);
        return lua_pushfstring(L, "%s: %p|%p", olua_typename(L, idx), p, p2);
    } else {
        intptr_t p = (intptr_t)lua_topointer(L, idx);
        return lua_pushfstring(L, "%s: %p", olua_typename(L, idx), p);
    }
}

LUALIB_API bool olua_isa(lua_State *L, int idx, const char *cls)
{
    bool isa = false;
    int top = lua_gettop(L);
    if (lua_getmetatable(L, idx)) {
        if (olua_rawgetfield(L, -1, CLS_ISA) == LUA_TTABLE) {
            olua_rawgetfield(L, -1, cls);
            isa = lua_toboolean(L, -1);
        }
    }
    lua_settop(L, top);
    return isa;
}

LUALIB_API void olua_getobjtable(lua_State *L)
{
    if (lua_rawgetp(L, LUA_REGISTRYINDEX, OBJ_REF_TABLE) != LUA_TTABLE) {
        lua_pop(L, 1); // pop nil
        lua_newtable(L);
        lua_pushvalue(L, -1);
        lua_pushstring(L, "kv");
        lua_setfield(L, -2, "__mode");  // mt.__mode = 'kv'
        lua_setmetatable(L, -2);        // mt.metatable = mt
        lua_pushvalue(L, -1);
        lua_rawsetp(L, LUA_REGISTRYINDEX, OBJ_REF_TABLE);
    }
}

LUALIB_API int olua_pushobj(lua_State *L, void *obj, const char *cls)
{
    int status = OLUA_OBJ_EXIST;
    
    if (!obj) {
        lua_pushnil(L);
        return status;
    }
    
    olua_getobjtable(L);
    
    if (lua_rawgetp(L, -1, obj) == LUA_TNIL) {      // L: mapping obj?
        lua_pop(L, 1);                              // L: mapping
        olua_newuserdata(L, obj, void *);           // L: mapping obj
        luaL_setmetatable(L, cls);                  // L: mapping obj
        lua_pushvalue(L, -1);                       // L: mapping obj obj
        lua_rawsetp(L, -3, obj);                    // L: mapping obj
        status = OLUA_OBJ_NEW;
        
        if (!lua_getmetatable(L, -1)) {
            luaL_error(L, "metatable not found: %s", cls);
        } else {
            lua_pop(L, 1);
        }
    }
    
    if (!strequal(cls, VOIDCLS) && luaL_testudata(L, -1, VOIDCLS)) {
        luaL_setmetatable(L, cls);
        status = OLUA_OBJ_UPDATE;
    }
    
#ifdef OLUA_DEBUG
    olua_checkobj(L, -1, cls);
#endif
    
    lua_remove(L, -2);                              // L: obj
    return status;
}

LUALIB_API bool olua_getobj(lua_State *L, void *obj)
{
    if (!obj) {
        return false;
    }
    olua_getobjtable(L);                            // L: uv
    if (lua_rawgetp(L, -1, obj) == LUA_TUSERDATA) { // L: uv obj
        lua_remove(L, -2);                          // L: obj
        return true;
    } else {
        lua_pop(L, 2);
        return false;
    }
}

void olua_getusertable(lua_State *L, int idx)
{
    idx = lua_absindex(L, idx);
    if (lua_getuservalue(L, idx) != LUA_TTABLE) {
#ifdef OLUA_DEBUG
        if (!olua_isnil(L, -1)) {
            luaL_error(L, "user value must be a table!");
        }
#endif
        lua_pop(L, 1);
        lua_createtable(L, 0, 4);
        lua_pushvalue(L, -1);
        lua_setuservalue(L, idx);
    }
}

LUALIB_API const char *olua_setcallback(lua_State *L, void *obj, const char *tag, int func, olua_callback_tag_t mode)
{
    static int ref = 0;
    const char *field = NULL;
    
    func = lua_absindex(L, func);
    luaL_checktype(L, func, LUA_TFUNCTION);
    
    if (!olua_getobj(L, obj)) {                         // L: obj
        luaL_error(L, "obj userdata not found");
    }
    
    olua_getusertable(L, -1);                           // L: obj ct
    lua_remove(L, -2);                                  // L: ct
    
    if (mode == OLUA_CALLBACK_TAG_REPLACE) {
        lua_pushnil(L);                                 // L: ct k
        while (lua_next(L, -2)) {                       // L: ct k v
            if (olua_isstring(L, -2)) {
                const char *s = lua_tostring(L, -2);
                if (strendwith(s, tag)) {
                    field = s;
                    lua_pop(L, 1);                      // L: ct k
                    break;
                }
            }
            lua_pop(L, 1);                              // L: ck k
        }
    } else {
#ifdef OLUA_DEBUG
        if (mode != OLUA_CALLBACK_TAG_NEW) {
            luaL_error(L, "unsupport callback tag: %d", (int)mode);
        }
#endif
    }
    
    if (!field) {
        field = lua_pushfstring(L, ".callback#%d@%s", ++ref, tag);
    }
    
    lua_pushvalue(L, func);                             // L: ct k  v
    olua_rawsetfield(L, -3, field);                     // L: ct k
    lua_remove(L, -2);                                  // L: k
    return lua_tostring(L, -1);
}

static bool shouldremovecallback(const char *field, const char *tag, olua_callback_tag_t mode)
{
    if (mode == OLUA_CALLBACK_TAG_WILDCARD) {
        return strstr(field, tag) != NULL;
    } else if (mode == OLUA_CALLBACK_TAG_ENDWITH) {
        return strendwith(field, tag);
    } else {
        return false;
    }
}

LUALIB_API void olua_removecallback(lua_State *L, void *obj, const char *tag, olua_callback_tag_t mode)
{
    int top = lua_gettop(L);
    if (olua_getobj(L, obj)) {
        olua_getusertable(L, -1);
        if (mode == OLUA_CALLBACK_TAG_EQUAL) {
            lua_pushnil(L);                                 // L: ct nil
            olua_rawsetfield(L, -2, tag);                   // L: ct
        } else {
            lua_pushnil(L);                                 // L: ct k
            while (lua_next(L, -2)) {                       // L: ct k v
                if (olua_isstring(L, -2)) {
                    const char *field = lua_tostring(L, -2);
                    if (shouldremovecallback(field, tag, mode)) {
                        lua_pushvalue(L, -2);               // L: ct k v k
                        lua_pushnil(L);                     // L: ct k v k nil
                        lua_rawset(L, -5);                  // L: ct k v
                    }
                }
                lua_pop(L, 1);                              // L: ct k
            }
        }
    }
    lua_settop(L, top);
}

LUALIB_API bool olua_callback(lua_State *L, void *obj, const char *field, int n)
{
    int top = lua_gettop(L) - n;
    bool ret = false;
    
    if (olua_getobj(L, obj)) {                                  // L: arg...n obj
        olua_getusertable(L, -1);                               // L: arg...n obj uv
        if (olua_rawgetfield(L, -1, field) == LUA_TFUNCTION) {  // L: arg...n obj uv callback
            lua_insert(L, top + 1);                             // L: callback arg...n obj uv
            lua_pop(L, 2);                                      // L: callback arg...n
            lua_pushcfunction(L, TRACEBACK);                    // L: callback arg...n errfunc
            lua_insert(L, top + 1);                             // L: errfunc callback arg...n
            ret = lua_pcall(L, n, 1, top + 1) == LUA_OK;        // L: errfunc result
            lua_remove(L, -2);                                  // L: result
        }
    }
    
    if (!ret) {
        lua_settop(L, top);
        lua_pushnil(L);
    }
    
    return ret;
}

LUALIB_API int olua_getvariable(lua_State *L, int idx)
{
    int type = LUA_TNIL;
    olua_getusertable(L, idx);      // L: k uv
    lua_insert(L, -2);              // L: uv k
    type = lua_rawget(L, -2);       // L: uv v
    lua_remove(L, -2);              // L: v
    return type;
}

LUALIB_API void olua_setvariable(lua_State *L, int idx)
{
    olua_getusertable(L, idx);      // L: k v uv
    lua_insert(L, -3);              // L: uv k v
    lua_rawset(L, -3);              // L: uv          idx.uservalue[k] = v
    lua_pop(L, 1);                  // L:
}

static const char *olua_pushrefkey(lua_State *L, const char *field)
{
    return lua_pushfstring(L, ".ref.%s", field);
}

static void olua_getreftable(lua_State *L, int idx, const char *field)
{
    idx = lua_absindex(L, idx);
    field = olua_pushrefkey(L, field);  // L: refkey
    luaL_getsubtable(L, idx, field);    // L: refkey reftable
    lua_remove(L, -2);                  // L: reftable
}

LUALIB_API void olua_singleref(lua_State *L, int obj, const char *field, int vidx)
{
    if (olua_isuserdata(L, vidx)) {
        obj = lua_absindex(L, obj);
        vidx = lua_absindex(L, vidx);
        olua_getusertable(L, obj);              // L: uv
        olua_pushrefkey(L, field);              // L: uv refk
        lua_pushvalue(L, vidx);                 // L: uv refk refv
        lua_rawset(L, -3);                      // L: uv      uv[refk] = refv
        lua_pop(L, 1);                          // L:
    }
}

LUALIB_API void olua_singleunref(lua_State *L, int obj, const char *field)
{
    obj = lua_absindex(L, obj);
    olua_getusertable(L, obj);              // L: uv
    olua_pushrefkey(L, field);              // L: uv refk
    lua_pushnil(L);                         // L: uv refk nil
    lua_rawset(L, -3);                      // L: uv      uv[refk] = nil
    lua_pop(L, 1);                          // L:
}

LUALIB_API void olua_mapref(lua_State *L, int obj, const char *t, int vidx)
{
    if (olua_isuserdata(L, vidx)) {
        obj = lua_absindex(L, obj);
        vidx = lua_absindex(L, vidx);
        olua_getusertable(L, obj);              // L: uv
        olua_getreftable(L, -1, t);             // L: uv t
        lua_pushvalue(L, vidx);                 // L: uv t v
        lua_pushboolean(L, true);               // L: uv t v true
        lua_rawset(L, -3);                      // L: uv t        t[v] = true
        lua_pop(L, 2);
    }
}

LUALIB_API void olua_mapunref(lua_State *L, int obj, const char *t, int vidx)
{
    if (olua_isuserdata(L, vidx)) {
        obj = lua_absindex(L, obj);
        vidx = lua_absindex(L, vidx);
        olua_getusertable(L, obj);              // L: uv
        olua_getreftable(L, -1, t);             // L: uv t
        lua_pushvalue(L, vidx);                 // L: uv t v
        lua_pushnil(L);                         // L: uv t v nil
        lua_rawset(L, -3);                      // L: uv t        t[v] = nil
        lua_pop(L, 2);
    }
}

LUALIB_API void olua_mapwalkunref(lua_State *L, int obj, const char *t, lua_CFunction walk)
{
    obj = lua_absindex(L, obj);
    olua_getusertable(L, obj);              // L: uv
    olua_getreftable(L, -1, t);             // L: uv t
    lua_pushnil(L);                         // L: uv t k
    while (lua_next(L, -2)) {               // L: uv t k v
        if (walk(L)) { // remove?
            lua_pushvalue(L, -2);           // L: uv t k v k
            lua_pushnil(L);                 // L: uv t k v k nil
            lua_rawset(L, -5);              // L: uv t k v
        }
        lua_pop(L, 1);                      // L: uv t k
    }
    lua_pop(L, 2);
}

LUALIB_API void olua_unrefall(lua_State *L, int obj, const char *t)
{
    olua_getusertable(L, obj);              // L: uv
    lua_pushnil(L);                         // L: uv nil
    lua_setfield(L, -2, t);                 // L: uv     uv[t] = nil
}

LUALIB_API void olua_arrayref(lua_State *L, int obj, const char *t, int vidx)
{
    if (olua_isuserdata(L, vidx)) {
        int len;
        obj = lua_absindex(L, obj);
        vidx = lua_absindex(L, vidx);
        olua_getusertable(L, obj);              // L: uv
        olua_getreftable(L, -1, t);             // L: uv t
        lua_pushnil(L);                         // L: uv t k
        while (lua_next(L, -2)) {               // L: uv t k v
            if (lua_rawequal(L, vidx, -1)) {
                lua_pop(L, 4);                  // L:
                return;
            }
            lua_pop(L, 1);                      // L: uv t k
        }
        len = (int)lua_rawlen(L, -1);
        lua_pushvalue(L, vidx);                 // L: uv t v
        lua_rawseti(L, -2, len + 1);            // L: uv t
        lua_pop(L, 2);                          // L:
    }
}

LUALIB_API void olua_arrayunref(lua_State *L, int obj, const char *t, int idx)
{
    size_t len;
    obj = lua_absindex(L, obj);
    olua_getusertable(L, obj);              // L: uv
    olua_getreftable(L, -1, t);             // L: uv t
    len = (size_t)lua_rawlen(L, -1);
    idx += idx < 0 ? (len + 1) : 0;
    if (idx >= 1 && idx <= len) {
        for ( ; idx < len; idx++) {
            lua_rawgeti(L, -1, idx + 1);    // L: uv t (idx+1)
            lua_rawseti(L, -2, idx);        // L: uv t      t[idx] = t[idx + 1]
        }
        lua_pushnil(L);
        lua_rawseti(L, -2, idx);
    }
    lua_pop(L, 2);
}

LUALIB_API size_t olua_arraylen(lua_State *L, int obj, const char *t)
{
    size_t len;
    olua_getusertable(L, obj);              // L: uv
    olua_getreftable(L, -1, t);             // L: uv t
    len = lua_rawlen(L, -1);
    lua_pop(L, 2);
    return len;
}

LUALIB_API void *olua_checkobj(lua_State *L, int idx, const char *cls)
{
    if (olua_isa(L, idx, cls)) {
        return olua_toobj(L, idx, cls);
    } else {
        luaL_error(L, "#%d argument error, expect: '%s', got '%s'", idx,
            cls, olua_typename(L, idx));
    }
    return NULL;
}

LUALIB_API void *olua_toobj(lua_State *L, int idx, const char *cls)
{
    if (olua_isuserdata(L, idx)) {
        void *obj = olua_touserdata(L, idx, void *);
        if (obj) {
            return obj;
        } else {
            luaL_error(L, "object live from gc");
        }
    } else {
        luaL_error(L, "#%d argument error, expect: '%s', got '%s'", idx,
            cls, lua_typename(L, lua_type(L, idx)));
    }
    return NULL;
}

LUALIB_API void olua_callgc(lua_State *L, int idx, bool isarrary)
{
    int top = lua_gettop(L);
    idx = lua_absindex(L, idx);
    if (isarrary) {
        if (olua_istable(L, idx)) {
            lua_pushnil(L);                     // L: k
            while (lua_next(L, idx)) {          // L: k v
                olua_callgc(L, -1, false);
                lua_pop(L, 1);
            }
        }
    } else if (olua_isuserdata(L, idx)) {
        void *obj = olua_touserdata(L, idx, void *);
        lua_pushcfunction(L, TRACEBACK);
        if (lua_getfield(L, idx, "__gc") == LUA_TFUNCTION) {
            lua_pushvalue(L, idx);
            lua_pcall(L, 1, 0, top + 1);
        }
        if (obj) {
            olua_getobjtable(L);
            lua_pushnil(L);
            lua_rawsetp(L, -2, obj);
        }
    }
    lua_settop(L, top);
}

static bool ismetafunc(lua_State *L, int idx, const char *func)
{
    static const char *const tm[] = {
        "__index", "__newindex",
        "__gc", "__mode", "__len", "__eq",
        "__add", "__sub", "__mul", "__mod", "__pow",
        "__div", "__idiv",
        "__band", "__bor", "__bxor", "__shl", "__shr",
        "__unm", "__bnot", "__lt", "__le",
        "__concat", "__call",
        NULL
    };
    
    if (!func && olua_isstring(L, idx)) {
        func = lua_tostring(L, idx);
    }
    
    if (func) {
        for (int i = 0;; ++i) {
            const char *name = tm[i];
            if (!name) {
                break;
            } else if (strequal(name, func)) {
                return true;
            }
        }
    }
    
    return false;
}


static int trycacheget(lua_State *L, int t, int kidx)
{
#define NILVALUE ((void *)trycacheget)
    int type;
    kidx = lua_absindex(L, kidx);
    lua_pushvalue(L, t);                        // L: t
    lua_pushvalue(L, kidx);                     // L: t k
    type = lua_rawget(L, -2);                   // L: t v
    if (type == LUA_TNIL) {
        lua_pop(L, 1);                          // L: t
        lua_pushvalue(L, kidx);                 // L: t k
        type = lua_gettable(L, -2);             // L: t v
        lua_pushvalue(L, kidx);                 // L: t v k
        if (type == LUA_TNIL) {
            lua_pushlightuserdata(L, NILVALUE); // L: t v k v
        } else {
            lua_pushvalue(L, -2);               // L: t v k v
        }
        lua_rawset(L, -4);                      // L: t v
    }
    if (type == LUA_TLIGHTUSERDATA && lua_touserdata(L, -1) == NILVALUE) {
        lua_pop(L, 1);
        lua_pushnil(L);
        type = LUA_TNIL;
    }
    lua_remove(L, -2);                          // L: v
    return type;
}

static int cls_index(lua_State *L)
{
    // try getter
    lua_settop(L, 2);
    if (trycacheget(L, CLS_GETIDX, 2) != LUA_TNIL) {
        lua_pushvalue(L, 1);                        // L: t k getter t
        lua_call(L, 1, 1);                          // L: t k ret
        return 1;
    }
    
    // try variable
    if (lua_type(L, 1) == LUA_TUSERDATA) {
        lua_settop(L, 2);
        lua_pushvalue(L, 2);
        if (olua_getvariable(L, 1) != LUA_TNIL) {
            return 1;
        }
    }
    
    // try func
    lua_settop(L, 2);
    if (trycacheget(L, CLS_FUNCIDX, 2) != LUA_TNIL) {
        return 1;
    }
    
    return 1;
}

static int cls_newindex(lua_State *L)
{
    // try setter
    lua_settop(L, 3);
    if (trycacheget(L, CLS_SETIDX, 2) != LUA_TNIL) {
        lua_pushvalue(L, 1);                    // L: t k v setter t
        lua_pushvalue(L, 3);                    // L: t k v setter t v
        lua_call(L, 2, 0);                      // L: t k v
        return 0;
    }
    
    if (olua_istable(L, 1)) {
        lua_settop(L, 3);                       // L: t k v
        lua_pushvalue(L, CLS_FUNCIDX);          // L: t k v .func
        lua_pushvalue(L, 2);                    // L: t k v .func k
        lua_pushvalue(L, 3);                    // L: t k v .func k v
        lua_rawset(L, -3);                      // L: t k v .func
        lua_pop(L, 1);                          // L: t k v
        
        if (ismetafunc(L, 2, NULL)) {
            lua_pushvalue(L, CLS_CLSIDX);       // L: t k v class
            lua_pushvalue(L, 2);                // L: t k v class k
            lua_pushvalue(L, 3);                // L: t k v class k v
            lua_rawset(L, -3);                  // L: t k v class
            lua_pop(L, 1);
        }
        
        return 0;
    }
    
    lua_settop(L, 3);
    if (trycacheget(L, CLS_GETIDX, 2) != LUA_TNIL) {
        luaL_error(L, "readonly property: %s", lua_tostring(L, 2));
    }
    
    if (lua_type(L, 1) == LUA_TUSERDATA) {
        lua_settop(L, 3);
        olua_setvariable(L, 1);
    } else {
        luaL_checktype(L, 1, LUA_TUSERDATA);
    }
    
    return 0;
}

static int cls_tostring(lua_State *L)
{
    olua_tostring(L, 1);
    
    return 1;
}

static void create_table(lua_State *L, int idx, const char *field, const char *supercls, bool copy)
{
    idx = lua_absindex(L, idx);
    
    lua_newtable(L);                        // L: t
    if (supercls) {
        luaL_getmetatable(L, supercls);     // L: t super
        olua_rawgetfield(L, -1, field);     // L: t super fv
        lua_createtable(L, 0, 1);           // L: t super fv mt
        lua_pushvalue(L, -2);               // L: t super fv mt fv
        olua_rawsetfield(L, -2, "__index"); // L: t super fv mt
        lua_setmetatable(L, -4);            // L: t super fv
        
        if (copy) {
            lua_pushnil(L);                 // L: t super fv k
            while (lua_next(L, -2)) {       // L: t super fv k v
                lua_pushvalue(L, -2);       // L: t super fv k v k
                lua_insert(L, -2);          // L: t super fv k k v
                lua_rawset(L, -6);          // L: t super fv k
            }                               // L: t super fv
        }
        
        lua_pop(L, 2);                      // L: t
    }
    
    lua_pushvalue(L, -1);                   // L: t t
    olua_rawsetfield(L, idx, field);        // L: t     idx[field] = t
}

static void copysupermetafunc(lua_State *L, int idx, const char *supercls)
{
    idx = lua_absindex(L, idx);             // L: mt
    if (supercls) {
        luaL_getmetatable(L, supercls);     // L: mt super
        lua_pushnil(L);                     // L: mt super k
        while (lua_next(L, -2)) {           // L: mt super k v
            if (ismetafunc(L, -2, NULL)) {
                lua_pushvalue(L, -2);       // L: mt super k v k
                lua_pushvalue(L, -2);       // L: mt super k v k v
                lua_rawset(L, idx);         // L: mt super k v
            }
            lua_pop(L, 1);                  // L: mt super k
        }                                   // L: mt super
        lua_pop(L, 1);                      // L: mt
    }
}

LUALIB_API void oluacls_class(lua_State *L, const char *cls, const char *super)
{
    if (super != NULL) {
        if (luaL_getmetatable(L, super) == LUA_TNIL) {
            luaL_error(L, "'%s' super class not found: %s", cls, super);
        }
        lua_pop(L, 1);
    } else {
        if (!strequal(cls, VOIDCLS)) {
            oluacls_class(L, VOIDCLS, NULL);
            lua_pop(L, 1);
            super = VOIDCLS;
        }
    }
    
    if (luaL_getmetatable(L, cls) == LUA_TNIL) {
        int idx = lua_gettop(L);
        lua_pop(L, 1);
        luaL_newmetatable(L, cls);                      // L: mt
        lua_pushvalue(L, -1);                           // L: mt mt
        copysupermetafunc(L, -1, super);
        create_table(L, idx, CLS_ISA, super, true);     // L: mt mt .isa
        create_table(L, idx, CLS_FUNC, super, false);   // L: mt mt .isa .func
        create_table(L, idx, CLS_GET, super, false);    // L: mt mt .isa .func .get
        create_table(L, idx, CLS_SET, super, false);    // L: mt mt .isa .func .get .set
        
        static const luaL_Reg lib[] = {
            {"__index", cls_index},
            {"__newindex", cls_newindex},
            {"__tostring", cls_tostring},
            {NULL, NULL}
        };
        luaL_setfuncs(L, lib,  5);                      // L: mt
        
        lua_pushvalue(L, -1);
        oluacls_const(L, "class");
        lua_pushstring(L, cls);
        oluacls_const(L, "classname");
        
        if (super) {
            luaL_getmetatable(L, super);
            oluacls_const(L, "super");
        }
        
        olua_rawgetfield(L, idx, CLS_ISA);
        lua_pushstring(L, cls);
        lua_pushboolean(L, true);
        lua_rawset(L, -3);
        lua_pop(L, 1);
    }
}

LUALIB_API void oluacls_createclassproxy(lua_State *L)
{
    lua_newtable(L);                        // L: cls p
    lua_createtable(L, 0, 2);               // L: cls p pmt
    lua_getfield(L, -3, "__index");         // L: cls p pmt __index
    olua_rawsetfield(L, -2, "__index");     // L: cls p pmt
    lua_getfield(L, -3, "__newindex");      // L: cls p pmt __newindex
    olua_rawsetfield(L, -2, "__newindex");  // L: cls p pmt
    lua_setmetatable(L, -2);                // L: cls p
}

static void aux_setfunc(lua_State *L, const char *t, const char *field, lua_CFunction func)
{
    if (func) {
        olua_rawgetfield(L, -1, t);         // L: cls t
        lua_pushcfunction(L, func);         // L: cls t func
        olua_rawsetfield(L, -2, field);     // L: cls t      t[field] = func
        lua_pop(L, 1);
    }
}

LUALIB_API void oluacls_property(lua_State *L, const char *field, lua_CFunction getter, lua_CFunction setter)
{
    aux_setfunc(L, CLS_GET, field, getter);
    aux_setfunc(L, CLS_SET, field, setter);
}

LUALIB_API void oluacls_setfunc(lua_State *L, const char *name, lua_CFunction func)
{
    aux_setfunc(L, CLS_FUNC, name, func);
    if (func && ismetafunc(L, 0, name)) {
        lua_pushcfunction(L, func);
        olua_rawsetfield(L, -2, name);
    }
}

static int cls_index_const(lua_State *L)
{
    lua_pushvalue(L, lua_upvalueindex(1));
    return 1;
}

LUALIB_API void oluacls_const(lua_State *L, const char *field)
{
    lua_pushvalue(L, -1);                       // L: cls v v
    olua_rawsetfield(L, -3, field);             // L: cls v
    lua_pushcclosure(L, cls_index_const, 1);    // L: cls getter
    olua_rawgetfield(L, -2, CLS_GET);           // L: cls getter .get
    lua_insert(L, -2);                          // L: cls .get getter
    olua_rawsetfield(L, -2, field);             // L: cls .get
    lua_pop(L, 1);                              // L: cls
}

LUALIB_API int olua_push_bool(lua_State *L, bool value)
{
    lua_pushboolean(L, value);
    return 1;
}

LUALIB_API void olua_check_bool(lua_State *L, int idx, bool *value)
{
    *value = olua_checkboolean(L, idx);
}

LUALIB_API void olua_opt_bool(lua_State *L, int idx, bool *value, bool def)
{
    *value = olua_isnoneornil(L, idx) ? def : lua_toboolean(L, idx) != 0;
}

LUALIB_API int olua_push_string(lua_State *L, const char *value)
{
    lua_pushstring(L, value);
    return 1;
}

LUALIB_API void olua_check_string(lua_State *L, int idx, const char **value)
{
    *value = olua_checkstring(L, idx);
}

LUALIB_API void olua_opt_string(lua_State *L, int idx, const char **value, const char *def)
{
    *value = luaL_optstring(L, idx, def);
}

LUALIB_API int olua_push_number(lua_State *L, lua_Number value)
{
    lua_pushnumber(L, value);
    return 1;
}

LUALIB_API void olua_check_number(lua_State *L, int idx, lua_Number *value)
{
    *value = olua_checknumber(L, idx);
}

LUALIB_API void olua_opt_number(lua_State *L, int idx, lua_Number *value, lua_Number def)
{
    *value = luaL_optnumber(L, idx, def);
}

LUALIB_API int olua_push_int(lua_State *L, lua_Integer value)
{
    lua_pushinteger(L, value);
    return 1;
}

LUALIB_API void olua_check_int(lua_State *L, int idx, lua_Integer *value)
{
    *value = olua_checkinteger(L, idx);
}

LUALIB_API void olua_opt_int(lua_State *L, int idx, lua_Integer *value, lua_Integer def)
{
    *value = luaL_optinteger(L, idx, def);
}

LUALIB_API int olua_push_uint(lua_State *L, lua_Unsigned value)
{
    return olua_push_int(L, (lua_Integer)value);
}

LUALIB_API void olua_check_uint(lua_State *L, int idx, lua_Unsigned *value)
{
    *value = (lua_Unsigned)olua_checkinteger(L, idx);
}

LUALIB_API void olua_opt_uint(lua_State *L, int idx, lua_Unsigned *value, lua_Unsigned def)
{
    *value = (lua_Unsigned)luaL_optinteger(L, idx, (lua_Integer)def);
}

LUALIB_API int olua_push_obj(lua_State *L, void *obj, const char *cls)
{
    olua_pushobj(L, obj, cls);
    return 1;
}

LUALIB_API void olua_check_obj(lua_State *L, int idx, void **value, const char *cls)
{
    *value = olua_checkobj(L, idx, cls);
}

LUALIB_API void olua_to_obj(lua_State *L, int idx, void **value, const char *cls)
{
    *value = olua_toobj(L, idx, cls);
}

static void auxchecktype(lua_State *L, int t, const char *field, int type, bool isinteger)
{
    int idx = lua_gettop(L) + 1;
    lua_getfield(L, t, field);
    
    if ((isinteger && !olua_isinteger(L, idx)) ||
        (!isinteger && lua_type(L, idx) != type)) {
        const char *msg, *typearg;
        const char *tname = lua_typename(L, type);
        if (isinteger) {
            tname = "integer";
        }
        if (luaL_getmetafield(L, idx, "__name") == LUA_TSTRING) {
            typearg = lua_tostring(L, -1);
        } else if (lua_type(L, idx) == LUA_TLIGHTUSERDATA) {
            typearg = "light userdata";
        } else {
            typearg = luaL_typename(L, idx);
        }
        msg = lua_pushfstring(L, "olua check '%s': %s expected, got %s", field, tname, typearg);
        luaL_argerror(L, idx, msg);
    }
}

LUALIB_API const char *olua_checkfieldstring(lua_State *L, int idx, const char *field)
{
    const char *value;
    auxchecktype(L, idx, field, LUA_TSTRING, false);
    value = lua_tostring(L, -1);
    lua_pop(L, 1);
    return value;
}

LUALIB_API lua_Number olua_checkfieldnumber(lua_State *L, int idx, const char *field)
{
    lua_Number value;
    auxchecktype(L, idx, field, LUA_TNUMBER, false);
    value = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return value;
}

LUALIB_API lua_Integer olua_checkfieldinteger(lua_State *L, int idx, const char *field)
{
    lua_Integer value;
    auxchecktype(L, idx, field, LUA_TNUMBER, true);
    value = lua_tointeger(L, -1);
    lua_pop(L, 1);
    return value;
}

LUALIB_API bool olua_checkfieldboolean(lua_State *L, int idx, const char *field)
{
    bool value;
    auxchecktype(L, idx, field, LUA_TBOOLEAN, false);
    value = lua_toboolean(L, -1);
    lua_pop(L, 1);
    return value;
}

LUALIB_API void olua_rawsetfieldnumber(lua_State *L, int idx, const char *field, lua_Number value)
{
    idx = lua_absindex(L, idx);
    lua_pushnumber(L, value);
    olua_rawsetfield(L, idx, field);
}

LUALIB_API void olua_rawsetfieldinteger(lua_State *L, int idx, const char *field, lua_Integer value)
{
    idx = lua_absindex(L, idx);
    lua_pushinteger(L, value);
    olua_rawsetfield(L, idx, field);
}

LUALIB_API void olua_rawsetfieldstring(lua_State *L, int idx, const char *field, const char *value)
{
    idx = lua_absindex(L, idx);
    lua_pushstring(L, value);
    olua_rawsetfield(L, idx, field);
}

LUALIB_API void olua_rawsetfieldboolean(lua_State *L, int idx, const char *field, bool value)
{
    idx = lua_absindex(L, idx);
    lua_pushboolean(L, value);
    olua_rawsetfield(L, idx, field);
}