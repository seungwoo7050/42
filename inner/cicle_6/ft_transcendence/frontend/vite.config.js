import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";

// https://vite.dev/config/
export default defineConfig({
  // base: process.env.mode === "production" ? "/static/" : "/",
  build: {
    manifest: true,
    rollupOptions: {
      input: "/frontend/src/index.html",
    },
  },
  plugins: [react()],
  root: "./src",
  server: {
    // port: process.env.VITE_DEV_PORT ? Number(process.env.VITE_DEV_PORT) : 5173,
    host: true,
    port: 8002,
    // origin: "http://127.0.0.1:8080",
    // open: "/frontend/src/index.html",
  },
});
