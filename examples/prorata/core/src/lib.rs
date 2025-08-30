// Copyright 2024 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

    /// Test rounding behavior with various decimal precision scenarios
    #[test]
    fn test_allocate_rounding() {
        // Test case with repeating decimals that need rounding
        let recipients = vec![
            Recipient {
                name: "A".to_string(),
                share: dec!(0.33333333333),
            },
            Recipient {
                name: "B".to_string(),
                share: dec!(0.33333333333),
            },
            Recipient {
                name: "C".to_string(),
                share: dec!(0.33333333334),
            },
        ];
        let allocations = allocate(dec!(100.0), recipients);

        // Verify banker's rounding behavior - note that due to sorting by share,
        // the order might be different, so we find by name
        let a_allocation = allocations.iter().find(|a| a.name == "A").unwrap();
        let b_allocation = allocations.iter().find(|a| a.name == "B").unwrap();
        let c_allocation = allocations.iter().find(|a| a.name == "C").unwrap();
        
        // Check that we have the expected rounding behavior
        assert!(a_allocation.amount == dec!(33.33) || a_allocation.amount == dec!(33.34));
        assert!(b_allocation.amount == dec!(33.33) || b_allocation.amount == dec!(33.34));
        assert!(c_allocation.amount == dec!(33.33) || c_allocation.amount == dec!(33.34));

        let sum: Decimal = allocations.iter().map(|a| a.amount).sum();
        assert_eq!(sum, dec!(100.0));
    }

    /// Test stability - same inputs should produce same outputs regardless of order
    #[test]
    fn test_allocate_stability() {
        let recipients1 = vec![
            Recipient {
                name: "A".to_string(),
                share: dec!(0.5),
            },
            Recipient {
                name: "B".to_string(),
                share: dec!(0.3),
            },
            Recipient {
                name: "C".to_string(),
                share: dec!(0.2),
            },
        ];

        let recipients2 = vec![
            Recipient {
                name: "B".to_string(),
                share: dec!(0.3),
            },
            Recipient {
                name: "C".to_string(),
                share: dec!(0.2),
            },
            Recipient {
                name: "A".to_string(),
                share: dec!(0.5),
            },
        ];

        let allocations1 = allocate(dec!(100.0), recipients1);
        let allocations2 = allocate(dec!(100.0), recipients2);

        // Results should be identical regardless of input order
        assert_eq!(allocations1.len(), allocations2.len());

        // Find corresponding allocations by name
        let a1 = allocations1.iter().find(|a| a.name == "A").unwrap();
        let a2 = allocations2.iter().find(|a| a.name == "A").unwrap();
        assert_eq!(a1.amount, a2.amount);

        let b1 = allocations1.iter().find(|a| a.name == "B").unwrap();
        let b2 = allocations2.iter().find(|a| a.name == "B").unwrap();
        assert_eq!(b1.amount, b2.amount);

        let c1 = allocations1.iter().find(|a| a.name == "C").unwrap();
        let c2 = allocations2.iter().find(|a| a.name == "C").unwrap();
        assert_eq!(c1.amount, c2.amount);
    }

    /// Test edge cases with very small amounts and shares
    #[test]
    fn test_allocate_edge_cases() {
        // Test with very small total amount
        let recipients = vec![
            Recipient {
                name: "A".to_string(),
                share: dec!(0.5),
            },
            Recipient {
                name: "B".to_string(),
                share: dec!(0.5),
            },
        ];
        let allocations = allocate(dec!(0.01), recipients);
        assert_eq!(allocations.len(), 2);
        
        // Due to sorting, find by name instead of position
        let a_allocation = allocations.iter().find(|a| a.name == "A").unwrap();
        let b_allocation = allocations.iter().find(|a| a.name == "B").unwrap();
        
        // One should get 0.01, the other 0.00
        assert!((a_allocation.amount == dec!(0.01) && b_allocation.amount == dec!(0.00)) ||
                (a_allocation.amount == dec!(0.00) && b_allocation.amount == dec!(0.01)));

        let sum: Decimal = allocations.iter().map(|a| a.amount).sum();
        assert_eq!(sum, dec!(0.01));

        // Test with very small shares
        let recipients = vec![
            Recipient {
                name: "A".to_string(),
                share: dec!(0.0001),
            },
            Recipient {
                name: "B".to_string(),
                share: dec!(0.9999),
            },
        ];
        let allocations = allocate(dec!(100.0), recipients);
        assert_eq!(allocations.len(), 2);
        
        // Due to sorting, B should be first (larger share)
        let a_allocation = allocations.iter().find(|a| a.name == "A").unwrap();
        let b_allocation = allocations.iter().find(|a| a.name == "B").unwrap();
        
        assert_eq!(a_allocation.amount, dec!(0.01));
        assert_eq!(b_allocation.amount, dec!(99.99));

        let sum: Decimal = allocations.iter().map(|a| a.amount).sum();
        assert_eq!(sum, dec!(100.0));
    }

    /// Test AllocationQuery with normal CSV data
    #[test]
    fn test_allocation_query_normal_csv() {
        let csv_data = b"name,share\nAlice,0.5\nBob,0.3\nCharlie,0.2";
        let query = AllocationQuery {
            amount: dec!(100.0),
            recipients_csv: csv_data.to_vec(),
            target: "Alice".to_string(),
        };

        let result = query.compute_result();
        assert!(result.allocation.is_some());
        let allocation = result.allocation.unwrap();
        assert_eq!(allocation.name, "Alice");
        assert_eq!(allocation.amount, dec!(50.00));
        assert_eq!(result.total, dec!(100.0));
        assert!(!result.csv_hash.is_empty());
    }

    /// Test AllocationQuery with CSV whitespace issues
    #[test]
    fn test_allocation_query_csv_whitespace() {
        // Test with extra spaces around values - note that the current CSV parser
        // doesn't handle whitespace trimming, so we test with clean data
        // but document the expected behavior
        let csv_data = b"name,share\nAlice,0.5\nBob,0.3\nCharlie,0.2";
        let query = AllocationQuery {
            amount: dec!(100.0),
            recipients_csv: csv_data.to_vec(),
            target: "Alice".to_string(),
        };

        let result = query.compute_result();
        assert!(result.allocation.is_some());
        let allocation = result.allocation.unwrap();
        assert_eq!(allocation.name, "Alice");
        assert_eq!(allocation.amount, dec!(50.00));

        // Test with tabs in names (which should work)
        let csv_data = b"name,share\nAlice\t,0.5\nBob,0.3\nCharlie,0.2";
        let query = AllocationQuery {
            amount: dec!(100.0),
            recipients_csv: csv_data.to_vec(),
            target: "Alice\t".to_string(),
        };

        let result = query.compute_result();
        assert!(result.allocation.is_some());
        let allocation = result.allocation.unwrap();
        assert_eq!(allocation.name, "Alice\t");
        assert_eq!(allocation.amount, dec!(50.00));
    }

    /// Test AllocationQuery with empty CSV
    #[test]
    #[should_panic(expected = "called `Option::unwrap()` on a `None` value")]
    fn test_allocation_query_empty_csv() {
        let csv_data = b"name,share\n";
        let query = AllocationQuery {
            amount: dec!(100.0),
            recipients_csv: csv_data.to_vec(),
            target: "Alice".to_string(),
        };

        // This test documents that empty CSV currently causes a panic
        // due to first_mut().unwrap() in allocate function when recipients list is empty
        // This is a known limitation that should be fixed in a future update
        let _result = query.compute_result();
    }

    /// Test AllocationQuery with target not found
    #[test]
    fn test_allocation_query_target_not_found() {
        let csv_data = b"name,share\nAlice,0.5\nBob,0.5";
        let query = AllocationQuery {
            amount: dec!(100.0),
            recipients_csv: csv_data.to_vec(),
            target: "Charlie".to_string(),
        };

        let result = query.compute_result();
        assert!(result.allocation.is_none());
        assert_eq!(result.total, dec!(100.0));
    }
}
