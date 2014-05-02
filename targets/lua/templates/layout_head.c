\#include "${out_file}.hpp"
#for header in $headers
\#include "${os.path.basename(header)}"
#end for
\#include "tolua_fix.h"
\#include "LuaBasicConversions.h"


static int lua_gc_callback_of_ref_class(lua_State* tolua_S)
{
    void* self = tolua_tousertype(tolua_S,1,0);
    
    cocos2d::Ref* ref = static_cast<cocos2d::Ref*>(self);
    
    CCLOG("gc: Ref type ( %s : %d)", typeid(*ref).name(), ref->getReferenceCount());
    ref->_luaID = 0;
    toluafix_remove_ccobject_by_refid(tolua_S, ref->_luaID);
    ref->release();

    return 0;
}
