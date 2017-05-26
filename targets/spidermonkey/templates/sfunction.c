## ===== static function implementation template

SE_FUNC_BEGIN(${signature_name}, se::NEED_THIS) //FIXME: bindings-generator should support configrue NEED_THIS flag
{
    bool ok = true;
#if len($arguments) >= $min_args
    #set arg_count = len($arguments)
    #set arg_idx = $min_args
    #while $arg_idx <= $arg_count
    if (argc == ${arg_idx}) {
        #set arg_list = ""
        #set arg_array = []
        #set $count = 0
        #while $count < $arg_idx
            #set $arg = $arguments[$count]
            #if $arg.is_numeric
        ${arg.to_string($generator)} arg${count} = 0;
            #elif $arg.is_pointer
        ${arg.to_string($generator)} arg${count} = nullptr;
            #else
        ${arg.to_string($generator)} arg${count};
            #end if
            #set $count = $count + 1
        #end while
        #set $count = 0
        #while $count < $arg_idx
            #set $arg = $arguments[$count]
        ${arg.to_native({"generator": $generator,
            "in_value": "args[" + str(count) + "]",
            "out_value": "arg" + str(count),
            "class_name": $class_name,
            "level": 2,
            "ntype": str($arg)})};
            #set $arg_array += ["arg"+str($count)]
            #set $count = $count + 1
        #end while
        #if $arg_idx > 0
        JSB_PRECONDITION2(ok, false, "${signature_name} : Error processing arguments");
        #end if
        #set $arg_list = ", ".join($arg_array)
    #if str($ret_type) != "void"
        #if $func_name.startswith("create") and $is_ref_class
        auto result = ${namespaced_class_name}::${func_name}($arg_list);
        result->retain();
        auto obj = se::Object::createObjectWithClass(__jsb_${generator.prefix}_${class_name}_class, false);
        obj->setPrivateData(result);
        SE_SET_RVAL(se::Value(obj));
        #elif $func_name.startswith("getInstance") and $is_ref_class
        auto result = ${namespaced_class_name}::${func_name}($arg_list);
        se::Object* obj = nullptr;
        if (result->_scriptObject == nullptr)
        {
            obj = se::Object::createObjectWithClass(__jsb_${generator.prefix}_${class_name}_class, true);
            obj->setPrivateData(result);
            result->_scriptObject = obj;
        }
        else
        {
            obj = se::Object::getObjectWithPtr(result);
        }
        assert(obj);
        SE_SET_RVAL(se::Value(obj));
        #else
          #if $ret_type.is_enum
        int result = (int)${namespaced_class_name}::${func_name}($arg_list);
          #else
        ${ret_type.get_whole_name($generator)} result = ${namespaced_class_name}::${func_name}($arg_list);
          #end if
        se::Value jsret;
        ${ret_type.from_native({"generator": $generator,
                                "in_value": "result",
                                "out_value": "jsret",
                                "class_name": $ret_type.get_class_name($generator),
                                "ntype": str($ret_type),
                                "level": 1})};
        SE_SET_RVAL(jsret);
        #end if
    #else
        ${namespaced_class_name}::${func_name}($arg_list);
    #end if
    }
        #set $arg_idx = $arg_idx + 1
    #end while
#end if
}
SE_FUNC_END
