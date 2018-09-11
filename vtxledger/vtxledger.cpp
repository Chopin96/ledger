﻿#include <eosiolib/eosio.hpp>
#include <eosiolib/multi_index.hpp>

using namespace eosio;

class Ledger: public contract {
public:
	Ledger(account_name s) :
			contract(s), ledger(s, s) {
	}
	/// @abi action
	void getblnc(std::string account, std::string tokey) {
		uint64_t amount = 0;
		if (account.empty()) {
			for (auto& item : ledger) {
				if (item.sToKey.compare(tokey) == 0) {
					amount += item.amount;
				}
			}
		} else if (tokey.empty()) {
			for (auto& item : ledger) {
				if (item.toAccount.compare(account) == 0) {
					amount += item.amount;
				}
				else if(item.fromAccount.compare(account) == 0){
					amount += item.amount;
				}
			}
		}
		else {
			for (auto& item : ledger) {
				if ((item.sToKey.compare(tokey) == 0 && item.toAccount.compare(account) == 0) ||
					 (item.sToKey.compare(tokey) == 0 && item.fromAccount.compare(account) == 0)) {
					amount += item.amount;
				}
			}
		}
		std::string s;
		s.append("{");
		s.append("'amount'");
		s.append(":");
		s.append(std::to_string(amount));
		s.append(", ");
		s.append("'currency'");
		s.append(":");
		s.append("'VTX'");
		s.append("}");
		print(s.c_str());
	}

	/// @abi action
	void retrvtxns(std::string account, std::string tokey, uint64_t limit) {
		uint64_t lKey = string_to_name(tokey.c_str());
		uint64_t amount = 0;
		int i = 0;

		for (auto& item : ledger) {
			std::string s;
			s.append("{");
			s.append("'fromaccount'");
			s.append(":");
			s.append(item.fromAccount);
			s.append(", ");
			s.append("'toaccount'");
			s.append(":");
			s.append(item.toAccount);
			s.append(", ");
			s.append("'fromkey'");
			s.append(":");
			s.append(item.fromKey);
			s.append(", ");
			s.append("'tokey'");
			s.append(":");
			s.append(item.sToKey);
			s.append(", ");
			s.append("'amount'");
			s.append(":");
			s.append(std::to_string(item.amount));
			s.append(", ");
			s.append("}");
			print(s.c_str());
			i++;
			if (i == limit) {
				break;
			}
		}
	}

	/// @abi action
	void rcrdtfr(account_name s, std::string fromaccount, std::string toaccount, std::string fromkey, std::string tokey, uint64_t amount) {
		if (tokey.empty())
		{
			tokey = "";
		}
		uint64_t lKey = string_to_name(tokey.c_str());
		uint64_t lSecKey = string_to_name(toaccount.c_str());
		//require_auth(s);
		ledger.emplace(get_self(), [&](auto& p)
		{
			p.key = ledger.available_primary_key();
			p.Id = ledger.available_primary_key();
			p.fromAccount = fromaccount;
			p.toAccount = toaccount;
			p.toKey = lKey;
			p.sToKey = tokey;
			p.fromKey = fromkey;
			p.amount = amount;
		});
	}


private:

	/// @abi table
	struct entry {
		account_name s;
		uint64_t key;
		uint64_t Id;
		std::string sToKey;
		std::string fromAccount;
		std::string toAccount;
		uint64_t toKey;
		std::string fromKey;
		uint64_t amount;
		uint64_t primary_key() const {
			return key;
		}
		uint64_t by_Id() const {
			return Id;
		}

	};
	typedef eosio::multi_index<N(entry), entry, indexed_by<N(Id), const_mem_fun<entry, uint64_t, &entry::by_Id>>> ledgertable;

	ledgertable ledger;

};

EOSIO_ABI( Ledger,(getblnc)(rcrdtfr)(retrvtxns))
