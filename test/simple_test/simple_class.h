#ifndef __SIMPLE_CLASS_H__
#define __SIMPLE_CLASS_H__

#include <string>
#include <stdint.h>

extern "C" {
#include "../../../../scripting/lua/luajit/include/lua.h"
}

namespace cocos2dTest {
enum someThingEnumerated {
	kValue1 = 1,
	kValue2,
	kValue3,
	kValue4
};

class Point
{
public:
    Point(int _x = 0,int _y = 0):x(_x),y(_y)
    {
        printf("Point Constutor:x = %d,y = %d\n",x,y);
    }
    void foo(){}
    int x;
    int y;
};
    
class Rect
{
public:
    Rect(){}
    int x;
    int y;
    int width;
    int height;
};

class Size
{
public:
    Size()
    {}
    float width;
    float height;
};
    
class Color4B
{
public:
    Color4B(){}
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};
    
class Color4F
{
public:
    Color4F(){}
    float r;
    float g;
    float b;
    float a;
};

class Color3B
{
public:
    Color3B(){}
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

class SimpleFatherClass
{
public:
	void fatherMethod1(int test)
	{
		printf("SimpleFatherClass method: fatherMethod1... %d", test);
	}
};
    
class SimpleSecondClass
{
};

class SimpleNativeClass:public SimpleFatherClass
{
public:
    SimpleNativeClass(int aaa = 0, int bbb = 1) { printf("SimpileNativeClass constructor..."); }

	int setSomeField(int f, int b) {
        printf("SimpleNativeClass method: setSomeField... %d, %d\n", f, b);
		return 1;
	}

	unsigned int setUnsignedint(unsigned int value,unsigned int b = 0)
	{
		printf("SimpleNativeClass method: setUnsignedint... %u,%u\n", value,b);
		return 2;
	}

	unsigned char setUnsignedchar(unsigned char value,unsigned int b = 0)
	{
		printf("SimpleNativeClass method: setUnsignedchar... %u,%u\n", value,b);
		return 3;
	}

	void setStringForKey(const std::string& strValue)
	{
		printf("SimpleNativeClass method: setStringForKey... %s\n", strValue.c_str());
		return ;
	}

	std::string fullPathForFilename(const char* filename)
	{
		printf("SimpleNativeClass method: fullPathForFilename... %s\n", filename);
		return filename;
	}

	SimpleFatherClass *setObject(int index,const SimpleFatherClass* object,const SimpleSecondClass* object1)
	{
		printf("SimpleNativeClass method: setObject... %s\n", "come in");
		return NULL;
	}
    
    Point pointTest(Point pt,int x)
    {
        _pt.x = pt.x;
        _pt.y = pt.y;
        printf("SimpleNativeClass method: pointTest...%d,%d\n",pt.x,pt.y);
        return _pt;
    }
    
    Rect setRect(Rect rt,int x)
    {
        _rt.x = rt.x;
        _rt.y = rt.y;
        _rt.width = rt.width;
        _rt.height = rt.height;
        printf("SimpleNativeClass method: setRect...x = %d,y = %d, width = %d,height = %d\n",rt.x,rt.y,rt.width,rt.height);
        return _rt;
    }
    
    Size sizeTest(const Size& sz)
    {
        _sz.width = sz.width;
        _sz.height = sz.height;
        printf("SimpleNativeClass method: sizeTest...width = %f,height = %f\n",sz.width,sz.height);
        return _sz;
    }
    
    Color4B setColor4B(const Color4B& color)
    {
        _cc4b.r = color.r;
        _cc4b.g = color.g;
        _cc4b.b = color.b;
        _cc4b.a = color.a;
        printf("SimpleNativeClass method: setColor4B...r = %d,g = %d, b = %d,a = %d\n",color.r,color.g,color.b,color.a);
        return _cc4b;
    }
    
    Color4F color4fTest(const Color4F& color,const Size& sz)
    {
        _cc4f.r = color.r;
        _cc4f.g = color.g;
        _cc4f.b = color.b;
        _cc4f.a = color.a;
        
        _sz.width = sz.width;
        _sz.height = sz.height;
        printf("SimpleNativeClass method: color4fTest...color:r = %f,g = %f, b = %f,a = %f,size:width = %f,height = %f\n",color.r,color.g,color.b,color.a,sz.width,sz.height);
        return _cc4f;
    }
    
    Color3B color3fTest(const Color3B& c3b,const Color4F& c4f)
    {
        
        _c3b.r = c3b.r;
        _c3b.g = c3b.g;
        _c3b.b = c3b.b;
        
        _cc4f.r = c4f.r;
        _cc4f.g = c4f.g;
        _cc4f.b = c4f.b;
        _cc4f.a = c4f.a;
        

        printf("SimpleNativeClass method: color4fTest...c3b:r = %d,g = %d, b = %d,c4f:r = %f,g = %f, b = %f,a = %f\n",c3b.r,c3b.g,c3b.b,c4f.r,c4f.g,c4f.b,c4f.a);
        return _c3b;
    }
    
    void overloadTest(int param1 = 0,int param2 = 0)
    {
         printf("overloadTest...param1 = %d,param2 = %d\n",param1,param2);
    }
    void overloadTest(const Color3B& c3b,int param2)
    {
        printf("overloadTest...c3b.r = %d,c3b.g = %d c3b.b = %d param2 = %d,param2\n",c3b.r,c3b.g,c3b.b,param2);
    }
    void overloadTest(const char* sz,int param2)
    {
        printf("overloadTest...sz = %s param2 = %d\n",sz,param2);
    }
private:
    Point _pt;
    Rect  _rt;
    Size  _sz;
    Color4B _cc4b;
    Color4F _cc4f;
    Color3B _c3b;
};

} // namespace cocos2d {
#endif//#define __SIMPLE_CLASS_H__

using namespace cocos2dTest;

bool luaval_to_int32(lua_State* L,int lo,int* outValue);
bool luaval_to_uint32(lua_State* L, int lo, unsigned int* outValue);
bool luaval_to_uint16(lua_State* L, int lo, uint16_t* outValue);
bool luaval_to_boolean(lua_State* L,int lo,bool* outValue);
bool luaval_to_number(lua_State* L,int lo,double* outValue);
bool luaval_to_long_long(lua_State* L,int lo,long long* outValue);
bool luaval_to_std_string(lua_State* L, int lo, std::string* outValue);
bool luaval_to_const_char(lua_State* L, int lo, const char* outValue);

bool luaval_to_point(lua_State* L,int lo,Point* outValue);
void point_to_luaval(lua_State* L,const Point& pt);

bool luaval_to_rect(lua_State* L,int lo,Rect* outValue);
void rect_to_luaval(lua_State* L,const Rect& rt);

bool luaval_to_size(lua_State* L,int lo,Size* outValue);
void size_to_luaval(lua_State* L,const Size& sz);

bool luaval_to_color4b(lua_State* L,int lo,Color4B* outValue);
void color4b_to_luaval(lua_State* L,const Color4B& cc);

bool luaval_to_color4f(lua_State* L,int lo,Color4F* outValue);
void color4f_to_luaval(lua_State* L,const Color4F& cc);

bool luaval_to_color3b(lua_State* L,int lo,Color3B* outValue);
void color3b_to_luaval(lua_State* L,const Color3B& cc);
