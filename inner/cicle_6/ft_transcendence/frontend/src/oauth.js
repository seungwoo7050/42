"use strict";

import { remToPx, openPopup } from "./utils.js";

const providers = ["42"];

/**
 * @param {str} provider
 * @return {Promise}
 */
export async function fetchAuthorizationEndpoint(provider) {
  const queryProviderUrl = new URL("/auth/login", window.location);
  queryProviderUrl.searchParams.set("provider", provider);

  return fetch(queryProviderUrl);
}

/**
 * @param {WindowProxy} popup
 * @return {undefined}
 */
async function monitorAuthStatus(popup) {
  const checkInterval = 1000; // Poll every second

  const poller = setInterval(async () => {
    const isAuthenticated = await checkAuthStatus();
    console.log(isAuthenticated);

    if (isAuthenticated) {
      clearInterval(poller); // Stop polling
      window.postMessage({ type: "auth_complete" }, window.location.origin); // Notify parent window
      popup.close(); // Close popup
    }
    console.log(popup.location.origin);
    // if (popup.location) {
    //   clearInterval(poller);
    //   console.log("Popup closed by user");
    // // }
  }, checkInterval);
}

/**
 * @param {str} provider
 * @return {WindowProxy}
 */
export function openOAuthPopup(provider) {
  // const response = await fetchProviderEndpoint(provider);
  // if (!response.ok) {
  //   alert(response.statusText);
  // }

  // const payload = await response.json();

  // const providerUrl = `${payload.endpoint}?client_id=${
  //   payload.client_id
  // }&redirect_uri=${encodeURIComponent(payload.redirect_uri)}&response_type=${
  //   payload.response_type
  // }`;

  // const url = new URL(provider.endpoint);
  // url.search = new URLSearchParams({
  //   client_id: provider.client_id,
  //   redirect_uri: provider.redirect_uri,
  //   response_type: provider.response_type,
  // });

  const url = new URL("http://127.0.0.1:8000/auth/redirect");

  const popup = openPopup(url, remToPx(30), remToPx(45));
  // if (!popup) {
  // alert("no popup?");
  // }

  return popup;

  // monitorAuthStatus(popup);
}
