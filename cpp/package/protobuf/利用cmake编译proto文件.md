### 方法
1. 使用cmake提供的宏`PROTOBUF_GENERATE_CPP`
2. 使用命令ADD_CUSTOM_COMMAND


### PROTOBUF_GENERATE_CPP

```
find_package(Protobuf REQUIRED)
FILE(GLOB protofiles "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
message(STATUS ${protofiles})
PROTOBUF_GENERATE_CPP(PROTOSRCS PROTOHDRS ${protofiles})
message(STATUS ${PROTOSRCS})
add_library(proto STATIC ${PROTOSRCS} ${PROTOHDRS}) 
target_link_libraries(proto protobuf) 
target_include_directories(proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

```

---

### 命令ADD_CUSTOM_COMMAND

```
FILE(GLOB proto_files ${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto)  
FOREACH(proto_file ${proto_files})
    STRING(REGEX REPLACE "[^/]proto" "" proto_file_name ${proto_file})
    LIST(APPEND PROTO_SRCS "${proto_file_name}.pb.cc")
	ADD_CUSTOM_COMMAND(
		OUTPUT "${proto_file_name}.pb.h" "${proto_file_name}.pb.cc"
		COMMAND protoc --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/proto
                       --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/proto/ ${proto_file} 
		DEPENDS ${proto_file}
	)
ENDFOREACH(proto_file)
message(STATUS ${PROTO_SRCS})
include_directories(./proto)
add_executable(demo main.cpp ${PROTO_SRCS}) 
target_link_libraries(demo protobuf)

```
