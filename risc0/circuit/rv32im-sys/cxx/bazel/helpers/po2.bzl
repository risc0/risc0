def make_po2(name, func, ext, platform, visibility = None, **kwargs):
    native.genrule(
        name = name,
        srcs = [],
        outs = [
            func + "_12." + ext,
            func + "_13." + ext,
            func + "_14." + ext,
            func + "_15." + ext,
            func + "_16." + ext,
            func + "_17." + ext,
            func + "_18." + ext,
            func + "_19." + ext,
            func + "_20." + ext,
            func + "_21." + ext,
            func + "_22." + ext,
        ],
        cmd = "$(location //bazel/helpers:make_po2s.py) " + func + " " + ext + " " + platform + " \"$(@D)\"",
        tools = ["//bazel/helpers:make_po2s.py"],
    )
