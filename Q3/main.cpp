#include<iostream>
#include<fstream>
#include<vector>

void restructure(std::ifstream& in, std::ofstream& out);

int main() {
    std::ifstream in{"db.txt"};
    std::ofstream out{"dbnew.txt"};

    if (!in.is_open()) {
        std::cout << "can not open file" << std::endl;
        return -1;
    }

    restructure(in, out);
    
    in.close();
    out.close();

    return 0;
}

void restructure(std::ifstream& in, std::ofstream& out){
    char temp{};
    int yearOld{}, monthOld{}, dayOld{}, yearNew{}, monthNew{}, dayNew{};
    int hour{}, min{};
    int customerID{}, productID{};
    
    
    in >> temp >> yearNew >> temp >> monthNew >> temp >> dayNew >> 
        hour >> temp >> min >> temp >> productID >> customerID;

    int productCount{};
    std::vector<int> customerIDs{};

    customerIDs.push_back(customerID);

    bool isNewCustomer{true};
    while(!in.eof()){

        productCount = 0;
        

        out << '[' << yearNew << '-' << monthNew << '-' << dayNew << ']';

        do {
            isNewCustomer = true;
            for(size_t i = 0; i < customerIDs.size(); i++)
                if (customerIDs[i] == customerID) {
                    isNewCustomer = false;
                    break;
                }
                
            if(isNewCustomer)
                customerIDs.push_back(customerID); //saves new customer ID

            yearOld = yearNew;
            monthOld = monthNew;
            dayOld = dayNew;
            
            in >> temp >> yearNew >> temp >> monthNew >> temp >> dayNew >> 
                hour >> temp >> min >> temp >> productID >> customerID;
            
            productCount++;
            
        } while(yearOld == yearNew && monthOld == monthNew && dayOld == dayNew && !in.eof());
        
        if (in.eof()) {
            productCount++; //for last days purchases only
            isNewCustomer = true;
            for(size_t i = 0; i < customerIDs.size(); i++)
                if (customerIDs[i] == customerID) {
                    isNewCustomer = false;
                    break;
                }
            
            if (isNewCustomer) {
                customerIDs.push_back(customerID);
            }
            

        }
        out << ' ' << productCount << ' ' << customerIDs.size() << std::endl;

        customerIDs.clear();    
    }
}