// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#[cfg(not(target_os = "zkvm"))]
use std::fmt;

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

impl AllocationQuery {
    pub fn compute_result(&self) -> AllocationQueryResult {
        let mut rdr = csv::Reader::from_reader(self.recipients_csv.as_slice());
        let recipients: Vec<Recipient> = rdr.deserialize().map(|result| result.unwrap()).collect();

        let mut hasher = Sha256::new();
        hasher.update(&self.recipients_csv);
        let recipients_csv_hash = hasher.finalize().to_vec();

        AllocationQueryResult {
            allocation: allocate_for(self.amount, recipients, &self.target),
            total: self.amount,
            csv_hash: recipients_csv_hash,
        }
    }
}

#[derive(Serialize, Deserialize)]
pub struct AllocationQueryResult {
    pub allocation: Option<Allocation>,
    pub total: Decimal,
    pub csv_hash: Vec<u8>,
}

// This is an example of functionality that we compile only for the host.
#[cfg(not(target_os = "zkvm"))]
impl fmt::Display for AllocationQueryResult {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match &self.allocation {
            None => {
                writeln!(f, "No allocation.").unwrap();
            }
            Some(allocation) => {
                writeln!(
                    f,
                    "Allocation for {}: {}",
                    allocation.name, allocation.amount,
                )
                .unwrap();
                writeln!(f, "Total: {}", &self.total).unwrap();
            }
        }
        writeln!(f, "CSV hash: {}", hex::encode(&self.csv_hash))
    }
}

/// Completely allocate the total funds `amount` by shares into dollars and
/// cents amounts for each recipient.
///
/// amount - total amount to distribute
/// recipients - list of recipients with their share of the total amount
pub fn allocate(amount: Decimal, recipients: Vec<Recipient>) -> Vec<Allocation> {
    // Sort recipients in descending order of ownership share to provide
    // consistent behavior regardless of input order.
    // TODO: In the case of ties in ownership share this is not sufficient to
    // give consistent behavior regardless of input order. Show an example of
    // testing with a tool like proptest to detect before fixing.
    let mut recipients = recipients;
    recipients.sort_by(|a, b| b.share.cmp(&a.share));

    // Compute an allocation for each recipient.
    let total_share: Decimal = recipients.iter().map(|r| r.share).sum();
    let mut allocations: Vec<Allocation> = Vec::new();
    let mut remainder = amount;
    for recipient in recipients {
        let allocation_amount = amount * recipient.share / total_share;

        // Round to two decimal places (dollars and cents) using banker's
        // rounding.
        let allocation_amount =
            allocation_amount.round_dp_with_strategy(2, RoundingStrategy::MidpointNearestEven);
        allocations.push(Allocation {
            name: recipient.name,
            amount: allocation_amount,
        });
        remainder -= allocation_amount;
    }

    // Adjust the first allocation by any remainder so as to keep the percentage
    // error small for each recipient while ensuring that funds are completely
    // distributed.
    allocations.first_mut().unwrap().amount += remainder;

    allocations
}

/// Allocate the total funds `amount` by shares into dollars and cents amounts
/// for the recipient with name `target`.
///
/// amount - total amount to distribute
/// recipients - list of recipients with their share of the total amount
/// target - name of the recipient to allocate for
pub fn allocate_for(
    amount: Decimal,
    recipients: Vec<Recipient>,
    target: &str,
) -> Option<Allocation> {
    let allocations = allocate(amount, recipients);
    allocations
        .into_iter()
        .find(|allocation| allocation.name == target)
}

#[cfg(test)]
mod tests {
    use rust_decimal_macros::dec;

    use super::*;

    // Basic test for allocate()
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

    // Basic test for allocate() with large share numbers.
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

        // Check that allocations add to 100
        let sum: Decimal = allocations.iter().map(|a| a.amount).sum();
        assert_eq!(sum, dec!(100.0));
    }

    /// Test allocation of remaining penny()
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

        // Check that allocations add to 100
        let sum: Decimal = allocations.iter().map(|a| a.amount).sum();
        assert_eq!(sum, dec!(100.0));
    }

    /// Basic test for allocate_for()
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

    /// Test serialize and deserialize of Recipient struct to vec
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

    // TODO: Add better test cases for allocate() to test rounding, stability,
    // etc.
    // TODO: Add test for AllocationQuery behavior including CSV white space
    // issues.
}
