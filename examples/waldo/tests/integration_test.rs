use std::process::Command;

#[test]
fn test_waldo() {
    let feature = if cfg!(feature = "metal") {
        "metal"
    } else if cfg!(feature = "cuda") {
        "cuda"
    } else {
        "default"
    };

    Command::new("cargo")
        .args([
            "run",
            "--release",
            "--features",
            feature,
            "--bin",
            "prove",
            "--",
            "--i",
            "waldo.webp",
            "-x",
            "1150",
            "-y",
            "291",
            "----width 58",
            "--height",
            "70",
            "-m",
            "waldo_mask.png",
        ])
        .output()
        .expect("failed to run Waldo prove");

    Command::new("cargo")
        .args([
            "run",
            "--release",
            "--features",
            feature,
            "--bin",
            "verify",
            "--",
            "--i",
            "waldo.webp",
            "-r",
            "receipt.bin",
        ])
        .output()
        .expect("failed to run Waldo verify");
}
