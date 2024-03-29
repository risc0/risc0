/**
 * @param {{ credential: string; }} response
 */
// biome-ignore lint/correctness/noUnusedVariables: keep
function doLogin(response) {
  document.cookie = `auth_token=${response.credential};`;
  window.location.replace("reports");
}
