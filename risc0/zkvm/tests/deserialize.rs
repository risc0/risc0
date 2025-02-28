use serde::{de::MapAccess, de::Visitor, ser::SerializeStruct, Deserialize, Serialize,
    Serializer};

use std::fmt;

use serde::de::DeserializeOwned;

#[derive(Eq, PartialEq, Debug, Clone, Hash)]
pub struct I2();

struct I2Visitor;

impl<'de> Visitor<'de> for I2Visitor {
    type Value = I2;
    fn expecting(&self, formatter: &mut fmt::Formatter<'_>) -> fmt::Result {
        formatter.write_str("I2")
    }
    fn visit_map<V>(self, mut _map: V) -> Result<I2, V::Error>
    where
        V: MapAccess<'de>,
    {
        Ok(I2())
    }
}

impl<'de> Deserialize<'de> for I2 {
    fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
    where
        D: serde::Deserializer<'de>,
    {
        deserializer.deserialize_struct("I2", &["value"], I2Visitor)
    }
}

impl Serialize for I2 {
    fn serialize<S: Serializer>(&self, serializer: S) -> Result<S::Ok, S::Error> {
        serializer.serialize_struct("I2", 0)?.end()
    }
}

fn read<R: risc0_zkvm::serde::WordRead, T: DeserializeOwned>(input: R) -> T {
    T::deserialize(&mut risc0_zkvm::serde::Deserializer::new(input)).unwrap()
}

#[test]
fn test_visitor() {
    let elem: I2 = read(r"{}");
    assert_eq!(elem, I2());
}
