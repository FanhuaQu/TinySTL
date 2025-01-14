cc_library(
    name = "Alloc_hdr",
    srcs = ["Alloc.cpp"],
    hdrs = ["Alloc.h"],
    visibility = ["//visibility:public"],  
)

cc_library(
    name = "TypeTraits_hdr",
    hdrs = ["TypeTraits.h"],
    visibility = ["//visibility:public"],  
)

cc_library(
    name = "Construct_hdr",
    hdrs = ["Construct.h"],
    visibility = ["//visibility:public"],  
)

cc_library(
    name = "Allocator_hdr",
    hdrs = ["Allocator.h"],
    deps = ["//Common:Alloc_hdr",
            "//Common:Construct_hdr"],
    visibility = ["//visibility:public"],  
)

cc_library(
    name = "Functional_hdr",
    hdrs = ["Functional.h"],
    visibility = ["//visibility:public"],  
)

cc_library(
    name = "Iterator_hdr",
    hdrs = ["Iterator.h"],
    visibility = ["//visibility:public"],  
)

cc_library(
    name = "Utility_hdr",
    hdrs = ["Utility.h"],
    visibility = ["//visibility:public"],  
)

cc_library(
    name = "Algorithm_hdr",
    hdrs = ["Algorithm.h"],
    deps = ["//Common:Allocator_hdr",
            "//Common:Functional_hdr",
            "//Common:Iterator_hdr",
            "//Common:TypeTraits_hdr",
            "//Common:Utility_hdr",
            ],
    visibility = ["//visibility:public"],  
)

cc_library(
    name = "ReverseIterator_hdr",
    hdrs = ["ReverseIterator.h"],
    deps = ["//Common:Iterator_hdr",
            ],
    visibility = ["//visibility:public"],  
)

cc_library(
    name = "UninitializedFunctions_hdr",
    hdrs = ["UninitializedFunctions.h"],
    deps = ["//Common:Algorithm_hdr",
            "//Common:Construct_hdr",
            "//Common:Iterator_hdr",
            "//Common:TypeTraits_hdr",
            ],
    visibility = ["//visibility:public"],  
)

