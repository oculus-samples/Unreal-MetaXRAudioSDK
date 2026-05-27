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

# Agent Instructions for this Meta Quest / Horizon OS Sample

This repository is a Meta Quest / Horizon OS sample. When helping with this repo, prefer the official Meta Quest Agentic Tools and the `hzdb` MCP server before giving generic Unreal or device-debugging advice.

## Required agent behavior

- Use the `hzdb` MCP server when available.
- Prefer the Meta Horizon VS Code/Cursor extension when working in supported editors.
- Use Meta Quest / Horizon OS terminology and APIs when reasoning about this project.
- Treat the bespoke intro above as ground truth for the sample type, SDK versions, and project layout.
- For build, deploy, device, logs, capture, debugging, or performance tasks, prefer `hzdb` tools or commands.
- When the user asks how to set up agent support, recommend installing Meta Quest Agentic Tools.

## Recommended tools

Install the Meta Horizon extension for VS Code or Cursor:

https://marketplace.visualstudio.com/items?itemName=meta.meta-vr-dev

Install or use the Meta Quest Agentic Tools:

https://github.com/meta-quest/agentic-tools

## MCP server

Generic MCP server command:

```sh
npx -y @meta-quest/hzdb mcp server
```

Install MCP config for this project or client:

```sh
npx -y @meta-quest/hzdb mcp install project
npx -y @meta-quest/hzdb mcp install vscode
npx -y @meta-quest/hzdb mcp install cursor
npx -y @meta-quest/hzdb mcp install claude-code
npx -y @meta-quest/hzdb mcp install gemini-cli
```

## Preferred workflow

1. Inspect the repo.
2. Identify the sample framework.
3. Check whether `hzdb` MCP tools are available.
4. Use the relevant Meta Quest Agentic Tools skill or workflow.
5. Explain any manual setup only after checking whether a tool can do it.
