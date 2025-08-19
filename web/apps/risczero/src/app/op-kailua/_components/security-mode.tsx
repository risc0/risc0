import { Button } from "@risc0/ui/button";
import {
  ArrowLeftRightIcon,
  CalendarIcon,
  CircleCheckBigIcon,
  CircleDollarSignIcon,
  ClockIcon,
  CoinsIcon,
  HandshakeIcon,
  LockKeyholeIcon,
  SettingsIcon,
  UsersIcon,
  XIcon,
  ZapIcon,
} from "lucide-react";
import Image from "next/image";
import Link from "next/link";
import { Fragment, type ReactNode } from "react";
import { Title } from "@/app/_components/title";

type SecurityFeature = {
  label: string;
  opfp: {
    label: string;
    icon?: ReactNode;
  };
  hybrid: {
    label: string;
    icon?: ReactNode;
  };
  validity: {
    label: string;
    icon?: ReactNode;
  };
};

const SECURITY_FEATURES: SecurityFeature[] = [
  {
    label: "Finality",
    opfp: {
      label: "7-day challenge period",
      icon: <CalendarIcon />,
    },
    hybrid: {
      label: "Configurable finality down to 3 hours",
      icon: <SettingsIcon />,
    },
    validity: {
      label: "1-hour finality",
      icon: <ClockIcon />,
    },
  },
  {
    label: "Security Model",
    opfp: {
      label: "Interactive disputes",
      icon: <ArrowLeftRightIcon />,
    },
    hybrid: {
      label: "Non-interactive disputes",
      icon: <CircleCheckBigIcon />,
    },
    validity: {
      label: "Validity proven",
      icon: <CircleCheckBigIcon />,
    },
  },
  {
    label: "Dispute Process",
    opfp: {
      label: "Requires an honest majority to reject transactions",
      icon: <UsersIcon />,
    },
    hybrid: {
      label: "Generates a ZKP only if there is a dispute",
      icon: <HandshakeIcon />,
    },
    validity: {
      label: "No disputes; generates a ZKP for every transaction",
      icon: <CircleCheckBigIcon />,
    },
  },
  {
    label: "Deposits Needed",
    opfp: {
      label: "Requires a new deposit per proposal or challenge",
      icon: <CoinsIcon />,
    },
    hybrid: {
      label: "Only one deposit for unlimited proposals",
      icon: <CircleDollarSignIcon />,
    },
    validity: {
      label: "No deposits required",
      icon: <XIcon />,
    },
  },
  {
    label: "Best For",
    opfp: {
      label: "—",
    },
    hybrid: {
      label: "Cost-sensitive chains that want faster finality",
      icon: <ZapIcon />,
    },
    validity: {
      label: "Large chains needing ultra-fast finality with maximum security",
      icon: <LockKeyholeIcon />,
    },
  },
];

export function SecurityMode() {
  return (
    <div className="container max-w-screen-2xl">
      <Title className="mb-0 max-w-max py-12 md:pt-24 md:pb-8">The Easiest Path to ZK for OP Chains</Title>

      <p className="mb-16 text-2xl">
        OP Kailua lets OP chains upgrade to ZK at their own pace. Choose between cost-efficient ZK Fraud proofs or full
        ZK Validity proofs, all with seamless integration and no switching costs.
      </p>

      <div className="pt-24">
        <Title className="mx-auto mb-24 w-full text-center md:text-5xl">Select Your Security Mode</Title>

        <div className="grid [grid-template-columns:auto_repeat(3,1fr)]">
          {/* Headers */}
          <div /> {/* Empty cell for alignment */}
          <div className="px-4 text-center">
            <h2 className="mb-3 h-[29px] font-bold text-2xl">OPFP</h2>
            <p className="font-bold">Default for OP Chains</p>
          </div>
          <div className="mb-5 px-4 text-center">
            <Image
              className="mx-auto mb-3 dark:invert"
              unoptimized
              src="/solutions/op-kailua.svg"
              alt="OP Kailua"
              width={200}
              height={29.18}
            />
            <p className="mb-3 font-bold">Hybrid Mode</p>
            <Link href="https://github.com/risc0/kailua" tabIndex={-1}>
              <Button
                size="sm"
                className="bg-op-kailua-light text-default-dark dark:bg-op-kailua-dark dark:text-default-light"
              >
                Try Now
              </Button>
            </Link>
          </div>
          <div className="mb-5 px-4 text-center">
            <Image
              className="mx-auto mb-3 dark:invert"
              unoptimized
              src="/solutions/op-kailua.svg"
              alt="OP Kailua"
              width={200}
              height={29.18}
            />
            <p className="mb-3 font-bold">Validity Mode</p>

            <Link href="https://github.com/risc0/kailua" tabIndex={-1}>
              <Button
                size="sm"
                className="bg-op-kailua-light text-default-dark dark:bg-op-kailua-dark dark:text-default-light"
              >
                Try Now
              </Button>
            </Link>
          </div>
          {/* Feature rows */}
          {SECURITY_FEATURES.map((feature, index) => (
            <Fragment key={feature.label}>
              <div
                className={`flex items-center rounded-l-xl font-bold text-xl md:px-12 md:py-8 ${index % 2 !== 1 ? "bg-op-kailua-light/5" : ""}`}
              >
                <span className="hidden md:block">{feature.label}</span>
              </div>
              <div
                className={`flex flex-col items-center justify-center gap-2 whitespace-pre-line rounded-l-xl px-2 py-8 text-center md:rounded-none md:px-12 ${index % 2 !== 1 ? "bg-op-kailua-light/5" : ""}`}
              >
                {feature.opfp.icon}
                <span className="text-xs md:text-base">{feature.opfp.label}</span>
              </div>
              <div
                className={`flex flex-col items-center justify-center gap-2 whitespace-pre-line px-2 py-8 text-center md:px-12 ${index % 2 !== 1 ? "bg-op-kailua-light/5" : ""}`}
              >
                {feature.hybrid.icon}
                <span className="text-xs md:text-base">{feature.hybrid.label}</span>
              </div>
              <div
                className={`flex flex-col items-center justify-center gap-2 whitespace-pre-line rounded-r-xl px-2 py-8 text-center md:px-12 ${index % 2 !== 1 ? "bg-op-kailua-light/5" : ""}`}
              >
                {feature.validity.icon}
                <span className="text-xs md:text-base">{feature.validity.label}</span>
              </div>
            </Fragment>
          ))}
        </div>
      </div>
    </div>
  );
}
