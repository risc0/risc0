import { createClient } from "@vercel/edge-config";

type FeatureFlags = {
  // all feature flags keys go here -- defined in https://vercel.com/risczero/benchmarks-and-reports/stores/edge-config/ecfg_gilzljkmtniynv2jyscjdscx16xg/items for benchmarks and reports app
  maintenance: boolean;
};

export async function getFeatureFlag(key: keyof FeatureFlags) {
  const prefixedKey = `featureFlag_${key}`;
  const edgeConfig = createClient(process.env.EDGE_CONFIG);
  const featureFlag = await edgeConfig.get<FeatureFlags>(prefixedKey);

  return featureFlag;
}
