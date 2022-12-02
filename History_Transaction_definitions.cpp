#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 1
//
Transaction::Transaction( std::string ticker_symbol,  unsigned int day_date, 
        unsigned int month_date,  unsigned year_date, 
        bool buy_sell_trans,  unsigned int number_shares,  
        double trans_amount ) : 
        symbol{ticker_symbol}, day{day_date}, month{month_date},
        year{year_date}, shares{number_shares}, amount{trans_amount},
        acb{}, acb_per_share{}, share_balance{}, cgl{}{
          if (buy_sell_trans) {
            trans_type = "Buy";
          } else {
            trans_type = "Sell";
          }
        
                           
          trans_id = assigned_trans_id;
          ++Transaction::assigned_trans_id;

          acb = 0;
          acb_per_share = 0;
          share_balance = 0;
          cgl = 0;
        
          p_next = nullptr;
        
        }


// Destructor
// TASK 1
//
Transaction::~Transaction() {
  delete p_next;
  p_next = nullptr; 
}


// Overloaded < operator.
// TASK 2
//
bool Transaction::operator<(Transaction const &other) {
  //Behavior for if 
  if(year == other.year && month == other.month && day == other.day) {
    if (trans_id > other.trans_id) {return true;}
    return false;
  } else {
    if (year < other.year) {
      return true;
    } else if (year == other.year) {
      if(month < other.month) {
        return true;
      } else if (month == other.month) {
        if (day < other.day) {
          return true;
        } else {
          return false;
        }
      } else {
        return false;
      }
    } else {
      return false;
    }
  }
}

// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
// TASK 3
//
History::History() {
  p_head = nullptr;
}

// Destructor
// TASK 3
//
History::~History() {
  delete p_head;
  p_head = nullptr;

}


// read_history(...): Read the transaction history from file.
// TASK 4
//
void History::read_history() {
  ece150::open_file();

  while (ece150::next_trans_entry()) {
    std::string ticker_symbol{ece150::get_trans_symbol()};
    
    unsigned int day_date{ece150::get_trans_day()};
    unsigned int month_date{ece150::get_trans_month()};
    unsigned int year_date{ece150::get_trans_year()};

    bool buy_sell_trans{ece150::get_trans_type()};
    
    unsigned int number_shares{ece150::get_trans_shares()};
    double trans_amount{ece150::get_trans_amount()};

    Transaction *new_trans{new Transaction(
      ticker_symbol, 
      day_date, 
      month_date, 
      year_date, 
      buy_sell_trans, 
      number_shares, 
      trans_amount)};

    this->insert(new_trans); 

  }
  
  ece150::close_file();

  return;
}
// insert(...): Insert transaction into linked list.
// TASK 5
//
void History::insert(Transaction *p_new_trans) {
  if (p_head == nullptr) {
    p_head = p_new_trans;
    return;
  }

  Transaction *p_temp = p_head;

  while (p_temp->get_next() != nullptr) {
    p_temp = p_temp->get_next();
  }

  p_temp->set_next(p_new_trans);
   
  return;
}

// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//
void History::sort_by_date() {
  if (this->p_head == nullptr || this->p_head->get_next() == nullptr) {
    return;
  } else {
    Transaction *p_i{this->p_head};
    Transaction *p_j{nullptr};

    while (p_i->get_next() != nullptr) {
      p_j = p_i->get_next();

      while (p_j != nullptr) {
        if (*(p_j) < *(p_i)) {
          // Transaction temp = *(p_i);
          // *(p_i) = *(p_j);
          // *(p_j) = temp;
          std::cout << "Pointer at I: ";
          p_i->print();
        }
        p_j = p_j->get_next();
      }
      std::cout << "LEFT INNER" << std::endl;
      p_i = p_i->get_next();    
    }
  }

  std::cout << "finished sorting" << std::endl;
  return;
}

// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//
void History::update_acb_cgl() {
  return;
}

// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8
double History::compute_cgl(unsigned int year) {
  return 0;
}



// print() Print the transaction history.
//TASK 9
//
void History::print() {
  Transaction *p_temp = p_head;
  
  std::cout << "========== BEGIN TRANSACTION HISTORY ============" << std::endl;
  while (p_temp != nullptr) {
    p_temp->print();
    p_temp = p_temp->get_next();
  }
  std::cout << "========== END TRANSACTION HISTORY ============" << std::endl;

  return;
}


// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }
