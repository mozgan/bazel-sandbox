load("@rules_cc//cc:cc_test.bzl", "cc_test")

cc_test(
    name = "lib_utility_str_test",
    srcs = ["lib_utility_str_test.cpp"],
    deps = [
        "//lib:utility",
        "//third_party:tl_expected",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "lib_utility_func_test",
    srcs = ["lib_utility_func_test.cpp"],
    deps = [
        "//lib:utility",
        "//third_party:tl_expected",
        "@googletest//:gtest_main",
    ],
)
