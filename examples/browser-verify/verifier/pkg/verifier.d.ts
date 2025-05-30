/* tslint:disable */
/* eslint-disable */
export function verify_proof(proof_bytes: Uint8Array, image_id_bytes: Uint8Array): number;

export type InitInput = RequestInfo | URL | Response | BufferSource | WebAssembly.Module;

export interface InitOutput {
  readonly memory: WebAssembly.Memory;
  readonly sys_halt: (a: number, b: number) => void;
  readonly sys_pause: (a: number, b: number) => void;
  readonly sys_input: (a: number) => number;
  readonly sys_sha_compress: (a: number, b: number, c: number, d: number) => void;
  readonly sys_sha_buffer: (a: number, b: number, c: number, d: number) => void;
  readonly sys_bigint: (a: number, b: number, c: number, d: number, e: number) => void;
  readonly sys_rand: (a: number, b: number) => void;
  readonly sys_log: (a: number, b: number) => void;
  readonly sys_cycle_count: () => bigint;
  readonly sys_read: (a: number, b: number, c: number) => number;
  readonly sys_read_words: (a: number, b: number, c: number) => number;
  readonly sys_write: (a: number, b: number, c: number) => void;
  readonly sys_getenv: (a: number, b: number, c: number, d: number) => number;
  readonly sys_argc: () => number;
  readonly sys_argv: (a: number, b: number, c: number) => number;
  readonly sys_alloc_words: (a: number) => number;
  readonly sys_alloc_aligned: (a: number, b: number) => number;
  readonly sys_verify_integrity: (a: number, b: number) => void;
  readonly sys_fork: () => number;
  readonly sys_pipe: (a: number) => number;
  readonly sys_exit: (a: number) => void;
  readonly syscall_0: (a: number, b: number, c: number, d: number) => void;
  readonly syscall_1: (a: number, b: number, c: number, d: number, e: number) => void;
  readonly syscall_2: (a: number, b: number, c: number, d: number, e: number, f: number) => void;
  readonly syscall_3: (a: number, b: number, c: number, d: number, e: number, f: number, g: number) => void;
  readonly syscall_4: (a: number, b: number, c: number, d: number, e: number, f: number, g: number, h: number) => void;
  readonly syscall_5: (a: number, b: number, c: number, d: number, e: number, f: number, g: number, h: number, i: number) => void;
  readonly verify_proof: (a: number, b: number, c: number, d: number) => [number, number, number];
  readonly sys_panic: (a: number, b: number) => void;
  readonly sys_verify_integrity2: (a: number, b: number) => void;
  readonly __wbindgen_export_0: WebAssembly.Table;
  readonly __wbindgen_malloc: (a: number, b: number) => number;
  readonly __externref_table_dealloc: (a: number) => void;
  readonly __wbindgen_start: () => void;
}

export type SyncInitInput = BufferSource | WebAssembly.Module;
/**
* Instantiates the given `module`, which can either be bytes or
* a precompiled `WebAssembly.Module`.
*
* @param {{ module: SyncInitInput }} module - Passing `SyncInitInput` directly is deprecated.
*
* @returns {InitOutput}
*/
export function initSync(module: { module: SyncInitInput } | SyncInitInput): InitOutput;

/**
* If `module_or_path` is {RequestInfo} or {URL}, makes a request and
* for everything else, calls `WebAssembly.instantiate` directly.
*
* @param {{ module_or_path: InitInput | Promise<InitInput> }} module_or_path - Passing `InitInput` directly is deprecated.
*
* @returns {Promise<InitOutput>}
*/
export default function __wbg_init (module_or_path?: { module_or_path: InitInput | Promise<InitInput> } | InitInput | Promise<InitInput>): Promise<InitOutput>;
