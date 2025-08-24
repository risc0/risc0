// Define interface for CSV row data
interface CSVRow {
  [key: string]: string;
}

export function convertCsvToJson(csvData: string): CSVRow[] {
  if (!csvData) {
    return [];
  }

  const lines = csvData.split("\n");
  const headers = lines[0].split(",");
  const result: CSVRow[] = [];

  for (let i = 1; i < lines.length; i++) {
    const obj: CSVRow = {};
    const currentLine = lines[i].split(",");

    for (let j = 0; j < headers.length; j++) {
      obj[headers[j]?.trim()] = currentLine[j]?.trim();
    }

    result.push(obj);
  }

  return result;
}
