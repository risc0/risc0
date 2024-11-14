set_field!(BabyBear);
define_buffer_list! {
all: [accum,code,data,global,mix,test,],
rows: [accum,code,data,test,],
taps: [accum,code,data,],
globals: [global,mix,],}
define_tap_buffer! {accum, /*count=*/4, /*groupId=*/0}
define_tap_buffer! {code, /*count=*/1, /*groupId=*/1}
define_tap_buffer! {data, /*count=*/334, /*groupId=*/2}
define_global_buffer! {global, /*count=*/16}
define_global_buffer! {mix, /*count=*/24}
define_buffer! {test, /*count=*/350}
