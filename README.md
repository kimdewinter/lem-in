# Lem-In
### An early school project which served as an introduction to flow networks.

>Imagine a flow network with a Source node, a Target node, and a web of intermediate nodes.<br/>
>Now you have a number of agents ("ants" they were called in the assignment, as if the network is an ant hill).<br/>
>The agents start at Source and want to traverse to Target.<br/>
>An agent can only move 1 step per 'turn'.<br/>
>Each intermediate nodes can only contain 1 agent.<br/>
>Objective is to get all agents from Source to Target in as few turns as possible

We ended up using Yefim Dinic's algorithm.<br/>
Also implemented pruning for dead-end branches and unnecessary side-branches to increase efficiency.

For more information you can read through the assignment PDF, included in the root of the repository.<br/>
Written in C, tested and compatible with macOS 10.14.6 and Ubuntu 21.04
