// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use rand::seq::IndexedRandom as _;

pub static WORDS: [&str; 775] = [
    "abate", "abbey", "abhor", "abide", "abort", "abuse", "abyss", "acorn", "actor", "acute",
    "adage", "adapt", "adept", "admit", "adopt", "adore", "adorn", "affix", "again", "agile",
    "aging", "agony", "agree", "aisle", "alarm", "alert", "alias", "alibi", "alien", "align",
    "alike", "alive", "allay", "alley", "allot", "allow", "alloy", "aloft", "aloud", "altar",
    "alter", "amass", "amaze", "amber", "amend", "ample", "amuse", "anger", "angry", "ankle",
    "annex", "annoy", "anvil", "apart", "apply", "april", "argue", "arise", "armed", "armor",
    "array", "arson", "aside", "aspen", "asset", "atlas", "attic", "aural", "avail", "avert",
    "avoid", "await", "awake", "award", "aware", "awash", "awful", "basic", "basis", "bathe",
    "beach", "beard", "begin", "below", "berth", "beset", "binge", "birth", "black", "blame",
    "blank", "blaze", "bleak", "blend", "bless", "blind", "blink", "bliss", "blood", "bloom",
    "blunt", "blush", "board", "boast", "boost", "booze", "bored", "bosom", "bosom", "bough",
    "bound", "bowel", "brace", "brain", "brake", "brand", "brash", "brass", "brave", "brawn",
    "bread", "break", "breed", "bride", "brick", "bride", "brief", "bring", "brisk", "broad",
    "brook", "brunt", "brush", "brute", "build", "bully", "bunch", "burst", "cabin", "camel",
    "canal", "carry", "catch", "cause", "cease", "chair", "chant", "chaos", "charm", "chart",
    "chase", "chasm", "cheap", "cheat", "cheek", "cheer", "chest", "chief", "child", "chill",
    "choke", "chore", "civic", "civil", "claim", "clash", "class", "clean", "clear", "clerk",
    "click", "cliff", "climb", "cling", "cloak", "close", "cloth", "cloud", "coach", "coast",
    "color", "comet", "cough", "count", "court", "crack", "craft", "crash", "crawl", "craze",
    "crazy", "creed", "creek", "creep", "crest", "crime", "crisp", "crock", "crone", "crony",
    "cross", "crowd", "crown", "crude", "cruel", "crumb", "crush", "crust", "crypto", "cubic",
    "curly", "curse", "cycle", "daily", "dairy", "daunt", "death", "debit", "decay", "defer",
    "deity", "delay", "delve", "dense", "depot", "depth", "detox", "devil", "digit", "dirty",
    "ditch", "dizzy", "doing", "doubt", "dozen", "draft", "drain", "dread", "dream", "drift",
    "drill", "drink", "drive", "droop", "drown", "drunk", "dummy", "dwell", "eager", "early",
    "earth", "edict", "elder", "elect", "elite", "elude", "empty", "enact", "endow", "enemy",
    "enjoy", "enter", "epoch", "equal", "equip", "erase", "erect", "erode", "error", "erupt",
    "ether", "ethic", "event", "every", "evoke", "exact", "exalt", "excel", "exert", "exile",
    "exist", "expel", "extra", "faint", "faith", "false", "famed", "fatal", "fatty", "fault",
    "favor", "feast", "fetch", "fever", "fiber", "fiend", "fight", "filth", "final", "first",
    "fixed", "flame", "flame", "flesh", "flick", "fling", "flirt", "float", "flock", "flood",
    "flora", "flour", "fluid", "fluke", "flunk", "flush", "focus", "folly", "foray", "force",
    "found", "frail", "frame", "frank", "fresh", "front", "frown", "funny", "fussy", "fuzzy",
    "gamut", "gauge", "glare", "gleam", "globe", "glory", "goods", "goody", "goose", "gourd",
    "grace", "grade", "graft", "grain", "grant", "grasp", "grass", "grave", "great", "greed",
    "greet", "grief", "grind", "gripe", "groan", "grope", "gross", "grove", "growl", "grown",
    "guess", "guilt", "gusto", "habit", "happy", "harsh", "haste", "hasty", "hatch", "haunt",
    "heave", "heavy", "hence", "hinge", "hoard", "hoist", "honor", "horse", "hotly", "house",
    "hover", "human", "humid", "hunch", "hurry", "ideal", "idiot", "imply", "incur", "index",
    "inert", "infer", "inlet", "inner", "irony", "issue", "ivory", "jewel", "joint", "jolly",
    "judge", "kneel", "labor", "lance", "lapse", "large", "larva", "later", "laugh", "layer",
    "learn", "least", "leave", "leech", "lefty", "legal", "level", "lever", "light", "linen",
    "liver", "local", "lofty", "logic", "loose", "lower", "loyal", "lunar", "lunch", "lyric",
    "major", "maple", "marry", "match", "maxim", "maybe", "mayor", "means", "mercy", "merge",
    "merry", "mimic", "minor", "moist", "money", "month", "mount", "mouth", "muddy", "mummy",
    "music", "naked", "nasty", "nerve", "never", "niece", "night", "noble", "noise", "novel",
    "nudge", "occur", "ocean", "offer", "often", "opium", "orbit", "order", "organ", "other",
    "outer", "overt", "oxide", "patch", "peace", "peril", "petal", "petty", "phase", "piece",
    "piety", "pilot", "pinch", "pious", "pique", "place", "plain", "plane", "plant", "plate",
    "plead", "pluck", "plumb", "plump", "point", "pound", "power", "prawn", "press", "prick",
    "prime", "prior", "prize", "probe", "prone", "proof", "prose", "proud", "prove", "pulse",
    "pupil", "puppy", "quail", "quake", "queer", "quell", "quest", "quick", "quiet", "quite",
    "quota", "quote", "rainy", "raise", "range", "rapid", "ratio", "reach", "react", "ready",
    "realm", "rebel", "recur", "refer", "reign", "relax", "relay", "relic", "remit", "renew",
    "repel", "reply", "rhyme", "right", "rigid", "rigor", "risky", "rival", "river", "rough",
    "round", "rouse", "royal", "ruler", "rumor", "rural", "rusty", "sadly", "saint", "scale",
    "scare", "scary", "scene", "scent", "scope", "score", "scorn", "screw", "scrub", "seize",
    "sense", "serve", "sever", "sewer", "shade", "shaft", "shake", "shame", "shape", "share",
    "shark", "sharp", "shear", "sheer", "shelf", "shell", "shift", "shine", "shiny", "shore",
    "short", "shout", "shove", "sight", "silly", "skill", "slack", "slant", "slave", "sleep",
    "slide", "smack", "small", "smart", "smear", "smell", "smile", "snare", "sneak", "sneer",
    "sober", "solar", "solid", "solve", "sorry", "sound", "space", "spare", "speak", "spork",
    "spell", "spend", "spice", "spill", "spine", "spite", "split", "spoil", "spook", "sport",
    "spurt", "stain", "stair", "stake", "stale", "stand", "stare", "start", "state", "steal",
    "steam", "steel", "steep", "steer", "stern", "stick", "stiff", "still", "sting", "stink",
    "stock", "stoop", "store", "storm", "stout", "straw", "strip", "stuff", "stump", "suave",
    "suite", "sunny", "swarm", "swear", "sweat", "sweep", "swell", "swift", "swing", "swirl",
    "swish", "table", "tacit", "tacky", "taste", "tasty", "taunt", "tease", "tempt", "tense",
    "terms", "thank", "thick", "thief", "thing", "think", "third", "throb", "throw", "thumb",
    "tight", "timid", "tired", "token", "tooth", "total", "tough", "toxic", "trace", "track",
    "trade", "train", "trait", "tramp", "trash", "tread", "treat", "trend", "trial", "tribe",
    "troop", "truly", "trunk", "trust", "truth", "twice", "twist", "ulcer", "uncle", "unify",
    "union", "unite", "unity", "upper", "upset", "urban", "usage", "usher", "usual", "utter",
    "vague", "valid", "value", "vapor", "verge", "vigor", "virus", "visit", "vista", "vital",
    "vivid", "vogue", "voice", "vouch", "wages", "waste", "watch", "water", "weary", "weave",
    "wedge", "weigh", "weird", "wheel", "whole", "whore", "widen", "width", "witch", "witty",
    "world", "worry", "worse", "worst", "worth", "wound", "wrath", "wreck", "wring", "write",
    "wrong", "yearn", "yield", "young", "youth",
];

pub fn pick_word() -> &'static str {
    WORDS.choose(&mut rand::rng()).unwrap()
}
