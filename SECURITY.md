# Security Policy

## Supported Versions

The following table lists which versions of **tgbotxx** currently receive security updates.

| Version | Supported |
|----------|------------|
| Latest (main branch) | ✅ |
| Older releases (< latest) | ❌ |

> **Warning**
>
> Only the most recent stable release (and its corresponding `main` branch) will receive security fixes.
> Please update to the latest version before reporting issues.

---

## Reporting a Vulnerability

If you discover a **security vulnerability** in **tgbotxx**, please **do not** open a public GitHub issue.

Instead, contact the maintainers **privately** at:

- **[LinkedIn](https://www.linkedin.com/in/badereddineouaich/)**

Please include the following information in your report:
- A clear description of the vulnerability.
- Steps to reproduce the issue (if applicable).
- The affected component(s) or file(s).
- Potential impact and possible mitigations (if known).

We will:
1. Acknowledge your report within **48 hours**.
2. Investigate and verify the issue.
3. Work with you (if needed) to resolve it.
4. Release a patch and publicly disclose the vulnerability **only after a fix is available**.

---

## Security Best Practices for Telegram Bot Developers

When using **tgbotxx** in your own applications:

- Keep tgbotxx updated. Pull the latest changes more often.
- Validate all user inputs before processing or sending data to the Telegram Bot API.
- Avoid storing tokens in plain text or committing them to version control.
- Use HTTPS endpoints for any external integrations or webhooks.
- Run bots with minimal privileges e.g., in a sandboxed Docker container or a restricted user account.
- Avoid dynamic code execution (e.g., `system`, `popen`) based on user input.
- Protect Your Bot Token Treat your **Bot Token** like a password (if leaked), anyone can control your bot.
- Never commit your token to GitHub or other version control systems.
- If you suspect your token was leaked, revoke it immediately via [@BotFather](https://t.me/BotFather).
- Avoid Command Injection and Unsafe Operations**  Never use `system()`, `popen()`, or shell commands with untrusted input.
- If you must run system commands, strictly sanitize inputs or use safe alternatives such as `std::filesystem`.
- Avoid deserializing arbitrary JSON from users; validate fields explicitly.
- Do not store private user data unless absolutely required.
- Encrypt sensitive information at rest using CryptoPP, OpenSSL AES, libsodium, or a trusted vault.
- Avoid logging full user messages or tokens in plain text.
- Implement data retention policies and delete unused data periodically.
- Telegram bots can be rate-limited; excessive requests may cause bans. Use throttling or rate limiting for incoming messages.
- Consider caching repetitive responses or static files locally.

---

## Security in Dependencies

`tgbotxx` depends on:
- [**libcpr**](https://github.com/libcpr/cpr) HTTP client library
- [**nlohmann/json**](https://github.com/nlohmann/json) JSON serialization library

Both libraries are **bundled and exposed** by default, so you don't need to install them separately.

---

## Acknowledgments

We thank the open-source community for helping make **tgbotxx** safe and reliable.  
Your reports, reviews, and contributions are greatly appreciated.

---