# RISC Zero Secure Development Life-cycle

RISC Zero believes in a comprehensive risk-based approach to security throughout our product and software development life-cycle.

This page provides an outline of the key practices that we utilize to harden our products and services against threats. These security techniques are continuously evolving as we learn from our experiences and adapt to new threats, and we encourage you to provide feedback or suggestions for improvement.

The key mechanisms that drive our process evolution are:

- External critique from customers, partners, and the security community
- Escape analysis of production defects and postmortem analysis of security incidents
- Identifying new potential activities based on industry frameworks including [NIST SSDF], [ISO 27002:2022], [BSIMM 14], [the ReKT test], and [OWASP SAAAM].
- Use of a maturity framework (known as FACTORS) to self-assess process maturity in the following areas:
  - F: Friction (pain felt across stakeholders)
  - A: Automation (is there an opportunity to automate this process further)
  - C: Coverage (both breadth and depth)
  - T: Timing (how early in the life-cycle security is considered, speed of execution, impact to developer agility)
  - O: Opportunity cost (what trade-offs are made between security and other business objectives)
  - R: Remediation maturity (how good are we at learning from issues discovered by this process)
  - S: Security resilience (how much harder does this activity make our systems to compromise)

Our secure development life cycle can be modeled as a series of five key phases:

## 1. Plan

During this phase, security experts work with product development and engineering resources to understand the product's intended use, the threats it may face, and the potential impact of a security breach.

Key security processes or features are identified based on risks factors known at this time, and a documented security plan is written which serves as a contract across project stakeholders for security expectations and release readiness.

## 2. Design

RISC Zero emphasizes secure design and architecture as a key component of our secure development life-cycle. During the design phase, security experts work with product development and engineering resources to ensure that security is built into the product from the ground up.

Based on risk, a formal asset-centric threat model may be developed in partnership across security and engineering leads. The high-level process for threat model development used is:

1. Develop a logical security model of the system's major components, data flows, and trust boundaries.
2. Determine the system's key assets and an initial set of controls that protect them.
3. Identify threat actors and their associated trust boundaries of the system.
4. Select attack classes that are relevant to the type of system, and brainstorm threats unique to that system where relevant.
5. Enumerate the identified intersection of threat actors and attack classes to system assets.
6. Determine the residual risk after applying controls to mitigate the attacks enumerated above.
7. Develop new controls, and iterate on the threat model until the residual risk is acceptable.
8. Model key failures to determine the impact of unforeseen control failure or bypass.
9. Document findings where residual risk is not acceptable, and develop a plan to address these risks.

For certain risk levels, lighter-weight design review processes (e.g. checklist-driven approaches) may be sufficient.

## 3. Develop

During software development, there is a focus shift toward avoiding implementation errors which result in security defects.

While specific practices, tools, and techniques vary by project, platform, and program language complexities ideally all projects benefit at this stage from:

- The use of secure-by-design components, libraries and frameworks.
- The use of languages that provide memory safety advantages.
- The use of static analysis tools to identify common security vulnerabilities.
- The use of software composition analysis tools to identify potential vulnerabilities in third-party libraries.
- The use of protected branches and a peer review process that's backed by named code owners who can provide substantive review including security best practices.

## 4. Verify

The verification phase is where the security of the product is tested. This phase includes a combination of manual and automated testing, including:

- [External deep dive audits] by leading security firms.
- Targeted fuzzing and dynamic security testing.
- Opportunistic use of formal verification in critical components of the system.
- The development and execution of security invariants and associated test cases.

## 5. Release

This phase validates if the objectives of the security plan have been met. This minimally includes verifying that:

- Findings from phase 4 have been addressed.
- Any necessary changes to the formal threat model have been made.
- Operational security processes are in place (e.g. IR and [Bug bounty]).

[BSIMM 14]: https://www.synopsys.com/software-integrity/software-security-services/bsimm-maturity-model.html
[Bug bounty]: https://hackenproof.com/programs/risc-zero-zkvm
[External deep dive audits]: https://github.com/risc0/rz-security/tree/release-2.1/audits
[ISO 27002:2022]: https://www.iso.org/standard/75652.html
[NIST SSDF]: https://csrc.nist.gov/Projects/ssdf
[OWASP SAAAM]: https://owasp.org/www-project-samm
[the ReKT test]: https://www.risczero.com/blog/risc-zero-take-the-rekt-test
