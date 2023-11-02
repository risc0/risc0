import React from "react";
import { Redirect } from "@docusaurus/router";
import useBaseUrl from "@docusaurus/useBaseUrl";

const Home = () => {
  const url = useBaseUrl("/api");
  return <Redirect to={url} />;
};

export default Home;
