# Contributing to Lux

## Branching Strategy

Lux uses **GitHub Flow**: all work happens on short-lived feature branches off `main`.

- Branch naming: `<type>/<short-description>`
  - `feat/null-move-pruning`
  - `fix/tt-collision`
  - `refactor/eval-cleanup`
  - `chore/update-deps`
- `main` is always releasable. Never commit directly to it.

## Commit Style

Use conventional commit prefixes:

| Prefix | When to use |
|--------|-------------|
| `feat:` | New feature or improvement |
| `fix:` | Bug fix |
| `refactor:` | Code change with no behavior change |
| `chore:` | Tooling, CI, versioning, docs |
| `tune:` | Eval or search parameter tuning |

Keep the subject line under 72 characters. No period at the end.

Every commit that changes search behavior must include `Bench: <nodes>` in the message body. Run `make hooks` once after cloning — the `prepare-commit-msg` hook appends it automatically by running `src/executables/Lux[.exe] bench`.

## Pull Request Workflow

1. Branch off `main`, do your work, push the branch.
2. Open a PR against `main`. The PR template will guide you.
3. All CI checks (compile on Linux/macOS/Windows) must pass.
4. Squash merge into `main` to keep history linear.

## Versioning

Lux uses `major.minor` versioning (e.g. `4.3`).

| Change type | Version bump |
|-------------|--------------|
| Architecture overhaul or large ELO jump | **major** |
| New feature, tuning, or incremental improvement | **minor** |

The authoritative version string lives in `src/types.h`:
```cpp
inline constexpr const char* VERSION = "5.0";
```

## Release Process

1. Bump `VERSION` in `src/types.h`.
2. Commit: `chore: bump version to X.Y`
3. Merge to `main` via PR.
4. Push a tag from `main`:
   ```bash
   git tag X.Y
   git push origin X.Y
   ```
5. GitHub Actions builds Linux and Windows binaries automatically and publishes a GitHub Release with them attached.
