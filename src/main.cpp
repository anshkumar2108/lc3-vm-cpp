#include"vm.hpp"
#include<iostream>
#include<string>
int main(int argc,char *argv[]){
    //Check if user provied the file name in terminal
    if(argc<2){
        std::cout<<"Usage: lc3-vm <program.obj>\n";
        return 1;
    }
    //Get filename from the command line arguments.
    std::string filename=argv[1];
    std::cout<<"Loading "<<filename<<"..." <<std::endl;
    
    // 3. Create the Virtual Machine .Calling the constructor

    VM vm;
    if(!vm.load_program(filename))return 1;
    std::cout<<"Starting execution...\n";
    //Starting the fetch decode execute cycle loop
    vm.run();
    std::cout<<"\n VM Execution Finished."<<std::endl;
    return 0;
}