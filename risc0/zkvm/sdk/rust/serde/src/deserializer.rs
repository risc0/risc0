use bytemuck;

use serde::de::{Deserialize, DeserializeSeed, IntoDeserializer, Visitor};

use crate::{
    align_up,
    err::{Error, Result},
};

pub fn from_slice<'a, T: Deserialize<'a>>(slice: &'a [u32]) -> Result<T> {
    let mut deserializer = Deserializer::new(slice);
    T::deserialize(&mut deserializer)
}

pub struct Deserializer<'de> {
    slice: &'de [u32],
}

struct SeqAccess<'a, 'de> {
    deserializer: &'a mut Deserializer<'de>,
    len: usize,
}

impl<'de, 'a> serde::de::SeqAccess<'de> for SeqAccess<'a, 'de> {
    type Error = Error;

    fn next_element_seed<T>(&mut self, seed: T) -> Result<Option<T::Value>>
    where
        T: DeserializeSeed<'de>,
    {
        if self.len > 0 {
            self.len -= 1;
            Ok(Some(DeserializeSeed::deserialize(
                seed,
                &mut *self.deserializer,
            )?))
        } else {
            Ok(None)
        }
    }

    fn size_hint(&self) -> Option<usize> {
        Some(self.len)
    }
}

impl<'de, 'a> serde::de::VariantAccess<'de> for &'a mut Deserializer<'de> {
    type Error = Error;

    fn unit_variant(self) -> Result<()> {
        Ok(())
    }

    fn newtype_variant_seed<V: DeserializeSeed<'de>>(self, seed: V) -> Result<V::Value> {
        DeserializeSeed::deserialize(seed, self)
    }

    fn tuple_variant<V: Visitor<'de>>(self, len: usize, visitor: V) -> Result<V::Value> {
        serde::de::Deserializer::deserialize_tuple(self, len, visitor)
    }

    fn struct_variant<V: Visitor<'de>>(
        self,
        fields: &'static [&'static str],
        visitor: V,
    ) -> Result<V::Value> {
        serde::de::Deserializer::deserialize_tuple(self, fields.len(), visitor)
    }
}

impl<'de, 'a> serde::de::EnumAccess<'de> for &'a mut Deserializer<'de> {
    type Error = Error;
    type Variant = Self;

    fn variant_seed<V: DeserializeSeed<'de>>(self, seed: V) -> Result<(V::Value, Self)> {
        let tag = self.try_take_word()?;
        let val = DeserializeSeed::deserialize(seed, tag.into_deserializer())?;
        Ok((val, self))
    }
}

struct MapAccess<'a, 'de> {
    deserializer: &'a mut Deserializer<'de>,
    len: usize,
}

impl<'a, 'de: 'a> serde::de::MapAccess<'de> for MapAccess<'a, 'de> {
    type Error = Error;

    fn next_key_seed<K: DeserializeSeed<'de>>(&mut self, seed: K) -> Result<Option<K::Value>> {
        if self.len > 0 {
            self.len -= 1;
            Ok(Some(DeserializeSeed::deserialize(
                seed,
                &mut *self.deserializer,
            )?))
        } else {
            Ok(None)
        }
    }

    fn next_value_seed<V: DeserializeSeed<'de>>(&mut self, seed: V) -> Result<V::Value> {
        DeserializeSeed::deserialize(seed, &mut *self.deserializer)
    }

    fn size_hint(&self) -> Option<usize> {
        Some(self.len)
    }
}

impl<'de> Deserializer<'de> {
    pub fn new(slice: &'de [u32]) -> Self {
        Deserializer { slice }
    }

    fn try_take_word(&mut self) -> Result<u32> {
        if self.slice.len() >= 1 {
            let (head, tail) = self.slice.split_first().unwrap();
            self.slice = tail;
            Ok(*head)
        } else {
            Err(Error::DeserializeUnexpectedEnd)
        }
    }

    fn try_take_dword(&mut self) -> Result<u64> {
        if self.slice.len() >= 2 {
            let (head, tail) = self.slice.split_at(2);
            self.slice = tail;
            let low: u64 = head[0].into();
            let high: u64 = head[1].into();
            Ok(low | high << 32)
        } else {
            Err(Error::DeserializeUnexpectedEnd)
        }
    }

    fn try_take_n(&mut self, len: usize) -> Result<&'de [u32]> {
        if self.slice.len() >= len {
            let (head, tail) = self.slice.split_at(len);
            self.slice = tail;
            Ok(head)
        } else {
            Err(Error::DeserializeUnexpectedEnd)
        }
    }

    fn try_take_n_bytes(&mut self, len: usize) -> Result<&'de [u8]> {
        let len_words = align_up(len, 4) / 4;
        let words: &'de [u32] = self.try_take_n(len_words)?;
        Ok(&bytemuck::cast_slice(words)[..len])
    }
}

impl<'de, 'a> serde::Deserializer<'de> for &'a mut Deserializer<'de> {
    type Error = Error;

    fn is_human_readable(&self) -> bool {
        false
    }

    fn deserialize_any<V>(self, _visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        Err(Error::NotSupported)
    }

    fn deserialize_bool<V>(self, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        let val = match self.try_take_word()? {
            0 => false,
            1 => true,
            _ => return Err(Error::DeserializeBadBool),
        };
        visitor.visit_bool(val)
    }

    fn deserialize_i8<V>(self, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        visitor.visit_i32(self.try_take_word()? as i32)
    }

    fn deserialize_i16<V>(self, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        visitor.visit_i32(self.try_take_word()? as i32)
    }

    fn deserialize_i32<V>(self, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        visitor.visit_i32(self.try_take_word()? as i32)
    }

    fn deserialize_i64<V>(self, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        visitor.visit_i64(self.try_take_dword()? as i64)
    }

    fn deserialize_u8<V>(self, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        visitor.visit_u32(self.try_take_word()?)
    }

    fn deserialize_u16<V>(self, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        visitor.visit_u32(self.try_take_word()?)
    }

    fn deserialize_u32<V>(self, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        visitor.visit_u32(self.try_take_word()?)
    }

    fn deserialize_u64<V>(self, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        visitor.visit_u64(self.try_take_dword()?)
    }

    fn deserialize_f32<V>(self, _visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        Err(Error::NotSupported)
    }

    fn deserialize_f64<V>(self, _visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        Err(Error::NotSupported)
    }

    fn deserialize_char<V>(self, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        let len_bytes = self.try_take_word()? as usize;
        if len_bytes > 4 {
            return Err(Error::DeserializeBadChar);
        }
        let bytes: &'de [u8] = self.try_take_n_bytes(len_bytes)?;
        // we pass the character through string conversion because
        // this handles transforming the array of code units to a
        // codepoint. we can't use char::from_u32() because it expects
        // an already-processed codepoint.
        let character = core::str::from_utf8(&bytes)
            .map_err(|_| Error::DeserializeBadChar)?
            .chars()
            .next()
            .ok_or(Error::DeserializeBadChar)?;
        visitor.visit_char(character)
    }

    fn deserialize_str<V>(self, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        let len_bytes = self.try_take_word()? as usize;
        let bytes = self.try_take_n_bytes(len_bytes)?;
        let str = core::str::from_utf8(bytes).map_err(|_| Error::DeserializeBadUtf8)?;
        visitor.visit_borrowed_str(str)
    }

    fn deserialize_string<V>(self, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        self.deserialize_str(visitor)
    }

    fn deserialize_bytes<V>(self, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        let len_bytes = self.try_take_word()? as usize;
        let bytes = self.try_take_n_bytes(len_bytes)?;
        visitor.visit_borrowed_bytes(bytes)
    }

    fn deserialize_byte_buf<V>(self, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        self.deserialize_bytes(visitor)
    }

    fn deserialize_option<V>(self, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        match self.try_take_word()? {
            0 => visitor.visit_none(),
            1 => visitor.visit_some(self),
            _ => Err(Error::DeserializeBadOption),
        }
    }

    fn deserialize_unit<V>(self, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        visitor.visit_unit()
    }

    fn deserialize_unit_struct<V>(self, _name: &'static str, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        self.deserialize_unit(visitor)
    }

    fn deserialize_newtype_struct<V>(self, _name: &'static str, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        visitor.visit_newtype_struct(self)
    }

    fn deserialize_seq<V>(self, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        let len = self.try_take_word()? as usize;
        visitor.visit_seq(SeqAccess {
            deserializer: self,
            len,
        })
    }

    fn deserialize_tuple<V>(self, len: usize, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        visitor.visit_seq(SeqAccess {
            deserializer: self,
            len,
        })
    }

    fn deserialize_tuple_struct<V>(
        self,
        _name: &'static str,
        len: usize,
        visitor: V,
    ) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        self.deserialize_tuple(len, visitor)
    }

    fn deserialize_map<V>(self, visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        let len = self.try_take_word()? as usize;
        visitor.visit_map(MapAccess {
            deserializer: self,
            len,
        })
    }

    fn deserialize_struct<V>(
        self,
        _name: &'static str,
        fields: &'static [&'static str],
        visitor: V,
    ) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        self.deserialize_tuple(fields.len(), visitor)
    }

    fn deserialize_enum<V>(
        self,
        _name: &'static str,
        _variants: &'static [&'static str],
        visitor: V,
    ) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        visitor.visit_enum(self)
    }

    fn deserialize_identifier<V>(self, _visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        Err(Error::NotSupported)
    }

    fn deserialize_ignored_any<V>(self, _visitor: V) -> Result<V::Value>
    where
        V: Visitor<'de>,
    {
        Err(Error::NotSupported)
    }
}

#[cfg(test)]
mod test {
    use alloc::string::String;

    use super::*;

    #[test]
    fn test_struct() {
        use serde::Deserialize;

        #[derive(Deserialize, PartialEq, Debug)]
        struct Test {
            bool: bool,
            i8: i8,
            u8: u8,
            i16: i16,
            u16: u16,
            i32: i32,
            u32: u32,
            i64: i64,
            u64: u64,
        }

        let words = [
            1,
            -4_i32 as u32,
            4,
            -5_i32 as u32,
            5,
            -6_i32 as u32,
            6,
            -7_i32 as u32,
            0xffffffff,
            7,
            0x00000000,
        ];
        let expected = Test {
            bool: true,
            i8: -4,
            u8: 4,
            i16: -5,
            u16: 5,
            i32: -6,
            u32: 6,
            i64: -7,
            u64: 7,
        };
        assert_eq!(expected, from_slice(&words).unwrap());
    }

    #[test]
    fn test_str() {
        use serde::Deserialize;

        #[derive(Deserialize, PartialEq, Debug)]
        struct Test {
            first: String,
            second: String,
        }

        let words = [1, 0x00000061, 3, 0x00636261];
        let expected = Test {
            first: "a".into(),
            second: "abc".into(),
        };
        assert_eq!(expected, from_slice(&words).unwrap());
    }
}
