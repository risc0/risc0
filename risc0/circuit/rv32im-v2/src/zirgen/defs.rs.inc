set_field!(BabyBear);
define_buffer_list! {
all: [accum,code,data,global,mix,test,],
rows: [accum,code,data,test,],
taps: [accum,code,data,],
globals: [global,mix,],}
define_tap_buffer! {accum, /*count=*/80, /*groupId=*/0}
define_tap_buffer! {code, /*count=*/1, /*groupId=*/1}
define_tap_buffer! {data, /*count=*/203, /*groupId=*/2}
define_global_buffer! {global, /*count=*/74}
define_global_buffer! {mix, /*count=*/32}
define_buffer! {test, /*count=*/203}
