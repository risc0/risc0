import { joinWords } from './join-words';

describe('joinWords', () => {
  it('should return an empty string if the input is empty', () => {
    expect(joinWords('')).toBe('');
  });

  it('should return an empty string if the input is null', () => {
    // @ts-expect-error -- tests
    expect(joinWords(null)).toBe('');
  });

  it('should return an empty string if the input is undefined', () => {
    // @ts-expect-error -- tests
    expect(joinWords(undefined)).toBe('');
  });

  it('should return a string with words joined by a space if the input is a string with multiple words', () => {
    expect(joinWords('HelloWorld')).toBe('Hello World');
  });

  it('should return the same string if the input is a string with one word', () => {
    expect(joinWords('Hello')).toBe('Hello');
  });

  it('should return the same string if the passed word is all uppercase', () => {
    expect(joinWords('HELLO')).toBe('HELLO');
  });
});
