#include <eosiolib/eosio.hpp>
#include <eosiolib/multi_index.hpp>
#include <eosiolib/types.hpp>
#include <string>

using namespace eosio;

class Ledger: public contract {
	public:
		Ledger(account_name s) :
				contract(s), ledger(s, s) {

		}
		using contract::contract;

		int64_t getbalanceaccount(std::string account) {
			int amount = 0;
			for (auto& item : ledger) {
				if (account.compare(item.fromAccount) == 0) {
					amount += amount;
				}
				if (account.compare(item.toAccount) == 0) {
					amount += amount;
				}

			}
			return amount;
		}
		uint64_t getbalancekey(std::string key) {
			int amount = 0;
			for (auto& item : ledger) {
				if (key.compare(item.sToKey) == 0) {
					amount += amount;
				}
				if (key.compare(item.fromKey) == 0) {
					amount += amount;
				}

			}
			return amount;
		}
		[[eosio::action]]
		void rcrdtfr(account_name s, std::string fromaccount,
				std::string toaccount, float amount, std::string fromkey,
				std::string tokey, std::string comment, std::string nonce) {

//require_auth(s);

//eosio_assert(amount != 0, "amount needs to be greater than 0");

			bool condition1 = false;
			bool condition2 = false;
			bool condition3 = false;
			bool condition4 = false;
			bool condition5 = false;
			bool condition6 = false;

			//All fields missing - No transaction
			condition1 = !fromaccount.empty() && !toaccount.empty()
					&& !fromkey.empty() && !tokey.empty();
			eosio_assert(!condition1, "all_fields_missing");
			//2 first fields missing - No transaction
			condition2 = fromaccount.empty() || toaccount.empty();
			//eosio_assert(!condition2, "missing toaccount or fromaccount or both");

			//All fields full - Wallet to Wallet
			condition3 = !fromkey.empty() && !tokey.empty();

			//fromkey field missing - Account to Wallet
			condition4 = fromkey.empty() && !tokey.empty();

			//tokey field missing - Wallet to Account
			condition5 = !fromkey.empty() && tokey.empty();

			//tokey fields missing - Account to Account
			condition6 = fromkey.empty() && tokey.empty();

			int64_t negAmount = -1 * amount;
			int64_t posAmount = amount;
			//Wallet to Wallet
			if (condition3) {
				//decrease with fromkey
				print("Wallet to Wallet");
				//check for funds
				//eosio_assert(getbalancekey(fromkey) >= amount,
				//		"insufficient_funds");
				ledger.emplace(get_self(), [&](auto& p)
				{
					p.key = ledger.available_primary_key();
					p.Id = ledger.available_primary_key();
					p.fromAccount = fromaccount;
					p.toAccount = "";
					p.sToKey = "";
					p.fromKey = fromkey;
					p.amount = negAmount;
					p.comment = comment;
					p.nonce = nonce;

				});
				//increase with sToKey
				ledger.emplace(get_self(), [&](auto& p)
				{
					p.key = ledger.available_primary_key();
					p.Id = ledger.available_primary_key();
					p.fromAccount = "";
					p.toAccount = toaccount;
					p.sToKey = tokey;
					p.fromKey = "";
					p.amount = posAmount;
					p.comment = comment;
					p.nonce = nonce;
				});
			}
			//Account to Wallet
			else if (condition4) {
				print("Account to Wallet");

				//check for funds
				//eosio_assert(getbalanceaccount(fromaccount) >= amount,
				//"insufficient_funds");
				//decrease with fromaccount
				ledger.emplace(get_self(), [&](auto& p)
				{
					p.key = ledger.available_primary_key();
					p.Id = ledger.available_primary_key();
					p.fromAccount = fromaccount;
					p.toAccount = "";
					p.sToKey = "";
					p.fromKey = "";
					p.amount = negAmount;
					p.comment = comment;
					p.nonce = nonce;

				});
				//increase with tokey
				ledger.emplace(get_self(), [&](auto& p)
				{
					p.key = ledger.available_primary_key();
					p.Id = ledger.available_primary_key();
					p.fromAccount = "";
					p.toAccount = toaccount;
					p.sToKey = tokey;
					p.fromKey = "";
					p.amount = posAmount;
					p.comment = comment;
					p.nonce = nonce;

				});
			}
			//Wallet to account
			else if (condition5) {
				print("Wallet to account-------------------------------------------");
				//eosio_assert(getbalancekey(fromkey) >= amount, "insufficient_funds");

				//decrease with fromaccount
				ledger.emplace(get_self(), [&](auto& p)
				{
					p.key = ledger.available_primary_key();
					p.Id = ledger.available_primary_key();
					p.fromAccount = fromaccount;
					p.toAccount = "";
					p.sToKey = "";
					p.fromKey = fromkey;
					p.amount = negAmount;
					p.comment = comment;
					p.nonce = nonce;

				});
				//increase with to account
				ledger.emplace(get_self(), [&](auto& p)
				{
					p.key = ledger.available_primary_key();
					p.Id = ledger.available_primary_key();
					p.fromAccount = "";
					p.toAccount = toaccount;
					p.sToKey = "";
					p.fromKey = "";
					p.amount = posAmount;
					p.comment = comment;
					p.nonce = nonce;

				});
			}
			//Account to Account
			else if (condition6) {
				print("Account to Account");
				//eosio_assert(getbalanceaccount(fromaccount) >= amount, "insufficient_funds");

				//decrease from account
				ledger.emplace(get_self(), [&](auto& p)
				{
					p.key = ledger.available_primary_key();
					p.Id = ledger.available_primary_key();
					p.fromAccount = fromaccount;
					p.toAccount = "";
					p.sToKey = "";
					p.fromKey = "";
					p.amount = negAmount;
					p.comment = comment;
					p.nonce = nonce;
				});
				//augment toaccount
				ledger.emplace(get_self(), [&](auto& p)
				{
					p.key = ledger.available_primary_key();
					p.Id = ledger.available_primary_key();
					p.fromAccount = "";
					p.toAccount = toaccount;
					p.sToKey = "";
					p.fromKey = "";
					p.amount = posAmount;
					p.comment = comment;
					p.nonce = nonce;
				});

			}

		}

	private:

		struct [[eosio::table]] entry {
				account_name s;
				uint64_t key = 0;
				uint64_t Id = 0;
				std::string sToKey;
				std::string fromAccount;
				std::string toAccount;
				std::string fromKey;
				int64_t amount;
				std::string comment;
				std::string nonce;
				uint64_t primary_key() const {
					return key;
				}
				uint64_t by_Id() const {
					return Id;
				}

		};
		typedef eosio::multi_index<N(entry), entry,
				indexed_by<N(Id), const_mem_fun<entry, uint64_t, &entry::by_Id>>> ledgertable;

		ledgertable ledger;

};

EOSIO_ABI( Ledger,(rcrdtfr))
