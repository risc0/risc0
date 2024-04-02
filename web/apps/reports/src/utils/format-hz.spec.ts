// FILEPATH: /Users/cohan/code/risc0/web/apps/reports/src/utils/format-hz.spec.ts
import formatHz from './format-hz';

describe('formatHz', () => {
  it('should return undefined for null or undefined', () => {
    // @ts-expect-error -- tests
    expect(formatHz(null)).toBeUndefined();
    // @ts-expect-error -- tests
    expect(formatHz(undefined)).toBeUndefined();
  });

  it('should return Hz correctly', () => {
    expect(formatHz(1)).toBe('1.00Hz');
  });

  it('should return KHz correctly', () => {
    expect(formatHz(1000)).toBe('1.00KHz');
  });

  it('should return MHz correctly', () => {
    expect(formatHz(1000 * 1000)).toBe('1.00MHz');
  });

  it('should return GHz correctly', () => {
    expect(formatHz(1000 * 1000 * 1000)).toBe('1.00GHz');
  });

  it('should return the correct value for non-exact frequencies', () => {
    expect(formatHz(1500)).toBe('1.50KHz');
    expect(formatHz(1500 * 1000)).toBe('1.50MHz');
  });

  it('should not go beyond GHz', () => {
    expect(formatHz(1000 * 1000 * 1000 * 1000)).toBe('1000.00GHz');
  });
});
