cc_library(
    name = "TestUtil_hdr",
    hdrs = ["TestUtil.h"],
    visibility = ["//visibility:public"], 
)

cc_library(
    name = "String_hdr",
    hdrs = ["String.h"],
    visibility = ["//visibility:public"], 
)
cc_library(
    name = "String_cpp",
    srcs = ["String.cpp"],
    deps = ["//Common:Allocator_hdr",
        "//Common:ReverseIterator_hdr",
        "//Common:UninitializedFunctions_hdr",
        "//Common:Utility_hdr",
        "//Detail:String_hdr",
        ],
    visibility = ["//visibility:public"],  
)
cc_binary(
    name = "string_test",
    srcs = ["test_string.cpp",],
    deps = ["//Detail:TestUtil_hdr", "//Detail:String_cpp"],
    copts = ["-g", "-O0"],
)


cc_library(
    name = "Vector_hdr",
    hdrs = ["Vector.h","Vector.impl.h",],   # "Vector.impl.h",
    deps = ["//Common:Allocator_hdr",
        "//Common:ReverseIterator_hdr",
        "//Common:UninitializedFunctions_hdr",
        "//Common:Iterator_hdr",
        "//Common:Algorithm_hdr",
        ],
    visibility = ["//visibility:public"],  
)
cc_binary(
    name = "vector_test",
    srcs = ["test_vector.cpp",],
    deps = ["//Detail:TestUtil_hdr", "//Detail:Vector_hdr"],
    copts = ["-g", "-O0"],
)

cc_library(
    name = "Deque_hdr",
    hdrs = ["Deque.h","Deque.impl.h",],   # "Vector.impl.h",
    deps = [
        "//Common:ReverseIterator_hdr",
        "//Common:Utility_hdr",
        "//Common:Iterator_hdr",
        "//Common:Algorithm_hdr",
        ],
    visibility = ["//visibility:public"],  
)
cc_binary(
    name = "deque_test",
    srcs = ["test_Deque.cpp",],
    deps = ["//Detail:TestUtil_hdr", "//Detail:Deque_hdr"],
    copts = ["-g", "-O0"],
)

cc_library(
    name = "Queue_hdr",
    hdrs = ["Queue.h",],
    deps = [
        "//Common:Functional_hdr",
        "Deque_hdr",
        "Vector_hdr",
        ],
    visibility = ["//visibility:public"],  
)
cc_binary(
    name = "queue_test",
    srcs = ["test_queue.cpp",],
    deps = ["//Detail:TestUtil_hdr", "//Detail:Queue_hdr"],
    copts = ["-g", "-O0"],
)







