const secp256k1 = require("secp256k1");
const keccak256 = require("keccak256")
const { MerkleTree } = require('merkletreejs')
const SHA256 = require('crypto-js/sha256')

/**
 * This ceremony would be done in private so that the signatories are kept confidential.
 * Corresponding Ethereum Addresses: 
 * - 0x99E483581bC6452a40fCFB9fce3e850103932472
 * - 0xAd34Ba1e867fD96d3183656336Cc0e7416BbfDD7
 * - 0x3bE0949AbFAec6c6f91873116CC90A7b29f2a19e
 * - 0x71Ba9F0B1676c289C82Ec2b410b4EF3C7b998bc8
 * - 0x0Ccb6aAE0D67421DCfA4e62c60e2738C9af42F35
 * - 0xB66CdeaEFb272040b9bA4D2DEA6B821075948b2C
 * - 0xC0AC8B29286Ed8562BFB27302b3963eaba1AB753
 */
const TEST_PRIVATE_KEYS = [ // DON'T SEND REAL ASSETS TO THESE - THIS EXAMPLE IF FOR EDUCATIONAL PURPOSES ONLY.
    "f99eea319daf811e9f0f2cf198734f4e5278458bc9994f211e4932646cb109c9",
    "9679ea806071e94176e68b6d1ea8c12c5372ebcca718ef3f6825807461053b86",
    "8b874743d2f8e0bf43fa34f86975fef92bb1f2fc2c5311c18b08e7313fed0bd2",
    "7cd8f2cb2791b9dcf508dff35b78b2e250e589db037efec744ecfc33bdad9734",
    "c6ecd64d30bd18b5d93bfee7051d6c6610ecf3b271d36cd794a20bb092ed57df",
    "7999ea3d2e381d011544924fb9b15c9893447e7ae0cc6c5ccbe8b4ac1e4ffeaa",
];
const LEAF_BYTES = 32;
let testPublicKeys = [];

function createAddress(privateKeyStr) {
    const privateKey = Buffer.from(privateKeyStr, 'hex');

    if (!secp256k1.privateKeyVerify(privateKey)) {
        throw new Error('Invalid private key');
    }

    const publicKey = secp256k1.publicKeyCreate(privateKey, false);
    testPublicKeys.push(Buffer.from(publicKey).toString("hex"));

    const publicKeyHash = keccak256(Buffer.from(publicKey.slice(1))); // Remove the first byte (0x04)
    const address = `${publicKeyHash.slice(-20).toString('hex')}`;

    return address; // skipping https://eips.ethereum.org/EIPS/eip-55 for now
}

function generateProof(proofIndex, addresses, tree) {
    const leaf = SHA256(addresses[proofIndex])
    const proof = tree.getProof(leaf)
    let proofForZkVM = "";
    for(let hash of proof) {
        proofForZkVM += hash.data.toString("hex");
    }
    proofForZkVM += proofIndex; // proof index is added to merkle proof
    return proofForZkVM;
}


let addresses = [];
for(let privateKey of TEST_PRIVATE_KEYS) {
    let address = createAddress(privateKey);
    addresses.push(address);
}

console.log(`%c ------------------------------------------
< Welcome to your private mooltisig wallet! >
 ------------------------------------------
        \\   ^__^
         \\  (oo)\\_______
            (__)\\       )\\/\\
                ||----w |
                ||     ||`, "font-family:monospace") // Credit:  https://gist.github.com/lhorie/1204893c2f0e3ba3c14ac204b2df4b24

console.log('\n\nMultiSig Participants - Ethereum Addresses:', addresses);
console.log('\n\nPublic Keys:', testPublicKeys);

const leaves = testPublicKeys.map(x => SHA256(x));
const tree = new MerkleTree(leaves, SHA256)
const root = tree.getRoot().toString("hex")
console.log(`\nMerkle Root: ${root}`);


let allLeavesConcatenated = "";
for (let leaf of tree.leaves) {
    if(leaf.length != LEAF_BYTES) throw new Error(`Expected leaf: ${leaf} to be ${LEAF_BYTES} bytes in size.`);
    allLeavesConcatenated += leaf.toString("hex");
}

console.log(`Generating merkle proofs for a private (2 of ${tree.leaves.length}) zk multisig wallet.`);
const proofIndexOne = 0;
const merkleProofOne = generateProof(proofIndexOne, testPublicKeys, tree);

console.log(`\nIndex of Proof: ${proofIndexOne}`);
console.log(`zkVM Merkle Proof: ${merkleProofOne}`);

const proofIndexTwo = 3;
const merkleProofTwo = generateProof(proofIndexTwo, testPublicKeys, tree);

console.log(`\nIndex of Proof: ${proofIndexTwo}`);
console.log(`zkVM Merkle Proof: ${merkleProofTwo}`);

// ############################### Signatures ############################### //
let signedMessage = '{"this": "would", "contain": "transaction", "data": "in", "practice": "maybe", "an": "erc4337", "user": "operation"}';
const msgHash = keccak256(Buffer.from(signedMessage));
const msgHashHex = msgHash.toString("hex"); // We could pass in the hash instead if we wanted to - this would speed up computation.
console.log(`Hash of message: ${msgHashHex}`);

const privateKeyOne = Buffer.from(TEST_PRIVATE_KEYS[proofIndexOne], 'hex');
const signatureOne = secp256k1.ecdsaSign(msgHash, privateKeyOne);
const sig_one_rec_id = signatureOne.recid;
const signatureHexOne = Buffer.from(signatureOne.signature).toString('hex');

const privateKeyTwo = Buffer.from(TEST_PRIVATE_KEYS[proofIndexTwo], 'hex');
const signatureTwo = secp256k1.ecdsaSign(msgHash, privateKeyTwo);
const sig_two_rec_id = signatureTwo.recid
const signatureHexTwo = Buffer.from(signatureTwo.signature).toString('hex');

// cargo run <sig1>||<sig1_recoveryId> <sig2>||<sig2_recoveryId> <merkleProof1>||<merkleProof1LeafIndex> <merkleProof2>||<merkleProof2LeafIndex> <signedMessage> <merkleLeaves>
console.log(`\nRun the following command: \n cargo run -- ${signatureHexOne}${sig_one_rec_id} ${signatureHexTwo}${sig_two_rec_id} ${merkleProofOne} ${merkleProofTwo} '${signedMessage}' ${allLeavesConcatenated}\n`);