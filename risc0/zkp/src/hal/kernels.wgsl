struct Fp {

};

@group(0)
@binding(0)
var<storage, read_write> input: Fp;

@compute
@workgroup_size(1)
fn eltwise_copy_elem(@builtin(global_invocation_id) global_id: vec3<u32>) {
    v_indices[global_id.x] = collatz_iterations(v_indices[global_id.x]);
}
