const test = require('node:test');
const assert = require('node:assert').strict;
const fs = require('fs').promises;
const { Receipt } = require("../pkg");

async function fetchBinaryFiles() {
  const receiptPromise = fs.readFile(__dirname + '/../../zkvm/receipts/src/fib_receipt.bin');
  const methodIdPromise = fs.readFile(__dirname + '/../../zkvm/receipts/src/fib_id.bin');

  return Promise.all([receiptPromise, methodIdPromise]);
}

test('example valid proof verification', async () => {
  const [receipt, method_id] = await fetchBinaryFiles();
  Receipt.bincode_deserialize(receipt).validate(method_id);
});

test('invalid proof verification should fail with invalid method id', async () => {
  const [serializedReceipt] = await fetchBinaryFiles();
  const invalidMethodId = Buffer.alloc(32, 1);
  const receipt = Receipt.bincode_deserialize(serializedReceipt);
  assert.throws(() => {
    receipt.validate(invalidMethodId);
  }, new Error('Failed to validate proof: image_id mismatch'));
});

test('invalid proof verification should fail with invalid journal', async () => {
  const [serializedReceipt, methodId] = await fetchBinaryFiles();
  // Write a new value as the journal (last bytes of the serialized receipt are the journal)
  serializedReceipt.writeUInt32LE(123456, serializedReceipt.length - 4);
  const receipt = Receipt.bincode_deserialize(serializedReceipt);
  assert.throws(() => {
    receipt.validate(methodId);
  }, new Error('Failed to validate proof: Journal digest mismatch detected'));
});

test('invalid bytes should throw bincode deserialize error', async () => {
  assert.throws(() => {
    Receipt.bincode_deserialize(Buffer.alloc(32, 1));
  });
});
