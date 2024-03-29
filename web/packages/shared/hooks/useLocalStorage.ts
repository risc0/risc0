import { isEqual, isFunction, isNil } from "lodash-es";
import { type Dispatch, type SetStateAction, useEffect, useRef, useState } from "react";
import parseJSON from "../utils/parseJSON";
import useEventListener from "./useEventListener";

type SetValue<T> = Dispatch<SetStateAction<T>>;

/**
 * Creating and read here and using window.setItem for writes. This avoids
 * tapping into the react rendering pipeline unnecessarily when it isnt needed
 *
 * @param key the key to use to store
 * @returns the value requested
 */
const readValueFromStorage = <T>(key: string) => {
  try {
    const item = window.localStorage.getItem(key);

    const value = item && (parseJSON(item) as T);

    return value ?? undefined;
  } catch (error) {
    console.warn(`Error reading localStorage key "${key}":`, error);

    return { error: "unable to read value" };
  }
};

type StorageError = {
  error: string;
};

const isError = (value: StorageError | any): value is StorageError => !!value?.error;

const useLocalStorage = <T>(key: string, initialValue: T): [T, SetValue<T>] => {
  const previousValueRef = useRef(initialValue);

  // Get from local storage then
  // parse stored json or return initialValue
  const readValue = (): T => {
    // Prevent build error "window is undefined" but keep keep working
    if (typeof window === "undefined") {
      return initialValue;
    }

    const value = readValueFromStorage<T>(key);

    return isError(value) || isNil(value) || value === "" ? initialValue : value;
  };

  // State to store our value
  // Pass initial state function to useState so logic is only executed once
  const [storedValue, setStoredValue] = useState<T>(readValue);

  // Return a wrapped version of useState's setter function that ...
  // ... persists the new value to localStorage.
  const setValue: SetValue<T> = (value) => {
    // Prevent build error "window is undefined" but keeps working
    if (typeof window === "undefined") {
      console.warn(`Tried setting localStorage key "${key}" even though environment is not a client`);
    }

    try {
      // Allow value to be a function so we have the same API as useState
      const newValue = isFunction(value) ? value(storedValue) : value;

      // Save to local storage
      window.localStorage.setItem(key, JSON.stringify(newValue));

      // Save state
      setStoredValue(newValue);

      // We dispatch a custom event so every useLocalStorage hook are notified
      window.dispatchEvent(new Event("local-storage"));
    } catch (error) {
      console.warn(`Error setting localStorage key "${key}":`, error);
    }
  };

  // biome-ignore lint/correctness/useExhaustiveDependencies: run only once
  useEffect(() => {
    const newValue = readValue();
    setStoredValue(newValue);
    previousValueRef.current = newValue;
    // run only once
  }, []);

  const handleStorageChange = () => {
    const newValue = readValue();

    if (isEqual(newValue, previousValueRef.current)) {
      return;
    }
    setStoredValue(newValue);
    previousValueRef.current = newValue;
    // run only once
  };

  // this only works for other documents, not the current one
  useEventListener("storage", handleStorageChange);

  // this is a custom event, triggered in writeValueToLocalStorage
  // See: useLocalStorage()
  useEventListener("local-storage", handleStorageChange);

  return [storedValue, setValue];
};

export default useLocalStorage;
