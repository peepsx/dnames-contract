#include <arisen/arisen.hpp>
#include "abcounter.cpp"

using namespace arisen;

class [[arisen::contract("dnames")]] dnames : public arisen::contract {

public:
    dnames (name receiver, name code, datastream<const char*> ds): contract(receiver);

    [[arisen::action]]
    void add(name domain, std::string record_name, std::string dweb_key) {
      require_auth(domain); // require authentication from domain's keys
      dname_index dnames(get_first_receiver(), get_first_receiver.value); //get dnames db index
      auto iterator = dnames.find(domain.value, record_name.value); //find the given domain and record name in db
      if( iterator == dnames.end() ) // if iterator is not found with above find function, add domain record
      {
       dnames.emplace(domain, record_name, [&]( auto& row ) { // add domain record
          row.key = domain;
          row.record_name = record_name;
          row.dweb_key = dweb_key;
       }); // end dnames.emplace
       send_summary(domain, " successfully added new dDNS record");
       increment_counter(domain, "emplace");
      }    
     else { // if iterator is found modify iterator dDNS record
        dnames.modify(iterator, domain, [&]( auto& row ) {
           row.key = domain;
           row.record_name = record_name;
           row.dweb_key = dweb_key;
       }); // end dnames.modify
       send_summary(domain, " successfully modified dDNS record");
       increment_counter(domain, "modify");
     } // end if/else
    } // end add action

// blank

    [[arisen::action]]
    void erase(name domain, std::string record_name) {
      require_auth(domain); // require authentication for domain's keys
      dname_index dnames(get_self(), get_first_receiver().value);
      auto iterator = dnames.find(domain.value, record_name.value);
      check(iterator != dnames.end(), "dDNS record does not exist");
      dnames.erase(iterator); // if iterator exists, erase record    
    }  // end erase action

// blank

    void increment_counter(name domain, std::string type) {
          abcounter::count_action count("abcounter"_n, (get_self(), "active"_n));
          count.send(domain, type);
    } // end increment_counter function

// blank

// end public data members

private:
    void send_summary(name domain, std::string message) {
       action(
          permission_level(get_self(), "active"_n),
          get_self(),
          "notify"_n,
          std::make_tuple(domain, name{domain}.to_string() + message)
       ).send();
    } // end send_summary function

} // end dnames contract