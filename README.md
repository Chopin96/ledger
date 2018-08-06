# ledger
> A recording system for credits and debits on the blockchain

The purpose of the ledger is to record transactions between different accounts before VTX has been
created and distributed. After VTX has been created, the transactions recorded here can be replayed
as actual transfers.

Each of the accounts defined here is an EOS account. Our intial idea is that each transaction is in
a smart contract and consists of a debit and a credit, each stored in its own EOS database.

There are many accounts that are kept track of, but the ones mentioned here are:
- Distribution: Holds the VTX for the crowdsale
- Trust: Records how much VTX each person is owed

Two functions are defined initially:

### `recordTransfer(fromAcct, toAcct, amount, fromKey?, toKey?)`

Specify a transfer from one account to another, and optionally with keys into that account (the keys
being used for the trust account). So for example, if Alice purchased 100 VTX, the call would be:

`recordTransfer(Distribution, Trust, 100, null, Alice)`

Note that the names here are actually symbols representing keys.

Internally some calls like this are written to the database:

```
Distribution : debit  100  // -> Trust[Alice]`
Trust[Alice] : credit 100  // <- Distribution`
```
where `A[k]` means a key `k` in the database of account `A`. 

### `retrieveBalance(acct, key?)`

Return the balance of a given account. For example, if I want to know how much is in Alice's trust
account, I would call:

`retrieveBalance(Trust, Alice)`

recalling again that `Trust` and `Alice` merely are symbols for long keys.

