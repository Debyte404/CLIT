# CLIT Git-in-C Tutorial Design

## Goal

Build a resume-worthy mini Git implementation in C called `clit`, while making the learning process explicit. The project should teach how Git works internally and how to express those ideas in C without hiding the important systems concepts behind copy-paste code.

The one-day target is not to clone every Git feature. The target is a coherent core:

- `clit init`
- `clit hash-object`
- `clit cat-file`
- `clit add`
- `clit status`
- `clit write-tree`
- `clit commit`
- `clit log`
- basic `clit checkout`

## User Context

The user knows basic C syntax through structs and has built simple data structures such as queues and linked lists. The tutorial should assume comfort with simple C programs, but explain the systems pieces carefully:

- command-line argument dispatch
- file and directory APIs
- binary-safe buffers
- structs for durable file formats
- dynamic arrays
- path normalization
- SHA-1 hashing
- zlib compression
- serialization and parsing
- defensive error handling
- manual verification from the terminal

## Current Repository Baseline

The repository currently has this shape:

- `include/clit.h` declares `cmd_init`.
- `src/repo.c` contains a first version of `cmd_init`.
- `src/main.c`, `src/object.c`, `src/tree.c`, and `include/utils.h` are effectively empty.
- `MAKEFILE` compiles all `src/*.c` into `bin/clit` and links `zlib` and OpenSSL crypto.

The first implementation lesson should repair and explain `init`, including the existing issue where `.clit` is created twice.

## Chosen Approach

Use an inside-out learning path:

1. Explain Git as a content-addressed object database.
2. Implement blob object storage.
3. Add object inspection.
4. Introduce the index as the staging area.
5. Serialize trees from index entries.
6. Create commits that point to trees and parents.
7. Read refs and print history.
8. Reconstruct files for a basic checkout.

This approach is best for a systems resume because it lets the user explain the underlying model:

```text
file bytes -> blob object -> tree object -> commit object -> branch ref -> HEAD
```

The tutorial will still be organized by runnable milestones so every chapter leaves the project in a testable state.

## Tutorial Artifact

Create one self-contained HTML tutorial at:

```text
docs/tutorial.html
```

The page should be readable offline and should include:

- a project roadmap
- visual diagrams using HTML/CSS, not external services
- command examples
- C concept callouts
- Git internals explanations
- implementation checklists
- manual verification commands
- debugging notes
- resume/interview talking points
- extra resources

The tutorial should be practical rather than decorative. Visuals should clarify object relationships, file layouts, and command flow.

## Tracker Artifact

Create a separate implementation tracker at:

```text
docs/clit-tracker.md
```

The tracker should use checkboxes and cover:

- each command milestone
- concepts learned
- files expected to change
- manual checks
- stretch ideas after the one-day target

This tracker lets the user proceed feature by feature while keeping the learning goal visible.

## Milestones

### Milestone 1: Project Skeleton and `init`

Teach:

- command dispatch in `main`
- repository directory layout
- cross-platform directory creation
- basic error handling

Target behavior:

```text
clit init
```

creates:

```text
.clit/
  HEAD
  objects/
  refs/
    heads/
```

### Milestone 2: Blob Objects

Teach:

- reading whole files safely
- Git object headers
- SHA-1 object IDs
- zlib compression
- object paths based on hash prefixes

Target behavior:

```text
clit hash-object path/to/file
clit hash-object -w path/to/file
```

### Milestone 3: Object Inspection

Teach:

- locating objects by hash
- decompression
- parsing object headers
- printing object content

Target behavior:

```text
clit cat-file -t <hash>
clit cat-file -p <hash>
```

### Milestone 4: Index and `add`

Teach:

- what staging means
- index entry structs
- path and mode storage
- why Git tracks snapshots rather than diffs

Target behavior:

```text
clit add file.txt
clit status
```

### Milestone 5: Trees

Teach:

- tree object shape
- sorted entries
- file modes
- recursive directory representation

Target behavior:

```text
clit write-tree
```

### Milestone 6: Commits

Teach:

- commit object format
- author metadata
- parent commits
- refs and HEAD

Target behavior:

```text
clit commit -m "message"
```

### Milestone 7: Log

Teach:

- following parent pointers
- reading refs
- formatting commit history

Target behavior:

```text
clit log
```

### Milestone 8: Basic Checkout

Teach:

- resolving commit IDs
- reading commit and tree objects
- reconstructing working files
- limitations of overwriting files safely

Target behavior:

```text
clit checkout <commit>
```

## Explicit Non-Goals For Today

The tutorial should mention these as future work but not treat them as required for the first completion:

- merges
- conflict resolution
- networking/remotes
- packfiles
- reflog
- rebase
- ignore rules
- full branch management
- full Git-compatible index binary format
- cryptographic security claims about SHA-1

## Error Handling Design

The implementation should prefer small helper functions with clear failure behavior:

- return `0` for success and nonzero for failure in commands
- return allocated pointers or `NULL` from loaders
- print concise error messages close to the failure site
- avoid crashing on missing files, invalid hashes, or malformed objects

## Testing and Verification

The first pass can rely on manual verification commands because the user is learning the system. The tracker should include commands like:

```text
make
bin/clit init
bin/clit hash-object -w README.md
bin/clit cat-file -p <hash>
bin/clit add README.md
bin/clit write-tree
bin/clit commit -m "first commit"
bin/clit log
```

Later stretch work can add shell-based integration tests.

## Resume Framing

The final project should be described as:

> Implemented a mini Git-compatible version control system in C, including content-addressed object storage, compressed blob/tree/commit objects, a staging index, commit history traversal, and basic checkout.

The tutorial should include a short section explaining how to discuss the project in interviews:

- what content-addressed storage means
- why commits point to trees
- how refs and HEAD work
- what the index does
- what was intentionally simplified

## Open Implementation Notes

The tutorial should not dump a full finished implementation all at once. It should guide the user chapter by chapter, with enough code to explain the key ideas and enough exercises to make the user write meaningful parts.

When implementation begins, the first practical step should be a small plan for repairing `init` and adding command dispatch, followed by object storage.
