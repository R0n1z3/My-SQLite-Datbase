# SQLite Login Project Journey Plan

## Goal
Move this project from text-file authentication to a modular SQLite-backed C++ application with clear module boundaries and predictable behavior.

## Current State
- SQLite CLI is installed and usable.
- Database file exists at src/database/users.db.
- Users table has been created and basic SQL checks were done.
- Project has started modularization with these files:
  - include/auth.h
  - include/database.h
  - src/auth.cpp
  - src/database.cpp
  - src/main.cpp

## Target Architecture
- src/main.cpp
  - Program flow only (menu + calling modules + user-facing messages).
- include/database.h and src/database.cpp
  - Database lifecycle and schema setup.
- include/auth.h and src/auth.cpp
  - Registration, login checks, and password policy helpers.

## How Compile-Time Organization Works
- Header files declare interfaces (what exists).
- Source files implement logic (how it works).
- Every .cpp should include its own matching .h first.
- main.cpp should include only the headers it needs.
- Never include .cpp files from headers.

## Step-by-Step Plan

### Step 1: Clean Header Contracts
Purpose:
- Define stable module interfaces before adding more logic.

What to do:
- In include/auth.h, keep only auth declarations.
- In include/database.h, add DB lifecycle declarations.
- Remove any include of source files from headers.

Why:
- Prevents duplicate symbol and linker issues.
- Makes module boundaries explicit.

Success check:
- Headers contain declarations only.

### Step 2: Build Database Lifecycle Module
Purpose:
- Ensure app can reliably open DB, enforce foreign keys, and bootstrap schema.

Functions to implement in src/database.cpp:
- openDatabase
- initializeDatabase
- closeDatabase

How each function should behave:
- openDatabase:
  - Open users.db connection.
  - On failure, report SQLite error message and return failure.
  - On success, enable foreign key checks for the connection.
  - If PRAGMA step fails, close connection and return failure.
- initializeDatabase:
  - Run CREATE TABLE IF NOT EXISTS users(...).
  - Return success on clean execution, failure otherwise.
- closeDatabase:
  - Close non-null connection safely.

Why:
- Auth features should not run until DB is known-good.

Success check:
- App can open and close DB without errors.
- Schema initialization is idempotent.

### Step 3: Build Auth Module Against SQLite
Purpose:
- Replace text-file credential logic with SQL-based auth flows.

Functions to keep/implement in src/auth.cpp:
- getUsername
- getPassword
- isUpper
- registerUser
- loginUser (or keep checkCredentials with improved behavior)

How each should behave:
- getUsername:
  - Prompt and validate minimum length.
  - Loop until valid.
- isUpper:
  - Count uppercase letters.
  - Return true when threshold is met.
- getPassword:
  - Prompt and validate via password policy helper(s).
  - Loop until valid.
- registerUser:
  - Gather username/password.
  - Hash password (do not store plain password long-term).
  - Run parameterized INSERT into users.
  - Return status for success, duplicate username, or DB error.
- loginUser/checkCredentials:
  - Run parameterized SELECT by username.
  - If no row, return user-not-found.
  - If row exists, compare entered password (or computed hash) with stored value.
  - Return success or wrong-password.

Why:
- Keeps auth policy and DB query behavior in one coherent module.

Success check:
- Duplicate registration is rejected.
- Valid login succeeds.
- Wrong password and missing user are distinguished cleanly.

### Step 4: Refactor main.cpp Last
Purpose:
- Keep main as a small orchestrator.

What main should do:
- Open DB.
- Initialize schema.
- Ask register/login choice.
- Call auth module functions.
- Print user-facing result messages.
- Close DB.

Why:
- Separation of concerns and easier debugging.

Success check:
- main is short and readable.
- No SQL or file I/O logic inside main.

### Step 5: Remove Legacy Text-File Path
Purpose:
- Avoid split sources of truth.

What to do:
- Remove database.txt flow once SQLite path is fully working.
- Keep database.txt only as historical reference if wanted.

Why:
- Prevents confusion and inconsistent states.

Success check:
- App auth behavior is entirely SQLite-backed.

### Step 6: Verification Checklist
- Register a new user.
- Attempt duplicate username.
- Login with correct password.
- Login with incorrect password.
- Login with unknown username.
- Inspect users.db with VS Code SQLite extension.

### Step 7: Hardening Next (After Basics Work)
- Replace plain password storage with strong password hashing strategy.
- Add better input sanitization and user feedback.
- Add small unit tests for validation/auth logic where practical.

## SQL Concepts Used in This Project
- CREATE TABLE IF NOT EXISTS
- UNIQUE constraint for usernames
- NOT NULL constraints for required fields
- DEFAULT CURRENT_TIMESTAMP for audit metadata
- Parameterized queries via prepared statements

## Responsibility Map
- database module owns connection and schema readiness.
- auth module owns user policy and credential operations.
- main module owns top-level app flow.

## Milestone Definition
Project reaches first milestone when:
- Text-file credential path is removed.
- Register/login behavior is fully SQLite-backed.
- main is orchestration-only and modules compile cleanly.
