use risc0_zkvm::guest::env;

thread_local! {
    pub static MY_STATIC_VAR: StaticVar = StaticVar::new();
}

struct StaticVar {
    pub value: String,
}

impl StaticVar {
    pub fn new() -> Self {
        env::log("new");
        Self {
            value: "xxx".to_string(),
        }
    }
}

fn main() {
    env::log("main");
    MY_STATIC_VAR.with(|x| println!("{}", x.value));
}
