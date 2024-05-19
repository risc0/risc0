import { formatDuration } from './format-duration';

describe('formatDuration', () => {
  it('should return undefined for null or undefined', () => {
    // @ts-expect-error -- tests
    expect(formatDuration(null)).toBeUndefined();
    // @ts-expect-error -- tests
    expect(formatDuration(undefined)).toBeUndefined();
  });

  it('should return nanoseconds correctly', () => {
    expect(formatDuration(1)).toBe('1.00ns');
  });

  it('should return microseconds correctly', () => {
    expect(formatDuration(1000)).toBe('1.00µs');
  });

  it('should return milliseconds correctly', () => {
    expect(formatDuration(1000 * 1000)).toBe('1.00ms');
  });

  it('should return seconds correctly', () => {
    expect(formatDuration(1000 * 1000 * 1000)).toBe('1.00s');
  });

  it('should return minutes correctly', () => {
    expect(formatDuration(1000 * 1000 * 1000 * 60)).toBe('1.00m');
  });

  it('should return hours correctly', () => {
    expect(formatDuration(1000 * 1000 * 1000 * 60 * 60)).toBe('1.00h');
  });

  it('should return the correct value for non-exact durations', () => {
    expect(formatDuration(1500)).toBe('1.50µs');
    expect(formatDuration(1500 * 1000)).toBe('1.50ms');
  });
});
