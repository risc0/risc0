import { Redirect } from "@docusaurus/router";
import useBaseUrl from "@docusaurus/useBaseUrl";
import React from "react";

const Home = () => {
  const url = useBaseUrl("/api");
  return <Redirect to={url} />;
};

export default Home;
