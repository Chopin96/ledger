#include <eosiolib/eosio.hpp>
#include <vector>
#include<tuple>

using namespace eosio;


class Ledger : public contract {
  public:
      Ledger(account_name s):contract(s), ledger(s, s)
      {}
      /// @abi action
      void getrcrd(std::string tokey)
      {
          uint64_t lKey = string_to_name(tokey.c_str());
          uint64_t amount = 0;
          for(auto& item : ledger)
          {
             if (item.toKey == lKey)
             {
               amount += item.amount;
             }
          }
          print("Amount of VTX: ", amount, "\n");
          print("Volentix Ledger version  0.01");
      };

      /// @abi action
      void rcrdtfr(account_name s, std::string fromaccount, std::string toaccount, std::string fromkey, std::string tokey, uint32_t amount )
      {
          uint64_t lKey = string_to_name(tokey.c_str());
          //require_auth(s);
          print("Add entry ", fromaccount, toaccount, tokey, fromkey, amount);
          ledger.emplace(get_self(), [&](auto& p)
                                      {
                                        p.key = ledger.available_primary_key();
                                        p.Id = ledger.available_primary_key();
                                        p.fromAccount = fromaccount;
                                        p.toAccount = toaccount;
                                        p.toKey = lKey;
                                        p.fromKey = fromkey;
                                        p.amount = amount;
                                       
                                                                   
                                      });
          
         
          
      };
  private:
     
    


      /// @abi table
      struct entry
      {
        uint64_t      key; 
        uint64_t      Id; 
        std::string   fromAccount;
        std::string   toAccount;
        uint64_t   toKey;
        std::string   fromKey;
        uint32_t      amount;
        uint64_t primary_key() const { return key; }
        uint64_t by_Id() const {return Id; }
      };
      typedef eosio::multi_index<N(entry), entry, indexed_by<N(Id), const_mem_fun<entry, uint64_t, &entry::by_Id>>> ledgertable;

     
      ledgertable ledger;

};


EOSIO_ABI( Ledger, (getrcrd)(rcrdtfr))
