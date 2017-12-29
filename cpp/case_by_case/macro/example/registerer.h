#define REGISTER_OP_NODE_WITH_DATA(clazz_name, protected_data_type) \
        ::dl_kernel::OpNode* _create_op_node_helper_ ## clazz_name(::dl_kernel::OpConstructor* opc) { \
                clazz_name * ptr = new clazz_name(opc); \
                return ptr; \
        } \
        int _create_global_data_helper_ ## clazz_name(::dl_kernel::OpConstructor* opc) { \
                void* ptr = new protected_data_type; \
                opc->set_global_data_ptr(ptr); \
                return 0; \
        } \
        int _delete_global_data_helper_ ## clazz_name(::dl_kernel::OpConstructor* opc) { \
                protected_data_type* ptr = (protected_data_type*)opc->get_global_data_ptr(); \
                if (ptr) { delete ptr; } \
                opc->set_global_data_ptr(NULL); \
                return 0; \
        } \
        __attribute((constructor(102))) void _register_op_node_ ## clazz_name(); \
        void _register_op_node_ ## clazz_name() { \
                ::dl_kernel::OpFactoryFuncs* opff = new ::dl_kernel::OpFactoryFuncs(); \
                opff->create_opnode_func_ = _create_op_node_helper_ ## clazz_name; \
                opff->pre_check_config_func_ = clazz_name::PreCheckConfigFunc; \
                opff->determine_shape_func_ = clazz_name::DetermineShapeFunc; \
                opff->create_global_data_func_ = _create_global_data_helper_ ## clazz_name; \
                opff->delete_global_data_func_ = _delete_global_data_helper_ ## clazz_name; \
                opff->determine_mem_needs_func_ = clazz_name::DetermineMemNeedFunc; \
                opff->check_connect_func_ = clazz_name::CheckConnectFunc; \
                (*::dl_kernel::OpConstructor::p_op_node_factory_func_map_)[#clazz_name] = opff; \
        }\
        __attribute((constructor(103))) void _modify_op_factory_funcs_ ## clazz_name(); \
        void _modify_op_factory_funcs_ ## clazz_name() { \
                std::map<std::string, ::dl_kernel::OpFactoryFuncs*>::iterator it; \
                it = ::dl_kernel::OpConstructor::p_op_node_factory_func_map_->find(#clazz_name); \
                assert(it != ::dl_kernel::OpConstructor::p_op_node_factory_func_map_->end()); \
                clazz_name::ModifyOpFactoryFuncs(it->second); \
        }

#define REGISTER_OP_NODE(clazz_name) REGISTER_OP_NODE_WITH_DATA(clazz_name, ::dl_kernel::BaseOpData)
