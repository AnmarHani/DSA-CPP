# The Idea

A Fullstack app for dealing with Data Structures and Algorithms, the main purpose of this is educational, so I tried to tackle different patterns and best practices in C++, did not give as much attention to the UI since I focused on learning C++.

# Technologies

## Backend (C++)

- CrowCpp For HTTP API
- Catch2 For Unit Testing
- sqlite_orm for Database ORM (SQLite)

## Frontend

- Astro Frontend Framework
- TailwindCSS for CSS
- Axios as an HTTP API Client Library

## Database

- SQL (SQLite)

# How to Setup (Running the app locally)

0. Make sure you have installed C++17 (v23 Recommended) or above and NodeJS v20+
1. Build the Server (From Root, in the Terminal)

```
mkdir build
cd build
cmake ..
cmake --build .
```

2. (In Another Terminal [For Better Speed]) Install Frontend Dependencies (From Root, in the Terminal)

```
cd frontend
npm install
```

3. Run the server (From Root, in the Terminal)
   ./build/bin/DSA-CPP (If you are windows add .exe in the end, like DSA-CPP.exe)

4. Run the Frontend (From Root, in the Terminal)

```
cd frontend
npm run dev
```
