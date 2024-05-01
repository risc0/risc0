import { formatHz } from './format-hz';

describe('formatHz', () => {
  it('should return undefined for null or undefined', () => {
    // @ts-expect-error -- tests
    expect(formatHz(null)).toBeUndefined();
    // @ts-expect-error -- tests
    expect(formatHz(undefined)).toBeUndefined();
  });

  it('should return Hz correctly', () => {
    expect(formatHz(1)).toBe('1.00 Hz');
  });

  it('should return KHz correctly', () => {
    expect(formatHz(1000)).toBe('1.00 KHz');
  });

  it('should return MHz correctly', () => {
    expect(formatHz(1000 * 1000)).toBe('1.00 MHz');
  });

  it('should return GHz correctly', () => {
    expect(formatHz(1000 * 1000 * 1000)).toBe('1.00 GHz');
  });

  it('should return the correct value for non-exact frequencies', () => {
    expect(formatHz(1500)).toBe('1.50 KHz');
    expect(formatHz(1500 * 1000)).toBe('1.50 MHz');
  });

  it('should not go beyond GHz', () => {
    expect(formatHz(1000 * 1000 * 1000 * 1000)).toBe('1000.00 GHz');
  });
});
