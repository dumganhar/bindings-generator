#set generator = $current_class.generator

extern se::Object* __jsb_${current_class.class_name}_proto;
extern se::Class* __jsb_${current_class.class_name}_class;

bool js_register_${generator.prefix}_${current_class.class_name}(se::Object* obj);

