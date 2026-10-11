*This project has been created as part of the 42 curriculum by amabbadi.*

# ft_irc

## Description

This project is a C++98 IRC server. It accepts TCP clients, authenticates them with a password, handles registration, channels, private messages, channel operators, topics, invitations, kicks, and channel modes.

## Instructions

Build the server from the project root:

```sh
make
```

Run it with a port and password:

```sh
./ircserv 6667 password
```

Connect with an IRC client or netcat on `127.0.0.1:6667`, then register with `PASS`, `NICK`, and `USER`.

## Tests

Build the server, then run the integration suite:

```sh
python3 test_ircserv.py
```

The suite starts a server with the password `password`, tests registration, CAP, messaging, channels, WHO, topics, invitations, kicks, modes, partial input, operator failover, and orderly cleanup. It prints every PASS/FAIL result, every command sent by each client, and the captured server log.

## Resources

- RFC 2812: Internet Relay Chat: Client Protocol
- RFC 1459: Internet Relay Chat Protocol
- The 42 ft_irc subject and evaluation guide

AI was used to help inspect protocol behavior, identify edge cases, review resource cleanup, and validate implementation details. All changes were reviewed and tested in the project workspace.

## Technical Notes

The server uses C++98, nonblocking IPv4 sockets, one `poll()` loop, and queued client output. Server-to-server communication, file transfer, and bots are not implemented.
