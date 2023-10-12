import React from "react";
import clsx from "clsx";
import styles from "./styles.module.css";

const FeatureList = [
  {
    title: "Open Source",
    png: require("@site/static/img/feature/apache2.png").default,
    description: (
      <>
        Our{" "}
        <a href="https://github.com/risc0/risc0">
          codebase is licensed under the Apache2 license
        </a>{" "}
        and includes a full proving and verification system.
      </>
    ),
  },
  {
    title: "Your Favorite Languages",
    png: require("@site/static/img/feature/languages.png").default,
    description: (
      <>
        RISC Zero supports Rust and C++ for writing ZK proofs. Any language that
        compiles to RISC-V can be supported.
      </>
    ),
  },
  {
    title: "Real Microarchitecture",
    png: require("@site/static/img/feature/zkvm.png").default,
    description: (
      <>
        The RISC Zero ZKVM is a verifiable computer that works like a real
        embedded RISC-V microprocessor, enabling programmers to write ZK proofs
        like they write any other code.
      </>
    ),
  },
];

function Feature({ png, title, description }) {
  return (
    <div className={clsx("col col--4")}>
      <div className="text--center">
        <img className={styles.featurePng} src={png} />
      </div>
      <div className="text--center padding-horiz--md">
        <h3>{title}</h3>
        <p>{description}</p>
      </div>
    </div>
  );
}

export default function HomepageFeatures() {
  return (
    <section className={styles.features}>
      <div className="container">
        <div className="row">
          {FeatureList.map((props, idx) => (
            <Feature key={idx} {...props} />
          ))}
        </div>
      </div>
    </section>
  );
}
