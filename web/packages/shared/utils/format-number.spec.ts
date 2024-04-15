import { formatNumber } from './format-number';

describe('formatNumber', () => {
  it('should correctly format numbers without options', () => {
    expect(formatNumber(123456.789)).toBe('123,456.789');
  });

  it('should correctly format numbers with options', () => {
    expect(formatNumber(123456.789, { style: 'currency', currency: 'USD' })).toBe('$123,456.79');
  });

  it('should correctly format strings without options', () => {
    expect(formatNumber('123456.789')).toBe('123,456.789');
  });

  it('should correctly format strings with options', () => {
    expect(formatNumber('123456.789', { style: 'currency', currency: 'USD' })).toBe('$123,456.79');
  });

  it('should return NaN for non-numeric strings', () => {
    expect(formatNumber('abc')).toBe('NaN');
  });
});
