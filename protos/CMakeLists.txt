find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(Threads)

add_library(tbf_grpc_proto
  tank_bot_fight.proto
)

target_include_directories(tbf_grpc_proto PUBLIC 
  "${CMAKE_CURRENT_BINARY_DIR}"
)

target_link_libraries(tbf_grpc_proto PUBLIC
  protobuf::libprotobuf
  gRPC::grpc
  gRPC::grpc++
  gRPC::grpc++_reflection
)

get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET tbf_grpc_proto LANGUAGE cpp)
protobuf_generate(TARGET tbf_grpc_proto LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")
