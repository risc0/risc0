use crate::{Profile, ProfileSettings};

// TODO: Replace this by using `Profile::from` for a `impl ToString` type
pub(crate) fn profile_from_name(name: impl ToString) -> Profile {
    Profile::new(name.to_string(), ProfileSettings::default(), None).unwrap()
}

pub(crate) fn profile_with_settings(args: (impl ToString, ProfileSettings)) -> Profile {
    Profile::new(args.0.to_string(), args.1, None).unwrap()
}
