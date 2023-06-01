// Use below if we want to make the guest code no_std.
// #![cfg_attr(not(test), no_std)]

use csv;
use rust_decimal::{Decimal, RoundingStrategy};
use serde::{Deserialize, Serialize};
use sha2::{Digest, Sha256};

#[derive(Serialize, Deserialize)]
pub struct Recipient {
    pub name: String,
    #[serde(with = "rust_decimal::serde::str")]
    pub share: Decimal,
}

#[derive(Serialize, Deserialize)]
pub struct Allocation {
    pub name: String,
    #[serde(with = "rust_decimal::serde::str")]
    pub amount: Decimal,
}

#[derive(Serialize, Deserialize)]
pub struct AllocationQuery {
    pub amount: Decimal,
    pub recipients_csv: Vec<u8>,
    pub target: String,
}

#[derive(Serialize, Deserialize)]
pub struct AllocationQueryResult {
    pub allocation: Option<Allocation>,
    pub total: Decimal,
    pub csv_hash: Vec<u8>,
}

pub fn allocate(amount: Decimal, recipients: Vec<Recipient>) -> Vec<Allocation> {
    // Completely allocate the total funds `amount` by shares into dollars and
    // cents amounts for each recipient.
    //
    // amount - total amount to distribute
    // recipients - list of recipients with their share of the total amount

    // sort recipients in place by share descending
    // deserialize the recipients from the csv into a variable called recipients
    let mut recipients = recipients;

    recipients.sort_by(|a, b| b.share.cmp(&a.share));
    let total_share: Decimal = recipients.iter().map(|r| r.share).sum();

    // compute an allocation for each recipient
    let mut allocations: Vec<Allocation> = Vec::new();
    let mut remainder = amount;
    for recipient in recipients {
        let allocation_amount = amount * recipient.share / total_share;

        // round to two decimal places (dollars and cents)
        let allocation_amount =
            allocation_amount.round_dp_with_strategy(2, RoundingStrategy::MidpointNearestEven);
        allocations.push(Allocation {
            name: recipient.name,
            amount: allocation_amount,
        });
        remainder -= allocation_amount;
    }

    // add any remainder to the first allocation so as to keep the total
    // percentage error small
    allocations.first_mut().unwrap().amount += remainder;
    // remainder = Decimal::from(0);

    allocations
}

pub fn allocate_for(
    amount: Decimal,
    recipients: Vec<Recipient>,
    target: &str,
) -> Option<Allocation> {
    // Allocate the total funds `amount` by shares into dollars and cents amounts
    // for the recipient with name `target`.
    //
    // amount - total amount to distribute
    // recipients - list of recipients with their share of the total amount
    // target - name of the recipient to allocate for

    let allocations = allocate(amount, recipients);
    for allocation in allocations {
        if allocation.name == target {
            return Some(allocation);
        }
    }
    None
}

pub fn allocate_csv(amount: Decimal, recipients_csv: Vec<u8>) -> Vec<Allocation> {
    let mut rdr = csv::Reader::from_reader(recipients_csv.as_slice());
    let recipients: Vec<Recipient> = rdr.deserialize().map(|result| result.unwrap()).collect();
    allocate(amount, recipients)
}

pub fn allocate_for_csv(
    amount: Decimal,
    recipients_csv: Vec<u8>,
    target: &str,
) -> AllocationQueryResult {
    let mut rdr = csv::Reader::from_reader(recipients_csv.as_slice());
    let recipients: Vec<Recipient> = rdr.deserialize().map(|result| result.unwrap()).collect();

    let mut hasher = Sha256::new();
    hasher.update(&recipients_csv);
    let recipients_csv_hash = hasher.finalize().to_vec();

    AllocationQueryResult {
        allocation: allocate_for(amount, recipients, target),
        total: amount,
        csv_hash: recipients_csv_hash,
    }
}

#[cfg(test)]
mod tests {
    use rust_decimal_macros::dec;

    use super::*;

    // basic test for allocate()
    #[test]
    fn test_allocate() {
        let recipients = vec![
            Recipient {
                name: "A".to_string(),
                share: dec!(0.5),
            },
            Recipient {
                name: "B".to_string(),
                share: dec!(0.25),
            },
            Recipient {
                name: "C".to_string(),
                share: dec!(0.25),
            },
        ];
        let allocations = allocate(dec!(100.0), recipients);
        assert_eq!(allocations.len(), 3);
        assert_eq!(allocations[0].name, "A");
        assert_eq!(allocations[0].amount, dec!(50.00));
        assert_eq!(allocations[1].name, "B");
        assert_eq!(allocations[1].amount, dec!(25.00));
        assert_eq!(allocations[2].name, "C");
        assert_eq!(allocations[2].amount, dec!(25.00));

        // check that allocations add to 100
        let sum: Decimal = allocations.iter().map(|a| a.amount).sum();
        assert_eq!(sum, dec!(100.0));
    }

    // basic test for allocate() with large share numbers
    #[test]
    fn test_allocate2() {
        let recipients = vec![
            Recipient {
                name: "A".to_string(),
                share: dec!(500),
            },
            Recipient {
                name: "B".to_string(),
                share: dec!(250),
            },
            Recipient {
                name: "C".to_string(),
                share: dec!(250),
            },
        ];
        let allocations = allocate(dec!(100.0), recipients);
        assert_eq!(allocations.len(), 3);
        assert_eq!(allocations[0].name, "A");
        assert_eq!(allocations[0].amount, dec!(50.00));
        assert_eq!(allocations[1].name, "B");
        assert_eq!(allocations[1].amount, dec!(25.00));
        assert_eq!(allocations[2].name, "C");
        assert_eq!(allocations[2].amount, dec!(25.00));

        // check that allocations add to 100
        let sum: Decimal = allocations.iter().map(|a| a.amount).sum();
        assert_eq!(sum, dec!(100.0));
    }

    // test allocate remaining penny()
    #[test]
    fn test_allocate_remainder() {
        let recipients = vec![
            Recipient {
                name: "A".to_string(),
                share: dec!(0.66666666666),
            },
            Recipient {
                name: "B".to_string(),
                share: dec!(0.33333333333),
            },
        ];
        let allocations = allocate(dec!(100.0), recipients);
        assert_eq!(allocations.len(), 2);
        assert_eq!(allocations[0].name, "A");
        assert_eq!(allocations[0].amount, dec!(66.67));
        assert_eq!(allocations[1].name, "B");
        assert_eq!(allocations[1].amount, dec!(33.33));

        // check that allocations add to 100
        let sum: Decimal = allocations.iter().map(|a| a.amount).sum();
        assert_eq!(sum, dec!(100.0));
    }

    // TODO: add better test cases for allocate() to test rounding, stability, etc.

    // basic test for allocate_for()
    #[test]
    fn test_allocate_for() {
        let recipients = vec![
            Recipient {
                name: "A".to_string(),
                share: dec!(0.5),
            },
            Recipient {
                name: "B".to_string(),
                share: dec!(0.25),
            },
            Recipient {
                name: "C".to_string(),
                share: dec!(0.25),
            },
        ];
        let allocation = allocate_for(dec!(100.0), recipients, "B").unwrap();
        assert_eq!(allocation.amount, dec!(25.00));
    }

    // test serialize and deserialize of Recipient struct to vec
    #[test]
    fn test_serialize_deserialize() {
        let recipient = Recipient {
            name: "A".to_string(),
            share: dec!(0.5),
        };
        let serialized = bincode::serialize(&recipient).unwrap();
        let deserialized: Recipient = bincode::deserialize(&serialized).unwrap();
        assert_eq!(deserialized.name, "A");
        assert_eq!(deserialized.share, dec!(0.5));
    }

    // test allocate_csv()
    #[test]
    fn test_allocate_csv() {
        let recipients_csv = b"name,share
A,0.5
B,0.25
C,0.25";
        let allocations = allocate_csv(dec!(100.0), recipients_csv.to_vec());
        assert_eq!(allocations.len(), 3);
        assert_eq!(allocations[0].name, "A");
        assert_eq!(allocations[0].amount, dec!(50.00));
        assert_eq!(allocations[1].name, "B");
        assert_eq!(allocations[1].amount, dec!(25.00));
        assert_eq!(allocations[2].name, "C");
        assert_eq!(allocations[2].amount, dec!(25.00));

        // check that allocations add to 100
        let sum: Decimal = allocations.iter().map(|a| a.amount).sum();
        assert_eq!(sum, dec!(100.0));
    }
}
