#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Commodity;
class Store;
class InputHandler;
class Sound;
class Smartphone;
class Laptop;


class InputHandler {
public:
    /*
     * The function is used to read a full line into a string variable.
     * It read the redundant '\n' character to prevent the problem of getline function.
     * There is an overload version which can read from the specified data stream.
     * INPUT: None, or fstream
     * RETURN: Full line input by user
     * */
    static string readWholeLine() {
        string input;
        cin.get();
        getline(cin, input);
        return input;
    }

    static string readWholeLine(fstream& file) {
        string input;
        file.get();
        getline(file, input);
        return input;
    }

    /*
     * This function is used to configure whether the input string is a number
     * INPUT: A string
     * RETURN: Bool. True if input string is a number, otherwise false.
     */
    static bool isNum(string& str) {
        for (int i = 0; i < str.size(); i++) {
            if (!isdigit(str[i])) {
                return false;
            }
        }
        return true;
    }

    /*
     * Check the input string is a valid number.
     * First check the input is a number or not, then identify whether it is bigger than 0
     * INPUT: string
     * RETURN: bool
     */
    static bool isValidNum(string& str) {
        if (!isNum(str) || (isNum(str) && stoi(str) <= 0))
            return false;
        return true;
    }

    /*
     * Get a number from the user. This function will check the input validation.
     * INPUT: none
     * OUTPUT: integer, the input number
     */
    static int numberInput() {
        string input;
        cin >> input;
        while (!isValidNum(input)) {
            cout << "Please input again your input is NOT an integer or is lower than or equal to 0:" << endl;
            cin >> input;
        }
        return stoi(input);
    }

    /*
     * This function is used in function getInput. Check the input range is inside the specified range
     */
    static int inputCheck(string input, int maxChoiceLen, bool noZero) {
        // Change input to the general integer
        int choice = 0;
        for (int i = 0; i < input.size(); i++) {
            if (isdigit(input[i])) {
                choice = choice * 10 + (input[i] - '0');
            } else {
                return -1;
            }
        }

        if (noZero) {
            return (choice <= maxChoiceLen && choice > 0) ? choice : -1;
        } else {
            return (choice <= maxChoiceLen && choice >= 0) ? choice : -1;
        }
    }

    /*
     * Get the input from the user, and limit the input between the range [0, maxChoiceLen].
     * If noZero is signaled. Then the range will be [1, maxChoiceLen]
     * INPUT: integer, bool(option)
     * OUTPUT: integer, the choice number
     */
    static int getInput(int maxChoiceLen, bool noZero = false) {
        string input;
        cin >> input;
        int choice = inputCheck(input, maxChoiceLen, noZero);
        while (choice == -1) {
            cout << "your input is wrong, please input again:" << endl;
            cin >> input;
            choice = inputCheck(input, maxChoiceLen, noZero);
        }

        return choice;
    }
};

/*
 * Commodity is about an item which the user can buy and the manager can add or delete.
 * ATTRIBUTE:
 *  price: The price of the commodity, an integer.
 *  description: The text which describe the commodity detail, a string.
 *  commodityName: The name of the commodity, a string.
 */
class Commodity {
protected:
    int price;
    string description;
    string commodityName;

public:
    ~Commodity() = default;
    Commodity() {
        price = 0;
        description = "";
        commodityName = "";
    }

    Commodity(int price, string commodityName, string description) {
        this->price = price;
        this->commodityName = commodityName;
        this->description = description;
    }

    /*
     * This method will show the full information of the commodity to user interface.
     * There is a overloading version, with an argument amount which will output the information with the amount
     * INPUT: None, or an integer specify the amount of this commodity
     * RETURN: None
     */
    virtual void detail() {
        cout << commodityName << endl;
        cout << "price: " << price << endl;
        cout << "description: " << description << endl;
        cout << "----------------------------" << endl;
    }

    virtual void detail(int amount) {
        cout << commodityName << endl;
        cout << "price: " << price << endl;
        cout << "description: " << description << endl;
        cout << "x " << amount << endl;
        cout << "----------------------------" << endl;
    }

    /*
     * Use this function to get the information data from the user, this will init the object.
     * INPUT: none
     * OUTPUT: none
     */
    virtual void userSpecifiedCommodity() {
        cout << "Please input the commodity name:" << endl;
        commodityName = InputHandler::readWholeLine();
        cout << "Please input the commodity price:" << endl;
        price = InputHandler::numberInput();
        cout << "Please input the detail of the commodity:" << endl;
        description = InputHandler::readWholeLine();
    }

    /*
     * Save and load function is used to write the data to the file or read the data from the file.
     * According to the input parameter fstream, they complete the I/O on the specified file.
     * There have no definition of those method, because it is used to be override in the derived class.
     * INPUT: fstream
     * OUTPUT: none
     */
    virtual void save(fstream& file) {
        file  << commodityName << '\n' << price << '\n' << description << '\n';
    }

    virtual void load(fstream& file) {
        commodityName = InputHandler::readWholeLine(file);
        file >>price;
        description = InputHandler::readWholeLine(file);
    }

    /*
     * The getter function of commodityName
     */
    virtual string getName() {
        return commodityName;
    }

    /*
     * The getter function of price
     */
    virtual int getPrice() {
        return price;
    }
};



/*
 * [YOU SHOULD FINISH THREE TYPES OF DERIVED COMMODITY CLASS HERE]
 * Please try your best to complete the definition of three classes.
 * Use the knowledge you learned from this course.
 * You should follow the OOP concept.
 */
class Sound : public Commodity{
private:
    int price;
    string description;
    string commodityName;
    int lowest_Frequency_Response;
    int highest_Frequency_Response;
    int Sensitivity;
    int Impedance;
public:
    ~Sound() =default;
    Sound(){
        price = 0;
        commodityName = "";
        lowest_Frequency_Response = 0;
        highest_Frequency_Response = 0;
        Sensitivity = 0;
        Impedance = 0;
        description = "";
    }

    void detail() override{
        cout << "* " << commodityName << " *" << endl;
        cout << "price: " << price << "  dollars" <<endl;
        cout << "Lowest Frequency Response: " <<lowest_Frequency_Response << "  Hz" <<endl;
        cout << "Highest Frequency Response: " <<highest_Frequency_Response << "  kHz" <<endl;
        cout << "Sensitivity: " <<Sensitivity<< "  dB" << endl;
        cout << "Impedance: " <<Impedance<< "  Ohm" <<endl;
        cout << "description: " << description << endl;
        cout << "----------------------------" << endl;
    }

    void detail(int amount) override{
        cout << "* " << commodityName << " *" << endl;
        cout << "price: " << price << "  dollars" <<endl;
        cout << "Lowest Frequency Response: " <<lowest_Frequency_Response << "  Hz" <<endl;
        cout << "Highest Frequency Response: " <<highest_Frequency_Response << "  kHz" <<endl;
        cout << "Sensitivity: " <<Sensitivity<< "  dB" << endl;
        cout << "Impedance: " <<Impedance<< "  Ohm" <<endl;
        cout << "description: " << description << endl;
        cout << "x " << amount << endl;
        cout << "----------------------------" << endl;
    }

    void userSpecifiedCommodity() override{
        cout << "Please input the commodity name:" << endl;
        commodityName = InputHandler::readWholeLine();
        cout << "Please input the commodity price:" << endl;
        price = InputHandler::numberInput();
        cout<<"Please intput the lowest frequency response"<<endl;
        lowest_Frequency_Response = InputHandler::numberInput();
        cout<<"Please intput the highest frequency response"<<endl;
        highest_Frequency_Response = InputHandler::numberInput();
        cout<<"Please input the Sensitivity"<<endl;
        Sensitivity = InputHandler::numberInput();
        cout<<"Please input the Impedance"<<endl;
        Impedance = InputHandler::numberInput();
        cout<<"Please input the Description"<<endl;
        description = InputHandler::readWholeLine();
    }
    string getName() override{
        return commodityName;
    }

    int getPrice() override{
        return price;
    }

    void save(fstream& file) override{
        file << price << '\n' << commodityName <<'\n' <<lowest_Frequency_Response;
        file << '\n' << highest_Frequency_Response << '\n' ;
        file << Sensitivity <<'\n' << Impedance << '\n' << description << '\n';
    }

    void load(fstream& file) override{
        file >> price ;
        commodityName = InputHandler::readWholeLine(file);
        file >> lowest_Frequency_Response >> highest_Frequency_Response ;
        file >> Sensitivity >> Impedance;
        description = InputHandler::readWholeLine(file);

    }
};

class Smartphone :public Commodity{
private:
    int price;
    string description;
    string commodityName;
    int Screen_Size;
    string CellularandWireless;
    int Camera;
    string chip;
    int weight;
    int Vedeo_playback;
public:
    ~Smartphone() = default;

    Smartphone(){
        price = 0;
        commodityName = "";
        description = "";
        Screen_Size = 0;
        CellularandWireless = "";
        Camera = 0;
        chip = "";
        weight = 0;
        Vedeo_playback = 0;
    }

    string getName()override {
        return commodityName;
    }

    int getPrice() override{
        return price;
    }

    void detail()override {
        cout << "* " << commodityName << " *" << endl;
        cout << "price: " << price << "  dollars" <<endl;
        cout << "Screen Size: " << Screen_Size << "  inch" <<endl;
        cout << "Cellular and Wireless: " << CellularandWireless <<endl;
        cout << "Camera: " << Camera << "  pixel" << endl;
        cout << "chip: " << chip <<endl;
        cout << "weight: " << weight << "  grams" <<endl;
        cout << "Vedeo playback time: " << Vedeo_playback << "  hours" <<endl;
        cout << "description: " << description << endl;
        cout << "----------------------------" << endl;
    }

    void detail(int amount) override{
        cout << "* " << commodityName << " *" << endl;
        cout << "price: " << price << "  dollars" <<endl;
        cout << "Screen Size: " << Screen_Size << "  inch" <<endl;
        cout << "Cellular and Wireless: " << CellularandWireless <<endl;
        cout << "Camera: " << Camera << "  pixel" << endl;
        cout << "chip: " << chip <<endl;
        cout << "weight: " << weight << "  grams" <<endl;
        cout << "Vedeo playback time: " << Vedeo_playback << "  hours" <<endl;
        cout << "description: " << description << endl;
        cout << "x " << amount << endl;
        cout << "----------------------------" << endl;
    }

    void userSpecifiedCommodity() override{
        cout << "Please input the commodity name:" << endl;
        commodityName = InputHandler::readWholeLine();
        cout << "Please input the commodity price:" << endl;
        price = InputHandler::numberInput();
        cout<<"Please intput the Screen Size"<<endl;
        Screen_Size = InputHandler::numberInput();
        cout<<"Please intput the Cellular and Wireless"<<endl;
        CellularandWireless = InputHandler::readWholeLine();
        cout<<"Please input the Camera(pixel)"<<endl;
        Camera = InputHandler::numberInput();
        cout<<"Please input the Chip"<<endl;
        chip= InputHandler::readWholeLine();
        cout<<"Please input the Weight"<<endl;
        weight = InputHandler::numberInput();
        cout<<"Please input the Vedeo playback time"<<endl;
        Vedeo_playback = InputHandler::numberInput();
        cout << "Please input the detail of the commodity:" << endl;
        description = InputHandler::readWholeLine();
    }

    void save(fstream& file) override{
        file  << price << '\n' << commodityName << '\n';
        file << Screen_Size << '\n'  << CellularandWireless;
        file << '\n' << Camera << '\n' << chip << '\n' << weight << '\n' << Vedeo_playback << '\n' << description << '\n';
    }

    void load(fstream& file) override{
        file >> price;
        commodityName = InputHandler::readWholeLine(file);
        file >> Screen_Size ;
        CellularandWireless = InputHandler::readWholeLine(file);
        file >> Camera;
        chip = InputHandler::readWholeLine(file);
        file >> weight >> Vedeo_playback;
        description = InputHandler::readWholeLine(file);

    }
};

class Laptop:public Commodity{
private:
    int price;
    string description;
    string commodityName;
    int Screen_Size;
    string OStype;
    string CPUtype;
    string GPUtype;
    int Disksize;
    int memorysize;
    int RGB;
public:
    ~Laptop() = default;

    Laptop(){
        price = 0;
        commodityName = "";
        description = "";
        Screen_Size = 0;
        OStype = "";
        CPUtype = "";
        GPUtype = "";
        Disksize = 0;
        memorysize = 0;
        RGB = 0;
    }

    string getName() override{
        return commodityName;
    }

    int getPrice() override{
        return price;
    }

    void detail() override{
        cout << "* " << commodityName << " *" << endl;
        cout << "price: " << price <<"  dollars"<< endl;
        cout << "Screen Size: " << Screen_Size << "  inch" <<endl;
        cout << "Operatin System: " <<OStype<<endl;
        cout << "CPU: " <<CPUtype<<endl;
        cout << "GPU: " <<GPUtype<<endl;
        cout << "Max Memory Size: " <<memorysize << "  GB" <<endl;
        cout << "Disk Size: " << Disksize << "  GB" <<endl;
        cout << "Does it have RGB light" ;
        if(RGB == 1)cout << "  yes" << endl;
        else if(RGB == 2)cout <<"  no" << endl;
        cout << "description: " << description << endl;
        cout << "----------------------------" << endl;
    }

    void detail(int amount) override{
        cout << "* " << commodityName << " *" << endl;
        cout << "price: " << price <<"  dollars"<< endl;
        cout << "Screen Size: " << Screen_Size << "  inch" <<endl;
        cout << "Operatin System: " <<OStype<<endl;
        cout << "CPU: " <<CPUtype<<endl;
        cout << "GPU: " <<GPUtype<<endl;
        cout << "Max Memory Size: " <<memorysize << "  GB" <<endl;
        cout << "Disk Size: " << Disksize << "  GB" <<endl;
        cout << "Does it have RGB light" ;
        if(RGB == 1)cout << "  yes" << endl;
        else if(RGB == 2)cout <<"  no" << endl;
        cout << "description: " << description << endl;
        cout << "x " << amount << endl;
        cout << "----------------------------" << endl;
    }

    void userSpecifiedCommodity()override {
        cout << "Please input the commodity name:" << endl;
        commodityName = InputHandler::readWholeLine();
        cout << "Please input the commodity price:" << endl;
        price = InputHandler::numberInput();
        cout<<"Please intput the Operating System"<<endl;
        OStype = InputHandler::readWholeLine();
        cout<<"Please intput the Screen Size"<<endl;
        Screen_Size = InputHandler::numberInput();
        cout<<"Please input the CPU"<<endl;
        CPUtype = InputHandler::readWholeLine();
        cout<<"Please input the max Memory Size"<<endl;
        memorysize = InputHandler::numberInput();
        cout<<"Please input the Disk Size"<<endl;
        Disksize = InputHandler::numberInput();
        cout<<"Please input the GPU"<<endl;
        GPUtype= InputHandler::readWholeLine();
        cout<< "Is this Laptop have RGB light?  1.yes/2.no " << endl;
        RGB = InputHandler::getInput(2);
        cout << "Please input the detail of the commodity:" << endl;
        description = InputHandler::readWholeLine();

    }

    void save(fstream& file) override{
        file << price << '\n' << commodityName ;
        file << '\n'  <<  Screen_Size << '\n' << OStype ;
        file << '\n'  << memorysize << '\n' << CPUtype   << '\n' << RGB << '\n' << GPUtype<< '\n' << Disksize << '\n' << description << '\n';
    }

    void load(fstream& file) override{
        file >> price ;
        commodityName = InputHandler::readWholeLine(file);
        file >> Screen_Size;
        OStype = InputHandler::readWholeLine(file);
        file >> memorysize;
        CPUtype = InputHandler::readWholeLine(file);
        file >> RGB;
        GPUtype = InputHandler::readWholeLine(file);
        file >> Disksize;
        description = InputHandler::readWholeLine(file);
    }

};



/*
 * [YOU NEED TO FINISH THIS CLASS]
 * This is a list storing the existing commodity in the store.
 * There are some method which can modify the content.
 * You may use any data structure to complete this class.
 */
class CommodityList {
private:
    vector<Commodity*> commodityList[3];
    vector<Commodity*>  ::iterator iter;

public:

    CommodityList() {
        iter = commodityList[0].begin();
    }

    /*
     * Print the full information of the commodities inside the list
     * You must call Commodity.detail() to show the commodity information.
     * INPUT: None
     * RETURN: None
     */
    void showCommoditiesDetail() {
        int time = 0;
        for(int i = 0 ; i < 3 ; i++ ){
            if(!commodityList[i].empty() &&  i == 0)cout << "Sound:" <<endl;
            if(!commodityList[i].empty() && i == 1)cout << "Smartphone:" << endl;
            if(!commodityList[i].empty() && i == 2)cout << "Laptop:" <<endl;
            iter = commodityList[i].begin();
            for(int j=0 ; (iter+j) != commodityList[i].end() ; j++){
                if(commodityList[i].empty())break;
                time++;
                cout << time << " ." <<endl;
                (*(iter+j))->detail();
            }
        }
    }

    /*
     * Print only the commodity name of the commodities inside the list
     * You don't need to use Commodity.detail() here, just call the Commodity.getName() function is ok
     * INPUT: None
     * RETURN: None
     */
    void showCommoditiesName() {
        int time = 0;
        for(int i = 0 ; i < 3 ; i++ ){
            if(!commodityList[i].empty() &&  i == 0)cout << "Sound:" <<endl;
            if(!commodityList[i].empty() && i == 1)cout << "Smartphone:" << endl;
            if(!commodityList[i].empty() && i == 2)cout << "Laptop:" <<endl;
            iter = commodityList[i].begin();
            for(int j=0 ; (iter+j) != commodityList[i].end() ; j++){
                if(commodityList[i].empty())break;
                time++;
                cout << time << " ." <<endl;
                cout << (*(iter+j))->getName() << endl;
            }
        }
    }

    /*
     * Check whether the list is empty or not
     * INPUT: None
     * RETURN: Bool. True if the list is empty, otherwise false
     */
    bool empty() {
        if(commodityList->empty())return true;
        else return false;
    }

    /*
     * Return the size(or length) of the list
     * INPUT: None
     * RETURN: Integer. List size
     */
    int size() {
        int time = 0;
        for(int i = 0 ; i < 3 ; i++ ){
            time = time + commodityList[i].size();
        }
        return time;
    }


    int Size_index(int index) {
        if(index == 0) return commodityList[0].size();
        if(index == 1) return commodityList[1].size();
        if(index == 2) return commodityList[2].size();
        return 0;
    }

    /*
     * Return a commodity object at specified position
     * INPUT: Integer. The index of that commodity
     * RETURN: Commodity. The wanted commodity object
     */
    Commodity* get(int index) {
        int time = 0;
        for(int i = 0 ; i < 3 ; i++ ){
            iter = commodityList[i].begin();
            for(int j=0 ; j < commodityList[i].size() ; j++){
                if(time == index){
                    return (*(iter+j));
                }
                time++;
            }
        }
        return nullptr;
    }

    int getIndex(int index){
        int time = 0;
        for(int i = 0 ; i < 3 ; i++ ){
            iter = commodityList[i].begin();
            for(int j=0 ; j < commodityList[i].size() ; j++){
                if(time == index)   return i;
                time++;
            }
        }
        return 0;
    }

    /*
     * Push a new commodity object into the list
     * INPUT: Commodity. The object need to be pushed
     * RETURN: None
     */
    void add(Commodity* newCommodity, int index) {
        commodityList[index].push_back(newCommodity);
    }

    /*
     * Check the input commodity object is existing inside the list
     * If the commodity name is the same, we take those objects the same object
     * INPUT: Commodity. The object need to be checked
     * OUTPUT: Bool. True if the object existing, otherwise false
     */
    bool isExist(Commodity* commodity) {
        for(int i = 0 ; i < 3 ; i++ ){
            iter = commodityList[i].begin();
            for(int j=0 ; j < commodityList[i].size() ; j++){
                if(commodity->getName() == (*(iter+j) )->getName() )return true;
            }
        }
        return false;
    }

    /*
     * Remove an object specified by the position
     * INPUT: Integer. The position of the object which need to be removed
     * OUTPUT: None
     */
    void remove(int index) {
        int time = 0;
        for(int i = 0 ; i < 3 ; i++ ){
            iter = commodityList[i].begin();
            for(int j=0 ; (iter+j) != commodityList[i].end() ; j++){
                if(time == index) {
                    commodityList[i].erase(iter+j);
                    time++;
                    break;
                }
                time++;
            }
        }
    }

    void save() {
        fstream FileOutput ;
        for(int i = 0 ; i < 3 ; i++){
            iter = commodityList[i].begin();
            if( i == 0 )FileOutput.open("SoundCommodity.txt" , ios::out);
            if( i == 1 )FileOutput.open("SmartphoneCommodity.txt" , ios::out);
            if( i == 2 )FileOutput.open("LaptopCommodity.txt" , ios::out);
            while(iter != commodityList[i].end()){
                (*iter)->save(FileOutput);
                iter++;
            }
            FileOutput.close();
        }
        cout << "save success\n";

    }
};

/*
 * [YOU NEED TO FINISH THIS CLASS]
 * The shopping cart is used to store the commodities user wanted.
 * Because the same name represents the same object, if there is a commodity which have more than one object inside
 * the cart, then it will be store as the same object and the cart must keep the amount of the object.
 * You may use any data structure to complete this class.
 */
class ShoppingCart {
private:
    vector<Commodity*> ShoppingCart_List[3];
    vector<int> Quantity[3];
    vector<Commodity*> ::iterator itershop;
    vector<int> ::iterator iterquan;
public:
    ~ShoppingCart() = default;
    ShoppingCart()  {
        iterquan = Quantity[0].begin();
        itershop = ShoppingCart_List[0].begin();
    }
    /*
     * Push an commodity object into the cart.
     * Be careful that if the input object is existing in the list, then keep the amount of that object rather than
     * actually push the object into the cart.
     * INPUT: Commodity. The object need to be pushed.
     * OUTPUT: None.
     */
    void BuildShoppingCart(int first , int second ,int third){
        ShoppingCart_List[0].resize(first);
        ShoppingCart_List[1].resize(second);
        ShoppingCart_List[2].resize(third);
    }

    void push(Commodity* entry , int index) {

        if(index == 0){
            itershop =  ShoppingCart_List[0].begin() ;
            iterquan = Quantity[0].begin();
            for(int i=0 ;(itershop+i) != ShoppingCart_List[0].end() ; i++) {
                if ( *(itershop+i) == NULL) {
                    ShoppingCart_List[0].insert((itershop+i), entry);
                    Quantity[0].insert((iterquan+i), 1);
                    break;
                }
                if ( (*(itershop+i))->getName() == entry->getName()) {
                    Quantity[0].insert((iterquan+i), (*(iterquan+i) + 1) );
                    break;
                }
            }
        }
        if(index == 1){
            iterquan = Quantity[1].begin();
            itershop =  ShoppingCart_List[1].begin() ;
            for(int i=0 ; (itershop+i) != ShoppingCart_List[1].end() ; i++) {
                if( *(itershop+i) == NULL )  {
                    ShoppingCart_List[1].insert( (itershop+i) , entry );
                    Quantity[1].insert((iterquan+i) , 1);
                    break;
                }
                if( (*(itershop+i))->getName() == entry->getName() ) {
                    Quantity[1].insert( (iterquan+i) , (*(iterquan+i)+1) );
                    break;
                }
            }
        }
        if(index == 2){
            itershop =  ShoppingCart_List[2].begin() ;
            iterquan = Quantity[2].begin();
            for(int i=0 ; (itershop+i) != ShoppingCart_List[2].end() ; i++) {
                if( *(itershop+i) == NULL ) {
                    ShoppingCart_List[2].insert( (itershop+i) , entry );
                    Quantity[2].insert((iterquan+i) , 1);
                    break;
                }
                if( (*(itershop+i) )->getName() == entry->getName() ) {
                    Quantity[2].insert( (iterquan+i) , (*(iterquan+i))+1);
                    break;
                }
            }
        }
    }

    /*
     * Show the content of the cart to user interface.
     * INPUT: None.
     * OUTPUT: None.
     */
    void showCart() {
        int time = 0;
        for(int i = 0 ; i < 3 ; i++ ){
            if(!ShoppingCart_List[i].empty() &&  i == 0)cout << "Sound:" <<endl;
            if(!ShoppingCart_List[i].empty() && i == 1)cout << "Smartphone:" << endl;
            if(!ShoppingCart_List[i].empty() && i == 2)cout << "Laptop:" <<endl;
            iterquan = Quantity[i].begin();
            for( itershop = ShoppingCart_List[i].begin() ; itershop != ShoppingCart_List[i].end() ; itershop++){
                if( *itershop == NULL )break;
                time++;
                cout << time <<"." <<endl;
                (*itershop)->detail(*iterquan);
                iterquan++;
            }
        }
    }

    /*
     * Return the cart size. (The same object must be seen as one entry)
     * INPUT: None.
     * OUTPUT: Integer. The cart size.
     */
    int size() {
        int Size = 0;
        for(int i=0 ; i<3 ; i++){
            Size = Size + ShoppingCart_List[i].size();
        }
        return Size;
    }

    /*
     * Remove an entry from the cart. Don't care about the amount of the commodity, just remove it.
     * INPUT: The order of the entry.
     * OUTPUT: None.
     */
    void remove(int index) {
        int time = 0;
        for(int i=0 ;i<3 ; i++){
            iterquan = Quantity[i].begin();
            itershop = ShoppingCart_List[i].begin();
            while(  itershop != ShoppingCart_List[i].end() ){
                if( (*itershop) == NULL )break;
                if( time == index ){
                    ShoppingCart_List[i].erase(itershop);
                    Quantity[i].erase(iterquan);
                    time++;
                    break;
                }
                itershop++;
                iterquan++;
                time++;
            }
        }
    }

    /*
     * Check the total amount of price for the user.
     * Remember to clear the list after checkout.
     * INPUT: None.
     * OUTPUT: Integer. The total price.
     */
    int checkOut() {
        int total=0;
        for(int i=0 ;i<3 ;i++){
            itershop = ShoppingCart_List[i].begin();
            iterquan = Quantity[i].begin();
            for(int j=0 ; (itershop+j) != ShoppingCart_List[i].end() ;j++){
                if( *(itershop+j) == NULL)break;
                total = total + ((*(itershop+j) )->getPrice())*(*(iterquan+j) );
            }
        }
        return total;
    }

    /*
     * Check if the cart have nothing inside.
     * INPUT: None.
     * OUTPUT: Bool. True if the cart is empty, otherwise false.
     */
    bool empty() {
        if(ShoppingCart_List->empty())return true;
        else return false;
    }
};

/*
 * [DO NOT MODIFY ANY CODE HERE]
 * The Store class manage the flow of control, and the interface showing to the user.
 * Store use status to choose the interface to show. As the result, status control is very important here.
 * If you can understand the code here, you will have great work on the above two class.
 * The detail of Store is in the README
 */
class Store {
private:
    enum UMode {USER, MANAGER} userStatus;
    enum SMode {OPENING, DECIDING, SHOPPING, CART_CHECKING, CHECK_OUT, MANAGING, CLOSE} storeStatus;
    CommodityList commodityList;
    ShoppingCart cart;



    void load(){
        Commodity * fileinput;
        fstream Fileinput ;
        int index ;
        for( int i = 0 ; i < 3 ; i++){
            if(i == 0){
                index = 0;
                Fileinput.open("SoundCommodity.txt" , ios::in);
                while(!Fileinput.eof()){
                    fileinput = new Sound();
                    fileinput->load(Fileinput);
                    if(!Fileinput.fail()){
                        commodityList.add(fileinput,index);
                    }
                }
            }
            if(i == 1){
                index = 1;
                Fileinput.open("SmartphoneCommodity.txt" , ios::in);
                while(!Fileinput.eof()){
                    fileinput = new Smartphone();
                    fileinput->load(Fileinput);
                    if(!Fileinput.fail()){
                        commodityList.add(fileinput,index);
                    }
                }
            }
            if(i == 2){
                index = 2;
                Fileinput.open("LaptopCommodity.txt" , ios::in);
                while(!Fileinput.eof()){
                    fileinput = new Laptop();
                    fileinput->load(Fileinput);
                    if(!Fileinput.fail()){
                        commodityList.add(fileinput,index);
                    }
                }
            }
            Fileinput.close();
        }
    }

    void commodityInput() {
        Commodity* commodityinput;
        cout << "Which type of commodity you want to add?" << endl;
        cout << "1. Sound, 2. Smartphone, 3. Laptop\n";
        int choice = InputHandler::getInput(3);
        if(choice == 1){
            commodityinput = new Sound();
            commodityinput ->userSpecifiedCommodity();
        }
        if(choice == 2){
            commodityinput = new Smartphone();
            commodityinput->userSpecifiedCommodity();
        }
        if(choice == 3){
            commodityinput = new Laptop();
            commodityinput->userSpecifiedCommodity();
        }
        if( commodityList.isExist(commodityinput) ){
            cout << "[WARNING] " << commodityinput->getName() << " is exist in the store. If you want to edit it, please delete it first" << endl;
        } else  commodityList.add(commodityinput , choice-1);

        /*
         * You should finish this method, because you need to identify the type of commodity, and instantiate a
         * corresponding derived commodity class here.
         */

    }

    void deleteCommodity() {
        if (commodityList.empty()) {
            cout << "No commodity inside the store" << endl;
            return;
        }

        int choice;
        cout << "There are existing commodity in our store:" << endl;
        commodityList.showCommoditiesName();
        cout << "Or type 0 to regret" << endl
             << "Which one do you want to delete?" << endl;

        choice = InputHandler::getInput(commodityList.size());

        if (choice != 0) {
            commodityList.remove(choice - 1);
        }
    }

    void showCommodity() {
        if (commodityList.empty()) {
            cout << "No commodity inside the store" << endl;
            return;
        }

        cout << "Here are all commodity in our store:" << endl;
        commodityList.showCommoditiesDetail();
        cout << endl;
    }

    void askMode() {
        string input;

        cout << "Are you a general user or a manager?" << endl
             << "1. general user, 2. manager" << endl
             << "Or type 0 to close the store" << endl;

        int choice = InputHandler::getInput(2);

        userStatus = (choice == 2) ? UMode::MANAGER : UMode::USER;

        if (choice == 0) {
            storeStatus = SMode::CLOSE;
        } else if (userStatus == UMode::USER) {
            storeStatus = SMode::DECIDING;
        } else if (userStatus == UMode::MANAGER) {
            storeStatus = SMode::MANAGING;
        }
    }

    void decideService() {
        string input;

        cout << "Below are our service:" << endl
             << "1. Buy the commodity you want" << endl
             << "2. Check your shopping cart" << endl
             << "3. Check out" << endl
             << "Or type 0 to exit user mode" << endl
             << "You may choose what you need:" << endl;

        int choice = InputHandler::getInput(3);

        if (choice == 1) {
            cart.BuildShoppingCart(commodityList.Size_index(0) , commodityList.Size_index(1) , commodityList.Size_index(2) );
            storeStatus = SMode::SHOPPING;
        } else if (choice == 2) {
            storeStatus = SMode::CART_CHECKING;
        } else if (choice == 3) {
            storeStatus = SMode::CHECK_OUT;
        } else if (choice == 0) {
            storeStatus = SMode::OPENING;
        }
    }

    void chooseCommodity() {
        string input;
        showCommodity();
        cout << "Or input 0 to exit shopping" << endl;

        int choice = InputHandler::getInput(commodityList.size());

        // Push the commodity into shopping cart here
        if (choice == 0) {
            storeStatus = SMode::DECIDING;
        } else {
            // May be some bug here, test later
            cout<<"check2\n";
            cart.push(commodityList.get(choice - 1) , commodityList.getIndex(choice-1));
        }
    }

    void showCart() {
        if (cart.empty()) {
            cout << "Your shopping cart is empty" << endl;
            storeStatus = SMode::DECIDING;
            return;
        }

        int choice;
        do {
            cout << "Here is the current cart content:" << endl;
            cart.showCart();
            cout<<"CHECK\n";
            cout << "Do you want to delete the entry from the cart?" << endl
                 << "1. yes, 2. no" << endl;

            choice = InputHandler::getInput(2, true);

            if (choice == 1) {
                cout << "Which one do you want to delete(type the commodity index)?" << endl
                     << "Or type 0 to regret" << endl;
                int index = InputHandler::getInput(cart.size());
                // **
                if (index == 0) {
                    break;
                }
                cart.remove(index - 1);
            }
        } while (choice == 1);

        cout << "Do you want to checkout?" << endl
             << "1. yes, 2. No, I want to buy more" << endl;
        choice = InputHandler::getInput(2, true);
        if (choice == 1) {
            storeStatus = SMode::CHECK_OUT;
        } else {
            storeStatus = SMode::DECIDING;
        }
    }

    void checkOut() {
        if (cart.empty()) {
            cout<<"CHECK\n";
            cout << "Your shopping cart is empty, nothing can checkout" << endl;
        } else {
            cout << "Here is the current cart content:" << endl;
            cart.showCart();
            cout << "Are you sure you want to buy all of them?" << endl
                 << "1. Yes, sure, 2. No, I want to buy more" << endl;

            int choice = InputHandler::getInput(2, true);

            if (choice == 1) {
                int amount = cart.checkOut();
                cout << "Total Amount: " << amount << endl;
                cout << "Thank you for your coming!" << endl;
                cout << "------------------------------" << endl << endl;
            }
        }

        storeStatus = SMode::DECIDING;
    }

    void managerInterface() {
        cout << "Here are some manager services you can use:" << endl
             << "1. Add new commodity" << endl
             << "2. Delete commodity from the commodity list" << endl
             << "3. Show all existing commodity" << endl
             << "Or type 0 to exit manager mode" << endl
             << "Which action do you need?" << endl;

        int choice = InputHandler::getInput(3);

        if (choice == 1) {
            commodityInput();
        } else if (choice == 2) {
            deleteCommodity();
        } else if (choice == 3) {
            showCommodity();
        } else if (choice == 0) {
            storeStatus = SMode::OPENING;
        }
    }

    void userInterface() {
        if (storeStatus == SMode::OPENING) {
            askMode();
        } else if (storeStatus == SMode::DECIDING) {
            decideService();
        } else if (storeStatus == SMode::SHOPPING) {
            chooseCommodity();
        } else if (storeStatus == SMode::CART_CHECKING) {
            showCart();
        } else if (storeStatus == SMode::CHECK_OUT) {
            checkOut();
        } else if (storeStatus == SMode::MANAGING) {
            managerInterface();
        } else if (storeStatus == SMode::CLOSE) {
            return;
        }
    }

public:
    Store() {
        userStatus = UMode::USER;
        storeStatus = SMode::CLOSE;
    }

    void open() {
        storeStatus = SMode::OPENING;
        load();
        while (storeStatus != SMode::CLOSE) {
            userInterface();
        }
        commodityList.save();
    }
};


int main() {
    Store csStore;
    csStore.open();
    return 0;
}
