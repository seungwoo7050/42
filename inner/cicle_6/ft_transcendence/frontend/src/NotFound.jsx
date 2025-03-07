import React, { useState, useEffect, useRef } from "react";
import { useLocation } from "react-router-dom";

export function NotFound() {
  const location = useLocation();
  return (
    <div className="position-absolute top-50 start-50 translate-middle">
      <div className="position-relative">
        <h1 className="display-4">404 Not Found</h1>
        <p className="lead">퐁퐁퐁</p>
        <hr className="my-4" />
        <p className="text-center">
          The requested URL {location.pathname} was not found on this server.
        </p>
      </div>
    </div>
  );
}

export default NotFound;
