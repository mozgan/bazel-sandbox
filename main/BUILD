load("@rules_cc//cc:cc_binary.bzl", "cc_binary")

cc_binary(
    name = "test_main",
    srcs = ["test_main.cpp"],
    deps = [
        "//lib:utility",
        "//third_party:tl_expected",
    ],
)

cc_binary(
    name = "main",
    srcs = ["production_main.cpp"],
    deps = [
        "//lib:utility",
    ],
)
