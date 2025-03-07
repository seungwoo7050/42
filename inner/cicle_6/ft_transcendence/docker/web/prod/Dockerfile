# Stage 1: Build JavaScript assets
FROM node:bookworm-slim AS frontend-builder
WORKDIR /frontend

COPY frontend/ .

RUN corepack enable \
    && yarn install \
    && yarn run build



# Stage 2: Build Django app
FROM python:3.12-slim

ENV PYTHONDONTWRITEBYTECODE 1
ENV PYTHONUNBUFFERED 1

WORKDIR /app

COPY backend/requirements.txt docker/web/prod/entrypoint.sh .
RUN pip install --no-cache-dir -r requirements.txt

COPY --from=frontend-builder /frontend/src/dist /app/frontend/src/dist

COPY backend/ .

EXPOSE 8000

