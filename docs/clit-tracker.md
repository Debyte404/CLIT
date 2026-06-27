# CLIT Beginner Build Tracker

Use this as your daily checklist. For every milestone, do the learning steps first, then write code, then run the proof command.

## Rule For Every Milestone

- [ ] I can explain the concept in plain English.
- [ ] I know which command I am building.
- [ ] I know which files the command reads or writes.
- [ ] I know which C concepts are needed.
- [ ] I wrote the smallest version first.
- [ ] I ran the proof command.
- [ ] I can explain what the command output means.

## Current Baseline

Before adding new Git features:

- [ ] Open `src/main.c` and understand whether it has a `main` function.
- [ ] Open `src/repo.c` and find `cmd_init`.
- [ ] Notice that `cmd_init` currently tries to create `.clit` twice.
- [ ] Understand that `.clit` is CLIT's private database folder.

## Milestone 1: `init`

**Plain English:** Make a normal folder ready to store version history.

**Command:** `bin\clit init`

**Files you will edit:** `src/main.c`, `src/repo.c`, `include/clit.h`

**Hidden files created by the command:**

```text
.clit/
  HEAD
  objects/
  refs/
    heads/
```

**C concepts:** `argc`, `argv`, `strcmp`, `mkdir`, `fopen`, `fprintf`, return codes.

**Proof:**

```powershell
make
bin\clit init
Get-ChildItem -Recurse .clit
Get-Content .clit\HEAD
```

- [ ] `bin\clit init` runs.
- [ ] `.clit/objects` exists.
- [ ] `.clit/refs/heads` exists.
- [ ] `.clit/HEAD` contains `ref: refs/heads/main`.
- [ ] I can explain why CLIT needs `.clit`.

## Milestone 2: `hash-object`

**Plain English:** Take a file and give its content a name based on its bytes.

**Command:** `bin\clit hash-object README.md`

**Files you will edit:** `src/object.c`, `src/sha1.c`, `include/utils.h`, `include/clit.h`

**C concepts:** reading bytes, `malloc`, buffer length, SHA-1, hex strings.

**Proof:**

```powershell
make
bin\clit hash-object README.md
bin\clit hash-object README.md
```

- [ ] The command prints a 40-character hash.
- [ ] Running it twice on the same file prints the same hash.
- [ ] I can explain why changing one byte changes the hash.

## Milestone 3: `hash-object -w`

**Plain English:** Store the hashed file content inside `.clit/objects`.

**Command:** `bin\clit hash-object -w README.md`

**Files you will edit:** `src/object.c`, `include/utils.h`

**C concepts:** zlib compression, folder creation, binary file writing.

**Proof:**

```powershell
bin\clit hash-object -w README.md
Get-ChildItem .clit\objects -Recurse
```

- [ ] Object file appears under `.clit/objects/xx/yyyy...`.
- [ ] I can explain why the first two hash characters become a folder name.

## Milestone 4: `cat-file`

**Plain English:** Read a stored object back and show what is inside it.

**Command:** `bin\clit cat-file -p <hash>`

**Files you will edit:** `src/object.c`, `include/clit.h`

**C concepts:** path building, binary reads, zlib decompression, parsing headers.

**Proof:**

```powershell
bin\clit cat-file -t <hash>
bin\clit cat-file -p <hash>
```

- [ ] `-t` prints `blob`.
- [ ] `-p` prints the original file content.
- [ ] I can point to the type, size, and payload in an object.

## Milestone 5: `add` and `status`

**Plain English:** Choose files that should go into the next snapshot.

**Commands:**

```powershell
bin\clit add README.md
bin\clit status
```

**Files you will edit:** `src/index.c`, `src/object.c`, `include/clit.h`

**C concepts:** structs, arrays, replacing entries by path, writing a simple text file.

**Proof:**

```powershell
Get-Content .clit\index
```

- [ ] `.clit/index` contains path, mode, and hash.
- [ ] Adding the same file twice does not duplicate it.
- [ ] I can explain the difference between add and commit.

## Milestone 6: `write-tree`

**Plain English:** Turn the staged files into a snapshot object.

**Command:** `bin\clit write-tree`

**Files you will edit:** `src/tree.c`, `src/index.c`, `src/object.c`

**C concepts:** loading index entries, sorting, formatting a tree payload.

**Proof:**

```powershell
bin\clit write-tree
bin\clit cat-file -p <tree-hash>
```

- [ ] Command prints a tree hash.
- [ ] Tree output lists staged files.
- [ ] I can explain how a tree connects names to blob hashes.

## Milestone 7: `commit`

**Plain English:** Save a named snapshot in history.

**Command:** `bin\clit commit -m "first commit"`

**Files you will edit:** `src/commit.c`, `src/tree.c`, `src/repo.c`, `include/clit.h`

**C concepts:** string building, timestamps, reading refs, writing refs.

**Proof:**

```powershell
bin\clit commit -m "first commit"
Get-Content .clit\refs\heads\main
bin\clit cat-file -p <commit-hash>
```

- [ ] Commit contains a tree hash.
- [ ] First commit has no parent.
- [ ] Branch file stores the newest commit hash.
- [ ] I can explain why a branch is just a pointer.

## Milestone 8: `log`

**Plain English:** Walk backward through commit history.

**Command:** `bin\clit log`

**Files you will edit:** `src/commit.c`, `src/repo.c`

**C concepts:** loops, parsing lines, copying hash strings.

**Proof:**

```powershell
bin\clit log
```

- [ ] Newest commit prints first.
- [ ] Parent commits print after it.
- [ ] I can explain why history acts like a linked list.

## Milestone 9: basic `checkout`

**Plain English:** Rebuild working files from a commit.

**Command:** `bin\clit checkout <commit-hash>`

**Files you will edit:** `src/checkout.c`, `src/tree.c`, `src/object.c`

**C concepts:** reading commit objects, reading tree objects, writing files safely.

**Proof:**

```powershell
bin\clit checkout <commit-hash>
```

- [ ] Checkout reads the commit's tree.
- [ ] Checkout restores tracked files from blobs.
- [ ] First version refuses to overwrite changed files.
- [ ] I can explain why checkout is object reconstruction.

## Stretch Work After The Core

- [ ] Recursive trees for nested directories.
- [ ] Branch creation and switching.
- [ ] Ignore rules.
- [ ] Integration test script.
- [ ] Merge base detection.
- [ ] Three-way merge prototype.
- [ ] Packfile reading.
