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

defined functions:
getblnc(string, string tokey) 
retrvtxns(string account, string tokey, unsigned_int limit)
rcrdtfr(account_name s, string fromaccount, string toaccount, uint amount, string fromkey, string tokey) 

*Fields are of string and uint type only*

### rcrdtfr(account_name s, string fromaccount, string toaccount, uint amount, string fromkey, string tokey) 
*account_name, fromaccount and toaccount are mandatory fields*
Specify a transfer from one account to another, and optionally with keys into that account (the keys
being used for the trust account). So for example, if Alice purchased 100 VTX, the call would be:

`rcrdtfr("vtxdistrib, "vtxtrust", 100, "", "Alice")`

Internally some calls like this are written to the database:

```
Distribution : debit  100  // -> Trust[Alice]
Trust[Alice] : credit 100  // <- Distribution
```
where `A[k]` means a key `k` in the database of account `A`. 

`Alice` merely are symbols for long key.

### getblnc(string account, string tokey) 
*account is mandatory field*

Return the balance of a given account. For example, if I want to know how much is in Alice's trust
account, I would call:

`getblnc("vtxtrust", "Alice")`

`Trust` and `Alice` merely are symbols for long keys.

### `rtrvtxns(string account, string key, uint limit)`
*account is a mandatory fields*

Return the last `limit` transactions executed in the given account. For example, if I want to know
the last 5 transactions in the vtxdistriburion account, I would call:

`rtrvtxns("vtxdistribution", "", 5)`

recalling again that `vtxdistribution` is merely a symbol for long keys.


