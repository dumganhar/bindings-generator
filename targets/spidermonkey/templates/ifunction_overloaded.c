## ===== instance function implementation template - for overloaded functions

SE_FUNC_BEGIN(${signature_name}, se::DONT_NEED_THIS)
{
    bool ok = true;
    ${namespaced_class_name}* cobj = (${namespaced_class_name}*)(nativeThisObject);
    JSB_PRECONDITION2( cobj, false, "${signature_name} : Invalid Native Object");

#for func in $implementations
#if len($func.arguments) >= $func.min_args
    #set arg_count = len($func.arguments)
    #set arg_idx = $func.min_args
    #while $arg_idx <= $arg_count
    #set arg_list = ""
    #set arg_array = []
    do {
        #if $func.min_args >= 0
        if (argc == $arg_idx) {
            #set $count = 0
            #while $count < $arg_idx
                #set $arg = $func.arguments[$count]
                #set $arg_type = arg.to_string($generator)
                #if $arg.is_numeric
            ${arg_type} arg${count} = 0;
                #elif $arg.is_pointer
            ${arg_type} arg${count} = nullptr;
                #else
            ${arg_type} arg${count};
                #end if
            ${arg.to_native({"generator": $generator,
                             "in_value": "args[" + str(count) + "]",
                             "out_value": "arg" + str(count),
                             "class_name": $class_name,
                             "level": 3,
                             "ntype": str($arg)})};
                #set $arg_array += ["arg"+str(count)]
                #set $count = $count + 1
            #if $arg_idx > 0 and arg_type != "bool"
            if (!ok) { ok = true; break; }
            #end if
            #end while
            #set $arg_list = ", ".join($arg_array)
        #end if
        #if str($func.ret_type) != "void"
            #if $func.ret_type.is_enum
            int result = (int)cobj->${func.func_name}($arg_list);
            #else
            ${func.ret_type.get_whole_name($generator)} result = cobj->${func.func_name}($arg_list);
            #end if
            se::Value jsret;
            ${func.ret_type.from_native({"generator": $generator,
                                                      "in_value": "result",
                                                      "out_value": "jsret",
                                                      "ntype": str($func.ret_type),
                                                      "level": 2})};
            SE_SET_RVAL(jsret);
        #else
            cobj->${func.func_name}($arg_list);
        #end if
        }
    } while(0);

    #set $arg_idx = $arg_idx + 1
    #end while
#end if
#end for
}
SE_FUNC_END
