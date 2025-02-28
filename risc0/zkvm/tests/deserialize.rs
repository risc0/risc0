use serde::{de::MapAccess, de::Visitor, ser::SerializeStruct, Deserialize, Serialize,
    Serializer};

use std::fmt;

use serde::de::DeserializeOwned;

#[derive(Eq, PartialEq, Debug, Clone, Hash)]
pub struct MinimalStruct();

struct MinimalStructVisitor;

impl<'de> Visitor<'de> for MinimalStructVisitor {
    type Value = MinimalStruct;
    fn expecting(&self, formatter: &mut fmt::Formatter<'_>) -> fmt::Result {
        formatter.write_str("MinimalStruct")
    }
    fn visit_map<V>(self, mut _map: V) -> Result<MinimalStruct, V::Error>
    where
        V: MapAccess<'de>,
    {
        Ok(MinimalStruct())
    }
}

impl<'de> Deserialize<'de> for MinimalStruct {
    fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
    where
        D: serde::Deserializer<'de>,
    {
        deserializer.deserialize_struct("MinimalStruct", &["value"], MinimalStructVisitor)
    }
}

impl Serialize for MinimalStruct {
    fn serialize<S: Serializer>(&self, serializer: S) -> Result<S::Ok, S::Error> {
        serializer.serialize_struct("MinimalStruct", 0)?.end()
    }
}

fn read<R: risc0_zkvm::serde::WordRead, T: DeserializeOwned>(input: R) -> T {
    T::deserialize(&mut risc0_zkvm::serde::Deserializer::new(input)).unwrap()
}

// #[test]
// fn test_visitor_raw() {
//     let visitor = MinimalStructVisitor;
//     use serde::de::value::MapDeserializer;
//     use serde::de::value::Error as ValueError;
//     let map = MapDeserializer::<_, ValueError>::new(std::collections::HashMap::new().into_iter());
//     let elem: MinimalStruct = visitor.visit_map(map).unwrap();
//     assert_eq!(elem, MinimalStruct());
// }


#[test]
fn test_visitor() {
    let elem: MinimalStruct = read(r"{}");
    assert_eq!(elem, MinimalStruct());
}
