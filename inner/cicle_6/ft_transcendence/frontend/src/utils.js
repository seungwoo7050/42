"use strict";

export function getRobustEndpoint(endpoint) {
  const protocol = window.location.protocol;
  const host = window.location.hostname;
  const port = window.location.port ? ":" + window.location.port : "";
  return new URL(endpoint, protocol + "//" + host + port);
}

/**
 * @return {0} status 200 (authorized)
 * @return {1} status 401 (unauthorized; no access token)
 * @return {2} status 403 (forbidden; 2fa required)
 */
export async function sendHeartbeat() {
  try {
    const response = await fetch(getRobustEndpoint("api/v1/auth/status"), {
      mode: "same-origin",
      credentials: "include",
    });
    if (response.status == 200) {
      // authorized
      // console.error(`sendHeartbeat: http status ${response.status}`);
      return 0;
    } else if (response.status == 403) {
      // 2fa
      return 2;
    } else {
      // unauthorized (no access token)
      return 1;
    }
    // const payload = await response.json();
    // // alert(payload.ack);
    // console.error(`payload: ${JSON.stringify(payload)}`);
    // return payload.ack || false;
  } catch (err) {
    console.error(`sendHeartbeat: ${err.message}`);
    return 1;
  }
}

// export function getCookie(name) {
//   let cookieValue = null;
//   if (document.cookie && document.cookie !== "") {
//     const cookies = document.cookie.split(";");
//     for (let i = 0; i < cookies.length; i++) {
//       const cookie = cookies[i].trim();
//       // Does this cookie string begin with the name we want?
//       if (cookie.substring(0, name.length + 1) === name + "=") {
//         cookieValue = decodeURIComponent(cookie.substring(name.length + 1));
//         break;
//       }
//     }
//   }
//   alert(cookieValue);
//   return cookieValue;
// }

export function remToPx(rem) {
  return (
    rem * parseFloat(window.getComputedStyle(document.documentElement).fontSize)
  );
}

export function openPopup(url, widthPx, heightPx) {
  const screenLeft = window.screenLeft ?? window.screenX;
  const screenTop = window.screenTop ?? window.screenY;
  const screenWidth =
    window.innerWidth ?? document.documentElement.clientWidth ?? screen.width;
  const screenHeight =
    window.innerHeight ??
    document.documentElement.clientHeight ??
    screen.height;

  const left = screenLeft + (screenWidth - widthPx) / 2;
  const top = screenTop + (screenHeight - heightPx) / 2;

  return window.open(
    url,
    "hahaha",
    `width=${widthPx},height=${heightPx},top=${top},left=${left},resizable,scrollbars`
  );
}

// async function sendHeartbeat() {
//   const response = await fetch("auth/v1/heartbeat");
//   const json = await response.json();
//   return json.authenticated;
// }
