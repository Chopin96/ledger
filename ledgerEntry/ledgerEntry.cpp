#include <eosiolib/eosio.hpp>
using namespace eosio;

class LedgerEntry : public eosio::contract {
public:
      using contract::contract;
      LedgerEntry(account_name n):contract(n) , _ledger_entry(){
    	  
      }
      /// @abi action 
      void rcrdtrf( account_name s, std::string fromAccount, std::string toAccount, uint64_t fromKey, uint64_t toKey, uint64_t amount) {
               print( "Hello, ", name{s},' ' , fromAccount, toAccount, fromKey, toKey, amount);
      }
        
  private:

      /// @abi table
	struct ledgerEntry 
	{
	   uint64_t     fromKey; 
	   uint64_t     toKey;
	   std::string  fromAccount; 
	   std::string  toAccount; 
	   uint128_t    amount;
	   uint64_t by_toKey() const {return toKey; }
	   auto primary_key() const { return toKey; }
	   std::string get_from_account() const { return fromAccount; }
	   std::string get_to_account() const { return toAccount; }
	   uint128_t get_amount() const { return amount; }
	  
	   EOSLIB_SERIALIZE( ledgerEntry, ( fromKey )( toKey )( fromAccount )( toAccount ) )
	   
	};
	typedef eosio::multi_index<N(toKey), ledgerEntry, indexed_by<N(toKey), const_mem_fun<ledgerEntry, uint64_t, &ledgerEntry::by_toKey>>> ledger_entry;
	
	ledgerEntry _ledger_entry;
};

EOSIO_ABI( LedgerEntry, (rcrdtrf) )
