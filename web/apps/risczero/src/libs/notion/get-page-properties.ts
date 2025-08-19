import type { Collection, ExtendedRecordMap } from "notion-types";
import { getDateValue, getTextContent } from "notion-utils";
import type { DefaultNotionProperties } from "@/app/blog/_types";

type SelectKeys = "type" | "tags" | "status";
type DateKey = "date";
type PersonKey = "person";

export function getPageProperties(
  id: string,
  block: ExtendedRecordMap["block"],
  schema: Collection["schema"],
): DefaultNotionProperties {
  const rawProperties = Object.entries(block[id]?.value.properties || []);
  const excludeProperties = ["date", "select", "multi_select", "person"];

  return rawProperties.reduce<DefaultNotionProperties>((properties, [key, value]) => {
    const type = schema[key]?.type;
    const name = schema[key]?.name;

    properties.id = id;

    if (type && !excludeProperties.includes(type)) {
      // @ts-expect-error
      properties[name as Exclude<keyof DefaultNotionProperties, SelectKeys>] = getTextContent(
        value as Parameters<typeof getTextContent>[0],
      );

      return properties;
    }

    switch (type) {
      case "date": {
        const tmpDateProperty: Partial<ReturnType<typeof getDateValue>> = getDateValue(
          value as Parameters<typeof getDateValue>[0],
        );

        if (tmpDateProperty) {
          tmpDateProperty.type = undefined;
          properties[name as DateKey] = tmpDateProperty;
        }
        break;
      }
      case "person": {
        properties[name as PersonKey] = (value as any).filter((item) => item[0] === "‣").map((item) => item[1][0][1]);

        break;
      }
      case "select":
      case "multi_select": {
        const selects = getTextContent(value as Parameters<typeof getTextContent>[0]);

        if (selects[0]?.length) {
          properties[name as SelectKeys] = selects.split(",");
        }
        break;
      }
      default: {
        break;
      }
    }

    return properties;
  }, {});
}
