# Distributed Calculator System using QNX Neutrino RTOS

**by**: Min Khant Soe Oke, Kaung Sithu

## Overview

This project implements a distributed calculator system using the client-server architecture in QNX Neutrino RTOS. The server coordinates and distributes computational tasks to multiple client processes, each performing a specific arithmetic operation (addition, subtraction, multiplication, or division). The goal is to explore interprocess communication (IPC) in a real-time operating system and demonstrate the efficient use of client-server models in real-time and distributed systems.

## Dependencies

**To run this project, you need to have the following dependencies installed:**

* QNX Neutrino RTOS
* Basic knowledge of C programming
* Familiarity with interprocess communication concepts
* Understanding of basic client-server architecture principles

## Features

**Client-Server Architecture**
- Clients request services from a server, which processes the requests and returns the results.

**QNX Neutrino IPC**
- Utilizes message passing for communication between clients and the server.

**Reply-Driven Scheme**
- The server remains responsive to client requests, processes them, and sends back the responses efficiently.

## How to Use

1. **Start the Server**:
   - Open a terminal and run `./server`.

2. **Start the Clients**:
   - Open another terminal and run `./add_client`.
   - Repeat for other clients (e.g., subtraction, multiplication, division) if implemented.

3. **Run the Main Client**:
   - Open a terminal and run `./client`.
   - Follow the prompt to enter calculation requests.

4. **Client-Server Interaction**:
   - The client will send calculation requests to the server.
   - The server will delegate the tasks to appropriate clients based on the operation.
   - The main client will display the received results.

## Authors

- Min Khant Soe Oke
- Kaung Sithu
