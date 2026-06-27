# CLIT Git-in-C Tutorial Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Create a self-contained HTML tutorial and Markdown tracker that guide the user through building a resume-worthy Git-like version control system in C.

**Architecture:** The tutorial is a static offline document with built-in CSS diagrams, learning chapters, code snippets, exercises, manual checks, and interview framing. The tracker is a lightweight Markdown checklist that mirrors the tutorial milestones and can be updated as implementation proceeds.

**Tech Stack:** HTML, CSS, Markdown, local browser verification, existing C project context.

---

## File Structure

- Create: `docs/tutorial.html`
  - Self-contained tutorial page with internal CSS.
  - Explains Git internals and C concepts from the current CLIT baseline.
  - Uses diagrams made from HTML/CSS boxes and arrows.
  - Includes command milestones and implementation exercises.

- Create: `docs/clit-tracker.md`
  - Checkbox-based project tracker.
  - Mirrors the eight approved milestones.
  - Records concept goals, files expected to change, and manual verification commands.

- Read-only reference: `docs/superpowers/specs/2026-06-19-clit-git-in-c-tutorial-design.md`
  - Source of truth for scope.

- Do not modify in this plan: `src/*.c`, `include/*.h`, `MAKEFILE`
  - Implementation comes after the tutorial/tracker artifact is reviewed.

---

### Task 1: Create Tutorial Page Skeleton

**Files:**
- Create: `docs/tutorial.html`

- [ ] **Step 1: Add the base HTML document**

Create `docs/tutorial.html` with this structure:

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>CLIT: Build Git in C</title>
  <style>
    :root {
      --bg: #f7f8fb;
      --panel: #ffffff;
      --ink: #172033;
      --muted: #5d6678;
      --line: #d8deea;
      --accent: #2563eb;
      --accent-dark: #1d4ed8;
      --code-bg: #111827;
      --code-ink: #f9fafb;
      --good: #047857;
      --warn: #b45309;
      --soft-blue: #e8f0ff;
      --soft-green: #e8f7ef;
      --soft-amber: #fff4df;
    }

    * {
      box-sizing: border-box;
    }

    body {
      margin: 0;
      font-family: Arial, Helvetica, sans-serif;
      color: var(--ink);
      background: var(--bg);
      line-height: 1.6;
    }

    header {
      background: #101827;
      color: white;
      padding: 48px 24px 36px;
    }

    header .inner,
    main {
      width: min(1120px, calc(100% - 32px));
      margin: 0 auto;
    }

    h1, h2, h3 {
      line-height: 1.2;
    }

    h1 {
      margin: 0 0 12px;
      font-size: 42px;
    }

    h2 {
      margin-top: 44px;
      padding-top: 12px;
      border-top: 1px solid var(--line);
      font-size: 28px;
    }

    h3 {
      margin-top: 28px;
      font-size: 21px;
    }

    p {
      max-width: 880px;
    }

    a {
      color: var(--accent-dark);
    }

    main {
      padding: 28px 0 60px;
    }

    .subtitle {
      color: #d5dbea;
      max-width: 820px;
      font-size: 18px;
    }

    .panel {
      background: var(--panel);
      border: 1px solid var(--line);
      border-radius: 8px;
      padding: 20px;
      margin: 18px 0;
    }

    .grid {
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(220px, 1fr));
      gap: 14px;
    }

    .callout {
      border-left: 4px solid var(--accent);
      background: var(--soft-blue);
      padding: 14px 16px;
      border-radius: 6px;
      margin: 16px 0;
    }

    .warn {
      border-left-color: var(--warn);
      background: var(--soft-amber);
    }

    .good {
      border-left-color: var(--good);
      background: var(--soft-green);
    }

    code {
      background: #eef2f7;
      padding: 2px 5px;
      border-radius: 4px;
      font-size: 0.95em;
    }

    pre {
      background: var(--code-bg);
      color: var(--code-ink);
      padding: 16px;
      border-radius: 8px;
      overflow-x: auto;
      line-height: 1.45;
    }

    pre code {
      background: transparent;
      color: inherit;
      padding: 0;
    }

    .flow {
      display: flex;
      flex-wrap: wrap;
      align-items: center;
      gap: 10px;
      margin: 18px 0;
    }

    .node {
      border: 1px solid var(--line);
      background: white;
      border-radius: 8px;
      padding: 12px 14px;
      min-width: 135px;
      text-align: center;
      font-weight: 700;
    }

    .arrow {
      color: var(--muted);
      font-weight: 700;
    }

    .diagram {
      border: 1px solid var(--line);
      background: white;
      border-radius: 8px;
      padding: 18px;
      margin: 18px 0;
    }

    .tree {
      font-family: Consolas, Monaco, monospace;
      white-space: pre;
      overflow-x: auto;
      background: #f2f5fa;
      padding: 14px;
      border-radius: 8px;
    }

    .milestone {
      border-left: 5px solid var(--accent);
    }

    .tag {
      display: inline-block;
      border: 1px solid var(--line);
      border-radius: 999px;
      padding: 2px 9px;
      margin: 3px;
      color: var(--muted);
      background: white;
      font-size: 13px;
    }

    table {
      width: 100%;
      border-collapse: collapse;
      margin: 16px 0;
      background: white;
    }

    th, td {
      border: 1px solid var(--line);
      padding: 10px;
      text-align: left;
      vertical-align: top;
    }

    th {
      background: #eef2f7;
    }

    @media (max-width: 720px) {
      h1 {
        font-size: 32px;
      }

      .arrow {
        display: none;
      }

      .node {
        flex: 1 1 100%;
      }
    }
  </style>
</head>
<body>
  <header>
    <div class="inner">
      <h1>CLIT: Build Git in C</h1>
      <p class="subtitle">A one-day, systems-focused roadmap for implementing the core of Git: objects, index, trees, commits, refs, log, and checkout.</p>
    </div>
  </header>
  <main>
    <!-- Tutorial sections are added in later tasks. -->
  </main>
</body>
</html>
```

- [ ] **Step 2: Open the file in a browser**

Run:

```powershell
Start-Process "D:\ValueProjects\CLIT\CLIT\docs\tutorial.html"
```

Expected: A page opens with a dark header and empty body.

---

### Task 2: Add Learning Roadmap and Mental Model

**Files:**
- Modify: `docs/tutorial.html`

- [ ] **Step 1: Add the first sections inside `<main>`**

Replace the scaffold comment in `<main>` with:

```html
    <section class="panel">
      <h2>What You Are Building Today</h2>
      <p>You are building a small Git-like version control system in C. The goal is not to match every Git command. The goal is to understand and implement the core model that makes Git powerful.</p>
      <div class="grid">
        <div><strong>Repository setup</strong><br><span class="tag">init</span></div>
        <div><strong>Object database</strong><br><span class="tag">hash-object</span><span class="tag">cat-file</span></div>
        <div><strong>Staging area</strong><br><span class="tag">add</span><span class="tag">status</span></div>
        <div><strong>Snapshots</strong><br><span class="tag">write-tree</span><span class="tag">commit</span></div>
        <div><strong>History</strong><br><span class="tag">log</span></div>
        <div><strong>Restore</strong><br><span class="tag">checkout</span></div>
      </div>
    </section>

    <section>
      <h2>The Core Git Mental Model</h2>
      <p>Git is mostly a content-addressed database. Content goes in, a hash comes out, and the hash becomes the object's name. Bigger objects point to smaller objects.</p>
      <div class="diagram">
        <div class="flow">
          <div class="node">file bytes</div>
          <div class="arrow">-&gt;</div>
          <div class="node">blob</div>
          <div class="arrow">-&gt;</div>
          <div class="node">tree</div>
          <div class="arrow">-&gt;</div>
          <div class="node">commit</div>
          <div class="arrow">-&gt;</div>
          <div class="node">branch ref</div>
          <div class="arrow">-&gt;</div>
          <div class="node">HEAD</div>
        </div>
      </div>
      <div class="callout">
        <strong>Interview sentence:</strong> I implemented a content-addressed object store in C where file contents become compressed blob objects, directories become tree objects, commits point to trees and parents, and refs name the latest commit on a branch.
      </div>
    </section>
```

- [ ] **Step 2: Verify layout**

Run:

```powershell
Start-Process "D:\ValueProjects\CLIT\CLIT\docs\tutorial.html"
```

Expected: The page shows six roadmap cells and a left-to-right Git object flow.

---

### Task 3: Add C Concepts Section

**Files:**
- Modify: `docs/tutorial.html`

- [ ] **Step 1: Add the concepts section after the mental model section**

Add:

```html
    <section>
      <h2>C Concepts You Will Use</h2>
      <table>
        <thead>
          <tr>
            <th>Concept</th>
            <th>Why CLIT needs it</th>
            <th>Where it appears</th>
          </tr>
        </thead>
        <tbody>
          <tr><td>Command-line arguments</td><td>Dispatch commands like <code>init</code>, <code>add</code>, and <code>commit</code>.</td><td><code>src/main.c</code></td></tr>
          <tr><td>File I/O</td><td>Read working files and write repository metadata.</td><td><code>src/repo.c</code>, <code>src/object.c</code></td></tr>
          <tr><td>Binary buffers</td><td>Git objects can contain any bytes, not only text.</td><td><code>include/utils.h</code>, <code>src/object.c</code></td></tr>
          <tr><td>Structs</td><td>Represent index entries, object metadata, and parsed commits.</td><td><code>include/clit.h</code></td></tr>
          <tr><td>Dynamic memory</td><td>File sizes are not known at compile time.</td><td>object loading and decompression</td></tr>
          <tr><td>Sorting</td><td>Tree entries must have stable ordering.</td><td><code>src/tree.c</code></td></tr>
          <tr><td>Hashing</td><td>The object ID is SHA-1 over the object header plus content.</td><td><code>src/sha1.c</code></td></tr>
          <tr><td>Compression</td><td>Objects are stored compressed under <code>.clit/objects</code>.</td><td>zlib in <code>src/object.c</code></td></tr>
        </tbody>
      </table>
      <div class="warn callout">
        <strong>Important simplification:</strong> CLIT can use a learning-friendly index format first. Full Git index compatibility is future work, not required today.
      </div>
    </section>
```

- [ ] **Step 2: Verify table readability**

Run:

```powershell
Start-Process "D:\ValueProjects\CLIT\CLIT\docs\tutorial.html"
```

Expected: The table is readable on desktop width and horizontally stable.

---

### Task 4: Add Milestone Chapters

**Files:**
- Modify: `docs/tutorial.html`

- [ ] **Step 1: Add the milestone section after the C concepts section**

Add:

```html
    <section>
      <h2>Milestone Chapters</h2>

      <article class="panel milestone">
        <h3>1. Project Skeleton and <code>init</code></h3>
        <p>Start by making the program dispatch commands and create the repository layout. Your current <code>cmd_init</code> already tries this, but it creates <code>.clit</code> twice. The lesson is to make each filesystem operation intentional and check errors clearly.</p>
        <div class="tree">.clit/
  HEAD
  objects/
  refs/
    heads/</div>
        <pre><code>bin/clit init
type .clit\HEAD</code></pre>
        <p><strong>Exercise:</strong> Write a helper like <code>ensure_dir(".clit/objects")</code> so <code>cmd_init</code> reads like a list of repository requirements.</p>
      </article>

      <article class="panel milestone">
        <h3>2. Blob Objects with <code>hash-object</code></h3>
        <p>A blob is file content stored as an object. The hash is computed over a header plus the original bytes: <code>blob &lt;size&gt;\0&lt;content&gt;</code>.</p>
        <div class="diagram">
          <div class="flow">
            <div class="node">README.md bytes</div>
            <div class="arrow">-&gt;</div>
            <div class="node">blob header</div>
            <div class="arrow">+</div>
            <div class="node">SHA-1</div>
            <div class="arrow">-&gt;</div>
            <div class="node">.clit/objects/ab/cdef...</div>
          </div>
        </div>
        <pre><code>bin/clit hash-object README.md
bin/clit hash-object -w README.md</code></pre>
        <p><strong>Exercise:</strong> Build a binary-safe buffer struct with <code>unsigned char *data</code> and <code>size_t len</code>.</p>
      </article>

      <article class="panel milestone">
        <h3>3. Object Inspection with <code>cat-file</code></h3>
        <p>Once objects exist, you need to prove you can read them back. <code>cat-file -t</code> prints the object type. <code>cat-file -p</code> prints the payload in a human-friendly way.</p>
        <pre><code>bin/clit cat-file -t &lt;hash&gt;
bin/clit cat-file -p &lt;hash&gt;</code></pre>
        <p><strong>Exercise:</strong> Parse bytes until the first space for the type, then until the NUL byte for the size.</p>
      </article>

      <article class="panel milestone">
        <h3>4. Staging with <code>add</code> and <code>status</code></h3>
        <p>The index is the staging area. It records which blob hash should appear at which path in the next snapshot.</p>
        <pre><code>path=README.md
mode=100644
hash=&lt;blob-hash&gt;</code></pre>
        <p><strong>Exercise:</strong> Use a simple text index first: one line per staged file. You can replace it with a binary format after the core works.</p>
      </article>

      <article class="panel milestone">
        <h3>5. Trees with <code>write-tree</code></h3>
        <p>A tree is a directory snapshot. It maps names to blob hashes or nested tree hashes. Sorting entries makes the snapshot deterministic.</p>
        <pre><code>100644 README.md &lt;blob-hash&gt;
100644 src/main.c &lt;blob-hash&gt;</code></pre>
        <p><strong>Exercise:</strong> Start with a flat tree for files in the repository root, then add recursive directories.</p>
      </article>

      <article class="panel milestone">
        <h3>6. Commits with <code>commit</code></h3>
        <p>A commit points to one tree and optionally one parent commit. Branches are just files that store the newest commit hash.</p>
        <pre><code>tree &lt;tree-hash&gt;
parent &lt;parent-hash&gt;
author Your Name &lt;you@example.com&gt; &lt;timestamp&gt;

first commit</code></pre>
        <p><strong>Exercise:</strong> Read <code>.clit/HEAD</code>, resolve it to <code>.clit/refs/heads/main</code>, then update that file after writing the commit object.</p>
      </article>

      <article class="panel milestone">
        <h3>7. History with <code>log</code></h3>
        <p><code>log</code> starts from the current branch commit, prints it, follows its parent, and repeats until there is no parent.</p>
        <pre><code>bin/clit log</code></pre>
        <p><strong>Exercise:</strong> Write a loop that keeps a current commit hash buffer and replaces it with the parsed parent hash each iteration.</p>
      </article>

      <article class="panel milestone">
        <h3>8. Restore with Basic <code>checkout</code></h3>
        <p>Checkout reads a commit, reads its tree, then writes the referenced blobs back to the working directory. A learning version can refuse to overwrite existing modified files.</p>
        <pre><code>bin/clit checkout &lt;commit&gt;</code></pre>
        <p><strong>Exercise:</strong> Make checkout conservative: if a target file exists and differs, print an error before writing anything.</p>
      </article>
    </section>
```

- [ ] **Step 2: Verify milestone flow**

Run:

```powershell
Start-Process "D:\ValueProjects\CLIT\CLIT\docs\tutorial.html"
```

Expected: Eight milestone cards appear in order, each with a concept, commands, and exercise.

---

### Task 5: Add Verification, Debugging, Resources, and Resume Sections

**Files:**
- Modify: `docs/tutorial.html`

- [ ] **Step 1: Add final tutorial sections after the milestone section**

Add:

```html
    <section>
      <h2>Manual Verification Path</h2>
      <p>Use this sequence whenever a new milestone lands. Do not trust the code until the command proves the stored data can be read back.</p>
      <pre><code>make
bin/clit init
bin/clit hash-object -w README.md
bin/clit cat-file -p &lt;hash-from-previous-step&gt;
bin/clit add README.md
bin/clit status
bin/clit write-tree
bin/clit commit -m "first commit"
bin/clit log</code></pre>
    </section>

    <section>
      <h2>Debugging Notes</h2>
      <div class="grid">
        <div class="callout"><strong>If hashes differ:</strong> Check the exact object header: <code>blob &lt;size&gt;\0</code>. One extra newline changes the hash.</div>
        <div class="callout"><strong>If decompression fails:</strong> Confirm you wrote compressed bytes, not the hex hash string or uncompressed object.</div>
        <div class="callout"><strong>If status is confusing:</strong> Print the index contents directly. A boring debug print often beats guessing.</div>
        <div class="callout"><strong>If checkout feels dangerous:</strong> Refuse to overwrite files first. Safety is a feature, not a delay.</div>
      </div>
    </section>

    <section>
      <h2>What To Say On Your Resume</h2>
      <div class="good callout">
        Implemented a mini Git-compatible version control system in C, including content-addressed object storage, compressed blob/tree/commit objects, a staging index, commit history traversal, and basic checkout.
      </div>
      <p>In interviews, explain what you simplified too: no remotes, no merge conflict engine, no packfiles, and a learning-friendly index format in the first version.</p>
    </section>

    <section>
      <h2>Extra Resources</h2>
      <ul>
        <li><a href="https://git-scm.com/book/en/v2/Git-Internals-Plumbing-and-Porcelain">Pro Git: Git Internals - Plumbing and Porcelain</a></li>
        <li><a href="https://git-scm.com/book/en/v2/Git-Internals-Git-Objects">Pro Git: Git Objects</a></li>
        <li><a href="https://git-scm.com/docs/git-hash-object">git-hash-object documentation</a></li>
        <li><a href="https://git-scm.com/docs/git-cat-file">git-cat-file documentation</a></li>
        <li><a href="https://zlib.net/manual.html">zlib manual</a></li>
        <li><a href="https://docs.openssl.org/">OpenSSL documentation</a></li>
      </ul>
    </section>
```

- [ ] **Step 2: Verify all links and sections render**

Run:

```powershell
Start-Process "D:\ValueProjects\CLIT\CLIT\docs\tutorial.html"
```

Expected: The tutorial ends with verification commands, debugging notes, resume phrasing, and resource links.

---

### Task 6: Create Markdown Tracker

**Files:**
- Create: `docs/clit-tracker.md`

- [ ] **Step 1: Add tracker content**

Create `docs/clit-tracker.md` with:

```markdown
# CLIT Implementation Tracker

Use this tracker while building the C implementation. Keep each milestone small: understand the concept, change the listed files, run the check, then mark it done.

## Current Baseline

- [ ] Confirm `src/main.c` dispatches commands.
- [ ] Fix `cmd_init` so it does not create `.clit` twice.
- [ ] Keep `.clit/HEAD` pointing to `ref: refs/heads/main`.
- [ ] Create `.clit/refs/heads/` during init.

## Milestone 1: `init`

**Concepts:** command dispatch, directories, metadata files, return codes.

**Expected files:** `src/main.c`, `src/repo.c`, `include/clit.h`.

**Checks:**

```powershell
make
bin\clit init
Get-ChildItem -Recurse .clit
Get-Content .clit\HEAD
```

- [ ] `bin/clit init` creates `.clit`.
- [ ] `.clit/objects` exists.
- [ ] `.clit/refs/heads` exists.
- [ ] `.clit/HEAD` contains `ref: refs/heads/main`.

## Milestone 2: `hash-object`

**Concepts:** binary file reads, object headers, SHA-1, zlib, object paths.

**Expected files:** `src/object.c`, `src/sha1.c`, `include/clit.h`, `include/utils.h`.

**Checks:**

```powershell
make
bin\clit hash-object README.md
bin\clit hash-object -w README.md
Get-ChildItem .clit\objects
```

- [ ] Prints a 40-character hash.
- [ ] `-w` stores the object under `.clit/objects/xx/yyyy...`.
- [ ] Re-running on unchanged content prints the same hash.

## Milestone 3: `cat-file`

**Concepts:** object lookup, decompression, object header parsing.

**Expected files:** `src/object.c`, `include/clit.h`.

**Checks:**

```powershell
bin\clit cat-file -t <hash>
bin\clit cat-file -p <hash>
```

- [ ] `-t` prints `blob`.
- [ ] `-p` prints the original file content.
- [ ] Invalid hashes produce a clear error.

## Milestone 4: `add` and `status`

**Concepts:** staging, index entries, path storage, modes.

**Expected files:** `src/index.c`, `src/object.c`, `include/clit.h`.

**Checks:**

```powershell
bin\clit add README.md
bin\clit status
Get-Content .clit\index
```

- [ ] `add` writes a blob if needed.
- [ ] `.clit/index` records path, mode, and hash.
- [ ] `status` shows staged files.

## Milestone 5: `write-tree`

**Concepts:** deterministic snapshots, sorted entries, tree objects.

**Expected files:** `src/tree.c`, `src/index.c`, `src/object.c`.

**Checks:**

```powershell
bin\clit write-tree
bin\clit cat-file -p <tree-hash>
```

- [ ] Prints a tree hash.
- [ ] Tree payload lists staged files.
- [ ] Same index produces the same tree hash.

## Milestone 6: `commit`

**Concepts:** commit object format, parent links, refs, HEAD.

**Expected files:** `src/commit.c`, `src/tree.c`, `src/repo.c`, `include/clit.h`.

**Checks:**

```powershell
bin\clit commit -m "first commit"
Get-Content .clit\refs\heads\main
bin\clit cat-file -p <commit-hash>
```

- [ ] Commit stores a tree hash.
- [ ] First commit has no parent.
- [ ] Later commits include a parent.
- [ ] Branch ref updates to the new commit.

## Milestone 7: `log`

**Concepts:** parent traversal, ref resolution, readable formatting.

**Expected files:** `src/commit.c`, `src/repo.c`.

**Checks:**

```powershell
bin\clit log
```

- [ ] Prints latest commit first.
- [ ] Follows parent hashes.
- [ ] Stops cleanly at the first commit.

## Milestone 8: basic `checkout`

**Concepts:** resolving commits, reading trees, restoring blobs, safe overwrite rules.

**Expected files:** `src/checkout.c`, `src/tree.c`, `src/object.c`.

**Checks:**

```powershell
bin\clit checkout <commit-hash>
```

- [ ] Reads the commit's tree.
- [ ] Restores tracked files from blobs.
- [ ] Refuses to overwrite changed files in the first version.

## Stretch Work After Today

- [ ] Branch creation and switching.
- [ ] Recursive tree support if the first tree implementation is flat.
- [ ] Ignore rules.
- [ ] Integration test script.
- [ ] Merge base detection.
- [ ] Three-way merge prototype.
- [ ] Packfile reading.
```

- [ ] **Step 2: Preview tracker**

Run:

```powershell
Get-Content docs\clit-tracker.md
```

Expected: The tracker shows all eight milestones with checkboxes and commands.

---

### Task 7: Final Verification and Review

**Files:**
- Verify: `docs/tutorial.html`
- Verify: `docs/clit-tracker.md`

- [ ] **Step 1: Check working tree scope**

Run:

```powershell
git status --short
```

Expected: Only documentation changes from this plan plus any pre-existing user changes appear.

- [ ] **Step 2: Search for unfinished markers**

Run:

```powershell
rg -n "TB[D]|TO[D]O|lorem|fix later" docs\tutorial.html docs\clit-tracker.md
```

Expected: No matches.

- [ ] **Step 3: Check tutorial file exists and is non-empty**

Run:

```powershell
Get-Item docs\tutorial.html
```

Expected: File exists with nonzero length.

- [ ] **Step 4: Check tracker file exists and is non-empty**

Run:

```powershell
Get-Item docs\clit-tracker.md
```

Expected: File exists with nonzero length.

- [ ] **Step 5: Open tutorial**

Run:

```powershell
Start-Process "D:\ValueProjects\CLIT\CLIT\docs\tutorial.html"
```

Expected: Tutorial opens locally in the default browser.

- [ ] **Step 6: Commit documentation artifacts only after user approval**

If the user asks to commit, run:

```powershell
git add docs\tutorial.html docs\clit-tracker.md docs\superpowers\plans\2026-06-19-clit-git-in-c-tutorial.md
git commit -m "Add CLIT tutorial and tracker"
```

Expected: A new commit containing only the tutorial, tracker, and plan.
