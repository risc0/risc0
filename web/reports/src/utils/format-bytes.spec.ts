import formatBytes from './format-bytes';

describe('formatBytes', () => {
  it('should return undefined for null or undefined', () => {
    // @ts-expect-error -- tests
    expect(formatBytes(null)).toBeUndefined();
    // @ts-expect-error -- tests
    expect(formatBytes(undefined)).toBeUndefined();
  });

  it('should return bytes correctly', () => {
    expect(formatBytes(1)).toBe('1.00B');
    expect(formatBytes(0)).toBe('0.00B');
  });

  it('should return kilobytes correctly', () => {
    expect(formatBytes(1024)).toBe('1.00KB');
  });

  it('should return megabytes correctly', () => {
    expect(formatBytes(1024 * 1024)).toBe('1.00MB');
  });

  it('should return gigabytes correctly', () => {
    expect(formatBytes(1024 * 1024 * 1024)).toBe('1.00GB');
  });

  it('should return terabytes correctly', () => {
    expect(formatBytes(1024 * 1024 * 1024 * 1024)).toBe('1.00TB');
  });

  it('should return the correct value for non-exact sizes', () => {
    expect(formatBytes(1500)).toBe('1.46KB');
    expect(formatBytes(1500 * 1024)).toBe('1.46MB');
  });
});
