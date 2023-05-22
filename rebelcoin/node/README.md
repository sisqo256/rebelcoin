# rebelcoin/node/

The [`rebelcoin/node/`](./) directory contains code that needs to access node state
(state in `CChain`, `CBlockIndex`, `CCoinsView`, `CTxMemPool`, and similar
classes).

Code in [`rebelcoin/node/`](./) is meant to be segregated from code in
[`rebelcoin/wallet/`](../wallet/) and [`rebelcoin/qt/`](../qt/), to ensure wallet and GUI
code changes don't interfere with node operation, to allow wallet and GUI code
to run in separate processes, and to perhaps eventually allow wallet and GUI
code to be maintained in separate source repositories.

As a rule of thumb, code in one of the [`rebelcoin/node/`](./),
[`rebelcoin/wallet/`](../wallet/), or [`rebelcoin/qt/`](../qt/) directories should avoid
calling code in the other directories directly, and only invoke it indirectly
through the more limited [`rebelcoin/interfaces/`](../interfaces/) classes.

The [`rebelcoin/node/`](./) directory is a new directory introduced in
[#14978](https://github.com/bitcoin/bitcoin/pull/14978) and at the moment is
sparsely populated. Eventually more substantial files like
[`rebelcoin/rebelblockchain.cpp`](../rebelblockchain.cpp) and
[`rebelcoin/txmempool.cpp`](../txmempool.cpp) might be moved there.
