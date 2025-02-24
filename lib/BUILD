load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "utility",
    hdrs = [
        "utility/func.hpp",
        "utility/str.hpp",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//third_party:tl_expected",
    ],
)

### Example of a library with sources
#cc_library(
#    name = "other_libs",
#    srcs = [
#        "src1.cpp",
#        "src2.cpp",
#    ],
#    hdrs = [
#        "hdr1.hpp",
#        "hdr2.hpp",
#    ],
#    visibility = ["//visibility:public"],
#    deps = [
#        "//third_party:tl_expected",
#    ],
#)
