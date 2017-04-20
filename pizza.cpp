using namespace std;
#include <iostream>
#include <string>
#include <cmath>

int size[4]; 
int crust[4];
int toppings[4][100];
int toppingsAmount[4];
int pizzaOn = 0;

int crustQoH[3];
int toppingsQoH[10];

void setQoH() {
    for(int i = 0; i < 3; i++) {
        crustQoH[i] = 100;
    }
    
    toppingsQoH[0] = 200; // Cheese
    toppingsQoH[9] = 50; // Pineapple
    
    for(int i = 1; i < 9; i++) {
        toppingsQoH[i] = 100;
    }
    
}


//Calculate the total price of an order

double calculate(int orderNumber) {
    double totalPrice = 0.00;
    
    // Size
    switch(size[orderNumber]) {
        case 1: case 2:
            totalPrice += 10.00;
            break;
        case 3: 
            totalPrice += 12.00;
            break;
        case 4: case 5: 
            totalPrice += 14.00;
            break;
        case 6: 
            totalPrice += 16.00; 
            break;
    }
    
    // Crust
    switch(crust[orderNumber]) {
        case 3: 
            totalPrice += 2.00;
            break;
    }
    
    // Toppings
    for(int i = 0; i < toppingsAmount[orderNumber]; i++) {
        switch(toppings[orderNumber][i]) {
            case 3: case 4: case 7: case 10: 
                totalPrice += 1.00;
                break;
        }
    }
    
    return totalPrice;
}

//user input check 
bool parseIn(string in) {
    if(in == "yes" || in == "y" || in == "Y" || in == "Yes" || in == "YES") {
        return true;
    } else {
        return false;
    }
}

//Check to see if it's a premium topping

bool premiumTopping(int topping) {
    switch(topping) {
        case 3: case 4: case 7: case 10:
            return true;
    }
    
    return false;
}

//function for topping option
string parseTopping(int topping) {
    switch(topping) {
        case 1:
            return "Cheese";
        case 2: 
            return "Pepperoni";
        case 3: 
            return "Mushroom";
        case 4: 
            return "Onions";
        case 5: 
            return "Sausage";
        case 6: 
            return "Hamburger";
        case 7: 
            return "Bacon Bits";
        case 8: 
            return "Black Olives";
        case 9: 
            return "Green Peppers"; 
        case 10: 
            return "Pineapple";
    }
}

//function where orders takes place
void order() {
    int sizeWanted, crustWanted, toppingsAmountWanted = 0;
    int toppingsWanted[100];
    bool validSize = false, validCrust = false, finishedToppings = false, validGuests = false; //checks for valid inputs
    string itemizedList = "Great your itemized total for your order was as follows:\n\n";
    
    // Pizza Size
    cout << "Welcome to Pizza Parlor, please enter a number from 1 to 6 to indicate the size pizza you want" << endl;
    
    while(!validSize) { //check for valid pizza size, if true, continue, if false, input valid number. 
        cin >> sizeWanted;
        
        if(sizeWanted < 7 && sizeWanted > 0) {
            validSize = true;
        } else {
            cout << "That's an invalid pizza size." << endl;
        }
    }
    
    switch(sizeWanted) { //select from 6 different sizes
        case 1:
            cout <<  "You have chosen to order a Personal Pan Pizza. This will feed 6 people." << endl;
            itemizedList += "Personal Pizza $10.00\n";
            break;
        case 2:
            cout <<  "You have chosen to order a Small Pizza. This will feed 6 people." << endl;
            itemizedList += "Small Pizza $10.00\n";
            break;
        case 3:
            cout <<  "You have chosen to order a Medium Pizza. This will feed 8 people." << endl;
            itemizedList += "Medium Pizza $12.00\n";
            break;
        case 4:
            cout <<  "You have chosen to order a Large Pizza. This will feed 10 people." << endl;
            itemizedList += "Large Pizza $14.00\n";
            break;
        case 5:
            cout <<  "You have chosen to order a Extra Large Pizza. This will feed 10 people." << endl;
            itemizedList += "Extra Large Pizza $14.00\n";
            break;
        case 6:
            cout <<  "You have chosen to order a NY Style Pizza. This will feed 12 people." << endl;
            itemizedList += "NY style pizza $16.00\n";
            break;
    }
    
    // Crust Type
    cout << "Please enter a number from 1 to 3 to indicate the type of crust you want." << endl;
    
    while(!validCrust) { //checks valid crust type that's only on menu. 
        cin >> crustWanted;
        
        if (crustWanted < 4 && crustWanted > 0){
            validCrust = true;
            crustQoH[crustWanted - 1] -= 1;
        } else {
            cout << "that's an invalid crust size."<<endl;
        }
    }
    
    switch(crustWanted){ //Adds item to itemized list and also tells user their selection
         case 1:
            cout <<  "You have chosen Thin crust as your crust" << endl;
            itemizedList += "Thin Crust $NC\n";
            break;
        case 2:
            cout <<  "You have chosen Flatbread as your crust" << endl;
            itemizedList += "Flatbread Crust $NC\n";
            break;
        case 3:
            cout <<  "You have chosen Thick crust as your crust." << endl;
            itemizedList += "Thick Crust $2.00\n";
            break;
    }
    
    // Topppings
    while(!finishedToppings) {
        cout << "Please enter a number from 1 to 10 to indicate what toppings you would like on your pizza" << endl;
        
        toppingsAmountWanted++; //will keep adding topics until user says No more. 
        
        int toppingSelected = 1;
        cin >> toppingSelected;
        
        toppingsWanted[toppingsAmountWanted - 1] = toppingSelected;
        toppingsQoH[toppingSelected - 1] -= 1;
        
        cout << "You have added " << parseTopping(toppingSelected) << " to your order. Would you like to add more toppings (Y = Yes N = N)" << endl;
        
        if(premiumTopping(toppingSelected)) {
            itemizedList += parseTopping(toppingSelected) + " Topping $1.00\n"; //decide between premuim vs non premium topping
        } else {
            itemizedList += parseTopping(toppingSelected) + " Topping $NC\n";
        }
        
        string input;
        cin >> input;
        bool moreToppings = parseIn(input);
        
        if(!moreToppings) {
            finishedToppings = true;
        }
    }
    
    size[pizzaOn - 1] = sizeWanted;
    crust[pizzaOn - 1] = crustWanted;
    toppingsAmount[pizzaOn - 1] = toppingsAmountWanted;

    for (int i = 0; i < toppingsAmountWanted; i++) {
        toppings[pizzaOn - 1][i] = toppingsWanted[i];
    }
    
    
    //guest input
    int guests = 0; 
    cout << "Please enter the number of guests you have in your party"<<endl;
    
    while(!validGuests) {
        cin >> guests;
        
        switch(size[pizzaOn - 1]) { //checks valid amount of people per pizza size. 
            case 1: case 2: 
                if(guests > 6) {
                    cout << "I am sorry you must enter a number less than 6 for a personal/small size pizza." <<endl;
                } else {
                    validGuests = true;
                }
                break;
            case 3: 
                if(guests > 8){
                    cout << "I am sorry you must enter a number less than 10 for a medium pizza." <<endl;
                } else {
                    validGuests = true;
                }
                break;
            case 4: case 5: 
                if(guests > 10){
                    cout << " I am sorry you must enter a number less than 10 for a large/extra pizza." <<endl;
                } else {
                    validGuests = true;
                }
                break;
            case 6: 
                if(guests > 12){
                    cout << "I am sorry you must enter a number less than 10 for a NY style pizza." <<endl;
                } else {
                    validGuests = true;
                }
                break; 
        }
    }
    
    //price for Total order
    double totalOrder = 0; 
    totalOrder = calculate(pizzaOn - 1);
    cout << "Great your total for today’s order at the Pizza Parlor was $" << totalOrder << endl;
    
    // Itemizer
    cout << "Would you like an itemized list of your order? (Y = Yes N = No)" << endl;
    string input; 
    cin >> input;
    
    if(parseIn(input)) {
        cout << itemizedList << endl << "Total Cost $" << calculate(pizzaOn - 1) << endl; //calls from itemized strings in other fucntions
    }
    
    //Price for each guest 
    double guestTotal = 0;
    guestTotal = calculate(pizzaOn - 1);
    cout << "The total cost for each of your " << guests << " guests will be $" << (calculate(pizzaOn -1) / guests) <<endl;
    
}

int main() {
    bool finished = false;
    setQoH();
    
    while(!finished) {
        pizzaOn++;
        order();
        
        if(pizzaOn < 4) { //can only make 4 pizzas a night, handles yes and no question for adding more pizza to order
            cout << "Would you like to order another pizza? You have " << (4 - pizzaOn) << " Pizzas remaining (Y = Yes N = No)" << endl;
            
            string input;
            cin >> input;
            bool morePizza = parseIn(input);
            
            if(!morePizza) {
                finished = true;
            }
        } else {
            finished = true;
        }
    }
    
    cout << "Thank you for eating at the Pizza Parlor! Please come again soon!" << endl;
    
    double revenue = 0.00;
    
    for(int i = 0; i < (pizzaOn); i++) {
        revenue += calculate(i); //for loop for calculating revenue from the order. pulls from calculate function
    }
    
    cout  << "My total revenue for the night was $" << revenue << endl;
    
    cout << "My new QOH totals are as follows:" << endl << endl << "Toppings QOH:" << endl;
    
    for(int i = 0; i < 10; i++) {
      cout << parseTopping(i + 1) << " " << toppingsQoH[i] << endl; //QoH for toppings loop
    }
    
    cout << endl << "Crust QOH:" << endl;
    
    for (int i = 0; i < 3; i++){ //QoH for crust loop. 
        switch(i) {
            case 0:
                cout << "Thin Crust " << crustQoH[i] << endl;
                break;
            case 1:
                cout << "Flatbread" << crustQoH[i] << endl;
                break;
            case 2:
                cout << "Thick Crust" << crustQoH[i] <<endl;
                break;
        }
    }
    
    return 0;
}
