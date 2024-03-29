import { type RefObject, useEffect, useRef } from "react";

/**
 * It returns a function that adds an event listener to a target element, and removes it when the
 * component unmounts
 * @param {keyof WindowEventMap | string} eventName - The name of the event to listen for.
 * @param handler - The function that will be called when the event is fired.
 * @param [element] - The element to listen to the event on. If not provided, it will default to
 * window.
 */
const useEventListener = <T extends HTMLElement = HTMLDivElement>(
  eventName: keyof WindowEventMap | string, // string to allow custom event
  handler: (event: Event) => void,
  element?: RefObject<T>,
) => {
  // Create a ref that stores handler
  const savedHandler = useRef<(event: Event) => void>();

  useEffect(() => {
    // Define the listening target
    const targetElement: T | Window = element?.current ?? window;

    if (!targetElement?.addEventListener) {
      return;
    }

    // Update saved handler if necessary
    if (savedHandler.current !== handler) {
      savedHandler.current = handler;
    }

    // Create event listener that calls handler function stored in ref
    const eventListener = (event: Event) => {
      if (savedHandler?.current) {
        savedHandler.current(event);
      }
    };

    targetElement.addEventListener(eventName, eventListener);

    // Remove event listener on cleanup
    return () => {
      targetElement.removeEventListener(eventName, eventListener);
    };
  }, [eventName, element, handler]);
};

export default useEventListener;
