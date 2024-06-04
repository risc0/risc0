import { isNil } from './is-nil';

describe('isNil', () => {
  it('should return true when the input is null', () => {
    expect(isNil(null)).toBe(true);
  });

  it('should return true when the input is undefined', () => {
    expect(isNil(undefined)).toBe(true);
  });

  it('should return true when the input is void 0', () => {
    expect(isNil(void 0)).toBe(true);
  });

  it('should return false when the input is a non-null and non-undefined value', () => {
    expect(isNil('test')).toBe(false);
    expect(isNil(0)).toBe(false);
    expect(isNil([])).toBe(false);
    expect(isNil({})).toBe(false);
  });
});
