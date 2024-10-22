#ifndef CART_HPP
#define CART_HPP

#include <iostream>
#include <string>
#include "Product.hpp"
//This class keeps account of all the products.
class Cart {

public:

    Cart(NameType theOwner) : owner(theOwner), itemNum(0) {}

    bool addItem(Product* theProduct);
    /*Returns true if the specified item is successfully added, otherwise false (when the cart is full)*/
    bool removeItem(prod_id_t theProductID);
    /*Returns true if the specified item is successfully searched and  removed, otherwise false (when the item is not found or the cart is empty)*/
    void displayCart();
    /*Traverse the items in the cart one by one and display the contents of each item followed by displaying the cart summary information. */

private:
  
    bool isCartFull();
    int itemNum;
    static const int MAX_ITEMS = 7; //maximum number of items cannot be changed and must be updated, hence it is static const
    NameType owner;
    Product * purchasedItems[MAX_ITEMS];

};

#endif
