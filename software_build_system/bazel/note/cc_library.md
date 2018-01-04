```
cc_library(
    name = "static_storage_path_source",
    srcs = ["static_storage_path_source.cc"],
    hdrs = ["static_storage_path_source.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        ":static_storage_path_source_proto",
        "//tensorflow_serving/core:servable_data",
        "//tensorflow_serving/core:servable_id",
        "//tensorflow_serving/core:source",
        "//tensorflow_serving/core:storage_path",
        "@org_tensorflow//tensorflow/core:lib",
    ],
)
```
