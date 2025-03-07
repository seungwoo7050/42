// "use strict";

// import { createRoot } from "react-dom/client";
// import { StrictMode } from "react";
// import { BrowserRouter } from "react-router-dom";
// import App from "./App.jsx";

// createRoot(document.getElementById("root")).render(
//   <StrictMode>
//     <BrowserRouter>
//       <App />
//     </BrowserRouter>
//   </StrictMode>
// );

// 2FA TEST
// import React from "react";
// import { createRoot } from "react-dom/client";
// import TestTwoFactorAuth from "./TestTwoFA"; // 테스트용 컴포넌트 가져오기

// createRoot(document.getElementById("root")).render(
//   <React.StrictMode>
//     <TestTwoFactorAuth />
//   </React.StrictMode>
// );

// Game TEST
import React from "react";
import { createRoot } from "react-dom/client";
import { StrictMode } from "react";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import App from "./App.jsx";

createRoot(document.getElementById("root")).render(
  // <StrictMode>
  <BrowserRouter>
    <App />
  </BrowserRouter>
  // </StrictMode>
);
