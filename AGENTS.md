# Agent Instructions — Unreal Meta XR Audio SDK Sample

Unreal reference app that showcases the Meta XR Audio (Presence Platform Audio) plug-in. A hub level launches per-feature sub-levels demonstrating HRTF, reverb, and spatialization wired into Unreal's audio engine.

## Source-of-truth files (read these first, do not duplicate their contents in this file)

For setup, build steps, SDK versions, and project layout, read:

- `README.md` — official setup, plug-in download/install instructions, and build/run flow
- `MetaXRAudioSample.uproject` — Unreal engine association, enabled/disabled plugins
- `Config/` — Unreal `.ini` settings (DefaultEngine, DefaultGame, etc.)
- `Source/MetaXRAudioSample/` — C++ module sources and `.Build.cs` files
- `LICENSE` and `THIRD_PARTY_NOTICES.txt` — license terms (helicopter audio under CC-BY 4.0 in `Third-party/`)

## Quest / Horizon-specific notes

- **Windows-only**: the Meta XR Audio plug-in currently only supports Windows development. Do not suggest macOS or Linux as a host.
- Git LFS is required; run `git lfs install` before cloning.
- The Meta XR Audio plug-in must be dropped into the **engine's** `Engine/Plugins/Marketplace/MetaXRAudio` directory, **not** the project's `Plugins/` folder.
- The project deliberately disables Unreal's built-in `ResonanceAudio` and `Metasound` plug-ins because they collide with Meta XR Audio. Do not silently re-enable them.
- If the Unreal engine version is bumped, verify a matching Meta XR plug-in build exists for that engine version before updating `EngineAssociation` in `MetaXRAudioSample.uproject`.

# Meta Quest tooling

This is a Meta Quest / Horizon OS sample. The bespoke intro above is the source of truth for what this project is and how it's built — use it (and the files it points at) instead of restating facts from memory.

When the user asks anything about Quest device behavior, build / deploy / debug / capture flows, on-device performance, or Horizon OS APIs, reach for these tools instead of generic Unreal answers:

- **`hzdb`** — Quest-aware ADB wrapper (device list, install / launch / stop, logs, screenshots, Perfetto traces, on-device docs search). Already wired up as an MCP server via `.mcp.json`, `.vscode/mcp.json`, and `.cursor/mcp.json`. Also runnable directly: `npx -y @meta-quest/hzdb <subcommand>`.
- **Meta Quest Agentic Tools** — the full skill set, including Unreal-specific skills: <https://github.com/meta-quest/agentic-tools>. Install per your client (Claude Code: `/plugin install meta-vr@meta-quest`; Gemini CLI: `gemini extensions install https://github.com/meta-quest/agentic-tools`; Cursor / VS Code: install the **Meta Horizon** extension from the Marketplace).

A few behavior expectations:

- **Read this repo's files first.** Before answering anything project-specific, read `README.md` and whichever source-of-truth files the intro above points at. Don't restate their contents in chat — quote or link instead.
- **Use `hzdb` for device-side work.** Anything that touches an attached Quest (install, launch, logs, screenshot, capture, manifest inspection) goes through `hzdb`, not raw `adb`.
- **Check live Horizon OS docs before answering API questions.** `hzdb docs search "..."` queries the live docs; training data on Horizon OS APIs goes stale fast.
- **Don't fabricate SDK / engine versions.** If a version isn't visible in this repo's files, say so rather than guessing.
