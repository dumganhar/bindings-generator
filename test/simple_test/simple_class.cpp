/**
 * Simple example of a C++ class that can be binded using the
 * automatic script generator
 */

#include "simple_class.h"
#include "tolua++.h"
#include "CCPlatformMacros.h"

void testErrlog(const char * pszFormat, ...)
{
    char szBuf[1024] = { 0 };
    
    va_list ap;
    va_start(ap, pszFormat);
    vsnprintf(szBuf, 1024, pszFormat, ap);
    va_end(ap);
    printf("%s", szBuf);
    printf("\n");
    fflush(stdout);
}

void luaval_to_native_err(lua_State* L,const char* msg,tolua_Error* err)
{
    if (NULL == L || NULL == err || NULL == msg || 0 == strlen(msg))
        return;

#if COCOS2D_DEBUG >= 1
    if (msg[0] == '#')
    {
       const char* expected = err->type;
        const char* provided = tolua_typename(L,err->index);
        if (msg[1]=='f')
        {
            int narg = err->index;
            if (err->array)
                testErrlog("%s\n     argument #%d is array of '%s'; array of '%s' expected.\n",msg+2,narg,provided,expected);
            else
                testErrlog("%s\n     argument #%d is '%s'; '%s' expected.\n",msg+2,narg,provided,expected);
        }
        else if (msg[1]=='v')
        {
            if (err->array)
                testErrlog("%s\n     value is array of '%s'; array of '%s' expected.\n",msg+2,provided,expected);
            else
                testErrlog("%s\n     value is '%s'; '%s' expected.\n",msg+2,provided,expected);
        }
    }
#endif
}

bool luaval_to_int32(lua_State* L,int lo,int* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
    if (ok)
    {
        *outValue = (int)tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_uint32(lua_State* L, int lo, unsigned int* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
    if (ok)
    {
        *outValue = (unsigned int)tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_uint16(lua_State* L,int lo,uint16_t* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
    if (ok)
    {
        *outValue = (unsigned char)tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_boolean(lua_State* L,int lo,bool* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_isboolean(L,lo,0,&tolua_err))
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
    if (ok)
    {
        *outValue = (bool)tolua_toboolean(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_number(lua_State* L,int lo,double* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
    if (ok)
    {
        *outValue = tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_long_long(lua_State* L,int lo,long long* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif 
    
    if (ok)
    {
        *outValue = (long long)tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_std_string(lua_State* L, int lo, std::string* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_iscppstring(L,lo,0,&tolua_err))
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
    if (ok)
    {
        *outValue = tolua_tocppstring(L,lo,NULL);
    }
    
    return ok;
}

bool luaval_to_const_char(lua_State* L, int lo, const char* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_isstring(L,lo,0,&tolua_err))
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
    if (ok)
    {
        outValue = tolua_tostring(L,lo,NULL);
    }
    
    return ok;
}

bool luaval_to_point(lua_State* L,int lo,Point* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
       luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
    if (ok)
    {
        lua_pushstring(L, "x");
        lua_gettable(L, lo);
        outValue->x = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "y");
        lua_gettable(L, lo);
        outValue->y = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    return ok;
}

void point_to_luaval(lua_State* L,const Point& pt)
{
    if (NULL  == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "x");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) pt.x);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "y");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) pt.y);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

bool luaval_to_rect(lua_State* L,int lo,Rect* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif

    if (ok)
    {
        lua_pushstring(L, "x");
        lua_gettable(L,lo);
        outValue->x = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "y");
        lua_gettable(L,lo);
        outValue->y = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "width");
        lua_gettable(L,lo);
        outValue->width = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "height");
        lua_gettable(L,lo);
        outValue->height = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    
    return ok;
}

void rect_to_luaval(lua_State* L,const Rect& rt)
{
    if (NULL  == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "x");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) rt.x);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "y");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) rt.y);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "width");                         /* L: table key */
    lua_pushnumber(L, (lua_Number) rt.width);           /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "height");                        /* L: table key */
    lua_pushnumber(L, (lua_Number) rt.height);          /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

bool luaval_to_size(lua_State* L,int lo,Size* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
    if (ok)
    {
        lua_pushstring(L, "width");  /* L: paramStack key */
        lua_gettable(L,lo);/* L: paramStack paramStack[lo][key] */
        outValue->width = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);/* L: paramStack*/
        
        lua_pushstring(L, "height");
        lua_gettable(L,lo);
        outValue->height = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    
    return ok;
}

void size_to_luaval(lua_State* L,const Size& sz)
{
    if (NULL  == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "width");                         /* L: table key */
    lua_pushnumber(L, (lua_Number) sz.width);           /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "height");                        /* L: table key */
    lua_pushnumber(L, (lua_Number) sz.height);          /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

bool luaval_to_color4b(lua_State* L,int lo,Color4B* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
    if(ok)
    {
        lua_pushstring(L, "r");
        lua_gettable(L,lo);
        outValue->r = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "g");
        lua_gettable(L,lo);
        outValue->g = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "b");
        lua_gettable(L,lo);
        outValue->b = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "a");
        lua_gettable(L,lo);
        outValue->a = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    
    return ok;
}

void color4b_to_luaval(lua_State* L,const Color4B& cc)
{
    if (NULL  == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "r");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.r);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "g");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.g);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "b");                         /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.b);           /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "a");                        /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.a);          /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

bool luaval_to_color4f(lua_State* L,int lo,Color4F* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
    if (ok)
    {
        lua_pushstring(L, "r");
        lua_gettable(L,lo);
        outValue->r = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "g");
        lua_gettable(L,lo);
        outValue->g = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "b");
        lua_gettable(L,lo);
        outValue->b = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "a");
        lua_gettable(L,lo);
        outValue->a = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    
    return ok;
}

void color4f_to_luaval(lua_State* L,const Color4F& cc)
{
    if (NULL  == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "r");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.r);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "g");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.g);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "b");                         /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.b);           /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "a");                        /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.a);          /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

bool luaval_to_color3b(lua_State* L,int lo,Color3B* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
    if (ok)
    {
        lua_pushstring(L, "r");
        lua_gettable(L,lo);
        outValue->r = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "g");
        lua_gettable(L,lo);
        outValue->g = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "b");
        lua_gettable(L,lo);
        outValue->b = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    
    return ok;
}

void color3b_to_luaval(lua_State* L,const Color3B& cc)
{
    if (NULL  == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "r");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.r);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "g");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.g);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "b");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.b);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

