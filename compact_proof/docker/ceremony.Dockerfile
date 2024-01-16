# syntax=docker/dockerfile:1
FROM node AS ceremony

WORKDIR /ceremony

# install snarkjs globally
RUN npm install -g snarkjs0.7.3

COPY scripts/run_ceremony.sh .
RUN chmod +x run_ceremony.sh
RUN ulimit -s unlimited

ENTRYPOINT ["/ceremony/run_ceremony.sh", "/ceremony/groth16/pot23.ptau"]
