FROM python:3.12-slim

# Set environment variables
ENV PYTHONDONTWRITEBYTECODE 1
ENV PYTHONUNBUFFERED 1

# Set working directory
WORKDIR /app

# Install system dependencies
RUN apt-get update && apt-get install -y \
    curl \
    && curl -fsSL https://deb.nodesource.com/setup_20.x | bash - \
    && apt-get install -y nodejs \
    --no-install-recommends \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Install Python dependencies
COPY backend/requirements.txt docker/web/dev/entrypoint.sh .
RUN pip install --no-cache-dir -r requirements.txt

COPY frontend/vite.config.js frontend/package.json frontend/yarn.lock .
COPY frontend/src src/
RUN corepack enable && yarn install

# Copy project files
COPY backend/ .


# # Install Node.js dependencies
# RUN cd frontend \
#     && corepack enable \
#     && yarn install \
#     && ../

# Expose the port Django runs on
EXPOSE 8000

# Command to run the Django server
CMD ["python", "manage.py", "runserver", "0.0.0.0:8000"]
