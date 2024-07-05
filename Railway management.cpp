#include<iostream>         // Standard input-output stream operations (like cin cout)
#include<iomanip>          // Manipulators for formatted output (like setw)
#include<fstream>          // File stream operations (ifstream, ofstream)
#include<string>           // String operations (string.length)
#include<windows.h>        // Windows API functions for system-specific operations
#include<cstdlib>          // General utilities library (for exit() function)
#include<limits>           // Numeric limits (for handling input validation)
#include<cctype>           // Character handling functions (like isdigit())
#include<conio.h>          // Console input-output operations (like _getch())


using namespace std;



void dotedlines();

void clearConsole();

void loginpage();

string toLower(string& str)
{
    string result;
    for (char c : str)
    {
        result += tolower(c);
    }
    return result;
}



class train
{

protected:
    string train_name;
    string train_no;
    string departure_time;
    string arrival_time;
    string departure_location;
    string destination_location;
    double fare;

public:
    void addintrain()
    {
        int no;

        cout<<"Please enter the number of trains you want to add \n";
        while(!(cin>>no))
        {
            cout<<"Enter valid number "<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"Enter number \n";
        }
        ofstream add("Train.txt", ios::app);
        for (int i=0; i<no; i++)
        {
            cout<<"Please enter the train name "<<endl<<endl;
            cin>>train_name;
            cout<<"Please enter the train No "<<endl<<endl;
            cin>>train_no;
            cout<<"Please enter the train Departure time  "<<endl<<endl;
            cin>>departure_time;
            cout<<"Please enter the train Departure Location  "<<endl<<endl;
            cin>>departure_location;
            cout<<"Please enter the train Arrival time  "<<endl<<endl;
            cin>>arrival_time;
            cout<<"Please enter the train Arrival Location  "<<endl<<endl;
            cin>>destination_location;
            cout<<"Please enter the train fare "<<endl<<endl;
            cin>>fare;


            add<<train_name<<" "<<train_no<<" "<<departure_time<<" "<<departure_location<<" "<<arrival_time<<" "<<destination_location<<" "<<fare<<endl;


        }
        add.close();

    }




    void modifyschdule()
    {
        string trainno;
        cout << "Please enter the train no: " << endl;
        cin >> trainno;

        ifstream fin("Train.txt");
        ofstream fout("TempTrain.txt",ios::app);



        bool trainFound = false;
        while (fin >> train_name >> train_no >> departure_time >> departure_location >> destination_location >> arrival_time >> fare)
        {
            if (trainno == train_no)
            {
                trainFound = true;
                cout << "Please enter the new details for the train:" << endl<<endl;
                cout << "Train name: ";
                cin >> train_name;
                cout << "Train No: ";
                cin >> train_no;
                cout << "Departure time: ";
                cin >> departure_time;
                cout << "Departure Location: ";
                cin >> departure_location;
                cout << "Arrival time: ";
                cin >> arrival_time;
                cout << "Arrival Location: ";
                cin >> destination_location;
                cout << "Fare: ";
                cin >> fare;

                fout << train_name << " " << train_no << " " << departure_time << " " << departure_location << " " << arrival_time << " " << destination_location << " " << fare << endl;
                cout << "Schedule modified successfully." << endl;
            }
            else
            {
                fout << train_name << " " << train_no << " " << departure_time << " " << departure_location << " " << arrival_time << " " << destination_location << " " << fare << endl;
            }
        }

        fin.close();
        fout.close();

        if (!trainFound)
        {
            cout << "Train with train number " << trainno << " not found." << endl;
        }
        else
        {
            // Replace original file with modified file
            remove("Train.txt");
            rename("TempTrain.txt", "Train.txt");
        }
    }





    virtual void display()
    {
        cout<<endl<<"________________________________________________Train Schedule_____________________________________________________"<<endl<<endl;
        dotedlines();


        ifstream f2("Train.txt");

        cout << "|  Train Name       | Train NO  | Departure Time |  Departure Location   | Arrival Time     | Arrival Location  | Fare   " << endl;

        while (f2 >> train_name >> train_no >> departure_time >> departure_location >> arrival_time >>destination_location >>fare)
        {
            cout<<endl << "|" << setw(19) << left << train_name << "|";
            cout << setw(10) << left << train_no << " |";
            cout << setw(15) << left << departure_time << " |";
            cout << setw(23) << left << departure_location << "|";
            cout << setw(13) << left << arrival_time << "      |";
            cout << setw(17) << left << destination_location << " |";

            cout << setw(13) << left << fare << endl;

        }

        // Close the file
        f2.close();

    }






    void searchtrain()
    {
        string arrival,desti,time;
        bool matched=false;
        cout<<"Enter your arrival location. "<<endl;
        cin>>arrival;
        cout<<"Enter your destination location "<<endl;
        cin>>desti;
        cout<<"Enter your arrival time (00:00)"<<endl;
        cin>>time;

        ifstream sear("Train.txt");
        while(sear >>  train_name >> train_no >> departure_time >> departure_location >> arrival_time >>destination_location >>fare )
        {
            if(toLower(arrival)==toLower(departure_location)&&toLower(desti)==toLower(destination_location)&&time==departure_time)
            {
                cout<<endl<<"Your train No is  "<<train_no<<endl<<endl;
                cout<<endl<<"Moving from "<<departure_location<<" at "<<departure_time<<" And will reached  "<<destination_location<<" at "<<arrival_time<<endl<<endl;
                cout<<endl<<"Fare of train is "<<fare<<" RS  "<<endl<<endl;
                matched=true;
            }

        }
        sear.close();
        if(!matched)
        {
            cout<<"Sorry train not found "<<endl;
        }

    }





};





class ticket:public train
{

private:
    bool found = false;


public:
    double total=0;
    int no;
    string tarinnn_no;



    void dis();



    void orderticket()
    {

        int seatno[100]= {9999};
        int classbook;


        do
        {
            cout <<endl<<endl<< "Please enter the number of passengers: " << endl;
            while (!(cin >> no))
            {
                cout << "Invalid input. Please enter a valid number of passengers \n ";
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard incorrect input
            }
            if(no==0)
            {
                cout<<"Enter valid no of passengers "<<endl;
            }
        }
        while(no==0);


        for(int i=0; i<no; i++)
        {
            do
            {
                do
                {
                    cout<<endl<<"Enter weather you want to book for passenger "<<i+1<<endl;
                    cout<<endl<<"\t\t\t\t\t|       1.AC Class              |"<<endl;
                    cout<<endl<<"\t\t\t\t\t|       2.Bussiness Class       | "<<endl;
                    cout<<endl<<"\t\t\t\t\t|       3.Berth                 |"<<endl;
                    cout<<endl<<" Select !   "<<endl;
                    while (!(cin >> classbook))
                    {
                        cout << "Invalid input. Please enter a valid Seat no \n: ";
                        cin.clear(); // Clear error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard incorrect input
                    }


                    if(classbook==1)
                    {
                        cout<<endl<<"Booked Ac class "<<endl;
                        total+=2000;
                    }
                    else if(classbook==2)
                    {
                        cout<<endl<<"Booked Bussiness class "<<endl;
                        total+=5000;

                    }
                    else if(classbook==3)
                    {
                        cout<<endl<<"Booked Berth "<<endl;
                        total+=1500;
                    }

                }
                while(classbook<0||classbook>3);


                cout<<"Enter seat no for passenger "<<i+1<<endl;
                while (!(cin >> seatno[i]))
                {
                    cout << "Invalid input. Please enter a valid Seat no \n: ";
                    cin.clear(); // Clear error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard incorrect input
                }


                if(seatno[i+1]>100||seatno[i+1]<0)
                {
                    cout<<"Sorry Enter valid seat no  "<<endl;

                }
                else if (seatno[i+1]==seatno[i])
                {
                    cout<<"Sorry seat already booked  "<<endl;
                }

            }
            while(seatno[i+1]>100||seatno[i+1]<0||seatno[i+1]==seatno[i]);
        }

        do
        {
            cout << "Enter the number of train: " << endl;
            cin >> tarinnn_no;


            ifstream file("Train.txt");

            while (file >> train_name >> train_no >> departure_time >> departure_location  >> arrival_time>> destination_location >> fare)
            {

                if (tarinnn_no == train_no)
                {
                    found = true;
                    break;

                }
            }


            ofstream traintotal("traintotal.txt",ios::app);
            ofstream grandtotal("grandtotal.txt",ios::app);

            if (found)
            {

                total=no*fare;
                traintotal<<total<<endl;
                grandtotal<<total<<endl;

                cout<<"_________________________________________Booking Details _____________________________________________________________"<<endl;
                cout<<endl;
                cout<<"You booked a train for "<<no<<" passengers. "<<endl;
                cout<<endl<<"From "<<departure_location<<" To "<<destination_location<<endl;
                cout<<endl<<"Which departs from "<<departure_location<<" at "<<departure_time <<" Arrives at "<<destination_location<<" at "<<arrival_time<<endl;

            }
            else
            {

                cout << "Train not found" << endl;


            }

            file.close();
        }
        while(!found);

    }






    void payticketbill()
    {
        int paychoice;
        string accountnumber,phno;
        double amount=0,amount1=0;
        int back;

        cout<<endl<<"Your total fare is "<<total<<" RS "<<endl;
        cout<<endl<<"Want to pay by :"<<endl;
        cout<<endl<<"1 .Account "<<endl;
        cout<<endl<<"2 .Jazz Cash "<<endl;
        cout<<endl<<"3 .Cash "<<endl;
        while (!(cin >> paychoice))
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "SELECT the choice! ";
        }

        switch(paychoice)
        {
        case 1:
        {
            string accountNumber;

            cout << endl << "Please enter your 12-digit account number. Your account number must be 12 digits." << endl;
            cin >> accountNumber;

            bool validAccount = true;

            // Check if all characters in accountNumber are digits
            for (char c : accountNumber)
            {
                if (!isdigit(c))
                {
                    validAccount = false;
                    break;
                }
            }

            if (accountNumber.length() != 12 || !validAccount)
            {
                cout << "Error: The account number must be exactly 12 digits and contain only digits." << endl;
                payticketbill();
            }
            else
            {

                cout << "Amount of " << total << " has been successfully deducted from your account." << endl;
            }
            cout<<endl<<"Press 0 to go back and 1 to exit "<<endl;
            cin>>back;
            if(back==0)
            {

            }
            dis();

        }


        break ;

        case 2:
        {
            cout << endl << "Please enter your 13-digit Phone Number. Your number must begin with 92" << endl;
            cin >> phno;

            bool validphone = true;


            for (char c : phno)
            {
                if (!isdigit(c))
                {
                    validphone = false;
                    break;
                }
            }

            if (phno.length() != 13 || !validphone&&phno.substr(0,2)!="92")
            {
                cout << "Error: The account number must be exactly 12 digits and contain only digits." << endl;
                payticketbill();
            }
            else
            {

                cout << "Amount of " << total << " has been successfully deducted from your account." << endl;
            }

        }

        break;


        case 3:
        {
            do
            {
                cout << "Please enter the amount: ";
                cin >> amount1;
                if (amount + amount1 < total)
                {
                    cout << "Your entered amount is less. Please enter more amount." << endl;
                }
                amount += amount1;
            }
            while (amount <= total);

            double returnamount = amount - total;
            cout << "Your return amount is " << returnamount << endl;

        }

        }

    }




};






class food
{

private:



    string itemname;
    double price;


public:


    void modifyfood()
    {

        string modify;
        bool check=false;

        ifstream fin ("food.txt");
        ofstream fou("tempfood.txt");

        cout<<"Enter the name of food you want to modify "<<endl;
        cin>>modify;

        while(fin>>itemname>>price)
        {
            if(modify==itemname)
            {
                check=true;
                cout<<"Enter the item name "<<endl;
                cin>>itemname;
                cout<<"Enter the item price "<<endl;
                cin>>price;
                fou<<itemname<<" "<<price<<endl;
                cout<<"Item Updated Successfully! "<<endl;

            }

            else
            {
                fou<<itemname<<" "<<price<<endl;
            }
        }
        fin.close();
        fou.close();
        if(!check)
        {
            cout<<"Your Searched item is not found "<<endl;


        }
        else
        {
            remove("food.txt");
            rename("tempfood.txt","food.txt");
        }

    }






    void addinfood()
    {
        int noofitems;
        cout<<"Enter the number of items you want to add "<<endl;
        while(!(cin>>noofitems))
        {
            cout<<"Enter valid number \n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"Enter number of items \n";
        }
        ofstream add("food.txt",ios::app);
        for (int i=0; i<noofitems; i++)
        {
            cout<<"Enter the name of item "<<endl;
            cin>>itemname;
            cout<<"Enter price of item "<<endl;
            cin>>price;
            add<<itemname<<" "<<price<<endl;
        }
        cout<<"Added Successfully!"<<endl;
        add.close();
    }






    void displayfood()
    {
        dotedlines();
        cout<<endl<<"____________________________________________WELCOME TO CANTEEN ____________________________________________________"<<endl<<endl;
        dotedlines();
        cout<<endl<<"__________________________________________________Our Menu_________________________________________________________"<<endl;



        ifstream fii("food.txt");

        cout << endl<< "\t\t\t\t_____________________________________________";
        cout << endl<<" \t\t\t\t|    Item name            |     Price        |";
        cout << endl<<" \t\t\t\t|_________________________|__________________|" << endl;

        while (fii >> itemname >> price)
        {
            cout << "\t\t\t\t|      " << setw(19) << left << itemname << "|";
            cout <<"\t" <<setw(13)  << price << "|" << endl;
        }


    }






    double total = 0;

    void orderfood()
    {
        const int MAX_ORDERS = 100;
        string orderNames[MAX_ORDERS];
        int orderQuantities[MAX_ORDERS];
        double orderPrices[MAX_ORDERS];
        int orderCount = 0;
        string name;
        int quant;


        ofstream foodtotal("foodtotal.txt",ios::app);
        ofstream grandtotal("grandtotal.txt",ios::app);

        while (true)
        {
            ifstream orderFile("food.txt");
            bool itemFound = false;

            cout << "Please enter the name of the item you want to order (enter '0' to display total and exit): " << endl;
            cin >> name;


            if (name == "0")
            {

                cout <<endl<< "Details of Orders:" << endl<<endl;;
                for (int i = 0; i < orderCount; ++i)
                {
                    cout <<endl<< "You ordered " << orderNames[i] << " with quantity " << orderQuantities[i] << " and total price for this item is " << orderPrices[i] <<endl<<endl;
                }

                cout <<endl<< "Thank you for ordering. Have a nice day!" << endl;
                break;
            }

            while (orderFile >> orderNames[orderCount] >> orderPrices[orderCount])
            {
                if (toLower(name) == toLower(orderNames[orderCount]))
                {
                    itemFound = true;
                    cout << "Enter the quantity: " << endl;
                    while(!(cin >> quant))
                    {
                        cout<<"Invalid qunatity "<<endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        cout<<"Please enter the Valid Quantity "<<endl;


                    }



                    orderQuantities[orderCount] = quant;
                    orderPrices[orderCount] *= quant;
                    total += orderPrices[orderCount];
                    foodtotal<<total<<endl;
                    grandtotal<<total<<endl;

                    orderCount++;

                    break;
                }
            }

            orderFile.close();

            if (!itemFound)
            {
                cout << "Sorry, the entered food is not present in our menu." << endl;
            }
        }
    }







    void payfood()
    {
        int paychoice;
        string accountnumber,phno;
        double amount=0,amount1;
        if(total<=0)
        {
            clearConsole();
            cout<<endl<<"Please Select the food first "<<endl;
            displayfood();
            orderfood();
        }

        cout<<endl<<"Your total amount is "<<total<<" RS "<<endl;
        cout<<"Want to pay by :"<<endl;
        cout<<"1 .Account "<<endl;
        cout<<"2 .Jazz Cash "<<endl;
        cout<<"3 .Cash "<<endl;
        cout<<endl<<"SELECT  !"<<endl;
        while (!(cin >> paychoice))
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "SELECT the choice! "<<endl;;
        }

        switch(paychoice)
        {
        case 1:
        {
            cout<<endl<<"Please Enter your 12 digit account number.Your account number must be 12 digit "<<endl;
            cin>>accountnumber;
            if(accountnumber.length()<12)
            {
                cout<<endl<<"Enter a valid account number "<<endl;
                payfood();
            }
            else
            {
                cout<<endl<<"Amount of "<<total <<" has been successfully deducted from your account "<<endl;
            }
        }


        break ;

        case 2:
        {

            cout<<"Enter 11 digit phone number "<<endl;
            cin>>phno;
            if(phno.length()<13&&phno.substr(0,2)!="92")
            {
                cout<<endl<<"Enter a valid jazz cash number and your number must start from 92 "<<endl;
                payfood();

            }
            cout<<endl<<"Amount of "<<total <<" has been successfully deducted from your account "<<endl;
        }

        break;


        case 3:
        {

            do
            {
                cout << "Please enter the amount: ";
                cin >> amount1;
                if (amount + amount1 < total)
                {
                    cout <<endl<< "Your entered amount is less. Please enter more amount." << endl;
                }
                amount += amount1;
            }
            while (amount < total);

            double returnamount = amount - total;
            cout <<endl<< "Your return amount is " << returnamount << endl;

        }
        break;
        default:
        {
            cout<<"Enter valid input "<<endl;
            payfood();
        }

        }

    }







};







class details
{

protected:
    string name;
    string dept;
    string number;
    string idcard;
    double salary;
    string email;
    string employee_id;

public:




    virtual void employeedetails ()=0;


};




class employee :public details
{

protected:


    string name;
    string dept;
    string number;
    string idcard;
    double salary;
    string email;
    string employee_id;

public:

    void employeedetails ()
    {
        ofstream emp ("employee.txt",ios::app);



        emp.close();

        cout<<endl<<"____________________________________________ Employee Details ________________________________________________________"<<endl;

        ifstream empo ("employee.txt");
        cout << "______________________________________________________________________________________________________________________" << endl;
        cout << "| Employee ID |     Name    |   Department     |     Number      |  Idcard Number  |  Salary   |      Email        " << endl;
        cout << "______________________________________________________________________________________________________________________" << endl;

        while (empo >> employee_id >> name >> dept >> number >> idcard >> salary >> email)
        {
            cout << left << setw(12) << employee_id << "  | ";
            cout << left << setw(11) << name << " | ";
            cout << left << setw(16) << dept << " | ";
            cout << left << setw(15) << number << " | ";
            cout << left << setw(15) << idcard << " | ";
            cout << left << setw(9) << salary << " | ";
            cout << left << setw(25) << email<<"   " <<endl<<endl;




        }
        empo.close();

    }





    void searchbydepartment()
    {

        string deptt;
        bool header=true;
        bool department=false;

        cout<<"Enter the name of department "<<endl;
        cin>>deptt;

        ifstream read("employee.txt");





        while (read >> employee_id >> name >> dept >> number >> idcard >> salary >> email)
        {


            if(deptt==dept)
            {
                if(header)
                {
                    cout<<endl<<"__________________________________________"<<deptt<<" Department Details _______________________________________"<<endl<<endl;;
                    cout << "______________________________________________________________________________________________________________________" << endl;
                    cout << "| Employee ID |     Name    |   Department     |     Number      |  Idcard Number  |  Salary   |      Email        " << endl;
                    cout << "______________________________________________________________________________________________________________________" << endl;


                }


                cout << left << setw(12) << employee_id << "  | ";
                cout << left << setw(11) << name << " | ";
                cout << left << setw(16) << dept << " | ";
                cout << left << setw(15) << number << " | ";
                cout << left << setw(15) << idcard << " | ";
                cout << left << setw(9) << salary << " | ";
                cout << left << setw(25) << email<<"   " <<endl<<endl;

                header=false;
                department=true;


            }




        }

        read.close();

        if(!department)
        {
            cout<<endl<<"Sorry Department not found. "<<endl;
        }

    }







    void addinemployee()
    {

        int empno;

        cout<<"Please enter the number of employees you want to add "<<endl;
        while (!(cin >> empno))
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout<<"Please enter the number of employees you want to add "<<endl;
        }


        ofstream add("employee.txt");

        for(int i=0; i<empno; i++)
        {
            cout<<"Enter Id "<<endl;
            cin>>employee_id;
            cout<<"Enter name "<<endl;
            cin>>name;
            cout<<"Enter department "<<endl;
            cin>>dept;
            cout<<"Enter phone number "<<endl;
            cin>>number;
            cout<<"Enter id card number "<<endl;
            cin>>idcard;
            cout<<"Enter Salary "<<endl;
            cin>>salary;
            cout<<"Enter Email "<<endl;
            cin>>email;




            add<<employee_id<<" "<<name<<" "<<dept<<" "<<number<<" "<<idcard<<" "<<salary<<" "<<email<<endl;
            cout<<endl<<"Added Successfully "<<endl;
        }


        add.close();




    }







    void changeinemployee()
    {


        string id ;
        bool found=false;

        cout<<"Enter Employee Id "<<endl;
        cin>>id;

        ifstream changein("employee.txt");
        ofstream changeout("tempemployee.txt");

        while (changein >> employee_id >> name >> dept >> number >> idcard >> salary >> email)
        {

            if(id==employee_id)
            {
                cout<<"Enter Id "<<endl;
                cin>>employee_id;
                cout<<"Enter name "<<endl;
                cin>>name;
                cout<<"Enter department "<<endl;
                cin>>dept;
                cout<<"Enter phone number "<<endl;
                cin>>number;
                cout<<"Enter id card number "<<endl;
                cin>>idcard;
                cout<<"Enter Salary "<<endl;
                cin>>salary;
                cout<<"Enter Email "<<endl;
                cin>>email;


                changeout<<employee_id<<" "<<name<<" "<<dept<<" "<<number<<" "<<idcard<<" "<<salary<<" "<<email<<endl;
                found=true;
                cout<<"Employee Details Updated Successfully "<<endl;
            }
            else
            {

                changeout<<employee_id<<" "<<name<<" "<<dept<<" "<<number<<" "<<idcard<<" "<<salary<<" "<<email<<endl;
            }
        }



        changein.close();
        changeout.close();
        if(!found)
        {
            cout<<"Sorry your entered id is not found "<<endl;
        }

        else
        {
            remove("employee.txt");
            rename("tempemployee.txt","employee.txt");

        }


    }






    void searchspecificeemployee()
    {

        string Id;
        bool check=false;
        cout<<"Enter Employee Id "<<endl;
        cin>>Id;

        ifstream searchh("employee.txt");


        while (searchh >> employee_id >> name >> dept >> number >> idcard >> salary >> email)
        {

            if(Id==employee_id)
            {
                check=true;

                cout << "______________________________________________________________________________________________________________________" << endl;
                cout << "| Employee ID |     Name    |   Department     |     Number      |  Idcard Number  |  Salary   |      Email        " << endl;
                cout << "______________________________________________________________________________________________________________________" << endl;





                cout << left << setw(12) << employee_id << "  | ";
                cout << left << setw(11) << name << " | ";
                cout << left << setw(16) << dept << " | ";
                cout << left << setw(15) << number << " | ";
                cout << left << setw(15) << idcard << " | ";
                cout << left << setw(9) << salary << " | ";
                cout << left << setw(25) << email<<"   " <<endl<<endl;


            }

        }
        searchh.close();
        if(!check)
        {
            cout<<"Sorry your Searched Employee is not found in any department. "<<endl;
        }

    }







};






class user
{



public:


    int choice;

    void faqs()
    {
        dotedlines();
        cout << "______________________________________________________FAQs________________________________________________________" << endl;
        cout << endl << "\t\t\t\t_________________________________________________" << endl;
        cout << endl << "\t\t\t\t|\tPress 1 to add complaint.               |" << endl;
        cout << endl << "\t\t\t\t|\tPress 2 to add suggestion.              |" << endl;
        cout << endl << "\t\t\t\t|\tPress 3 for lost or found things        |" << endl;
        cout << endl << "\t\t\t\t|\tPress 4 for rating.                     |" << endl;
        cout << endl << "\t\t\t\t|\tPress 0 for Exit.                       |" << endl;
        cout << endl << "\t\t\t\t_________________________________________________" << endl;
        cout << "choice !" << endl;
        while (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "SELECT the choice! ";
        }

        switch (choice)
        {
        case 1:
        {
            int train;
            cout << endl << "__________________________________________________Complaint Section _________________________________________________" << endl;
            cout << endl << "\t\t\t\t\tWe are sorry if you have any complaint. " << endl;
            cout << endl << "\t\t\t\t\tLet us know about your complaint ." << endl;
            cout << "Complaint about !" << endl << endl;
            cout << "\3  1.Train " << endl << endl;
            cout << "\3  2.Staff " << endl << endl;
            cout << "\3  3.other " << endl << endl;
            cout << "\3  4.Exit " << endl << endl;
            while (!(cin >> train))
            {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear(); // Clear the fail state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "SELECT the choice! ";
            }
            switch (train)
            {
            case 1:
            {
                int com;
                cout << endl << "Complaint about :" << endl << endl;
                cout << "\3 1.Train Timings. " << endl << endl;
                cout << "\3 2.Train cleanniness. " << endl << endl;
                cout << "\3 3.Train Schedule. " << endl << endl;
                cout << "\3 4.Exit. " << endl << endl;
                cout << " Choice ! " << endl;
                while (!(cin >> com))
                {
                    cout << "Invalid input. Please enter a number.\n";
                    cin.clear(); // Clear the fail state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "SELECT the choice! ";
                }
                switch (train)
                {
                case 1:
                    cout << endl << "We try to improve Train timings .Thanks for your Complaint. " << endl;
                    break;
                case 2:
                    cout << endl << "We try to improve Train cleanniness .Thanks for your Complaint. " << endl;
                    break;
                case 3:
                    cout << endl << "We try to improve Train Schedule .Thanks for your Complaint. " << endl;
                    break;
                case 4:
                    faqs();
                    break;
                default:
                    cout << "Invalid input .Try again." << endl;
                    break;
                }
                break;
            }
            case 2:
            {
                int staff;
                cout << "Complaint about ! " << endl;
                cout << "\3 1.Train staff " << endl;
                cout << "\3 2.Management staff " << endl;
                cout << "\3 3.Security " << endl;
                cout << "\3 4.Exit " << endl;
                while (!(cin >> staff))
                {
                    cout << "Invalid input. Please enter a number.\n";
                    cin.clear(); // Clear the fail state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "SELECT the choice! ";
                }

                switch (staff)
                {
                case 1:
                    cout << "We will try to improve our train staff .Thanks for your Complaint " << endl<<endl;
                    break;
                case 2:
                    cout << "We will try to improve our Management staff .Thanks for your Complaint " << endl<<endl;
                    break;
                case 3:
                    cout << "We will try to improve our Security staff .Thanks for your Complaint " << endl<<endl;
                    break;
                case 4:
                    faqs();
                    break;
                default:
                    cout << "Invalid choice " << endl;
                    break;
                }

            }
            break;
            case 3:
            {
                string getcom;
                cout <<"Enter the complaint "<<endl;
                cin.ignore();
                getline(cin,getcom);
            }
            break;
            case 4:
            {
                faqs();

            }
            }

        }

        break ;
        case 2:
        {
            string suggestion;
            cout<<"_________________________________________________________Suggestions _______________________________________________"<<endl;
            cout<<endl<<"Please enter your suggestions "<<endl;
            cin.ignore();
            getline(cin,suggestion);
            cout<<"Your suggestion submitted successfully .Thanks for your suggestions "<<endl;


        }
        break;

        case 3:
        {
            int lostorfound;
            string found,lost,number;
            cout<<"1.Thing Found "<<endl;
            cout<<"2.Thing Lost "<<endl;
            cout<<"choice !"<<endl;
            cin>>lostorfound;
            switch(lostorfound)
            {
            case 1:
                cout<<"Enter about the thing you found "<<endl;
                cin.ignore();
                getline(cin,found);
                cout<<"Thanks for your help. "<<endl;

                break;
            case 2:
                cout<<"Enter about the thing you lost "<<endl;
                cin.ignore();
                getline(cin,lost);
                cout<<"Please enter your number so that we may call you when we found thing "<<endl;
                cin.ignore();
                getline(cin,number);
                break;
            default:
                cout<<"Invalid choice "<<endl;

            }
        }
        break ;

        case 4:
        {
            string rating;
            while (true)
            {
                cout << "Please rate us (* * * * *): "<<endl;
                cin.ignore();
                getline(cin, rating);

                if (rating == "*"||rating =="**"||rating =="* *"||rating =="***"||rating =="* * *"||rating =="****"||rating =="* * * *"
                        ||rating =="*****"||rating =="* * * * *")
                {
                    cout << "Thanks for your rating." << endl;
                    break;
                }
                else
                {
                    cout << "Invalid rating. Please enter exactly five stars and less than 5." << endl;
                }
            }

        }
        break;
        case 0 :
        {
            exit(0);

        }
        break;
        default:
        {
            cout<<"Invalid Choice !"<<endl;
        }
        }
    }




};




class management:public train
{


protected :




    string username;
    string password;
    string admin_username;
    string admin_password;;
    string adminname,adminpassword,adminpin;




    train a;
    food b;
    ticket c;
    user d;
    employee e;




public:



    management()
    {
        username="umar";
        password="Pakistan";

    }



    void finance();



    void setConsoleColor(int color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }




    void displayy(string menu[], int size, int highlight)
    {
        setConsoleColor(FOREGROUND_GREEN);
        cout<<endl<<"\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout<<endl<<"\t\t\t\t WELCOME TO PAKISTAN RAILWAYS "<<endl;
        cout<<endl<<"\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout<<endl;
        for (int i = 0; i < size; i++)
        {
            if (i == highlight)
            {
                setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED); // Highlighted text with green background
                cout << "\t\t\t\t\t" << menu[i] << endl;

            }
            else
            {
                setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Default text color
                cout << "\t\t\t\t\t" << menu[i] << endl;
            }
        }
        // Reset console color after displaying the menu
        setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    void handleMenu(string menu[], int size)
    {
        int currentOption = 0;



        while (true)
        {
            system("cls");

            displayy(menu, size, currentOption);

            int key = _getch();


            if (key == 224)
            {
                key = _getch();
                if (key == 72 && currentOption > 0)
                {
                    currentOption--;
                }
                else if (key == 80 && currentOption < size-1)
                {
                    currentOption++;
                }
            }
            else if (key == 13)
            {
                cout << endl; // To move to a new line after the selected mode message
                if (currentOption == 0)
                {

                    adminmode();
                    break;
                    // Add logic for admin mode
                }
                else if (currentOption == 1)
                {

                    usermode();
                    break;
                    // Add logic for user mode
                }
                else if (currentOption == 2)
                {
                    cout<<"\t\t\t\t THANKS FOR USING PAKISTAN RAILWAYS "<<endl;
                    // Add cleanup logic if needed
                    break; // Exit the loop when 'exit' option is selected
                }
                _getch(); // Wait for a key press before returning to the menu
            }
        }
    }



/*
// iss mai apna path dai folder mai pic wala folder ka chal jai ga
    void captcha()
    {
        string path = "C:\\Users\\umar\\Desktop\\oop project\\project by me again\\new pics";

        string e;


        static int count=0;
        string a = "\\";

        string b = ".png";

        srand(time(0));

        string arr[48] = {"2d44cd", "3kvdw3","3mkhp8","3n6mb6","3xtrav8","4ds7ft7","4ty4yux","4tkyt3z","5pfpibn",

                          "6zuv29","7c3ydra","8tsndml","17m52p","33ibs4f","62tlndi","88bnsm","852bbb","7526fhf","aj8ntpr","b424dy",

                          "bjwnejn","cnd929","db6jza7","dffwtbk","eizwkyu","ern7me","exbxmx","i78resi","jtyc26b","ju7c3ma","kn4uvar","ku6usji","lfpwhxy","m3unbt",

                          "m5pvbp","miyvwp","mrada5s","nxtzhvd","p6efmia","pt67knh","rh738si","sicn4dy","srndscv","u3smrc","u3346z","yubky4","y64ryt3","zmzeuy"
                         };

        string d = arr[rand() % 48];

        string fullPath = path + a + d + b;

        ShellExecute(NULL, "open", fullPath.c_str(), NULL, NULL, SW_SHOWNORMAL);

        cout<<"enter code or press 1 to reload the image. " << endl;

        cin>>e;


        if(count==3)
        {
            cout<<"Sorry You cannot reload Exiting the Programe. "<<endl;
            exit(0);
        }

        if (e == d)
        {

            cout << "Matched You are not a robot. " << endl;

        }

        else if (e=="1")
        {
            count++;
            cout<<"You have left "<<3-count<<" chances of reload. "<<endl;
            captcha();


        }


        else if(e!=d&&e!="1")
        {

            cout << "Not matched Sorry You are a robot. " << endl;

            captcha();



        }

    }

*/


    void mainMenu();


    void usermenu();


    void userlogin();



    void adminmode()
    {
        loginpage();
        static int count1=0,count2=0;
        int choice2;
        dotedlines();
        cout<<"\t\t\t\t        |       ADMIN MODE          |     " << endl;
        dotedlines();
        cout<<"\t\t\t\t|      1 . Create New Account                |" << endl;
        cout<<"\t\t\t\t|      2 . Login using existing account      |" << endl;
        cout<<"\t\t\t\t|      3 . EXIT                              |" << endl;
        cout<<"\t\t\t\t|      0 . To go back                        |" << endl;
        cout << "Select: ";
        while (!(cin >> choice2))
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "SELECT the choice! ";
        }
        switch(choice2)
        {
        case 0:
        {
            display();
        }
        break;
        case 1:
        {
            loginpage();
            ofstream admi("admin.txt",ios::app);

            string pin="12345";
            cout<<"Enter the user name. "<<endl;
            cin>>adminname;
            cout<<"Enter the password. "<<endl;
            cin>>adminpassword;


            do
            {
                if(count2==3)
                {
                    cout<<"SORRY ending programe due to security issues."<<endl;
                    exit(0);
                }

                cout<<"Enter the pin provided by the authority "<<endl;
                cin>>adminpin;
                if(adminpin==pin)
                {
                    admi<<adminname<<" "<<adminpassword<<endl;
                    cout<<"Account Created "<<endl;
                    adminmode();

                }
                count2++;
            }
            while(adminpin!=pin);
            admi.close();
        }
        break;
        case 2:
        {
            clearConsole();


            if(count1==3)
            {
                cout<<"Sorry programe is ending due to security issues "<<endl;
                exit(0);
            }

            cout<<endl<<"Enter the Admin user name.  "<<endl;
            cin>>admin_username;
            cout<<endl<<"Enter the Admin password. "<<endl;
            cin>>admin_password;
           // captcha();
            ifstream add("admin.txt");
            while(add >> adminname >>adminpassword)
            {
                if((admin_username==username&&admin_password==password)||(admin_username==adminname&&admin_password==adminpassword))
                {
                    count1=0;
                    clearConsole();
                    cout<<"\t\t\t\t\tUser name and password matched. "<<endl;
                    mainMenu();

                }
                else
                {
                    count1++;
                    clearConsole();
                    cout<<"Wrong user name or password "<<endl;
                    adminmode();
                }
            }
            add.close();
        }
        break;
        case 3:
        {
            cout<<"\t\t\t\t THANKS FOR USING PAKISTAN RAILWAYS "<<endl;
        }
        break;
        default:
        {
            cout<<"Invalid choice "<<endl;
            adminmode();
        }
        }
    }



    void usermode()
    {
        loginpage();


        int choice1;


        dotedlines();
        cout<<"\t\t\t\t        |       USER MODE          |     " << endl;
        dotedlines();
        cout<<"\t\t\t\t|      1 . Create New Account                |" << endl;
        cout<<"\t\t\t\t|      2 . Login using existing account      |" << endl;
        cout<<"\t\t\t\t|      3 . Change Password                   |" << endl;
        cout<<"\t\t\t\t|      4 . EXIT                              |" << endl;
        cout<<"\t\t\t\t|      0 . To go back                        |" << endl;
        cout << "Select: ";
        while (!(cin >> choice1))
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "SELECT the choice! ";
        }

        switch(choice1)
        {
        case 0:
        {
            clearConsole();
            display();
        }

        case 1:
        {
            clearConsole();
            string user_name;
            string user_password;
            string userr,pass;
            bool matched=false;
            dotedlines();
            cout << "____________________________________________________CREATING NEW ACCOUNT__________________________________________" << endl;

            cout<<endl<<"Enter user name "<<endl;
            cin>>user_name;
            cout<<endl<<"Enter user Password  "<<endl;
            cin>>user_password;
            ifstream of("User.txt");

            while (of >> userr >> pass)
            {


                if (userr == user_name && pass == user_password)
                {
                    matched = true;
                    break;
                }
            }

            of.close();

            if (matched)
            {
                cout << "Sorry User already found ." << endl;
                usermode();



            }
            else
            {


                ofstream f("User.txt", ios_base::app);
                f << user_name<<" "<<user_password << endl;
                f.close();
                cout <<endl<<"New User ID created!";
                dotedlines();
                cout << "Your User ID is " <<user_name<< " and password is " <<user_password << endl;
                cout <<endl<<"Use this as Login Credentials!" << endl;
                display();
            }
        }
        break;
        case 2:
        {
            userlogin();
        }
        break;
        case 3 :
        {
            clearConsole();
            string usern;
            string us,pas;
            string newna,newpass;
            bool chek=false;

            cout<<"Enter the user name "<<endl;
            cin>>usern;

            ofstream uf("tempUser.txt");
            ifstream ui("User.txt");

            while(ui>>us>>pas)
            {
                if(usern==us)
                {
                    chek=true;
                    cout<<endl<<"User name matched "<<endl<<endl;
                    cout<<"Enter the user name "<<endl;
                    cin>>newna;
                    cout<<"Enter the new password  "<<endl;
                    cin>>newpass;
                    uf<<newna<<" "<<newpass<<endl;
                    cout<<"Password Updated Successfully "<<endl;

                }
                else
                {
                    uf<<newna<<" "<<newpass<<endl;
                }
            }
            uf.close();
            ui.close();
            if(!chek)
            {
                cout<<"Sorry User name not found "<<endl;
            }
            else
            {
                remove ("User.txt");
                rename("tempUser.txt","User.txt");
            }

        }
        break;
        case 4:
        {
            cout<<"\t\t\t\tTHANKS FOR USING PAKISTAN RAILWAYS. "<<endl;

            exit(0);


        }


        }


    }





    void userlogindetails()
    {
        loginpage();
        string id,password;
        int count=1;
        cout<<"\t\t\t\t\tAll users login details are under "<<endl;
        ifstream det("user.txt");
        while(det>>id>>password)
        {
            cout<<endl<<count<<" User name is "<<id <<"  and password is "<<password<<endl;
            count++;
        }

        det.close();
    }





    void display ()
    {
        int choice;




        string menu[] = {"1.Admin mode", "2.User mode", "3.Exit"};
        int size = sizeof(menu) / sizeof(menu[0]);


        handleMenu(menu, size);

        dotedlines();

    }





};





void management::mainMenu()
{
    loginpage();

    int choice1;
    int back;


    cout<<endl<<"\t\t\t\t\t|         Admin mode        |"<<endl;


    cout << "\t\t\t_________________________________________________________" << endl;
    cout << "\t\t\t|\t\t\t\t\t\t\t|" << endl;

    cout << "\t\t\t|           Press 1 to see Train details.               |" << endl<<endl;
    cout << "\t\t\t|           Press 2 to change in trains section.        |" << endl<<endl;
    cout << "\t\t\t|           Press 3 to see employee details.            |" << endl<<endl;
    cout << "\t\t\t|           Press 4 to add or change in employee.       |" << endl<<endl;
    cout << "\t\t\t|           Press 5 to Search some Employee.            |" << endl<<endl;
    cout << "\t\t\t|           press 6 to see all login user details.      |" << endl<<endl;
    cout << "\t\t\t|           Press 7 to see food details.                |" << endl<<endl;
    cout << "\t\t\t|           Press 8 to add or change in food section.   |" << endl<<endl;
    cout << "\t\t\t|           Press 9 to see Finance.                     |" << endl<<endl;
    cout << "\t\t\t|           Press 10 exit                                |" << endl<<endl;
    cout << "\t\t\t|           Press 0 to go back                          |" << endl<<endl;
    cout << "\t\t\t|\t\t\t\t\t\t\t|" << endl;

    cout << "\t\t\t_________________________________________________________" << endl;

    cout << "Enter the Choice: ";
    while (!(cin >> choice1))
    {
        cout << "Invalid input. Please enter a number.\n";
        cin.clear(); // Clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "SELECT the choice! ";
    }



    switch (choice1)
    {

    case 0:
    {
        clearConsole();
        display();

    }
    case 1:

    {
        clearConsole();
        a.display();
        cout<<"Press 0 to go back "<<endl;
        cin>>back;
        if(back==0)
        {
            mainMenu();

        }
        else
        {
            cout<<"\t\t\t\tTHANKS FOR USING PAKISTAN RAILWAYS. "<<endl;
            exit(0);
        }
    }
    break;
    case 2:
    {
        clearConsole();
        int ch;
        cout<<endl<<"1.To add new train schedule "<<endl;
        cout<<endl<<"2.To change in existing train schedule "<<endl;
        cout<<endl<<"Press 0 to go back "<<endl;
        cout<<endl<<"SELECT ! "<<endl;
        cin>>ch;
        if(ch==1)
        {
            a.addintrain();
        }
        else if(ch==2)
        {
            a.modifyschdule();
        }
        else if(ch==0)
        {
            mainMenu();
        }
        else
        {
            cout<<"Invalid choice "<<endl;
            mainMenu();
        }

    }
    break;
    case 3:
    {
        e.employeedetails();
        cout<<"Press 0 to go back "<<endl;
        cin>>back;
        if(back==0)
        {
            mainMenu();
        }
    }
    break;
    case 4:
    {
        clearConsole();
        int ch;
        cout<<endl<<"1.To add new Employee Detail.  "<<endl;
        cout<<endl<<"2.To change in existing Employee detail "<<endl;
        cout<<endl<<"Press 0 to go back "<<endl;
        cout<<endl<<"SELECT ! "<<endl;
        cin>>ch;
        if(ch==1)
        {
            e.addinemployee();
        }
        else if(ch==2)
        {
            e.changeinemployee();
        }
        else if(ch==0)
        {
            mainMenu();
        }
        else
        {
            cout<<"Invalid choice "<<endl;
            mainMenu();
        }
    }
    break;
    case 5:
    {
        int cho;
        cout<<" 1. Search details of employee of a department "<<endl;
        cout<<" 2.Search details of a specific Employee "<<endl;
        cout<<" 0. To go back "<<endl;
        cout<<endl<<"SELECT ! "<<endl;
        cin>>cho;
        if(cho==1)
        {
            e.searchbydepartment();
        }
        else if(cho==2)
        {
            e.searchspecificeemployee();
        }
        else if(cho==0)
        {
            mainMenu();
        }
        else
        {
            clearConsole();
            cout<<"Invalid choice "<<endl;
            mainMenu();
        }

    }
    break;
    case 6:
    {
        clearConsole();
        userlogindetails();
        cout<<endl<<"Press 0 to go back "<<endl;
        cin>>back;
        if(back==0)
        {
            mainMenu();
        }
        else
        {
            cout<<"\t\t\t\t\tTHANKS FOR USING PAKISTAN RAILWAYS. "<<endl;
            exit(0);
        }
    }
    break;
    case 7:
    {
        clearConsole();
        b.displayfood();
        cout<<endl<<"Press 0 to go back "<<endl;
        cin>>back;
        if(back==0)
        {
            clearConsole();
            mainMenu();
        }
        else
        {
            exit(0);
        }

    }

    break;
    case 8:
    {
        clearConsole();
        int foo;
        cout<<endl<<"1. To add in food section "<<endl;
        cout<<endl<<"2. To change in existing food "<<endl;
        cout<<endl<<"0. To go back "<<endl;
        cin>>foo;
        if(foo==1)
        {
            b.addinfood();

        }
        else if(foo==2)
        {
            b.modifyfood();
        }
        else if (foo==0)
        {
            mainMenu();
        }
        else
        {
            cout<<"Invalid choice "<<endl;
            mainMenu();
        }

    }
    break;

    case 9:
    {
        finance();
    }
    break;
    case 10:
    {
        clearConsole();
        cout<<"\t\t\t\tTHANKS FOR USING PAKISTAN RAILWAYS. "<<endl;
        exit(0);

    }
    break;
    default:
    {
        clearConsole();
        cout<<"Invalid choice "<<endl;
        mainMenu();
    }


    }

}






void management::usermenu()
{
    loginpage();
    int choice,back;
    cout<<"____________________________________________USER MODE _____________________________________________________________"<<endl;
    cout << "\t\t\t_________________________________________________________" << endl;
    cout << "\t\t\t|\t\t\t\t\t\t\t|" << endl;

    cout << "\t\t\t|           Press 1 to see Train details.               |" << endl<<endl;
    cout << "\t\t\t|           Press 2 to search train.                    |" << endl<<endl;
    cout << "\t\t\t|           Press 3 to book tickets.                    |" << endl<<endl;
    cout << "\t\t\t|           Press 4 to display food.                    |" << endl<<endl;
    cout << "\t\t\t|           Press 5 to order food.                      |" << endl<<endl;
    cout << "\t\t\t|           Press 6 to FAQs                             |" << endl<<endl;
    cout << "\t\t\t|           Press 7 exit                                |" << endl<<endl;
    cout << "\t\t\t|           Press 0 to go back.                         |" << endl<<endl;
    cout << "\t\t\t|\t\t\t\t\t\t\t|" << endl;
    cout << "\t\t\t_________________________________________________________" << endl;
    cout<<"Select !"<<endl;
    while (!(cin >> choice))
    {
        cout << "Invalid input. Please enter a number.\n";
        cin.clear(); // Clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "SELECT the choice! ";
    }

    switch (choice)
    {

    case 0:
    {
        clearConsole();
        display();
    }
    case 1:
    {
        clearConsole();
        a.display();
        cout<<"Press 0 to go back "<<endl;
        cin>>back;
        if(back==0)
        {
            clearConsole();
            usermenu();
        }
        else
        {
            cout<<"\t\t\t\tTHANKS FOR USING PAKISTAN RAILWAYS. "<<endl;
            exit(0);
        }
    }
    break;
    case 2:
    {
        a.searchtrain();
        cout<<endl<<"1.To order ticket "<<endl;
        cout<<endl<<"0.To go back "<<endl;
        cout<<endl<<"Choice !"<<endl;
        cin>>back;
        if(back==1)
        {
            c.orderticket();
        }
        else if(back==0)
        {
            clearConsole();
            usermenu();
        }
        else
        {
            cout<<"\t\t\t\tTHANKS FOR USING PAKISTAN RAILWAYS. "<<endl;
            exit(0);
        }


    }
    break;
    case 3:
    {
        clearConsole();
        c.orderticket();
        cout<<"Press 1 to print ticket invoice and 0 to go back."<<endl;
        cin>>back;
        if(back==1)
        {
            c.payticketbill();
            cout<<"Press 0 to go back."<<endl;
            cin>>back;
            if(back==0)
            {
                clearConsole();
                usermenu();
            }

        }
        else if(back==0)
        {
            clearConsole();
            usermenu();
        }
        else
        {
            cout<<"\t\t\t\tTHANKS FOR USING PAKISTAN RAILWAYS. "<<endl;
            exit(0);
        }
    }

    break;
    case 4:
    {
        clearConsole();
        b.displayfood();
        cout<<"Press 0 to go back "<<endl;
        cin>>back;
        if(back==0)
        {
            clearConsole();
            usermenu();
        }
        else
        {
            cout<<"\t\t\t\tTHANKS FOR USING PAKISTAN RAILWAYS. "<<endl;
            exit(0);
        }
    }
    case 5:
    {
        clearConsole();
        b.displayfood();
        b.orderfood();
        cout<<"Press 1 to print food invoice and 0 to go back "<<endl;
        cin>>back;
        if(back==1)
        {
            b.payfood();
            cout<<"Press  0 to go back "<<endl;
            cin>>back;
            if (back==0)
            {
                clearConsole();
                usermenu();
            }
        }
        else if (back==0)
        {
            clearConsole();
            usermenu();
        }
        else
        {
            exit(0);
        }
    }
    break;
    case 6:
    {
        clearConsole();
        d.faqs();
        cout<<"press 0 to go back "<<endl;
        cin>>back;
        if(back==0)
        {
            clearConsole();
            usermenu();
        }
        else
        {
            exit(0);
        }
    }
    break;
    case 7:
    {
        cout<<"\t\t\t\tTHANKS FOR USING PAKISTAN RAILWAYS. "<<endl;
        exit(0);
    }

    break;
    default:
    {
        cout<<"Invalid choice "<<endl;
        exit(0);
    }

    }
}





void management ::userlogin()
{
    loginpage();

    string confirm_name;
    string confirm_password;
    string id,passwordd;
    bool matched =false;
    static int count=0;

    if(count==3)
    {
        cout<<"Sorry Programe is ending due to security issues. "<<endl;
        exit(0);
    }

    dotedlines();
    cout << "_____________________________________________LOGING IN___________________________________________________________" << endl;
    cout<<endl<<"Enter user name"<<endl;
    cin>>confirm_name;
    cout<<endl<<"Enter password"<<endl;
    cin>>confirm_password;

    ifstream f("User.txt");

    while (f >> id >> passwordd)
    {


        if (id == confirm_name && passwordd == confirm_password)
        {
            matched = true;
            count=0;
            break;
        }
    }

    f.close();

    if (matched)
    {
        cout << "\nCredentials Matched!" << endl;
        usermenu();

    }




    else
    {
        count++;
        cout << "\nCredentials not Matched!" << endl;
        cout<<"Enter correct details or make new account "<<endl;


        userlogin();
    }



}





void management ::finance()
{
    int cho,total,back;
    double foodtotal,traintotal,grandtotal;

    ifstream foo ("foodtotal.txt");
    while(foo>>total)
    {
        foodtotal+=total;
    }
    ifstream tra ("traintotal.txt");
    while(tra>>total)
    {
        traintotal+=total;
    }

    ifstream gra("grandtotal.txt");
    while(gra>>total)
    {
        grandtotal+=total;
    }
    cout<<endl<<"______________________________________________________Finance_______________________________________________________ "<<endl<<endl;
    cout<<endl<<"\t\t\t\t\t|    Press 1 to see food finance      |"<<endl;
    cout<<endl<<"\t\t\t\t\t|    Press 2 to see train finance     |"<<endl;
    cout<<endl<<"\t\t\t\t\t|    Press 3 to see total finance     |"<<endl;
    cout<<"Choice  !  "<<endl;
    while(!(cin>>cho))
    {
        cout<<"Enter valid Choice !  /n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }

    switch(cho)
    {

    case 1:
    {

        cout<<"Total amount earned from food is "<<foodtotal<<" RS ";
        cout<<"Press 0 to go back "<<endl;
        cin>>back;
        if(back==0)
        {
            finance();
        }
    }
    break;
    case 2:
    {
        cout<<"Total amount earned from train is "<<traintotal<<" RS ";
        cout<<"Press 0 to go back "<<endl;
        cin>>back;
        if(back==0)
        {
            finance();

        }
    }
    break;
    case 3:
    {

        cout<<"Total amount in railway account is "<<grandtotal <<" RS ";
        cout<<"Press 0 to go back "<<endl;
        cin>>back;
        if(back==0)
        {
            finance();
        }
    }

    break;
    default:
    {

        cout<<"Invalid Selection "<<endl;
    }

    }

}






void ticket ::dis()
{
    management a;
    a.usermenu();

}





void clearConsole()
{

    system("cls");
}




void dotedlines()
{
    cout<<endl;
    cout<<"__________________________________________________________________________________________________________________"<<endl;
    cout<<endl;

}




void loginpage()
{
    system("cls");
    string loadingAnimation = "LOADING DONE.";

    cout << "\n\n\n\n\n\n\n";
    int progress = 0;


    for(int i=0; i<10; i++)
    {
        cout << "                                     " << progress  <<".....";
        cout<<"\r";
        Sleep(100);
        progress += 10;
    }
    cout << "                                 ";
    for (int i = 0; i < loadingAnimation.size(); ++i)
    {
        char c = loadingAnimation[i];
        cout << c << " ";
        Sleep(100); // Sleep for 100 milliseconds (adjust as needed)
    }

    system("cls");
}






int main()
{


    train *a;       // polymorphism
    management b;
    a=&b;

    a->display();




    return 0;
}
