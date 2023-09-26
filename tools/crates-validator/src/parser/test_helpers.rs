use crate::{Profile, ProfileSettings};

// Replace this by using `Profile::from` for a `impl ToString` type
pub(crate) fn profile_from_name(name: impl ToString) -> Profile {
    Profile {
        name: name.to_string(),
        settings: ProfileSettings::default(),
    }
}

pub(crate) fn profile_with_settings(args: (impl ToString, ProfileSettings)) -> Profile {
    Profile {
        name: args.0.to_string(),
        settings: args.1,
    }
}
