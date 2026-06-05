# Install guide: Nordic MCP in VS Code with GitHub Copilot

This guide walks you through connecting Nordic MCP to Visual Studio Code with GitHub Copilot. Nordic MCP is a hosted HTTP MCP server — you configure VS Code to talk to it and sign in with myNordic. You do not install a local npm package or clone a repo.

## Official References
- [Nordic MCP overview](https://docs.nordicsemi.com/r/bundle/nordic-mcp/page/index.html)
- [Get started with Nordic MCP (user guide)](https://docs.nordicsemi.com/r/bundle/nordic-mcp/page/user_guide.html)
- [VS Code: Add and manage MCP servers](https://code.visualstudio.com/docs/agent-customization/mcp-servers)
- [AI-assisted development at Nordic](https://www.nordicsemi.com/Products/Technologies/AI-assisted-development/Get-started)


## Prerequisites

### 1. Accounts and subscriptions

| Requirements | Notes |
|--------------|-------|
| [myNordic account](https://mynordic.nordicsemi.com/) | __Required__ for Nordic MCP authentication |
| GitHub Copilot subscription                          | Individual, Business, or Enterprise        |  
| GitHub account                                       | Signed in to VS Code                       |

### 2. Software

| Software | Notes |
|----------|-------|
| [Visual Studio Code](https://code.visualstudio.com/download) | Latest stable release recommended |
| [GitHub Copilot Chat](https://marketplace.visualstudio.com/items?itemName=GitHub.copilot-chat) | Chat + Agent support |

> __Version Note:__ Remote HTTP MCP servers with OAuth need a recent VS Code build. Use VS Code 1.99+ at minimum; 1.101+ is recommended for remote MCP + OAuth (same requirement as other hosted MCP servers such as GitHub’s)

### 3. Browser (for OAuth sign-in)

Nordic has tested these browsers with VS Code + Copilot

| OS | Tested browers |
|----|----------------|
| Windows | Chrome, Vivaldi, Firefox, Edge |
| macOS   | Chrome, Vivaldi, Firefox, Edge, Opera, Safari |
| Linux (Ubuntu | Chrome, Vivaldi |

### 4. Network
- Outbound HTTPS to https://aidev.nordicsemi.com
- Corporate proxies/firewalls must allow that endpoint

### 5. Optional (separate from MCP)

[nRF Connect for VS Code](https://marketplace.visualstudio.com/items?itemName=nordic-semiconductor.nrf-connect-extension-pack) helps with builds, flashing, and debugging, but Nordic MCP is not yet tightly integrated with that extension. Copilot and nRF Connect can still share the same workspace files.

-----
## Nordic MCP server details

Use this exact endpoint (including https:// and /mcp): https://aidev.nordicsemi.com/mcp

| Field | Value |
|-------|-------|
| Type  | HTTP MCP server (hosted by Nordic) |
| Authentication | OAuth via myNordic |
| Local install | None |

-----

## Installation (choose one method)

### Method A: _Command Palette (recommended)_
1. Open VS Code.
2. Open the Command Palette: Ctrl+Shift+P (Windows/Linux) or Cmd+Shift+P (macOS).
3. Run MCP: Add Server.
4. Choose HTTP as the transport type.
5. Enter the server URL: https://aidev.nordicsemi.com/mcp
6. Enter a name, for example: nordic-mcp.
7. Choose scope:
- Global (User) — available in all workspaces (good default)
- Workspace — only the current project (stored in .vscode/mcp.json)

VS Code adds the entry to your mcp.json automatically.

### Method B: _Settings UI_
1. Open VS Code Settings (Ctrl+, / Cmd+,).
2. Search for MCP.
3. Open the MCP servers section (wording may vary slightly by VS Code version).
4. Add a new server:
- Name: nordic-mcp
- Type: HTTP
- URL: https://aidev.nordicsemi.com/mcp
5. Save the configuration.

This is equivalent to Method A and edits the same mcp.json file.

### Method C: _Edit mcp.json manually

#### Workspace configuration (share with team)

Create or edit .vscode/mcp.json in your project:

    {
       "servers": {
          "nordic-mcp": {
             "type": "http",
             "url": "https://aidev.nordicsemi.com/mcp"
           }
       }
    }

Commit .vscode/mcp.json if you want the team to use the same MCP setup (each person still authenticates with their own myNordic account).

#### User configuration (all projects)
1. Command Palette → MCP: Open User Configuration
2. Add the same JSON block under "servers".
3. Save the file.

### Method D: _VS Code CLI (code --add-mcp)

From a terminal (with code on your PATH):

__Windows (PowerShell)__ — for HTTP servers, prefer Methods A–C; the CLI is mainly documented for stdio servers. If your VS Code version supports HTTP via CLI, use the guided MCP: Add Server flow instead.

For __stdio__ servers, the pattern is:
    code --add-mcp '{\"name\":\"my-server\",\"command\":\"npx\",\"args\":[\"-y\",\"somemcp-server\"]}'

For __Nordic MCP__, use __Method A or C__ because it is a remote HTTP server with OAuth, not a local command.


## Authenticate with myNordic

After the server is configured:

1. Open Copilot Chat (Ctrl+Alt+I / Cmd+Ctrl+I, or the chat icon).
2. Switch to Agent mode (dropdown near the chat input). MCP tools run in Agent mode.
3. Send a prompt that uses Nordic MCP, for example:
   > Use Nordic MCP and list the documentation sources available through nordicsemi_list_sources.
4. When prompted, sign in with myNordic in the browser.
5. Approve the OAuth authorization.
6. The browser redirects back to VS Code via a local callback URI.

__macOS browser tip__

If the OAuth tab does not open on the first try (especially on Opera/Vivaldi when the browser was not already running):
- Retry the sign-in, or
- Paste the authorization URL into an already-open browser window.

## Verify the installation

1. __List MCP servers__
   > Command Palette → __MCP: List Servers__  
   >
   > You should see nordic-mcp (or the name you chose). Start/restart the server if needed.
2. __Check tools in Copilot Chat__
   > In __Agent__ mode, ask:
   >
   > Use Nordic MCP. What Kconfig options exist for Zephyr zbus?
   >
   > Copilot should call nordicsemi_search_sources and answer from Nordic documentation.
3. __Test a resource__
   > Use Nordic MCP and read the embedded-code-guidance-ncs-zephyr resource.
4. __Optional setup workflow__
   > In a __new chat__ (Nordic recommends separate chats for setup vs. workflow):
   >
   > Use Nordic MCP and explain the full NCS environment setup workflow for Windows.
   >
   > Pause before changing any files on disk.
   >
   > Or use the slash command if your client exposes it: /nordicsemi-setup-ncs

## Configuration Reference

__Minimal VS Code mcp.json__

    {
       "servers": {
          "nordic-mcp": {
             "type": "http",
             "url": "https://aidev.nordicsemi.com/mcp"
          }
       }
    }

__Generic client format (from Nordic docs)__

Some non-VS Code clients use this shape (VS Code uses "servers" as the top-level key):

    {
       "nordic-mcp": {
          "type": "http",
          "url": "https://aidev.nordicsemi.com/mcp"
       }
    }

## Troubleshooting

| Symptom | Likely cause | Fix |
|---------|--------------|-----|
| No MCP tools appear | Not in Agent mode | Switch Copilot Chat to Agent | 
| Sign-in never starts | Server not started | MCP: List Servers → start/restart nordicmcp |
| Authorization Failed on 127.0.0.1:... | OAuth callback issue | Retry; ensure URL is https://aidev.nordicsemi.com/mcp (not an old host) |
| Auth fails with old URL | Wrong endpoint | Replace legacy hosts (e.g. nordicsemi.mcp.kapa.ai) with https://aidev.nordicsemi.com/mcp |
| Missing https:// | Malformed URL | URL must be full HTTPS including /mcp  |
| Tools work in Chat but not elsewhere | MCP scope | Check user vs. workspace mcp.json |
| Linux auth issues | Browser support | Use Chrome or Vivaldi (Nordic-tested on Ubuntu) |
| Copilot ignores Nordic docs | Prompt too vague | Say “Use Nordic MCP” and name NCS version, board, and task |

__Re-authenticate__
1. MCP: List Servers
2. Remove or restart the nordic-mcp server
3. Trigger OAuth again from Copilot Chat in Agent mode

__Get logs__
- Command Palette → MCP: List Servers → show output for the server
- Output panel → select GitHub Copilot or MCP related channels (names vary by version)

## Using Nordic MCP after install

Example prompts (from [Nordic’s user guide](https://docs.nordicsemi.com/r/bundle/nordic-mcp/page/user_guide.html)):

__Setup (new chat):__

Use Nordic MCP and install the nRF Connect SDK v3.3.0, prepare a freestanding application for the nRF54L15 DK, and pause to ask me before programming the application to the DK.

__Build/debug (separate chat):__

Use Nordic MCP and build and debug my application for the nrf5340dk/nrf5340/cpuapp build target. If anything is unclear, ask first.

__Documentation lookup:__

Use Nordic MCP and search Nordic sources for how to configure zbus message subscribers in NCS 3.x. Enable explicit tool confirmation in Copilot settings when you want approval before flash, erase, or file changes.

## Quick checklist
- myNordic account created
- VS Code + GitHub Copilot (+ Chat) installed and updated
- MCP server added with URL https://aidev.nordicsemi.com/mcp
- Signed in via myNordic OAuth
- Copilot Chat in Agent mode
- Test prompt returns Nordic documentation via MCP tools

## Related documentation
- Nordic MCP user guide — Configure in your IDE
- VS Code MCP configuration reference
- nRF Connect for VS Code (optional, for build/flash alongside Copilot)
If you want this saved as a file (for example docs/nordic-mcp-vscode-install.md in a project), say where it should live and I can create it there.
