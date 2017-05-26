## ===== instance function implementation template

SE_FUNC_BEGIN(${signature_name}, se::NEED_THIS) //FIXME: bindings-generator should support configrue NEED_THIS flag
{
    bool ok = true;
    ${namespaced_class_name}* cobj = (${namespaced_class_name}*)nativeThisObject;
    JSB_PRECONDITION2(cobj, false, "${signature_name} : Invalid Native Object");
#if len($arguments) >= $min_args
    #set arg_count = len($arguments)
    #set arg_idx = $min_args
    #while $arg_idx <= $arg_count
    if (argc == ${arg_idx}) {
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
        #set arg_list = ""
        #set arg_array = []
        #while $count < $arg_idx
            #set $arg = $arguments[$count]
        ${arg.to_native({"generator": $generator,
                             "in_value": "args[" + str(count) + "]",
                             "out_value": "arg" + str(count),
                             "class_name": $class_name,
                             "level": 2,
                             "ntype": str($arg)})};
            #set $arg_array += ["arg"+str(count)]
            #set $count = $count + 1
        #end while
        #if $arg_idx > 0
        JSB_PRECONDITION2(ok, false, "${signature_name} : Error processing arguments");
        #end if
        #set $arg_list = ", ".join($arg_array)
        #if $ret_type.name != "void"
            #if $ret_type.is_enum
        int result = (int)cobj->${func_name}($arg_list);
            #else
        ${ret_type.get_whole_name($generator)} result = cobj->${func_name}($arg_list);
            #end if
        se::Value jsret;
        ${ret_type.from_native({"generator": $generator,
                                    "in_value": "result",
                                    "out_value": "jsret",
                                    "class_name": $ret_type.get_class_name($generator),
                                    "ntype": str($ret_type),
                                    "level": 2})};
        SE_SET_RVAL(jsret);
        #else
        cobj->${func_name}($arg_list);
        #end if
    }
        #set $arg_idx = $arg_idx + 1
    #end while
#end if
}
SE_FUNC_END
