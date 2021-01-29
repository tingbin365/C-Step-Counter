load("@rules_cc//cc:defs.bzl",  "cc_library","cc_test","cc_binary")
# load(":bazel_build.bzl","export_include_folder")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "step_counter",
    srcs = glob(["src/*.c"]),     
    hdrs = glob(["include/*.h"]),
    includes = ["include"],    
    copts =  ["/WX","/wd4005","/wd4142"],    
)

cc_binary (
    name = "hardware_config",
    srcs = [
        "tests/test_main.cc",
    ],    
    deps = [
        ":step_counter",       
        # "@gtest//:gtest" # Only if hello_test.cc has no main()
        "@googletest//:gtest_main"
    ],
    data = ["tests/data/abc.txt"]
)