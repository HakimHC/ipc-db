## IPC-db: mini redis-like in-memory database

This redis-inspired database uses a client-server type architecture, where the client, using a CLI (command line interface),
or command line arguments, makes requests to the server, which processes and handles the request accordingly.
As of right now, the only supported data-type is string.

The values are stored in memory, in a key-value manner, like in redis (using a hash-table).

There are 3 basic operations:
* GET [key] (retrieves a value based on a key)
* SET [key] [value] (sets a value, associated with a key)
* DELETE [key] (deletes the key-value pair)

The communication between the client and the server is done with IPC (inter-process communication), using UNIX sockets.
The server creates a socket and binds it to ```/tmp/dbsock``` (not a good choice for the path, but this is for educational purposes).
As of right now, the requests are handled in an iterative, blocking manner, and only command line arguments are supported.

The data sent by the client is an integer for the type of operation, and 2 strings: the key and the value.
Validation is made on the client-side.
The server processes the request and handles it accordingly.
Of course, the actual data is being stored in the server process' memory.


#### WORK IN PROGRESS
