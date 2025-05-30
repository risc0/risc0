import { ScrollArea, ScrollBar } from "@/components/ui/scroll-area"
import { Button } from "@/components/ui/button"
import { Check, Copy } from "lucide-react"
import { useState, Dispatch, SetStateAction } from "react"
import { Highlight, themes } from "prism-react-renderer"
import { Tabs, TabsContent, TabsList, TabsTrigger } from "@/components/ui/tabs"

const fibonacciSource = `/** Return no. of digits and time taken to calculate for the nth Fibonacci number. */
function calculateFibbonaci(n: number): { digits: number, timeMs: number } {
  let a = 0n,
    b = 1n;
  const start = performance.now();

  for (let i = 0; i < n; i++) {
    [a, b] = [b, a + b];
  }

  return {
    digits: a.toString().length,
    timeMs: performance.now() - start,
  };
}`;

const guestSource = `/// fast-doubling fib in O(log n) multiplications
fn fib_pair(n: u32) -> (BigUint, BigUint) {
    if n == 0 {
        (BigUint::zero(), BigUint::one())
    } else {
        let (a, b) = fib_pair(n >> 1);
        // F(2k) = F(k) * (2·F(k+1) – F(k))
        let two_b_minus_a = &b * 2u32 - &a;
        let c = &a * two_b_minus_a;
        // F(2k+1) = F(k)^2 + F(k+1)^2
        let d = &a * &a + &b * &b;
        if n & 1 == 0 {
            (c, d)
        } else {
            (d.clone(), c + d)
        }
    }
}

fn main() {
    let n: u32 = env::read();

    // compute F_n exactly
    let (f_n, _) = fib_pair(n);

    // decimal-serialize and count digits
    let s = f_n.to_str_radix(10);
    let digit_count = s.len() as u32;

    // only commit the digit count
    env::commit(&digit_count);
}
`

const verifierSource = `#[wasm_bindgen]
pub fn verify_proof(proof_bytes: &[u8], image_id_bytes: &[u8]) -> Result<u32, JsValue> {
    // deseralize proof into Receipt
    let receipt = Receipt::try_from_slice(proof_bytes)
        .map_err(|e| JsValue::from(format!("Bad receipt: {e}")))?;

    // decode and log journal value
    let value: u32 = receipt
        .journal
        .decode()
        .map_err(|e| JsValue::from(format!("Journal decode: {e}")))?;
    console::log_1(&format!("Decoded journal value = {value}").into());

    // deseralize and log image ID
    let image_id = Digest::try_from_slice(image_id_bytes)
        .map_err(|_| JsValue::from("ImageID not 32 bytes"))?;
    console::log_1(&format!("Image ID: 0x{image_id}").into());

    // verify proof
    receipt
        .verify(image_id)
        .map_err(|e| JsValue::from(format!("Verify failed: {e}")))?;

    console::log_1(&"Proof verified successfully".into());
    Ok(value)
}`;

interface TabbedCodeBlockProps {
  activeTab?: string;
  onTabChange?: Dispatch<SetStateAction<string>>;
}

export function TabbedCodeBlock({ activeTab, onTabChange }: TabbedCodeBlockProps) {
  const [copied, setCopied] = useState(false)
  const [internalActiveTab, setInternalActiveTab] = useState("wasm")

  const currentTab = activeTab || internalActiveTab;

  const handleTabChange = (value: string) => {
    setInternalActiveTab(value);
    if (onTabChange) {
      onTabChange(value);
    }
  };

  const getCode = () => {
    switch (currentTab) {
      case "wasm":
        return verifierSource;
      case "guest":
        return guestSource;
      case "fibonacci":
        return fibonacciSource;
      default:
        return verifierSource;
    }
  }

  function handleCopy() {
    navigator.clipboard.writeText(getCode()).then(() => {
      setCopied(true)
      setTimeout(() => setCopied(false), 2000)
    })
  }

  return (
    <div className="relative my-4 border rounded-lg">
      <Tabs value={currentTab} onValueChange={handleTabChange} className="bg-muted rounded-t-lg w-full">
        <TabsList className="px-2 pt-2">
          <TabsTrigger value="guest">Guest Program</TabsTrigger>
          <TabsTrigger value="fibonacci">Fibonacci TS</TabsTrigger>
          <TabsTrigger value="wasm">WASM Verifier</TabsTrigger>
        </TabsList>
        <TabsContent value="fibonacci" className="relative w-[600px]">
          <ScrollArea>
            <Highlight
              code={fibonacciSource.trim()}
              language={'typescript'}
              theme={themes.dracula}
            >
              {({ className, style, tokens, getLineProps, getTokenProps }) => (
                <pre className={`${className} p-4 text-sm`} style={style}>
                  {tokens.map((line, i) => (
                    <div key={i} {...getLineProps({ line })}>
                      {line.map((tok, key) => (
                        <span key={key} {...getTokenProps({ token: tok })} />
                      ))}
                    </div>
                  ))}
                </pre>
              )}
            </Highlight>
            <ScrollBar orientation="horizontal" />
          </ScrollArea>
        </TabsContent>
        <TabsContent value="wasm" className="relative w-[600px]">
          <ScrollArea>
            <Highlight
              code={verifierSource.trim()}
              language={'rust'}
              theme={themes.dracula}
            >
              {({ className, style, tokens, getLineProps, getTokenProps }) => (
                <pre className={`${className} p-4 text-sm`} style={style}>
                  {tokens.map((line, i) => (
                    <div key={i} {...getLineProps({ line })}>
                      {line.map((tok, key) => (
                        <span key={key} {...getTokenProps({ token: tok })} />
                      ))}
                    </div>
                  ))}
                </pre>
              )}
            </Highlight>
            <ScrollBar orientation="horizontal" />
          </ScrollArea>
        </TabsContent>
        <TabsContent value="guest" className="relative rounded-lg w-[600px]">
          <ScrollArea className="">
            <Highlight
              code={guestSource.trim()}
              language={'rust'}
              theme={themes.dracula}
            >
              {({ className, style, tokens, getLineProps, getTokenProps }) => (
                <pre className={`${className} p-4 text-sm`} style={style}>
                  {tokens.map((line, i) => (
                    <div key={i} {...getLineProps({ line })}>
                      {line.map((tok, key) => (
                        <span key={key} {...getTokenProps({ token: tok })} />
                      ))}
                    </div>
                  ))}
                </pre>
              )}
            </Highlight>
            <ScrollBar orientation="horizontal" />
          </ScrollArea>
        </TabsContent>
      </Tabs>
      <Button
        onClick={handleCopy}
        size="icon"
        variant="ghost"
        className="absolute top-1 right-1"
      >
        {copied ? <Check className="h-4 w-4" /> : <Copy className="h-4 w-4" />}
      </Button>
    </div>
  )
} 
