#include<iostream>
#include<fstream>
using namespace std;

class Shopping
{
    private:
    int product_code;
    float product_price;
    float discount;
    string product_name;

    public:
    void mainmenu();
    void admin();
    void customer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void Shopping :: mainmenu()
{
    s:
    int choice;
    string username;
    string password;

    cout<<"________________________\n";
    cout<<"                        \n";
    cout<<"  Shop's Main Menu      \n";
    cout<<"                        \n";
    cout<<"________________________\n";
    cout<<"  Press 1 -- Admin     \n";
    cout<<"  Press 2 -- Customer     \n";
    cout<<"  Press 3 -- Exit     \n";
    cout<<"\n Please Enter your choice ";
    cin>>choice;

    switch(choice)
    {
        case 1:
        {
        cout<<" -- Login -- \n";
        cout<<" Enter Username : ";
        cin>>username;
        cout<<" Enter password : ";
        cin>>password;

        if( username == "sweet_shop" && password == "kesar@123")
        {
           admin(); 
        }
        else
        {
            cout<<"Invalid Password";
        }
        break;
    }
    case 2:
    {
        customer();
    }
    case 3:
    {
        exit(0);
    }
    default:
    {
        cout<< " Invalid choice";
    }
        
    }
 goto s;   // will jump to start of the function
}

void Shopping ::  admin()
{   s:
    int choice;
    cout<<"      Admin Menu  \n";
    cout<<"_____________________\n";
    cout<<" Press 1 - Add the product\n";
    cout<<" Press 2 - Modify the product\n";
    cout<<" Press 3 - Remove the product\n";
    cout<<" Press 4 - back to main menu\n";
    cout<<"\n Please Enter your choice ";
    cin>>choice;

    switch(choice)
    {
        case 1:
        add();
        break;

        case 2:
        edit();
        break;

        case 3:
        rem();
        break;

        case 4:
        mainmenu();
        break;

        default:
        cout<< " Invalid choice";

    }
    goto s;

}


void Shopping :: customer()
{
    s:
    int choice;
    cout<<" Press 1 - Buy Product\n";
    cout<<" Press 2 - Go Back\n";
    cout<<"\n Please Enter your choice ";
    cin>>choice;

    switch(choice)
    {
        case 1:
        receipt();
        break;

        case 2:
        mainmenu();
        break;

        default:
        cout<<"Invalid Selection";
    }
    goto s;
}

void Shopping :: add()
{
    s:
    fstream data;
    int c;
    int token = 0;
    float p,d;
    string n;

    cout<<" ---Add new Product---\n";
    cout<<" product code : ";
    cin>>product_code;
    cout<<" product Name : ";
    cin>>product_name;
    cout<<" product price : ";
    cin>>product_price;
    cout<<" product discount : ";
    cin>>discount;

    data.open("database.txt", ios::in);  // open a file in reading mode
    if(!data)
    {
        data.open("database.txt", ios::app| ios::out);   // append mode or write mode
        data<<" "<<product_code<<" "<<product_name<<" "<<product_price<<" "<<discount<<"\n";   //write inside a file
        data.close();
    }
    else 
    {
        data>>c>>n>>p>>d;

        while(!data.eof())  //end of file 
        {
            if(c == product_code)
            {
                token++;
            }
            data>>c>>n>>p>>d; //to access index
        }
        data.close();  
    }
    if(token==1) //duplicate data present
    {
       goto s; 
    }
    else
    {
        data.open("database.txt", ios::app| ios::out);   // append mode or write mode
        data<<" "<<product_code<<" "<<product_name<<" "<<product_price<<" "<<discount<<"\n";   //write inside a file
        data.close();
    }
    cout<<" product is added to the list";
}

void Shopping :: edit()
{
    fstream data, data1;
    int product_key;
    int token = 0;
    int code;
    float price;
    float discount;
    string name;

    cout<<"    Update the Record";
    cout<<"Enter the Product Code : ";
    cin>>product_key;

    data.open("database.txt", ios::in);
    if(!data)
    {
        cout<<"Error : File doesn't Exist";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);  // edited data will be saved in database1

        data>>product_code>>product_name>>product_price>>discount;
        while(data.eof())
        {
            if(product_key == product_code)
            {
                cout<<"Enter updated code: ";
                cin>>code;
                cout<<"Enter updated product name: ";
                cin>>name;
                cout<<"Enter updated price: ";
                cin>>price;
                cout<<"Enter updated discount: ";
                cin>>discount;
                data1<<" "<<code<<" "<<name<<" "<<price<<" "<<discount;
                cout<<"successfully modified";
                token++;
            }
            else
            {
                data1<<" "<<product_code<<" "<<product_name<<" "<<product_price<<" "<<discount<<"\n";
            }
            data>>product_code>>product_name>>product_price>>discount;
        }
        data.close();
        data1.close();

        //remove database.txt file using remove function
        //rename database1.txt as database.txt

        remove("database.txt");
        rename("database1.txt","database.txt");
        if(token==0)
        {
            cout<<"Data not found";
        }
    }   
}

void Shopping :: rem()
{
   fstream data, data1;
   int product_key;
   int token = 0;
   cout<<"  Delete Product Info ";
   cout<<" Product code : ";
   cin>>product_key;
   data.open("database.txt", ios::in);
   if(!data)
   {
    cout<<"File doesn't exist";
   } 
   else
   {
    data1.open("database1.txt", ios::app | ios::out);
    data>>product_code>>product_name>>product_price>>discount;
    while(!data.eof())
    {
        if(product_code== product_key)
        {
            cout<<"deletion successfull";
            token++;
        }
        else
        {
            data1<<" "<<product_code<<" "<<product_name<<" "<<product_price<<" "<<discount<<"\n";
        }
        data>>product_code>>product_name>>product_price>>discount;
    }
    data.close();
    data1.close();

    remove("database.txt");
    rename("database1.txt","database.txt");
    if(token==0)
    {
        cout<<"Data not found";
    }
    }
}

void Shopping:: list()
{
   fstream data, data1;
   data.open(" database.txt", ios::in);
   cout<<" ______________________________________\n";
   cout<<"ProductNo. \t\t\tProductName\t\t\tPrice\n";
   cout<<" ______________________________________\n";
   data>>product_code>>product_name>>product_price>>discount;
   while(!data.eof())
   {
    cout<<product_code<<"\t\t\t"<<product_name<<"\t\t\t"<<product_price<<"\n";
    data>>product_code>>product_name>>product_price>>discount;
   }
   data.close(); 

}

void Shopping :: receipt()
{
    fstream data;
    int arrayforcode[100], arrayforquantity[100];
    char ch;
    int count = 0;
    float discount = 0;
    float amount = 0;
    float total = 0;
    cout<<" ----- Receipt -----\n";
    data.open("database.txt",ios::in);
    if(!data)
    {
        cout<<"Error : Data not found";
    }
    else
    {
        data.close();
        list();
        cout<<"_______________________\n";
        cout<<"    Enter your orde    \n";
        cout<<"_______________________\n";

        do
        {
            s:
            cout<<" Product code :";
            cin>>arrayforcode[count];
            cout<<"Quantity    :";
            cin>>arrayforquantity[count];
            //to check duplictae product in the list
            for(int i = 0; i < count; i++)
            {
                if(arrayforcode[count]==arrayforcode[i])
                {
                    cout<<" You entered Product Twice\nPlease Try Again";
                    goto s;
                }
            }
            count++;
            cout<<" Do you want to continue? Y or N";
            cin>>ch;
        }while(ch == 'y'); 
         
         cout<<"\n\n________RECEIPT___________\n";
         cout<<"\nProductNo\t\tProductName \t\tProductquantity \t\t Price \t\tAmount \t\tAfter discount\n";
         for(int i = 0; i<count ; i++)
         {
            data.open("database.txt", ios::in);
            data>>product_code>>product_name>>product_price>>discount;
            while(!data.eof())
            {
                if(product_code== arrayforcode[i])
                {
                 amount = product_price * arrayforquantity[i];
                 discount = amount - (amount * discount/100);
                 total = total * discount;
                 cout<<"\n"<<product_code<<"\t\t"<<product_name<<"\t\t"<<arrayforquantity[i]<<"\t\t"<<product_price<<"\t\t"<<amount<<"\t\t"<<discount;
                 }
                 data>>product_code>>product_name>>product_price>>discount;
                 }
        data.close();
    }
    cout<<"_________________________________________\n";
    cout<<"\t\t\t Total Amount: "<<total;
}
}

int main()
{
    Shopping s;
    s.mainmenu();
    return 0;
}