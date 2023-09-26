use super::*;

pub trait Group {
    fn group(self) -> GroupedProfiles;
}

pub trait Merge {
    fn merge(self, other: Self) -> Self;
}

pub trait Exclude {
    fn exclude(self, other: Self) -> Self;
}

pub trait IsValid {
    fn is_valid(&self) -> Result<(), ValidationErrors>;
}
