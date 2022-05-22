#[cfg(test)]

mod test {
    use std::collections::HashMap;

    #[test]
    fn test_vec_round_trip() {
        let input: Vec<u64> = vec![1, 2, 3];
        let data = crate::to_vec(&input).unwrap();
        let output: Vec<u64> = crate::from_slice(data.as_slice()).unwrap();
        assert_eq!(input, output);
    }

    #[test]
    fn test_map_round_trip() {
        let input: HashMap<&str, u32> = HashMap::from([("foo", 1), ("bar", 2), ("baz", 3)]);
        let data = crate::to_vec(&input).unwrap();
        let output: HashMap<&str, u32> = crate::from_slice(data.as_slice()).unwrap();
        assert_eq!(input, output);
    }

    #[test]
    fn test_tuple_round_trip() {
        let input: (u32, u64) = (1, 2);
        let data = crate::to_vec(&input).unwrap();
        let output: (u32, u64) = crate::from_slice(data.as_slice()).unwrap();
        assert_eq!(input, output);
    }
}
