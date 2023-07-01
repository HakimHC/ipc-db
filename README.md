## IPC-db: mini redis-like in-memory database

This redis-inspired database uses a client-server type architecture, where the client, using a CLI (command line interface)
makes requests to the server, which processes and handles the request accordingly.

The values are stored in memory, in a key-value manner, like in redis (using a hash-table).

There are 3 basic operations:
* GET [key] (retrieves a value based on a key)
* SET [key] [value] (sets a value, associated with a key)
* DELETE [key] (deletes the key-value pair)

The communication between the client and the server will be done with IPC (inter-process communication), using UNIX sockets.

#### WORK IN PROGRESS
